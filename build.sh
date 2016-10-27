#!/bin/bash
pushd `dirname $0` > /dev/null
DOSROOT=`pwd -P`
popd > /dev/null
DOSROOT+="/dosroot"

cat > MAKE.BAT <<EOF
mount -u d
mount d $DOSROOT
D:
cd src
del *.EXE
del *.OBJ
del *.MAP
set PATH=D:\TC\BIN
MAKE thread.exe
EOF

open -a /Applications/DOSBox.app MAKE.BAT
