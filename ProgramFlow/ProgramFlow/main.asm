
/*Mnemonic	Description
cp	compare
cpc	compare with carry
cpi	compare with immediate
tst	test for zero or minus
*/
;Conditional Branching
/*Mnemonic	Description
brbs	branch if status flag set
brbc	branch if status flag cleared
breq	branch if equal
brne	branch if not equal
brcs	branch if carry set
brcc	branch if carry cleared
brsh	branch if same or higher
brlo	branch if lower
brmi	branch if minus
brpl	branch if plus
brge	branch if greater or equal, signed
brlt	branch if less than, signed
brhs	branch if half carry set
brhc	branch if half carry cleared
brts	branch if t flag set
brts	branch if t flag cleared
brvs	branch if overflow flag set
brvc	branch if overflow flag cleared
brie	branch if interrupt enabled
brid	branch if interrupt disabled*/

.CSEG
;Compare 2 registers
;LDI	r16,0x01		; load r16 with 0x01
;LDI	r17,0x02		; load r17 with 0x02
;CP	r16,r17			; compare r16 and r17

;Compare 16-bit numbers
;LDI	r16,0x01		; load r16 with 0x01
;LDI	r17,0xAA		; load r17 with 0xAA
;LDI	r18,0x02		; load r18 with 0x02
;LDI	r19,0xAA		; load r19 with 0xAA
;CP	r16,r18			; compare r16 and r18
;CPC	r17,r19			; compare r19 and r17 with carry

;Check if a number is negative
;LDI	r16,0x80		; load r16 with 0x80
;TST	r16			; test r16

;While Loop
;LDI     r16, 98;
;loop:	
;INC     r16
;CPI     r16,100		; compare r16 and 100
;BRSH	next			; branch if r16 >= 100
;RJMP	loop			; repeat loop

;next:

;Do While Loop
;LDI     r16,2;
;loop:	
;DEC     r16;
;CPI     r16,0			; check if r16 is zero
;BRNE	loop			; repeat loop if r16 is not 0

;For Loop
;CLR	r16			; clear r16
;loop:	
;CPI	r16,11			; compare r16 to 11
;BREQ	next			; break loop if equal
;INC	    r16			; increment r16
;RJMP	loop			; repeat loop

;next:

;"Skip" Branching
/*Mnemonic	Description
sbrc	skip if bit in register cleared
sbrs	skip if bit in register set
sbic	skip if bit in i/o register cleared
sbis	skip if bit in i/o register set*/

;LDI r16,8;
;MOV r0,r16;
;loop:					; loop code
;SBRS	r0,3			; break loop if bit 3 of r0 is 1
;RJMP	loop

LDI     r16,8
OUT     PORTB,r16
loop:				; loop code
SBIC	PINB,3			; break loop when PINB3 is 0
RJMP	loop			; repeat loop

start: RJMP start