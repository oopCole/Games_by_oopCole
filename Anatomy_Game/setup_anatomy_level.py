#!/usr/bin/env python3
"""
Set up the anatomy level for BabyduckGame.
Creates level.json with the anatomy word bank labels.
Place your image (no labels—diagram with pointer lines only) as levels/anatomy/image.png.

Run authoring after this to define click positions:
  python extract_pptx.py --author levels/anatomy
"""

from pathlib import Path

import json

LEVEL_DIR = Path(__file__).resolve().parent / "levels" / "anatomy"
LABELS = [
    "Ductus deferens",
    "Epididymis",
    "Interstitial cells",
    "Lumen of seminiferous tubule with spermatozoon",
    "Scrotum",
    "Seminiferous tubule",
    "Spermatic cord",
    "Spermatogonia",
]


def main():
    LEVEL_DIR.mkdir(parents=True, exist_ok=True)

    image_path = LEVEL_DIR / "image.png"
    if not image_path.exists():
        print("Place your anatomy diagram at levels/anatomy/image.png")
        print("(Use an image with pointer lines but no text labels.)")
        return

    data = {"image": "image.png", "labels": [{"text": t, "x": None, "y": None} for t in LABELS]}
    json_path = LEVEL_DIR / "level.json"
    with open(json_path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)
    print(f"Updated: {json_path}")

    print("\n--- Next step: run authoring to define click positions ---")
    print("  python extract_pptx.py --author levels/anatomy")
    print("  (Click on each anatomical part when prompted.)\n")


if __name__ == "__main__":
    main()
