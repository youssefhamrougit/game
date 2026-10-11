# Player Sprite Assets

Pixel-art character for the dark-fantasy game (SDL2 / C++).

## Folder layout

```
player/
├── idle/
│   ├── down.png      # Front-facing idle (frame 0 of walk)
│   ├── up.png        # Back-facing idle
│   ├── left.png
│   └── right.png
├── walk/
│   ├── down_0.png … down_3.png   # Front walk cycle (4 frames)
│   ├── up_0.png … up_3.png       # Back walk cycle
│   ├── left_0.png … left_3.png
│   └── right_0.png … right_3.png
├── preview/
│   ├── contact_sheet.png         # All 16 frames on checkerboard
│   ├── down_preview.png
│   ├── left_preview.png
│   ├── right_preview.png
│   └── up_preview.png
└── README.md
```

## Source

- Original image: `attachments/ChatGPT Image 9 oct. 2026, 14_28_25.png`
- Detected as a 4×4 display of 32×32 intended frames (front / left / right / back).
- Processing script: `tools/process_player_sprites.py`
- All frames are 32×32 RGBA with transparent background.
- Pixel-art edges preserved via nearest-neighbour resize after background removal.

## Animation notes

- **Walk cycle**: 4 frames per direction. Animate by advancing the frame index with elapsed time (e.g. every 120–150 ms).
- **Idle**: Uses the first frame of the corresponding walk direction. No dedicated idle animation was present in the source.
- Both eyes are visible on all `down_*` (front) frames.
- Left / right are distinct drawings (not simple horizontal flips). Prefer the matching asset rather than flipping unless you intentionally want a mirrored pose.

## SDL2 quick load example

See `tools/sdl_player_sprite_example.cpp` for a minimal loader that uses `IMG_Load` + `SDL_RenderCopy` / `SDL_RenderCopyEx`. Keep the source PNG intact; never overwrite it.
