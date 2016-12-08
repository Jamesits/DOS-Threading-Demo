#!/bin/bash
set -eu

SCRIPT_PATH="`dirname \"$0\"`"
mkdir -p ${BUILD_TEMP}/mnt
cp ${BUILD_SYSTEM_QEMU_IMAGE_TEMPLATE} ${BUILD_TEMP}/system.img

if [[ "`uname`" == 'Darwin' ]]; then
    # mount image
    DEVICE=`hdiutil attach -imagekey diskimage-class=CRawDiskImage -nomount ${BUILD_TEMP}/system.img | grep s1 | cut -f1 -d" "`
    echo "Disk image mounted at ${DEVICE}"
    mount -t msdos ${DEVICE} ${BUILD_TEMP}/mnt

    # copy files
    cp -rf ${BUILD_DOSROOT}/* ${BUILD_TEMP}/mnt
    cp -f ${SCRIPT_PATH}/AUTOEXEC.BAT ${BUILD_TEMP}/mnt

    # unmount image
    umount ${BUILD_TEMP}/mnt
    hdiutil detach `echo ${DEVICE} | grep -oE "/dev/disk\d+"`

    # run system
    qemu-system-x86_64 -localtime -s -serial file:"${BUILD_TEMP}/DEBUG.LOG" -curses ${BUILD_TEMP}/system.img

elif [[ $OSTYPE == 'linux-gnu' ]]; then
    #mount image
    mount -t msdos -o loop,offset=32256 ${BUILD_TEMP}/system.img ${BUILD_TEMP}/mnt

    # copy files
    cp -rf ${BUILD_DOSROOT}/* ${BUILD_TEMP}/mnt
    cp -f ${SCRIPT_PATH}/AUTOEXEC.BAT ${BUILD_TEMP}/mnt

    #unmount image
    umount ${BUILD_TEMP}/mnt

    # run system
    qemu -localtime -s -serial file:"${BUILD_TEMP}/DEBUG.LOG" ${BUILD_TEMP}/system.img
else
    echo "Unsupported system!"
fi
