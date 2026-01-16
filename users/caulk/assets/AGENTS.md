# Keymap screenshot generation

This folder stores rendered keymap screenshots for Lily58. To regenerate from scratch, run these steps from the repo root.

## Prereqs
- `qmk` CLI installed and configured
- `keymap` CLI installed (`~/.local/bin/keymap` here)
- `rsvg-convert` for SVG -> PNG
- `magick` (ImageMagick) for montage

## Generate assets
1. Generate QMK JSON from the keymap:
   ```
   qmk c2json -kb lily58/rev1 -km caulk -o users/caulk/assets/lily58.keymap.json keyboards/lily58/keymaps/caulk/keymap.c
   ```
2. Parse JSON to YAML (for `keymap draw`):
   ```
   keymap parse -q users/caulk/assets/lily58.keymap.json -l BASE NAV SYM ADJ -c 6 -o users/caulk/assets/lily58.keymap.yaml
   ```
3. Render layer SVGs + PNGs using the dark theme config:
   ```
   for layer in BASE NAV SYM ADJ; do \
     keymap -c users/caulk/assets/keymap_drawer.yaml draw -k lily58/rev1 -l LAYOUT -s "$layer" \
       -o users/caulk/assets/lily58_${layer}.svg users/caulk/assets/lily58.keymap.yaml; \
     rsvg-convert users/caulk/assets/lily58_${layer}.svg -o users/caulk/assets/lily58_${layer}.png; \
   done
   ```
4. Build the 2x2 montage:
   ```
   magick montage users/caulk/assets/lily58_BASE.png users/caulk/assets/lily58_NAV.png \
     users/caulk/assets/lily58_SYM.png users/caulk/assets/lily58_ADJ.png \
     -tile 2x2 -geometry +0+0 users/caulk/assets/lily58_all_layers.png
   ```

## Notes
- Theme config lives at `users/caulk/assets/keymap_drawer.yaml`.
- `qmk c2json` may leave `lily58.keymap.json.bak`; delete it if not needed.
