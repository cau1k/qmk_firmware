#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
USER_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
ROOT_DIR="$(cd "${USER_DIR}/../.." && pwd)"
ASSETS_DIR="${SCRIPT_DIR}"
KEYBOARD="lily58/rev1"
KEYMAP="caulk"

require_cmd() {
  local cmd="$1"
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "Missing required command: ${cmd}"
    return 1
  fi
}

require_cmd qmk
require_cmd keymap
require_cmd rsvg-convert
require_cmd magick

cd "$ROOT_DIR"

qmk c2json --no-cpp -kb "$KEYBOARD" -km "$KEYMAP" -o "${ASSETS_DIR}/lily58.keymap.json" "keyboards/lily58/keymaps/caulk/keymap.c"
keymap parse -q "${ASSETS_DIR}/lily58.keymap.json" -l BASE NAV SYM ADJ -c 6 -o "${ASSETS_DIR}/lily58.keymap.yaml"

for layer in BASE NAV SYM ADJ; do
  keymap -c "${ASSETS_DIR}/keymap_drawer.yaml" draw -k "$KEYBOARD" -l LAYOUT -s "$layer" \
    -o "${ASSETS_DIR}/lily58_${layer}.svg" "${ASSETS_DIR}/lily58.keymap.yaml"
  rsvg-convert "${ASSETS_DIR}/lily58_${layer}.svg" -o "${ASSETS_DIR}/lily58_${layer}.png"
done

magick montage "${ASSETS_DIR}/lily58_BASE.png" "${ASSETS_DIR}/lily58_NAV.png" \
  "${ASSETS_DIR}/lily58_SYM.png" "${ASSETS_DIR}/lily58_ADJ.png" \
  -tile 2x2 -geometry +0+0 "${ASSETS_DIR}/lily58_all_layers.png"

echo "Regenerated Lily58 assets in ${ASSETS_DIR}"
