/*
Bit 0: Carry Flag
Bit 1: Zero Flag
Bit 2: Negative Flag
Bit 3: Two's Complement Overflow Flag
Bit 4: Sign Bit
Bit 5: Half Carry Flag
Bit 6: Bit Copy Storage
Bit 7: Global Interrupt Enable
*/

        .include "m328pdef.inc"
        .cseg
	    .org	0x00

;The Carry Flag (C)
        ;ldi	r16,0xFF	    ; load r16 with 0xFF
	    ;ldi	r17,0xFF	    ; load r17 with 0xFF
	    ;add	r16,r17		    ; carry will be set

        ;ldi     r16,0x01       ; load r16 with 0x01
        ;ldi     r17,0x02       ; load r17 with 0x02
        ;add     r16,r17        ; carry will not be set

        ;Shift
        ;ldi	r16,0b10000000	; load 0b10000000 into r16
	    ;lsl	r16		        ; carry will be set

;The Zero Flag (Z)
        ;ldi	r16,0x03	    ; load r16 with 0x01
	    ;dec	r16		        ; zero flag not set (r16 = 0x02)
	    ;dec	r16		        ; zero flag not set (r16 = 0x01)
	    ;dec	r16		        ; zero flag set (r16 = 0x00)

;The Negative Flag (N)
        ;ldi	r16,1		    ; load r16 with 0x01
	    ;subi	r16,2		    ; negative flag set (result = -1 or 255)

;The Two's Complement Overflow Flag (V)
        ;ldi	r16,-128	    ; load r16 with -128
	    ;dec	r16		        ; two's complement overflow set

	    ;ldi	r17,127		    ; load r17 with 127
	    ;inc	r17		        ; two's complement overflow set

;The Sign Flag (S)
        ;ldi	r16,0x88	    ; load r16 with 0x88 (-120)
        ;ldi	r17,0x0A	    ; load r17 with 0x0A (10)
        ;sub	r16,r17		    ; subtract r17 from r16 (result = 0x7E = 126)

;The Half Carry Flag (H)
        ldi	r16,0x0F	; load r16 with 0x0F
	    inc	r16 		; increment r16 (half carry set)
        
;Bit Copy Storage (T)
        set			; set T flag
	    clt			; clear T flag

;Global Interrupt Enable (I)
        sei			; enable interrupts
	    cli			; disable interrupts
start: rjmp start
