#!/usr/bin/env python3
"""
BabyduckGame: place labels on the correct spots on an image.
Load levels created by extract_pptx.py (after authoring).
"""

from __future__ import annotations

import argparse
import json
import math
import random
import sys
from pathlib import Path

try:
    from PIL import Image
    import io
except ImportError:
    Image = None
    io = None


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


def run_game(level_dir: Path, tolerance: float = 40.0) -> None:
    """Run the label-pinpoint game for one level."""
    import tkinter as tk
    from tkinter import font as tkfont

    image_path, labels = load_level(Path(level_dir))
    if not Image:
        raise RuntimeError("Pillow required. pip install Pillow")

    img = Image.open(image_path).convert("RGB")
    orig_w, orig_h = img.size
    placed: dict[str, tuple[float, float]] = {}
    shuffled = list(labels)
    random.shuffle(shuffled)

    # Scale and offset for drawing (image fit within canvas)
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

    root = tk.Tk()
    root.title("BabyduckGame")
    root.geometry("1100x720")
    root.configure(bg="#1a1b26")

    main = tk.Frame(root, bg="#1a1b26", padx=12, pady=12)
    main.pack(fill=tk.BOTH, expand=True)

    header_font = tkfont.Font(family="Segoe UI", size=14, weight="bold")
    normal_font = tkfont.Font(family="Segoe UI", size=11)
    status_var = tk.StringVar(value="Select a label, then click on the image where it belongs.")
    tk.Label(main, textvariable=status_var, font=header_font, fg="#a9b1d6", bg="#1a1b26").pack(pady=(0, 8))

    content = tk.Frame(main, bg="#1a1b26")
    content.pack(fill=tk.BOTH, expand=True)

    left = tk.Frame(content, bg="#16161e", width=200, padx=10, pady=10)
    left.pack(side=tk.LEFT, fill=tk.Y, padx=(0, 10))
    left.pack_propagate(False)
    tk.Label(left, text="Labels", font=header_font, fg="#7aa2f7", bg="#16161e").pack(anchor=tk.W)
    tk.Label(left, text="Click one, then click on the image.", font=normal_font, fg="#565f89", bg="#16161e").pack(anchor=tk.W, pady=(0, 8))

    selected = [None]

    def on_label_click(lb: dict):
        selected[0] = lb
        for w in left.winfo_children():
            if isinstance(w, tk.Button):
                w.configure(bg="#414868" if w.cget("text") == lb["text"] else "#24283b", fg="#c0caf5")
        status_var.set(f"Selected: '{lb['text']}' — click on the image to place it.")

    for lb in shuffled:
        btn = tk.Button(
            left,
            text=lb["text"],
            font=normal_font,
            bg="#24283b",
            fg="#c0caf5",
            activebackground="#414868",
            activeforeground="#c0caf5",
            relief=tk.FLAT,
            padx=8,
            pady=6,
            anchor=tk.W,
            command=lambda l=lb: on_label_click(l),
        )
        btn.pack(fill=tk.X, pady=2)

    resample = getattr(Image, "Resampling", None)
    resample = (resample.LANCZOS if resample else None) or getattr(Image, "LANCZOS", Image.NEAREST)
    img_disp = img.resize((disp_w, disp_h), resample)
    try:
        from PIL import ImageTk
        photo = ImageTk.PhotoImage(img_disp)
    except Exception:
        photo = None

    canvas = tk.Canvas(content, width=canvas_w, height=canvas_h, bg="#24283b", highlightthickness=0)
    canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
    if photo:
        canvas.create_image(off_x + disp_w // 2, off_y + disp_h // 2, image=photo, tags="img")
        canvas.image = photo

    # Draw image outline
    canvas.create_rectangle(off_x, off_y, off_x + disp_w, off_y + disp_h, outline="#7aa2f7", width=1, tags="border")

    marker_ids: list[int] = []

    def clear_markers():
        for mid in marker_ids:
            canvas.delete(mid)
        marker_ids.clear()
        canvas.delete("correct")

    def draw_markers():
        clear_markers()
        for lb, (ux, uy) in placed.items():
            cx, cy = to_canvas_coords(ux, uy)
            r = 6
            mid = canvas.create_oval(cx - r, cy - r, cx + r, cy + r, fill="#7dcfff", outline="#7aa2f7", width=2, tags="marker")
            marker_ids.append(mid)
            tid = canvas.create_text(cx, cy - 14, text=lb, font=("Segoe UI", 9), fill="#c0caf5", tags="marker")
            marker_ids.append(tid)

    def on_canvas_click(event):
        lb = selected[0]
        if not lb or lb["text"] in placed:
            return
        ix, iy = to_image_coords(event.x, event.y)
        if not (off_x <= event.x <= off_x + disp_w and off_y <= event.y <= off_y + disp_h):
            return
        placed[lb["text"]] = (ix, iy)
        draw_markers()
        remaining = [l["text"] for l in shuffled if l["text"] not in placed]
        if not remaining:
            status_var.set("All placed! Click 'Check' to see your score.")
        else:
            status_var.set(f"Placed '{lb['text']}'. Select another label, or click 'Check' when done.")

    canvas.bind("<Button-1>", on_canvas_click)

    def check():
        if len(placed) != len(labels):
            status_var.set("Place all labels first, then check.")
            return
        correct = 0
        for lb in labels:
            ux, uy = placed.get(lb["text"], (0, 0))
            tx, ty = float(lb["x"]), float(lb["y"])
            d = math.hypot(ux - tx, uy - ty)
            if d <= tolerance:
                correct += 1
        pct = 100 * correct / len(labels)
        status_var.set(f"Score: {correct}/{len(labels)} ({pct:.0f}%) correct within {tolerance:.0f} px.")
        for lb in labels:
            cx, cy = to_canvas_coords(lb["x"], lb["y"])
            r = 8
            canvas.create_oval(cx - r, cy - r, cx + r, cy + r, outline="#9ece6a", width=2, dash=(4, 4), tags="correct")
        btn_check.config(state=tk.DISABLED)
        btn_reset.config(state=tk.NORMAL)

    def reset():
        placed.clear()
        clear_markers()
        for w in left.winfo_children():
            if isinstance(w, tk.Button):
                w.configure(bg="#24283b", fg="#c0caf5")
        selected[0] = None
        status_var.set("Select a label, then click on the image where it belongs.")
        btn_check.config(state=tk.NORMAL)
        btn_reset.config(state=tk.DISABLED)

    btns = tk.Frame(main, bg="#1a1b26")
    btns.pack(pady=10)
    btn_check = tk.Button(btns, text="Check", font=header_font, fg="#1a1b26", bg="#7aa2f7", activebackground="#89b4fa", relief=tk.FLAT, padx=20, pady=8, command=check)
    btn_check.pack(side=tk.LEFT, padx=4)
    btn_reset = tk.Button(btns, text="Reset", font=header_font, fg="#1a1b26", bg="#565f89", activebackground="#414868", relief=tk.FLAT, padx=20, pady=8, command=reset, state=tk.DISABLED)
    btn_reset.pack(side=tk.LEFT, padx=4)

    root.mainloop()


def main():
    ap = argparse.ArgumentParser(description="Run BabyduckGame.")
    ap.add_argument("level", type=Path, nargs="?", default=Path("levels/sample"), help="Level directory (e.g. levels/sample or levels/slide_0)")
    ap.add_argument("-t", "--tolerance", type=float, default=40, help="Pixel tolerance for correct placement")
    args = ap.parse_args()
    level_dir = Path(args.level)
    if not level_dir.is_dir():
        print(f"Level directory not found: {level_dir}", file=sys.stderr)
        sys.exit(1)
    run_game(level_dir, tolerance=args.tolerance)


if __name__ == "__main__":
    main()
