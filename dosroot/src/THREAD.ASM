	ifndef	??version
?debug	macro
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	S "thread.c"
	?debug	C E9E2A68149087468726561642E63
	?debug	C E9F68A5B49145C54435C494E434C5544455C7374646C69622E68
	?debug	C E9F68A5B49135C54435C494E434C5544455C5F646566732E68
	?debug	C E9F68A5B49135C54435C494E434C5544455C5F6E756C6C2E68
	?debug	C E9F58A5B49135C54435C494E434C5544455C616C6C6F632E68
	?debug	C E96AA68149087468726561642E68
	?debug	C E9F58A5B49115C54435C494E434C5544455C444F532E68
	?debug	C E9F68A5B49135C54435C494E434C5544455C737464696F2E68
	?debug	C E9F68A5B49145C54435C494E434C5544455C7374646C69622E68
	?debug	C E9F68A5B49145C54435C494E434C5544455C737472696E672E68
	?debug	C E9B67372490A75736572636F64652E68
	?debug	C E9F68A5B49135C54435C494E434C5544455C737464696F2E68
	?debug	C E96AA68149087468726561642E68
	?debug	C E9A29478490764656275672E68
	?debug	C E9E6A27849066D61696E2E68
	?debug	C E9ECA2784909646F737574696C2E68
THREAD_TEXT	segment byte public 'CODE'
THREAD_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:THREAD_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
THREAD5_DATA	segment para public 'FAR_DATA'
_tcb_count	label	word
	db	0
	db	0
THREAD5_DATA	ends
_DATA	segment word public 'DATA'
_schedule_reent	label	byte
	db	0
_in_kernel	label	byte
	db	0
_on_thread_death	label	byte
	db	0
_DATA	ends
THREAD_TEXT	segment byte public 'CODE'
	?debug	C E800087468726561642E63E2A68149
	?debug	L 14
	assume	cs:THREAD_TEXT
_get_last_running_thread_id	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	?debug	B
	?debug	L 16
	xor	si,si
	jmp	short @1@170
@1@58:
	?debug	L 17
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	cmp	word ptr es:_tcb[bx+8],1
	jne	short @1@142
	?debug	L 18
	mov	ax,si
@1@114:
	jmp	short @1@226
@1@142:
	?debug	L 16
	inc	si
@1@170:
	mov	ax,seg _tcb_count
	mov	es,ax
	cmp	word ptr es:_tcb_count,si
	jg	short @1@58
	?debug	L 21
	mov	ax,65535
	jmp	short @1@114
@1@226:
	?debug	L 22
	pop	si
	pop	bp
	ret	
	?debug	C E60169040406
	?debug	E
	?debug	E
_get_last_running_thread_id	endp
	?debug	L 24
	assume	cs:THREAD_TEXT
_get_next_running_thread_id	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	push	di
	?debug	B
	?debug	L 25
	push	cs
	call	near ptr _get_last_running_thread_id
	mov	di,ax
	?debug	L 27
	cmp	di,65535
	jne	short @2@394
	?debug	L 28
	mov	ax,seg _tcb_count
	mov	es,ax
	cmp	word ptr es:_tcb_count,0
	jne	short @2@198
	?debug	L 29
	push	ds
	mov	ax,offset DGROUP:s@
	push	ax
	mov	ax,2
@2@114:
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 30
	mov	ax,65535
@2@142:
	jmp	@2@702
	?debug	L 31
	jmp	short @2@366
@2@198:
	?debug	L 32
	xor	si,si
	jmp	short @2@310
@2@226:
	?debug	L 33
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	cmp	word ptr es:_tcb[bx+8],2
	jne	short @2@282
	?debug	L 34
	jmp	short @2@590
@2@282:
	?debug	L 32
	inc	si
@2@310:
	mov	ax,seg _tcb_count
	mov	es,ax
	cmp	word ptr es:_tcb_count,si
	jg	short @2@226
	?debug	L 37
	push	ds
	mov	ax,offset DGROUP:s@+14
	push	ax
	mov	ax,4
	jmp	short @2@114
@2@366:
	?debug	L 40
	jmp	short @2@702
@2@394:
	?debug	L 41
	mov	si,di
	jmp	short @2@506
@2@422:
	?debug	L 42
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	cmp	word ptr es:_tcb[bx+8],2
	jne	short @2@478
	jmp	short @2@590
@2@478:
	?debug	L 41
	inc	si
