#!/bin/bash
set -eu

if [[ "`uname`" == 'Darwin' ]]; then
    ${BUILD_SYSTEM_DOSBOX_ROOT}/DOSBox.app/Contents/MacOS/DOSBox $@
elif [[ $OSTYPE == 'linux-gnu' ]]; then
    dosbox $@
else
    echo "Unsupported system!"
fi
