    .include "DelayMacro.inc"
    .cseg
    .org    0x00
    .def    mask = r16      ; mask register
    .def    ledR = r17      ; led register
    ;.def    loopCt = r18    ; delay loop count

    ; initialize stack pointer to RAMEND
    ldi     r16, LOW(RAMEND); store lower bits of last RAM address
    out     SPL, r16        ; stack pointer
    ldi     r16, HIGH(RAMEND);
    out     SPH, r16

    clr     ledR
    ldi     mask, (1 << PIND0);
    out     DDRD, mask

start:
    eor     ledR, mask
    out     PORTD, ledR

    ;ldi     loopCt, 50      ; initialize delay multiple for 0.5 sec
    ;rcall   delay10ms       ; call delay subroutine

    delayms 500;

    rjmp    start

    .include "delay10ms.asm"