@2@506:
	mov	ax,seg _tcb_count
	mov	es,ax
	cmp	word ptr es:_tcb_count,si
	jg	short @2@422
	?debug	L 46
	xor	si,si
	jmp	short @2@646
@2@562:
	?debug	L 47
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	cmp	word ptr es:_tcb[bx+8],2
	jne	short @2@618
@2@590:
	?debug	L 48
	mov	ax,si
	jmp	@2@142
@2@618:
	?debug	L 46
	inc	si
@2@646:
	cmp	si,di
	jle	short @2@562
	?debug	L 51
	push	ds
	mov	ax,offset DGROUP:s@+34
	push	ax
	mov	ax,2
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 52
	mov	ax,di
	jmp	@2@142
@2@702:
	?debug	L 54
	pop	di
	pop	si
	pop	bp
	ret	
	?debug	C E60169040406046C617374040407
	?debug	E
	?debug	E
_get_next_running_thread_id	endp
	?debug	L 56
	assume	cs:THREAD_TEXT
_thread_end_trigger	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	?debug	B
	?debug	L 58
	call	far ptr _begin_transaction
	?debug	L 59
	mov	byte ptr DGROUP:_on_thread_death,1
	?debug	L 60
	push	cs
	call	near ptr _get_last_running_thread_id
	mov	si,ax
	?debug	L 61
	push	si
	push	ds
	mov	ax,offset DGROUP:s@+66
	push	ax
	mov	ax,1
	push	ax
	call	far ptr _lprintf
	add	sp,8
	?debug	L 62
	or	si,si
	jl	short @3@86
	push	si
	call	far ptr _destroy
	pop	cx
@3@86:
	?debug	L 63
	push	ds
	mov	ax,offset DGROUP:s@+83
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 64
	call	far ptr _print_tcb
	?debug	L 65
	mov	byte ptr DGROUP:_on_thread_death,0
	?debug	L 66
	call	far ptr _end_transaction
	?debug	L 67
	int	8
	?debug	L 68
	xor	ax,ax
	jmp	short @3@114
@3@114:
	?debug	L 69
	pop	si
	pop	bp
	ret	
	?debug	C E6046C617374040406
	?debug	E
	?debug	E
_thread_end_trigger	endp
	?debug	L 71
	assume	cs:THREAD_TEXT
_create	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	?debug	C E318000400160200
	?debug	C E31A00000023040400
	?debug	C E319000400161A00
	?debug	C E608737461636B6C656E0A0A0E000F7468726561+
	?debug	C 645F66756E6374696F6E190A0A00046E616D6518+
	?debug	C 0A0600
	mov	si,word ptr [bp+14]
	?debug	B
	?debug	L 73
	call	far ptr _begin_transaction
	?debug	L 74
	mov	byte ptr DGROUP:_in_kernel,1
	?debug	L 75
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	mov	ax,seg _tcb_count
	mov	es,ax
	push	word ptr es:_tcb_count
	push	ds
	mov	ax,offset DGROUP:s@+113
	push	ax
	mov	ax,1
	push	ax
	call	far ptr _lprintf
	add	sp,12
	?debug	L 76
	mov	ax,seg _tcb_count
	mov	es,ax
	cmp	word ptr es:_tcb_count,32
	jl	short @4@114
	?debug	L 77
	push	ds
	mov	ax,offset DGROUP:s@+137
@4@86:
	push	ax
	mov	ax,3
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 78
	jmp	@4@198
@4@114:
	?debug	L 80
	push	si
	call	far ptr _malloc
	pop	cx
	mov	bx,seg _tcb_count
	mov	es,bx
	push	ax
	mov	ax,word ptr es:_tcb_count
	mov	bx,46
	push	dx
	imul	bx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	pop	ax
	mov	word ptr es:_tcb[bx+2],ax
	pop	ax
	mov	word ptr es:_tcb[bx],ax
	?debug	L 81
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	ax,word ptr es:_tcb[bx]
	or	ax,word ptr es:_tcb[bx+2]
	jne	short @4@170
	?debug	L 82
	push	ds
	mov	ax,offset DGROUP:s@+153
	jmp	short @4@86
