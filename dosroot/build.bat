
C:
cd src
set PATH=%PATH%\;C:\TC\;C:\TC\BIN\;Z:\\;
set CLASSPATH=%CLASSPATH%\;C:\TC\LIB\;
set LIB=%LIB%\;C:\TC\LIB\;
set INCLUDE=%INCLUDE%\;C:\DOSROOT\SRC\;C:\TC\INCLUDE\;

tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u butler.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u cbrkint.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u chprio.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u clkinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u clkint.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u close.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u conf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u control.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u create.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dfalloc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dfckmd.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dfdsrch.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dio.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u doprnt.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u doscall.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dscntl.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsinter.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dskbcpy.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dskenq.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dskqopt.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsksync.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsnap.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsopen.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsread.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dsseek.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u dswrite.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u fprintf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u freebuf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u freemem.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getbuf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getdev.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getitem.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getmem.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getpid.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u getprio.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ibclear.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ibget.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u iblfree.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ibnew.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ibput.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u init.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u initiali.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u insert.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u insertd.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ioerr.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ionull.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u kgetc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u kill.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u kprintf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u kputc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfclose.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfgetc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfputc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfread.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfsdfree.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfseek.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfsetup.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfsflush.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfsnewd.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lfwrite.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwattr.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwbord.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwclose.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwcntl.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwgetc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwoproc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwputc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwread.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u lwwrite.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u map.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mark.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfalloc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfclose.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfdsrch.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfgetc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfputc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfread.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfseek.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfsetup.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfsflush.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mfwrite.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mkpool.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u mscntl.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u msopen.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u newqueue.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u open.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u panic.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u pcount.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u pcreate.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u pcscreen.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u pdelete.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u pinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u poolinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u preceive.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u preset.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u printf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u proto.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u psend.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u psnap.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ptclear.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u putc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u queue.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u read.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u readcopy.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ready.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u receive.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u recvclr.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u resched.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u resume.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u scount.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u screate.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u sdelete.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u seek.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u send.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u sendf.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u sendn.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u signal.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u signaln.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u sleep.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u sleept.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u sreset.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ssclock.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u suspend.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u tsnap.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttycntl.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttygetc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyiin.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyinit.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyiproc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyopen.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyoproc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyputc.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttyread.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u ttywrite.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u userret.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u wait.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u wakeup.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u wputcsr.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u writcopy.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u write.c
tcc -ml -DTURBOC -I. -C -M -N -b -c -d -v -y -u xdone.c
tasm /MX ctxsw.asm ,
tasm /MX dos.asm ,
tasm /MX dskio.asm ,
tasm /MX eidi.asm ,
tasm /MX intmap.asm ,
tasm /MX kbdio.asm ,
tasm /MX proto.asm ,
tasm /MX stack.asm ,
tasm /MX vidio.asm ,
tasm /MX xeidi.asm ,
tlink \TC\LIB\C0L.OBJ BUTLER CBRKINT CHPRIO CLKINIT CLKINT CLOSE CONF CONTROL CREATE CTXSW DFALLOC DFCKMD DFDSRCH DIO DOPRNT DSCNTL DSINIT DSINTER DSKBCPY DSKENQ DSKIO DSKQOPT DSKSYNC DSNAP DSOPEN DSREAD DSSEEK DSWRITE EIDI FPRINTF FREEBUF FREEMEM GETBUF GETC GETDEV GETITEM GETMEM GETPID GETPRIO IBCLEAR IBGET IBLFREE IBNEW IBPUT INIT INITIALI INSERT INSERTD INTMAP IOERR IONULL KBDIO KGETC KILL KPRINTF KPUTC LFCLOSE LFGETC LFINIT LFPUTC LFREAD LFSDFREE LFSEEK LFSETUP LFSFLUSH LFSNEWD LFWRITE LWCLOSE LWCNTL LWGETC LWINIT LWOPROC LWPUTC LWREAD LWWRITE MAP MARK MFALLOC MFCLOSE MFDSRCH MFGETC MFINIT MFPUTC MFREAD MFSEEK MFSETUP MFSFLUSH MFWRITE MKPOOL MSCNTL MSOPEN NEWQUEUE OPEN PANIC PCOUNT PCREATE PCSCREEN PDELETE PINIT POOLINIT PRECEIVE PRESET PRINTF PSEND PSNAP PTCLEAR PUTC QUEUE READ READCOPY READY RECEIVE RECVCLR RESCHED RESUME SCOUNT SCREATE SDELETE SEEK SEND SENDF SENDN SIGNAL SIGNALN SLEEP SLEEPT SRESET SSCLOCK STACK SUSPEND TSNAP TTYCNTL TTYGETC TTYIIN TTYINIT TTYIPROC TTYOPEN TTYOPROC TTYPUTC TTYREAD TTYWRITE USERRET VIDIO WAIT WAKEUP WPUTCSR WRITCOPY WRITE XDONE XEIDI, thread.exe, , \TC\LIB\CL.lib \TC\LIB\MATHL.lib
