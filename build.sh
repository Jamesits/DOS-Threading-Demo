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

find dosroot/src -iregex ".*\.c" | rev | cut -d / -f 1 | rev | sed "s/^/tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u /g" | tee -a dosroot/build.bat
find dosroot/src -iregex ".*\.asm" | rev | cut -d / -f 1 | rev | sed "s/^/tasm \/MX /g" | sed "s/$/ ,/g" | tee -a dosroot/build.bat
find dosroot/src -iregex ".*\.OBJ" | rev | cut -d / -f 1 | rev | cut -d "." -f 1 | xargs | sed "s/^/tlink \\\\TC\\\\LIB\\\\C0L.OBJ /g" | sed "s/$/, thread.exe, , \\\\TC\\\\LIB\\\\CL.lib \\\\TC\\\\LIB\\\\MATHL.lib/g" | tee -a dosroot/build.bat


buildsystem/dosbox/DOSBox.app/Contents/MacOS/DOSBox dosroot/build.bat
