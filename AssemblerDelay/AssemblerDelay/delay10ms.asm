;**************************************************************
;* subroutine: delay10ms
;*
;* inputs: r18 - sets multiple of 10ms for delay
;*
;* registers modified: r18, r24, r25
;**************************************************************

    .def    oLoopR = r18    ; outer loop register
    .def    iLoopRl = r24   ; inner loop register low
    .def    iLoopRh = r25   ; inner loop register high

    .equ    iVal = 39998    ; inner loop value

delay10ms:
    ldi     iLoopRl, LOW(iVal); initialize inner loop count in inner
    ldi     iLoopRh, HIGH(iVal); loop hight and low registers

iLoop:
    sbiw    iLoopRl, 1      ; decrement inner loop registers
    brne    iLoop           ; branch to iLoop if iLoop register != 0

    dec     oLoopR          ; decrement outer loop
    brne    delay10ms       ; branch to outer loop if outer loop register != 0

    nop                     ; no operation

    ret                     ; return from subroutine
