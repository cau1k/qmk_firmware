#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"
KEYBOARD="lily58/rev1"
KEYMAP="caulk"
UF2="${ROOT_DIR}/lily58_rev1_caulk.uf2"
LABELS=("RPI-RP2" "RP2040")
MOUNT_BASES=("/run/media/$USER" "/media/$USER" "/media" "/mnt")

find_mount() {
  local base
  local mount
  local name

  for base in "${MOUNT_BASES[@]}"; do
    [[ -d "$base" ]] || continue
    while IFS= read -r -d '' mount; do
      name="${mount##*/}"
      for want in "${LABELS[@]}"; do
        if [[ "$name" == "$want"* ]]; then
          echo "$mount"
          return 0
        fi
      done
    done < <(find "$base" -maxdepth 1 -mindepth 1 -type d -print0 2>/dev/null)
  done

  while read -r devname label mount; do
    [[ -n "$label" ]] || continue
    for want in "${LABELS[@]}"; do
      if [[ "$label" == "$want" ]]; then
        if [[ -n "$mount" ]]; then
          echo "$mount"
          return 0
        fi

        local dev="/dev/${devname}"
        local output

        if command -v udisksctl >/dev/null 2>&1; then
          output=$(udisksctl mount -b "$dev" 2>/dev/null || true)
          if [[ "$output" == *" at "* ]]; then
            echo "${output##* at }"
            return 0
          fi
        fi
      fi
    done
  done < <(lsblk -rno NAME,LABEL,MOUNTPOINT)

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
MASTER_SIDE=left POINTING_DEVICE_POSITION=left qmk compile -kb "$KEYBOARD" -km "$KEYMAP"

if [[ ! -f "$UF2" ]]; then
  echo "UF2 not found at ${UF2}"
  exit 1
fi

flash_once "left"
echo "Left done. Unplug it, then plug the right half."
flash_once "right"

echo "Done."
