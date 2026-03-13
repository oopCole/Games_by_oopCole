#!/usr/bin/env python3
"""Create a sample level (image + level.json) so you can try BabyduckGame without a PowerPoint."""

from pathlib import Path

try:
    from PIL import Image, ImageDraw
except ImportError:
    raise SystemExit("Pillow required: pip install Pillow")

LEVEL_DIR = Path(__file__).resolve().parent / "levels" / "sample"
LEVEL_DIR.mkdir(parents=True, exist_ok=True)

# Simple diagram: a few shapes with obvious "target" points
W, H = 600, 400
img = Image.new("RGB", (W, H), (250, 250, 252))
draw = ImageDraw.Draw(img)
draw.rectangle([80, 80, 220, 180], outline=(120, 120, 140), width=3, fill=(220, 220, 255))
draw.ellipse([280, 100, 420, 220], outline=(120, 120, 140), width=3, fill=(255, 220, 220))
draw.polygon([(450, 250), (550, 350), (350, 350)], outline=(120, 120, 140), width=3, fill=(220, 255, 220))
draw.text((140, 125), "A", fill=(80, 80, 100))
draw.text((340, 145), "B", fill=(80, 80, 100))
draw.text((450, 295), "C", fill=(80, 80, 100))

image_path = LEVEL_DIR / "image.png"
img.save(image_path)

# Label positions at center of each shape (where the letter is)
level = {
    "image": "image.png",
    "labels": [
        {"text": "Rectangle", "x": 150, "y": 130},
        {"text": "Circle", "x": 350, "y": 160},
        {"text": "Triangle", "x": 450, "y": 300},
    ],
}
import json
with open(LEVEL_DIR / "level.json", "w", encoding="utf-8") as f:
    json.dump(level, f, indent=2)

print(f"Created sample level at {LEVEL_DIR}")
print("Run: python game.py levels/sample")
