.autodepend
SRC = hello.c
.c.obj:
	\TC\BIN\TCC {$< }
hello.exe:: hello.obj
	\TC\BIN\TLINK /v /L\TC\LIB\ $(SRC:.c=.obj) $*
!