@4@170:
	?debug	L 85
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	ax,word ptr es:_tcb[bx+2]
	mov	dx,word ptr es:_tcb[bx]
	mov	bx,si
	shl	bx,1
	add	dx,bx
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
	?debug	L 86
	sub	word ptr [bp-4],28
	?debug	L 87
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,word ptr [bp-2]
	mov	es,dx
	xchg	bx,ax
	mov	word ptr es:_tcb[bx+4],ax
	?debug	L 88
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,word ptr [bp-4]
	mov	es,dx
	xchg	bx,ax
	mov	word ptr es:_tcb[bx+6],ax
	?debug	L 89
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	word ptr es:_tcb[bx+8],2
	?debug	L 90
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb+14
	push	dx
	push	ax
	call	far ptr _strcpy
	add	sp,8
	?debug	L 91
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+8]
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+6]
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+4]
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+2]
	push	word ptr es:_tcb[bx]
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb+14
	push	dx
	push	ax
	mov	ax,seg _tcb_count
	mov	es,ax
	push	word ptr es:_tcb_count
	push	ds
	mov	ax,offset DGROUP:s@+193
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,22
	?debug	L 92
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr [bp+12]
	mov	word ptr es:[bx+20],ax
	?debug	L 93
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr [bp+10]
	mov	word ptr es:[bx+18],ax
	?debug	L 94
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+6],ds
	?debug	L 95
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+8],es
	?debug	L 96
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+26],seg _thread_end_trigger
	?debug	L 97
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+24],offset _thread_end_trigger
	?debug	L 98
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+22],512
	?debug	L 99
	mov	ax,seg _tcb_count
	mov	es,ax
	inc	word ptr es:_tcb_count
	?debug	L 100
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	ds
	mov	ax,offset DGROUP:s@+226
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,10
@4@198:
	?debug	L 102
	call	far ptr _print_tcb
	?debug	L 103
	mov	byte ptr DGROUP:_in_kernel,0
	?debug	L 104
	call	far ptr _end_transaction
	?debug	L 105
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	ax,word ptr es:_tcb_count
	jmp	short @4@226
@4@226:
	?debug	L 106
	pop	si
	mov	sp,bp
	pop	bp
	ret	
	?debug	C E2000262700A000264690A000273690A00026473+
	?debug	C 0A000265730A000264780A000263780A00026278+
	?debug	C 0A000261780A000269700A000263730A0005666C+
	?debug	C 6167730A00036F66660A00037365670AC01C0000+
	?debug	C 00
	?debug	C E31C08696E745F726567731C001E
	?debug	C E31B000400161C00
	?debug	C E604726567731B02FCFF046E616D65180A06000F+
	?debug	C 7468726561645F66756E6374696F6E190A0A0008+
	?debug	C 737461636B6C656E0A0C06
	?debug	E
	?debug	E
_create	endp
	?debug	L 108
	assume	cs:THREAD_TEXT
_destroy	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	push	di
	?debug	C E6026964040A0600
	mov	si,word ptr [bp+6]
	?debug	B
	?debug	L 110
	call	far ptr _begin_transaction
	?debug	L 111
	mov	byte ptr DGROUP:_in_kernel,1
	?debug	L 112
	mov	ax,seg _tcb_count
	mov	es,ax
	cmp	word ptr es:_tcb_count,si
	jg	short @5@86
	?debug	L 113
	push	si
	push	ds
	mov	ax,offset DGROUP:s@+256
	push	ax
	mov	ax,4
	push	ax
	call	far ptr _lprintf
	add	sp,8
	?debug	L 114
	jmp	@5@226
@5@86:
	?debug	L 116
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb+14
	push	dx
	push	ax
	push	ds
	mov	ax,offset DGROUP:s@+282
	push	ax
	mov	ax,1
	push	ax
	call	far ptr _lprintf
	add	sp,10
	?debug	L 118
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+2]
	push	word ptr es:_tcb[bx]
	call	far ptr _free
	pop	cx
	pop	cx
	?debug	L 119
	mov	ax,si
	inc	ax
	mov	di,ax
	jmp	short @5@170
@5@114:
	?debug	L 120
	mov	ax,46
	push	ax
	mov	ax,di
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb
	push	dx
	push	ax
	mov	ax,di
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb+65490
	push	dx
	push	ax
	call	far ptr _memcpy
	add	sp,10
	?debug	L 119
	inc	di
@5@170:
	mov	ax,32
	sub	ax,si
	cmp	ax,di
	jg	short @5@114
	?debug	L 122
	mov	ax,seg _tcb_count
	mov	es,ax
	dec	word ptr es:_tcb_count
	?debug	L 123
	push	ds
	mov	ax,offset DGROUP:s@+303
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 124
	call	far ptr _print_tcb
