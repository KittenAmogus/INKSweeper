#!/usr/bin/env bash

# Wait for InkPad
echo "-- Waiting for '$INKPAD_DISK'..."
while [ ! -e "$INKPAD_DISK" ]; do
  sleep 0.5
done
echo "-- Found InkPad"

if [ -e "${INKPAD_DISK}1" ]; then
  echo "Disk '$INKPAD_DISK' is not InkPad!"
  echo "Change flush.sh"
else
  # Mount InkPad
  sudo mount "$INKPAD_DISK" /mnt
  echo "-- Mounted"

  # Copy build to InkPad
  sudo cp ./app.app /mnt/applications/sweeper.app
  echo "-- Copied app"

  # Copy icons
  sudo cp ./icon.bmp /mnt/applications/icons/sweeper.bmp
  sudo cp ./icon_f.bmp /mnt/applications/icons/sweeper_f.bmp
  echo "-- Copied icons"

  # Unmount InkPad
  sudo umount /mnt
  echo "-- Unmounted"
fi
