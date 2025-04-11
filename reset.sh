#!/bin/bash

# Define your camera's USB identifiers
VENDOR_ID="054c"
PRODUCT_ID="0e90"

# Find the camera's USB bus and device numbers
DEVICE_INFO=$(lsusb -d "$VENDOR_ID:$PRODUCT_ID" | head -n 1)
if [ -z "$DEVICE_INFO" ]; then
    echo "Error: Camera not found!"
    exit 1
fi

# Extract bus and device numbers
BUS=$(echo "$DEVICE_INFO" | awk '{print $2}' | sed 's/^0*//')
DEVICE=$(echo "$DEVICE_INFO" | awk '{print $4}' | cut -d: -f1 | sed 's/^0*//')

# Format with leading zeros for 3-digit format
BUS=$(printf "%03d" "$BUS")
DEVICE=$(printf "%03d" "$DEVICE")

# Construct device path
DEVICE_PATH="/dev/bus/usb/$BUS/$DEVICE"

# Verify device path exists
if [ ! -e "$DEVICE_PATH" ]; then
    echo "Error: Device path $DEVICE_PATH not found!"
    exit 1
fi

# Check for reset utility
if ! command -v ./usb_reset/reset_usb &> /dev/null; then
    echo "Error: ./usb_reset/reset_usb utility not found!"
    echo "Compile the C program first with: gcc usbreset.c -o usbreset"
    exit 1
fi

# Reset the device
echo "Resetting Sony ILX-LR1 at $DEVICE_PATH..."
sudo ./usb_reset/reset_usb "$DEVICE_PATH"

# Check result
if [ $? -eq 0 ]; then
    echo "Reset successful!"
else
    echo "Reset failed!"
    exit 1
fi