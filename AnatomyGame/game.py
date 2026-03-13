#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import math
import sys
from pathlib import Path

LEVEL_NAMES = {
    "anatomy": "TESTES",
    "endocrine": "MAJOR ENDOCRINE GLANDS",
    "pituitary": "PITUITARY GLAND",
    "thyroid": "THYROID GLAND",
    "thyroid2": "THYROID GLAND 2",
    "parathyroid": "PARATHYROID GLANDS",
    "adrenal": "ADRENAL GLANDS",
}

try:
    from PIL import Image
except ImportError:
    Image = None


def get_available_levels(levels_dir: Path = Path("levels")) -> list[tuple[str, Path]]:
    """Return list of (display_name, path) for playable levels."""
    result = []
    if not levels_dir.is_dir():
        return result
    for d in sorted(levels_dir.iterdir()):
        if not d.is_dir():
            continue
        if (d / "level.json").exists():
            try:
                load_level(d)
            except (FileNotFoundError, ValueError):
                continue
            name = LEVEL_NAMES.get(d.name, d.name.replace("_", " ").title())
            result.append((name, d))
    return result


def load_level(level_dir: Path) -> tuple[Path, list[dict]]:
    """Load level.json and return (image_path, labels)."""
    json_path = level_dir / "level.json"
    if not json_path.exists():
        raise FileNotFoundError(f"No level.json in {level_dir}")
    with open(json_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    image_path = level_dir / data["image"]
    if not image_path.exists():
        raise FileNotFoundError(f"Image not found: {image_path}")
    labels = [lb for lb in data["labels"] if lb.get("x") is not None and lb.get("y") is not None]
    if not labels:
        raise ValueError(f"No labels with positions in {json_path}. Run authoring first.")
    return image_path, labels


def run_game(level_dir: Path, tolerance: float = 80.0) -> None:
    """Run BabyduckGame: click shape, type its name."""
    import tkinter as tk
    from tkinter import font as tkfont
    from tkinter import simpledialog, messagebox

    image_path, labels = load_level(Path(level_dir))
    if not Image:
        raise RuntimeError("Pillow required. pip install Pillow")

    root = tk.Tk()
    root.title("BabyduckGame")
    root.geometry("1100x720")
    root.configure(bg="#f0d4e0")

    img = Image.open(image_path).convert("RGB")
    orig_w, orig_h = img.size
    identified_indices: set[int] = set()

    # word bank: (display_text, index), sorted by display text
    word_bank = sorted([(lb["text"], i) for i, lb in enumerate(labels)], key=lambda x: x[0].lower())

    # scale and offset for drawing (image fit within canvas)
    canvas_w, canvas_h = 900, 600
    scale = min(canvas_w / orig_w, canvas_h / orig_h)
    disp_w = int(orig_w * scale)
    disp_h = int(orig_h * scale)
    off_x = (canvas_w - disp_w) // 2
    off_y = (canvas_h - disp_h) // 2

    def to_image_coords(cx: float, cy: float) -> tuple[float, float]:
        ix = (cx - off_x) / scale
        iy = (cy - off_y) / scale
        return (max(0, min(orig_w, ix)), max(0, min(orig_h, iy)))

    def to_canvas_coords(ix: float, iy: float) -> tuple[int, int]:
        return (int(off_x + ix * scale), int(off_y + iy * scale))

    def find_nearest_label(ix: float, iy: float) -> tuple[dict, int] | None:
        """Return (label, index) whose target is nearest to (ix, iy), if within tolerance."""
        best = None
        best_idx = -1
        best_d = float("inf")
        for i, lb in enumerate(labels):
            tx, ty = float(lb["x"]), float(lb["y"])
            d = math.hypot(ix - tx, iy - ty)
            if d <= tolerance and d < best_d:
                best = lb
                best_idx = i
                best_d = d
        return (best, best_idx) if best else None

    levels_dir = level_dir.resolve().parent
    available = get_available_levels(levels_dir)
    current_name = LEVEL_NAMES.get(level_dir.name, level_dir.name.replace("_", " ").title())

    def switch_level():
        sel = level_var.get()
        for name, path in available:
            if name == sel:
                root.destroy()
                run_game(path, tolerance)
                return

    top = tk.Frame(root, bg="#f0d4e0", padx=12, pady=6)
    top.pack(fill=tk.X)
    header_font = tkfont.Font(family="Segoe UI", size=14, weight="bold")
    tk.Label(top, text="Level:", font=header_font, fg="#2d2d2d", bg="#f0d4e0").pack(side=tk.LEFT, padx=(0, 8))
    level_var = tk.StringVar(value=current_name)
    if available:
        names = [n for n, _ in available]
        om = tk.OptionMenu(top, level_var, *names, command=lambda _: switch_level())
        om.config(font=header_font, fg="#2d2d2d", bg="#d4a5b5", relief=tk.FLAT)
        om.pack(side=tk.LEFT)

    main = tk.Frame(root, bg="#f0d4e0", padx=12, pady=12)
    main.pack(fill=tk.BOTH, expand=True)

    header_font = tkfont.Font(family="Segoe UI", size=14, weight="bold")
    normal_font = tkfont.Font(family="Segoe UI", size=11)
    word_bank_font = tkfont.Font(family="Segoe UI", size=11, weight="bold")
    status_var = tk.StringVar(value="Click on a shape, then type its name when prompted.")
    tk.Label(main, textvariable=status_var, font=header_font, fg="#2d2d2d", bg="#f0d4e0").pack(pady=(0, 8))

    content = tk.Frame(main, bg="#f0d4e0")
    content.pack(fill=tk.BOTH, expand=True)

    left = tk.Frame(content, bg="#ebc8d4", width=200, padx=10, pady=10)
    left.pack(side=tk.LEFT, fill=tk.Y, padx=(0, 10))
    left.pack_propagate(False)
    tk.Label(left, text="Word Bank", font=header_font, fg="#2d2d2d", bg="#ebc8d4").pack(anchor=tk.W)
    desc = tk.Label(left, text="Click on a pink box, then type the name of the gland that it points to.", font=normal_font, fg="#4a4a4a", bg="#ebc8d4", wraplength=180, justify=tk.LEFT)
    desc.pack(anchor=tk.W, pady=(0, 8))

    # word bank labels (read-only)
    word_labels: list[tuple[str, int, tk.Label]] = []
    for display_text, idx in word_bank:
        lb = tk.Label(left, text=display_text, font=word_bank_font, fg="#ffffff", bg="#ebc8d4", anchor=tk.W, wraplength=180, justify=tk.LEFT)
        lb.pack(fill=tk.X, pady=2)
        word_labels.append((display_text, idx, lb))

    def update_word_bank():
        for _, idx, wl in word_labels:
            if idx in identified_indices:
                wl.configure(fg="#ffffff")
            else:
                wl.configure(fg="#ffffff")

    resample = getattr(Image, "Resampling", None)
    resample = (resample.LANCZOS if resample else None) or getattr(Image, "LANCZOS", Image.NEAREST)
    img_disp = img.resize((disp_w, disp_h), resample)
    try:
        from PIL import ImageTk
        photo = ImageTk.PhotoImage(img_disp)
    except Exception:
        photo = None

    canvas = tk.Canvas(content, width=canvas_w, height=canvas_h, bg="#e8c4d0", highlightthickness=0)
    canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
    if photo:
        canvas.create_image(off_x + disp_w // 2, off_y + disp_h // 2, image=photo, tags="img")
        canvas.image = photo

    canvas.create_rectangle(off_x, off_y, off_x + disp_w, off_y + disp_h, outline="#c99aa8", width=1, tags="border")

    marker_ids: list[int] = []

    def clear_markers():
        for mid in marker_ids:
            canvas.delete(mid)
        marker_ids.clear()

    def draw_checkmarks():
        """Draw green checkmarks on correctly identified shapes."""
        clear_markers()
        for i, lb in enumerate(labels):
            if i in identified_indices:
                cx, cy = to_canvas_coords(lb["x"], lb["y"])
                r = 8
                mid = canvas.create_oval(cx - r, cy - r, cx + r, cy + r, outline="#c99aa8", width=2, fill="#c99aa8", tags="marker")
                marker_ids.append(mid)

    def on_canvas_click(event):
        if not (off_x <= event.x <= off_x + disp_w and off_y <= event.y <= off_y + disp_h):
            return
        ix, iy = to_image_coords(event.x, event.y)
        result = find_nearest_label(ix, iy)
        if not result:
            status_var.set("No shape there — try clicking closer to the center of a shape.")
            return
        target, target_idx = result
        if target_idx in identified_indices:
            status_var.set(f"'{target['text']}' is already identified. Click another shape.")
            return

        root.update()
        user_input = simpledialog.askstring(
            "Name this gland",
            "What is this gland?",
            parent=root,
        )
        if user_input is None:
            status_var.set("Click on a shape, then type its name when prompted.")
            return

        answer = target.get("answer", target["text"])
        if user_input.strip().lower() == answer.lower():
            identified_indices.add(target_idx)
            draw_checkmarks()
            update_word_bank()
            if len(identified_indices) == len(labels):
                status_var.set("All correct! Well done!")
                messagebox.showinfo("BabyduckGame", "You identified all shapes correctly!")
            else:
                status_var.set(f"Correct! {len(identified_indices)}/{len(labels)} identified.")
        else:
            status_var.set(f"Incorrect. The correct answer was '{target['text']}'.")
            messagebox.showinfo("Incorrect", f"The correct answer is: {target['text']}")

    canvas.bind("<Button-1>", on_canvas_click)

    def reset():
        identified_indices.clear()
        clear_markers()
        update_word_bank()
        status_var.set("Click on a shape, then type its name when prompted.")

    tk.Button(main, text="Reset", font=header_font, fg="#4a3a3a", bg="#d4a5b5", activebackground="#c99aa8", relief=tk.FLAT, padx=20, pady=8, command=reset).pack(pady=10)

    root.mainloop()


def main():
    ap = argparse.ArgumentParser(description="Run BabyduckGame.")
    ap.add_argument("level", type=Path, nargs="?", default=Path("levels/anatomy"), help="Level directory (e.g. levels/anatomy or levels/endocrine)")
    ap.add_argument("-t", "--tolerance", type=float, default=80, help="Pixel tolerance for click-to-select shape (larger = easier to click)")
    args = ap.parse_args()
    level_dir = Path(args.level)
    if not level_dir.is_dir():
        print(f"Level directory not found: {level_dir}", file=sys.stderr)
        sys.exit(1)
    run_game(level_dir, tolerance=args.tolerance)


if __name__ == "__main__":
    main()
