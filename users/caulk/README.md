# caulk keymaps

## Lily58

Generated from `keyboards/lily58/keymaps/caulk/keymap.c`.

- `lily58.keymap.json`: output of `qmk c2json -kb lily58/rev1 -km caulk`
- `lily58.keymap.yaml`: output of `keymap parse -q lily58.keymap.json -l BASE NAV SYM ADJ -c 6`

### Layers

![ALL](lily58_all_layers.png)

![BASE](lily58_BASE.png)
![NAV](lily58_NAV.png)
![SYM](lily58_SYM.png)
![ADJ](lily58_ADJ.png)

### Regenerate

```
qmk c2json -kb lily58/rev1 -km caulk -o users/caulk/lily58.keymap.json keyboards/lily58/keymaps/caulk/keymap.c
keymap parse -q users/caulk/lily58.keymap.json -l BASE NAV SYM ADJ -c 6 -o users/caulk/lily58.keymap.yaml
for layer in BASE NAV SYM ADJ; do keymap draw -k lily58/rev1 -l LAYOUT -s "$layer" -o users/caulk/lily58_${layer}.svg users/caulk/lily58.keymap.yaml; rsvg-convert users/caulk/lily58_${layer}.svg -o users/caulk/lily58_${layer}.png; done
```
