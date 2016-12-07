#!/bin/bash
set -eu

mkdir -p build/mnt
DEVICE=`hdiutil attach -imagekey diskimage-class=CRawDiskImage -nomount build/system.img | grep s1 | cut -f1 -d" "`
echo "Disk image mounted at ${DEVICE}"
mount -t msdos ${DEVICE} build/mnt

echo "Image mounted. Press any key to continue..."
read -n 1 # pause

# unmount image
umount build/mnt
hdiutil detach `echo ${DEVICE} | grep -oE "/dev/disk\d+"`
echo "Image unmounted."
