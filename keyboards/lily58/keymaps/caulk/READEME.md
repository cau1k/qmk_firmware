This is a keymap for the Lily58 keyboard.

Below are some resources to reference.

## Per Repo Findings

### rwarcards762/lily58_bongocat:

- 4 layers; LOWER packs F1–F12 + !@#$%^&\*() + {} + |, RAISE adds nav + arrows + []\ cluster; OLED shows WPM/GUI/Caps/Layer and a WPM‑driven BongoCat animation. ​/home/user/.library-catalog/c/rwarcards762.lily58_bongocat/keymap.c:21 ​/home/user/.library-catalog/c/rwarcards762.lily58_bongocat/keymap.c:132

### MihaelN/lily58pro:

- 3 layers; L1 is F keys + keypad/mouse, L2 is RGB/media; OLED renders static “venom” bitmaps on both halves (no layer/WPM). ​/home/user/.library-catalog/c/mihaeln.lily58pro/firmware/keymap.c:10 ​/home/user/.library-catalog/c/mihaeln.lily58pro/firmware/keymap.c:16

### Kuji5/Kuji-Lily58:

### base + F‑key/arrow layer + numpad layer; OLED is Luna pet + WPM on master, logo on slave. ​/home/user/.library-catalog/c/kuji5.kuji-lily58/keymap.c:24 ​/home/user/.library-catalog/c/kuji5.kuji-lily58/keymap.c:291

### riiadesign/lily58-kiumi: base QWERTY with layer‑tap space/backspace; LOWER is F‑keys + nav, RAISE is media/numpad; OLED master shows layer + mod icons + logo, slave runs BongoCat and a minimal prompt blink. ​/home/user/.library-catalog/c/riiadesign.lily58-kiumi/keymap.c:11 ​/home/user/.library-catalog/c/riiadesign.lily58-kiumi/brain.c:21

### karlnicoll/lily58-cbiscuit: base has braces on inner column, LSPO/RSPC for parens, LALT_T/RALT_T for brackets; symbol layer includes F1–F20, < >, \ |, + -; nav has arrows + paging; OLED is minimal layer/LED text. ​/home/user/.library-catalog/c/karlnicoll.lily58-cbiscuit/keymap.c:11 ​/home/user/.library-catalog/c/karlnicoll.lily58-cbiscuit/keymap.c:148

### oldfieldtc/Lily58-keymap: LOWER has F1–F12 + full symbol row with {} and |, RAISE has arrows + []\ + + - =; OLED shows layer + keylog + WPM. ​/home/user/.library-catalog/c/oldfieldtc.lily58-keymap/keymap.c:38 ​/home/user/.library-catalog/c/oldfieldtc.lily58-keymap/keymap.c:120

### miroresh/lily58: LOWER puts {}/[] top‑right and arrows + + - / |; RAISE repeats arrows + []\; encoder for volume; OLED shows layer + keylog. ​/home/user/.library-catalog/c/miroresh.lily58/keymap.c:48 ​/home/user/.library-catalog/c/miroresh.lily58/keymap.c:148

### siketyan/lily58-keymap: LOWER is dense with F1–F20 and !@#$%^&\*() + < > \_ + { } |; RAISE adds arrows, nav, and parens; OLED shows layer + keylog. ​/home/user/.library-catalog/c/siketyan.lily58-keymap/keymap.c:48 ​/home/user/.library-catalog/c/siketyan.lily58-keymap/keymap.c:138

### aciceri/lily58: standard LOWER/RAISE symbol layout with {} + | + arrows; OLED can display 4 lines sent from host via raw HID (useful for editor state). ​/home/user/.library-catalog/c/aciceri.lily58/keymap.c:39 ​/home/user/.library-catalog/c/aciceri.lily58/keymap.c:95

### isaacsa51/lily58-keycat: Colemak‑DH base + QWERTY layer, TT layer toggles, select_word helper; LOWER is media/nav, RAISE is F‑keys + mouse; OLED shows WPM/GUI/Caps/Layer plus BongoCat on slave. ​/home/user/.library-catalog/c/isaacsa51.lily58-keycat/keymap.c:24 ​/home/user/.library-catalog/c/isaacsa51.lily58-keycat/keymap.c:124

### NewAbbreviations950/NA_Lily58: RIGHT layer has F1–F12 + [](){}<> + desktop switch; LEFT layer is mouse/num pad; OLED shows layer/locks/macro state + jiggler + Luna pet; Cirque trackpad enabled in config. ​/home/user/.library-catalog/c/newabbreviations950.na_lily58/keymap.c:17 ​/home/user/.library-catalog/c/newabbreviations950.na_lily58/keymap.c:353

# Programming-Focused Observations

## Strongest symbol optimization for { } [ ] ( ) < > | and F‑keys:

- karlnicoll/lily58-cbiscuit and siketyan/lily58-keymap; miroresh/lily58 and NA_Lily58 are good but less dense. ​/home/user/.library-catalog/c/karlnicoll.lily58-cbiscuit/keymap.c:57 ​/home/user/.library-catalog/c/siketyan.lily58-keymap/keymap.c:69

- Arrow ergonomics are mostly right‑hand clusters on LOWER/RAISE; no Vim‑style HJKL layer found. ​/home/user/.library-catalog/c/miroresh.lily58/keymap.c:69

- No repo defines direct macros for =>, ->, ::, or |> (no combos/tap‑dance/SendString for these). ​/home/user/.library-catalog/c/karlnicoll.lily58-cbiscuit/keymap.c:11

## Ranked Picks (TS/Rust/Go + Calm OLED)

-   1. karlnicoll/lily58-cbiscuit — best symbol ergonomics + F1–F20 + < > on same layer; minimal OLED text; braces and parens on base/shifted. ​/home/user/.library-catalog/c/karlnicoll.lily58-cbiscuit/keymap.c:34 ​/home/user/.library-catalog/c/karlnicoll.lily58-cbiscuit/keymap.c:193
-   2. siketyan/lily58-keymap — dense symbol layer with F1–F20 and < > { } |; OLED stays text‑only. ​/home/user/.library-catalog/c/siketyan.lily58-keymap/keymap.c:69 ​/home/user/.library-catalog/c/siketyan.lily58-keymap/keymap.c:159
-   3. miroresh/lily58 — compact { } [ ] + - / | placement with arrow cluster; encoder for volume; OLED is minimal. ​/home/user/.library-catalog/c/miroresh.lily58/keymap.c:69 ​/home/user/.library-catalog/c/miroresh.lily58/keymap.c:169
-   4. oldfieldtc/Lily58-keymap — close to your 3‑layer style with symbol row and arrows; OLED shows keylog/WPM but no animation. ​/home/user/.library-catalog/c/oldfieldtc.lily58-keymap/keymap.c:60 ​/home/user/.library-catalog/c/oldfieldtc.lily58-keymap/keymap.c:136
-   5. NewAbbreviations950/NA_Lily58 — strong symbol row + F‑keys + trackpad; OLED is busy but can be pruned by trimming the pet/macro blocks. ​/home/user/.library-catalog/c/newabbreviations950.na_lily58/keymap.c:77 ​/home/user/.library-catalog/c/newabbreviations950.na_lily58/keymap.c:353
