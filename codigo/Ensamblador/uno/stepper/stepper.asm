; Copyright 2015 Marius Ghita
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.


; Everything after a semicolon is a comment

; We specify the Atmel microprocessor. The Uno uses ATmega328P,
; older versions might use ATmega328
.device ATmega328P

; These are all constant definitions taken from m328Pdef.inc
; and we will go in more detail of what they are, when they
; are used
.equ PORTB = 0x05
.equ PORTD = 0x0b
.equ PIND  = 0x09
.equ DDRB  = 0x04
.equ DDRD  = 0x0a
.equ SREG  = 0x3f
.equ SREG_Z	= 1	; Zero Flag

; At ORiGin 0x0000 we "hook" in our call to our programm main
; we do not write our program here, as of why, we will go over
; that later
.org 0x0000
    jmp main

main:
; DDRB maps over pins 8-13.
; We set[1] pin 10 and 12 (starting DDRB pin is 8):
;  - 8 + 2 = 10
;  - 8 + 4 = 12
; [1] Set means we assign the bit value to 1 = output
sbi DDRB, 2
sbi DDRB, 4

; DDRD maps over pins 0-7
; We clear the 2nd bit: 0 + 2 = 2
; Clear means we assign the bit value to 0 = input
cbi DDRD, 2
cbi DDRD, 3
; just set register r20 to 0
clr r20

check_press_loop:
    ; if input on pin 2, skip next instruction
    sbis PIND, 2
    sbis PIND, 3  ; this is the one we will skip
    rjmp pasos
    rjmp cambio_dir

pasos:
    call paso
    call retraso
    call paso
    call retraso
    rjmp check_press_loop

cambio_dir:
    sbis PORTB, 4
    rjmp atras
    rjmp adelante

adelante:
    sbi PORTB, 4
    rjmp check_press_loop

atras:
    cbi PORTB, 4
    rjmp check_press_loop

paso:
    sbi PORTB, 2
    cbi PORTB, 2
    ret

retraso:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    ret

retraso_mejor:
    ldi r20, 127
    rjmp retraso_loop

retraso_loop:
    tst r20
    sbrs SREG, SREG_Z
    ret
    dec r20
    rjmp retraso_loop

; NOTE a program must never terminate. If you're not processing something
; in a loop like this program did, you can just add an infinite loop at
; the end, like
;
; loop:
;      rjmp loop
