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

EOF

open -a /Applications/DOSBox.app MAKE.BAT
