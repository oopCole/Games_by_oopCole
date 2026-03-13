# BabyduckGame

A small interactive game that uses **images and labels from PowerPoint slides**. You place each label on the correct spot on the image (e.g. diagram parts, map locations). Great for anatomy, geography, or any labeled-diagram practice.

## Quick start (no PowerPoint)

1. Install deps and create a sample level:
   ```bash
   cd label-pinpoint-game
   pip install -r requirements.txt
   python create_sample_level.py
   ```
2. Run the game:
   ```bash
   python game.py
   ```
   (Defaults to `levels/sample`. Or pass a level explicitly: `python game.py levels/slide_0`.)

## Using your own PowerPoint slides

### 1. Extract images and labels

```bash
python extract_pptx.py path/to/your.pptx -o levels
```

- Use `-s 0` to extract only slide 0 (first slide).
- This creates `levels/slide_0/`, `levels/slide_1/`, etc., each with `image.*` and `level.json`.

### 2. Author label positions

The extractor only has label **text**; it doesn’t know where each label should go. You define that once per level:

```bash
python extract_pptx.py path/to/your.pptx --author levels/slide_0
```

A window opens with the level image. **Click where each label points** (in order). When you’re done, positions are saved into `level.json`. Repeat for each `levels/slide_N` you care about.

### 3. Play the game

```bash
python game.py levels/slide_0
```

- Select a label in the list, then **click on the image** where it belongs.
- Place all labels, then click **Check** to see your score.
- Use **Reset** to try again. Green dashed circles show the correct positions after checking.

### Options

- **Game:** `python game.py levels/slide_0 -t 50` — set placement tolerance in pixels (default 40).
- **Extract:** `python extract_pptx.py deck.pptx -o my_levels -s 2` — output to `my_levels`, extract only slide 2.

## Requirements

- Python 3.9+
- `python-pptx`, `Pillow` (see `requirements.txt`)

## Project layout

```
label-pinpoint-game/
  extract_pptx.py      # Extract from .pptx, run authoring
  game.py              # Main game UI
  create_sample_level.py
  requirements.txt
  levels/              # Extracted levels (slide_0, slide_1, ... or sample)
    slide_0/
      image.png
      level.json
```

## Tips

- **PowerPoint:** Use one main image per slide (diagram, map) and separate text boxes for each label. The extractor picks the largest picture and all short text shapes (≤200 chars) as labels.
- **Authoring:** Click the **exact** spot the label should point to (e.g. center of a region or end of a line).
- **Tolerance:** If correctly placed labels often score wrong, increase `-t` (e.g. `-t 60`).