@5@226:
	?debug	L 126
	mov	byte ptr DGROUP:_in_kernel,0
	?debug	L 127
	call	far ptr _end_transaction
	?debug	L 128
	xor	ax,ax
	jmp	short @5@254
@5@254:
	?debug	L 129
	pop	di
	pop	si
	pop	bp
	ret	
	?debug	C E60169040407026964040C06
	?debug	E
	?debug	E
_destroy	endp
	?debug	L 132
	assume	cs:THREAD_TEXT
_pswitch	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	push	di
	?debug	B
	?debug	L 135
	push	ds
	mov	ax,offset DGROUP:s@+322
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 136
	call	far ptr _print_tcb
	?debug	L 137
	push	cs
	call	near ptr _get_last_running_thread_id
	mov	si,ax
	?debug	L 138
	push	cs
	call	near ptr _get_next_running_thread_id
	mov	di,ax
	?debug	L 140
	or	si,si
	jge	@@0
	jmp	@6@86
@@0:
	?debug	L 141
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb+14
	push	dx
	push	ax
	push	si
	push	ds
	mov	ax,offset DGROUP:s@+331
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,12
	?debug	L 142
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	word ptr es:_tcb[bx+8],2
	?debug	L 143
	?debug	L 150
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	ax,word ptr es:_tcb[bx+6]
	sub	ax,sp
	push	ax
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	ax,word ptr es:_tcb[bx+4]
	mov	dx,ss
	sub	ax,dx
	push	ax
	push	sp
	push	ss
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+6]
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	push	word ptr es:_tcb[bx+4]
	push	ds
	mov	ax,offset DGROUP:s@+362
	push	ax
	mov	ax,1
	push	ax
	call	far ptr _lprintf
	add	sp,18
	?debug	L 151
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	word ptr es:_tcb[bx+4],ss
	?debug	L 152
	mov	ax,si
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	word ptr es:_tcb[bx+6],sp
	?debug	L 153
	jmp	short @6@86
@6@86:
	?debug	L 155
	or	di,di
	jl	short @6@142
	?debug	L 156
	mov	ax,di
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	add	ax,offset _tcb+14
	push	dx
	push	ax
	push	di
	push	ds
	mov	ax,offset DGROUP:s@+416
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,12
	?debug	L 157
	mov	ax,di
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	word ptr es:_tcb[bx+8],1
	?debug	L 158
	mov	ax,di
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	ss,word ptr es:_tcb[bx+4]
	?debug	L 159
	mov	ax,di
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,ax
	mov	es,dx
	mov	sp,word ptr es:_tcb[bx+6]
	?debug	L 160
	jmp	short @6@170
@6@142:
	?debug	L 161
	push	ds
	mov	ax,offset DGROUP:s@+444
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 162
	mov	ax,seg _tcb_count
	mov	es,ax
	mov	word ptr es:_tcb_count,0
	?debug	L 163
	call	far ptr _end_transaction
	?debug	L 164
	call	far ptr _cleanup
@6@170:
	?debug	L 166
	call	far ptr _print_tcb
	?debug	L 167
	push	ds
	mov	ax,offset DGROUP:s@+470
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 168
	pop	di
	pop	si
	pop	bp
	ret	
	?debug	C E6136E6578745F72756E6E696E675F7468726561+
	?debug	C 64040407136C6173745F72756E6E696E675F7468+
	?debug	C 72656164040406
	?debug	E
	?debug	E
_pswitch	endp
	?debug	L 170
	assume	cs:THREAD_TEXT
_timeslicehandler	proc	far
	?debug	B
	push	ax
	push	bx
	push	cx
	push	dx
	push	es
	push	ds
	push	si
	push	di
	push	bp
	mov	bp,DGROUP
	mov	ds,bp
	mov	bp,sp
	?debug	B
	?debug	L 171
	pushf	
	call	dword ptr DGROUP:_oldtimeslicehandler
	?debug	L 172
	call	far ptr _DosBusy
	or	ax,ax
	jne	short @7@114
	cmp	byte ptr DGROUP:_in_kernel,0
	jne	short @7@114
	cmp	byte ptr DGROUP:_on_thread_death,0
	je	short @7@142
@7@114:
	?debug	L 173
	jmp	short @7@310
