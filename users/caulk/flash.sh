#!/usr/bin/env bash
set -euo pipefail

KEYBOARD="lily58/rev1"
KEYMAP="caulk"
UF2="lily58_rev1_caulk.uf2"
MOUNTS=(
  "/media/$USER/RPI-RP2"
  "/run/media/$USER/RPI-RP2"
  "/media/$USER/RP2040"
  "/run/media/$USER/RP2040"
)

find_mount() {
  for mount in "${MOUNTS[@]}"; do
    if [ -d "$mount" ]; then
      echo "$mount"
      return 0
    fi
  done
  return 1
}

flash_once() {
  local label="$1"

  echo "Put the ${label} half into bootloader mode (RPI-RP2 drive)."
  read -r -p "Press Enter when ready..."

  for _ in {1..120}; do
    if mount_path=$(find_mount); then
      cp "$UF2" "$mount_path/"
      sync
      echo "Flashed ${label} to ${mount_path}."
      return 0
    fi
    sleep 1
  done

  echo "Timed out waiting for ${label} bootloader."
  return 1
}

qmk compile -kb "$KEYBOARD" -km "$KEYMAP"

flash_once "left"
flash_once "right"

echo "Done."
