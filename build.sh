#!/bin/bash
rm dosroot/build.bat
echo "
C:
cd src
set PATH=%PATH%\;C:\\TC\;C:\\TC\\BIN\;Z:\\\;
set CLASSPATH=%CLASSPATH%\;C:\\TC\\LIB\;
set LIB=%LIB%\;C:\\TC\\LIB\;
set INCLUDE=%INCLUDE%\;C:\\DOSROOT\\SRC\;C:\\TC\\INCLUDE\;
" | tee -a dosroot/build.bat

#buildsystem/dosbox/DOSBox.app/Contents/MacOS/DOSBox dosroot/build.bat

sed -i "s/$#include\<(.*)\>/#include \"\1\"/g" **/*.c
find dosroot/src -iregex ".*\.c" | rev | cut -d / -f 1 | rev | sed "s/^/tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y /g" | tee -a dosroot/build.bat
find dosroot/src -iregex ".*\.asm" | rev | cut -d / -f 1 | rev | sed "s/^/tasm \/MX /g" | tee -a dosroot/build.bat

buildsystem/dosbox/DOSBox.app/Contents/MacOS/DOSBox dosroot/build.bat
