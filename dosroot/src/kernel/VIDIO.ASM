; vidio.asm - _wtty, _vidint

VID	equ	10h			; video interrupt
WTTY 	equ	0EH				; TTY write subfunction
FORE	equ	7			; foreground color
ADP	equ	0			; active display page

_FARDATA   SEGMENT WORD PUBLIC 'FAR_DATA'

; dummy
     
_FARDATA   ENDS
	
	public	_wtty
	public	_vidint

_TEXT   SEGMENT WORD PUBLIC 'CODE'
        ASSUME CS:_TEXT, DS:_FARDATA
	
        extrn   pcxflag:word

;--------------------------------------------------------------------------
; _wtty  --  put a character to the video display using WTTY call
;--------------------------------------------------------------------------
; void wtty(ch)
; char ch;
_wtty	proc	far
	push	bp			; follows C calling conventions
	mov	bp,sp
	pushf				; push the flags
	push	si			; push registers since . . .
	push	di			; . . . INT VID clobbers these
        cli                             ; disable interrupts
        xor     ax,ax                   ; to defer rescheduling, ...
        xchg    ax,cs:pcxflag           ; ... get and clear pcxflag ...
        push    ax
	mov	al,[bp+6]		; character to write
	mov	ah,WTTY			; TTY write subcommand
	mov	bl,FORE			; foreground color
	mov	bh,ADP			; display page
	int	VID			; call the video function
        cli                             ; is this needed ?
        pop     cs:pcxflag              ; restore pcxflag
        pop     di
	pop	si			; restore registers
	popf
	pop	bp
	ret
_wtty	endp

;-------------------------------------------------------------------------
; vidint  --  general access to VID interrupts; returns flags
;-------------------------------------------------------------------------
; int vidint(r)
; union REGS *r;
_vidint	proc	far
	push	bp
	mov	bp,sp			; follows C calling conventions
	pushf				; save flags
	push	si
	push	di			; save registers
        cli                             ; disable interrupts
        xor     ax,ax                   ; to defer rescheduling, ...
        xchg    ax,cs:pcxflag           ; ... get and clear pcxflag ...
        push    ax
        mov     si,[bp+6]               ; get pointer to register structure
	mov	es,[bp+8]
	mov	ax,es:[si]
	mov	bx,es:[si+2]
	mov	cx,es:[si+4]
	mov	dx,es:[si+6]		; set up registers for call
        push    si
	int	VID			; call the VID BIOS interrupt
        cli                             ; is this needed ?
        pop     si                      ; recover register pointer
        pushf                           ; save flags for return value
	mov	es:[si],ax
	mov	es:[si+2],bx
	mov	es:[si+4],cx
	mov	es:[si+6],dx		; return registers
	pop	ax			; return flags value
        pop     cs:pcxflag              ; restore pcxflag
        pop     di
	pop	si			; restore registers
	popf				; and the flags
	pop	bp
	ret
_vidint	endp

_TEXT ENDS
	
	end