@7@142:
	?debug	L 176
	call	far ptr _begin_transaction
	?debug	L 177
	mov	byte ptr DGROUP:_in_kernel,1
	?debug	L 178
	push	ds
	mov	ax,offset DGROUP:s@+483
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 179
	cmp	byte ptr DGROUP:_schedule_reent,0
	je	short @7@198
	?debug	L 180
	push	ds
	mov	ax,offset DGROUP:s@+504
	push	ax
	mov	ax,2
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 181
	jmp	short @7@282
@7@198:
	?debug	L 183
	mov	byte ptr DGROUP:_schedule_reent,1
	?debug	L 184
	call	far ptr _DosBusy
	or	ax,ax
	jne	short @7@254
	?debug	L 185
	push	cs
	call	near ptr _pswitch
@7@254:
	?debug	L 187
	push	ds
	mov	ax,offset DGROUP:s@+542
	push	ax
	xor	ax,ax
	push	ax
	call	far ptr _lprintf
	add	sp,6
	?debug	L 188
	mov	byte ptr DGROUP:_schedule_reent,0
	?debug	L 189
	mov	byte ptr DGROUP:_in_kernel,0
@7@282:
	?debug	L 191
	call	far ptr _end_transaction
@7@310:
	?debug	L 192
	pop	bp
	pop	di
	pop	si
	pop	ds
	pop	es
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	iret	
	?debug	E
	?debug	E
_timeslicehandler	endp
	?debug	L 194
	assume	cs:THREAD_TEXT
_set_thread_state	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E4000846494E49534845440000000752554E4E49+
	?debug	C 4E4701000005524541445902000007424C4F434B+
	?debug	C 45440300800C494E49545F424C4F434B45440400
	?debug	C E31D0D5448524541445F53544154555302002200+
	?debug	C 0080FF7F
	?debug	C E6096E65775F73746174651D0A0800026964040A+
	?debug	C 0600
	?debug	B
	?debug	L 196
	mov	ax,word ptr [bp+6]
	mov	dx,46
	imul	dx
	mov	dx,seg _tcb
	mov	bx,word ptr [bp+8]
	mov	es,dx
	xchg	bx,ax
	mov	word ptr es:_tcb[bx+8],ax
	?debug	L 197
	pop	bp
	ret	
	?debug	C E6026964040A0600096E65775F73746174651D0A+
	?debug	C 0800
	?debug	E
	?debug	E
_set_thread_state	endp
	?debug	L 199
	assume	cs:THREAD_TEXT
_block_myself	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	B
	?debug	L 201
	mov	ax,3
	push	ax
	push	cs
	call	near ptr _get_last_running_thread_id
	push	ax
	push	cs
	call	near ptr _set_thread_state
	pop	cx
	pop	cx
	?debug	L 202
	pop	bp
	ret	
	?debug	E
	?debug	E
_block_myself	endp
THREAD_TEXT	ends
THREAD5_DATA	segment para public 'FAR_DATA'
_tcb	label	word
	db	1472 dup (0)
	?debug	C E9
THREAD5_DATA	ends
_DATA	segment word public 'DATA'
s@	label	byte
	db	'System idle.'
	db	10
	db	0
	db	'DEADLOCK DETECTED!'
	db	10
	db	0
	db	'Cannot find next ready thread.'
	db	10
	db	0
	db	'Thread #%d end.'
	db	10
	db	0
	db	'Thread end trigger finished.'
	db	10
	db	0
	db	'Creating thread #%d:%s'
	db	10
	db	0
	db	'TCB stack full!'
	db	0
	db	'Thread stack memory allocation failed!'
	db	10
	db	0
	db	'TCB: %d'
	db	9
	db	'%s'
	db	9
	db	'0x%Fp'
	db	9
	db	'0x%Np:0x%Np'
	db	9
	db	'%d'
	db	10
	db	0
	db	'Creating thread %s finished.'
	db	10
	db	0
	db	'Cannot destroy thread #%d'
	db	0
	db	'Destroing thread %s'
	db	10
	db	0
	db	'Thread destroied.'
	db	10
	db	0
	db	'pswitch'
	db	10
	db	0
	db	'Saving state of thread #%d:%s'
	db	10
	db	0
	db	'SS:SP in TCB: %Np:%Np; Current: %Np:%Np; Diff: %d:%d'
	db	10
	db	0
	db	'Switching to thread #%d:%s'
	db	10
	db	0
	db	'All threads have an end.'
	db	10
	db	0
	db	'pswitch end'
	db	10
	db	0
	db	'Time slice reached.'
	db	10
	db	0
	db	'Re-entering scheduler, cancelling...'
	db	10
	db	0
	db	'Time slice handler finished.'
	db	10
	db	0
