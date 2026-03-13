# AnatomyGame
## (BabyduckGame) - made to help Tiffany study for her exam

A small interactive game that uses **images and labels from PowerPoint slides**. Click on a shape in the image, then type its name from the word bank. Spelling must be correct, but capitalization does not matter. Click on the pink box to begin typing the label name.

## Quick start (no PowerPoint)

1. Install deps and create a sample level:
   ```bash
   cd BabyduckGame
   pip install -r requirements.txt
   python create_sample_level.py
   ```
2. Run the game:
   ```bash
   python game.py
   ```
   (Defaults to `levels/sample`. Or pass a level explicitly: `python game.py levels/slide_0`.)

## Requirements

- Python 3.9+
- `python-pptx`, `Pillow` (see `requirements.txt`)

## Project layout

```
BabyduckGame/
  extract_pptx.py      # Extract from .pptx, run authoring
  game.py              # Main game UI
  create_sample_level.py
  requirements.txt
  levels/              # Extracted levels 
    slide_0/
      image.png
      level.json
```

## Play:
   ```bash
   python game.py levels/anatomy
   ```
