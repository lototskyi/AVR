;**************************************************************
;* macro: delayms
;*
;* description: creates a delay for the specified number of
;*		milliseconds
;*
;* inputs: @0 - number of milliseconds to delay for
;*
;* registers modified: none
;**************************************************************
.macro delayms

push r18
push r24
push r25

ldi r18, @0/10
rcall delay10ms

pop r25
pop r24
pop r18

.endmacro
