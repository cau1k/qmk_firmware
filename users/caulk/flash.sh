#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"
KEYBOARD="lily58/rev1"
KEYMAP="caulk"
UF2="${ROOT_DIR}/lily58_rev1_caulk.uf2"
LABELS=("RPI-RP2" "RP2040")

find_mount() {
  while read -r label mount; do
    for want in "${LABELS[@]}"; do
      if [[ "$label" == "$want" && -n "$mount" ]]; then
        echo "$mount"
        return 0
      fi
    done
  done < <(lsblk -rno LABEL,MOUNTPOINT)
  return 1
}

flash_once() {
  local label="$1"

  echo ""
  echo "Flash ${label} half"
  echo "- Unplug TRRS"
  echo "- Plug ${label} half into USB"
  echo "- Enter bootloader (RPI-RP2 drive)"
  read -r -p "Press Enter when the drive appears..."

  echo "Waiting for ${label} bootloader..."
  for i in {1..120}; do
    if mount_path=$(find_mount); then
      echo "Found ${mount_path}. Copying UF2..."
      cp "$UF2" "$mount_path/"
      sync
      echo "${label} flashed."
      return 0
    fi

    if (( i % 10 == 0 )); then
      echo "Still waiting for ${label} bootloader..."
    fi
    sleep 1
  done

  echo "Timed out waiting for ${label} bootloader."
  return 1
}

cd "$ROOT_DIR"
qmk compile -kb "$KEYBOARD" -km "$KEYMAP"

if [[ ! -f "$UF2" ]]; then
  echo "UF2 not found at ${UF2}"
  exit 1
fi

flash_once "left"
echo "Left done. Unplug it, then plug the right half."
flash_once "right"

echo "Done."