_DATA	ends
THREAD_TEXT	segment byte public 'CODE'
THREAD_TEXT	ends
	public	_on_thread_death
	public	_schedule_reent
	extrn	_end_transaction:far
	extrn	_begin_transaction:far
	extrn	_DosBusy:far
	extrn	_cleanup:far
	extrn	_oldtimeslicehandler:dword
	extrn	_lprintf:far
	extrn	_print_tcb:far
	public	_in_kernel
	public	_tcb_count
	public	_tcb
	public	_pswitch
	public	_block_myself
	public	_set_thread_state
	public	_get_next_running_thread_id
	public	_get_last_running_thread_id
	public	_timeslicehandler
	public	_thread_end_trigger
	public	_destroy
	public	_create
	extrn	_strcpy:far
	extrn	_memcpy:far
	extrn	_malloc:far
	extrn	_free:far
_s@	equ	s@
	?debug	C EA010C
	?debug	C EC105F6F6E5F7468726561645F64656174680200
	?debug	C EC0F5F7363686564756C655F7265656E740200
	?debug	C E31F00000023010400
	?debug	C EB105F656E645F7472616E73616374696F6E1F
	?debug	C E32000000023010400
	?debug	C EB125F626567696E5F7472616E73616374696F6E+
	?debug	C 20
	?debug	C E32100000023040400
	?debug	C EB085F446F734275737921
	?debug	C E32200000023010400
	?debug	C EB085F636C65616E757022
	?debug	C E32400000023010700
	?debug	C E323000400162400
	?debug	C EB145F6F6C6474696D65736C69636568616E646C+
	?debug	C 657223
	?debug	C E32500000023040401
	?debug	C EB085F6C7072696E746625
	?debug	C E32600000023010400
	?debug	C EB0A5F7072696E745F74636226
	?debug	C EC0A5F696E5F6B65726E656C0200
	?debug	C EC0A5F7463625F636F756E740400
	?debug	C E329000400160100
	?debug	C E32A000400162800
	?debug	C E32B0020001A02
	?debug	C E20005737461636B29000273730A000273700A00+
	?debug	C 0573746174651D00046E6578742A00046E616D65+
	?debug	C 2BC02E000000
	?debug	C E328035443422E001E
	?debug	C E32700C0051A28
	?debug	C EC045F7463622700
	?debug	C E32C00000023010400
	?debug	C EC085F707377697463682C18
	?debug	C E32D00000023010400
	?debug	C EC0D5F626C6F636B5F6D7973656C662D18
	?debug	C E32E00000023010400
	?debug	C EC115F7365745F7468726561645F73746174652E+
	?debug	C 18
	?debug	C E32F00000023040400
	?debug	C EC1B5F6765745F6E6578745F72756E6E696E675F+
	?debug	C 7468726561645F69642F18
	?debug	C E33000000023040400
	?debug	C EC1B5F6765745F6C6173745F72756E6E696E675F+
	?debug	C 7468726561645F69643018
	?debug	C E33100000023010700
	?debug	C EC115F74696D65736C69636568616E646C657231+
	?debug	C 98
	?debug	C E33200000023040400
	?debug	C EC135F7468726561645F656E645F747269676765+
	?debug	C 723218
	?debug	C E33300000023040400
	?debug	C EC085F64657374726F793318
	?debug	C E33400000023040400
	?debug	C EC075F6372656174653418
	?debug	C E33500000023180400
	?debug	C EB075F73747263707935
	?debug	C E33600000023290400
	?debug	C EB075F6D656D63707936
	?debug	C E33700000023290400
	?debug	C EB075F6D616C6C6F6337
	?debug	C E33800000023010400
	?debug	C EB055F6672656538
	?debug	C E60466756E63190608696E745F726567731C0605+
	?debug	C 735F54434228060D5448524541445F5354415455+
	?debug	C 531D060666706F735F7406060970747264696666+
	?debug	C 5F7406060777636861725F7402060673697A655F+
	?debug	C 740A0608696E745F726567731C07035443422807+
	?debug	C 0D5448524541445F5354415455531D07
	end
