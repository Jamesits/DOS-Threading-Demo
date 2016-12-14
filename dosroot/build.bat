
C:
cd src
set PATH=%PATH%\;C:\TC\;C:\TC\BIN\;Z:\\;
set CLASSPATH=%CLASSPATH%\;C:\TC\LIB\;
set LIB=%LIB%\;C:\TC\LIB\;
set INCLUDE=%INCLUDE%\;C:\DOSROOT\SRC\;C:\TC\INCLUDE\;

tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y butler.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y cbrkint.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y chprio.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y clkinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y clkint.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y close.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y conf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y control.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y create.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dfalloc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dfckmd.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dfdsrch.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dio.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y doprnt.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y doscall.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dscntl.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsinter.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dskbcpy.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dskenq.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dskqopt.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsksync.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsnap.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsopen.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsread.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dsseek.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y dswrite.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y fprintf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y freebuf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y freemem.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getbuf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getdev.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getitem.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getmem.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getpid.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y getprio.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ibclear.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ibget.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y iblfree.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ibnew.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ibput.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y init.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y initiali.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y insert.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y insertd.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ioerr.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ionull.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y kgetc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y kill.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y kprintf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y kputc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfclose.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfgetc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfputc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfread.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfsdfree.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfseek.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfsetup.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfsflush.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfsnewd.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lfwrite.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwattr.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwbord.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwclose.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwcntl.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwgetc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwoproc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwputc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwread.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y lwwrite.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y map.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mark.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfalloc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfclose.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfdsrch.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfgetc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfputc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfread.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfseek.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfsetup.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfsflush.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mfwrite.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mkpool.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y mscntl.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y msopen.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y newqueue.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y open.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y panic.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y pcount.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y pcreate.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y pcscreen.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y pdelete.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y pinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y poolinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y preceive.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y preset.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y printf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y proto.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y psend.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y psnap.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ptclear.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y putc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y queue.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y read.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y readcopy.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ready.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y receive.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y recvclr.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y resched.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y resume.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y scount.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y screate.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y sdelete.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y seek.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y send.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y sendf.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y sendn.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y signal.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y signaln.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y sleep.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y sleept.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y sreset.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ssclock.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y suspend.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y tsnap.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttycntl.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttygetc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyiin.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyinit.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyiproc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyopen.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyoproc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyputc.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttyread.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y ttywrite.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y userret.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y wait.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y wakeup.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y wputcsr.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y writcopy.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y write.c
tcc -ml -DTURBOC -I\DOSROOT\SRC -C -M -N -b -c -d -v -y xdone.c
tasm /MX ctxsw.asm
tasm /MX dos.asm
tasm /MX dskio.asm
tasm /MX eidi.asm
tasm /MX intmap.asm
tasm /MX kbdio.asm
tasm /MX proto.asm
tasm /MX stack.asm
tasm /MX vidio.asm
tasm /MX xeidi.asm
