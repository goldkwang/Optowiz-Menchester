/*******************************************************************************
* Copyright (C) 2018 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
*/

#define MAXQ20

#ifndef MAXQ20
#error MAXQ20 and MAXQ68 must be defined accordingly
#endif

;
; Float Math Library for IAR's EWMAXQ tools
;
; PUBLIC  ?F_ADD_HW
; PUBLIC  ?F_SUB_HW
; PUBLIC  ?F_MUL_HW
; PUBLIC  ?F_DIV_HW
;
; implements IEEE 754 standard with rounding to nearest


#define MCNT  M\1[0]
#define MA    M\1[1]
#define MB    M\1[2]
#define MC2   M\1[3]
#define MC1   M\1[4]
#define MC0   M\1[5]

; MCNT control bits
#define SUS   001h
#define MMAC  002h
#define MSUB  004h
#define OPCS  008h
#define SQU   010h
#define CLD   020h
#define MCW   040h



;***************************************************************************** 
;; for float addition ?F_ADD_HW:
;; for float subtraction ?F_SUB_HW:
 ; input parameter 1 A[1] and A[0]
 ;   one float value high word in A[1] and low word in A[0]
 ; input parameter 2 A[3] and A[2]
 ;   one float value high word in A[3] and low word in A[2]
 ; the output result
 ; output sum A[1] and A[0]
 ;   one float value high word in A[1] and low word in A[0]
;*****************************************************************************
 MODULE  ?F_ADD_HW
  PUBLIC ?F_ADD_HW, ?F_SUB_HW
  EXTERN Q20_Float_Init, Q20_Float_Wrap,Q20_Float_Final
  EXTERN set_zero, set_inf, set_ind
  RSEG CODE:CODE:REORDER:NOROOT

?F_SUB_HW:
;;Q20_Subtract_Float:

; Algorithm description
; 1. Check if arg1==NaN or arg2==NaN, then return special (NaN).
; 2. Check if arg1==INF or ==0, or arg2==INF, or ==0;
;     then flip the sign of arg2 and return special (INF or 0).
; 3. Flip the sign of arg2, then do as sum arg1+(-arg2).

  call Q20_Float_Init
  ret   S ; return if NaN
  move  AP,#7 ; flip sign bit A[7].1
  xor   #2
  sjump NC,fa_b ; jump if not 0 or INF
  move  AP,#3   ; flip sign bit A[3].15
  xor   #8000h
  move  AP,#5
  sjump fa_a  

?F_ADD_HW:
;;Q20_Add_Float:

; Algorithm description
; 1. Check if arg1==NaN or arg2==NaN, then return special (NaN).
; 2. Check if arg1==INF or ==0, or arg2==INF, or ==0;
;     then return special (INF or 0).
; 3. Unpack arg1 to (Sgn1,Exp1,Mnt1), unpack arg2 to (Sgn2,Exp2,Mnt2).
; 4. Align mantissas by shifting one of them (with lesser Exp) to the right.
;     No shift necessary if abs(Exp1-Exp2)>24.
; 5. Add aligned mantissas (Mnt0=Mnt1+Mnt2).
; 6  Normalize the sum, i.e. extract the sign (Sgn0), make Mnt0 positive with
;     MSB=1, adjust Exp0.
; 6. Round the sum (Mnt0) at 24-th bit. 
; 7. Pack and return Sum=(Sgn0,Exp0,Mnt0)

  call Q20_Float_Init
  sjump NC,fa_b ; jump if not 0 or INF
  ret   S ; return special (NaN)

fa_a:
    ; one or both arg1 and arg2 =INF or =0.
    ; return special (INF or 0)
    ; inf=81, zero=80, nn=00.
  cmp   #81h
  move  C,A[4].0
  sjump E,inf2
  ret   C
  sjump Z,ret2
  move  C,A[4].7
  ret   NC
  move  AP,#1 
  and   A[3]
  ret
inf2:
  sjump NC,ret2
  move  AP,#1
  xor   A[3]
  jump  S,set_ind
ret2:
  move  A[0],A[2]
  move  A[1],A[3]
ret1:
  ret

fa_b:
    ; store tmp GRH=Exp1, GRL=5 (will be AP)
  move  PFX[0],A[4]
  move  GR,#5
    ; Exp1 == Exp2 ?
  move  AP,#4
  cmp   A[6]  ; set E=1 if Exp1==Exp2
  sjump E,fa_sign ; jump if Exp1==Exp2
    ; Exp1 < Exp2 ?
  sub   A[6]
  sjump S,fa_c  ; jump if Exp1<Exp2

      ; store LC[0] = Exp1-Exp2 (shift count)
    move  LC[0],A[4]  
      ; Exp1-Exp2 < 25 ?
    sub   #25
    sjump S,fa_sign ; jump if <25
      ; arg2 is too small, return arg1
    move  A[4],GRH  ; restore A[4]=Exp1
    jump  Q20_Float_Final ; pack arg1 and exit

fa_c:
      ; store tmp GRH=Exp2, GRL=1 (will be AP)
    move  PFX[0],A[6]
    move  GR,#1
    neg
      ; store LC[0] = Exp2-Exp1 (shift count)
    move  LC[0],A[4]
      ; Exp2-Exp1 < 25 ?
    sub   #25
    sjump S,fa_sign ; jump if <25
      ; arg1 is too small, return arg2
    move  A[0],A[2] ; lsb
    move  A[1],A[3] ; msb
    move  A[4],A[6] ; exp
    move  A[5],A[7] ; sign
    jump  Q20_Float_Final ; pack and exit

fa_sign:
    ; make Mnt2 signed
  move  C,A[7].1  ; Sgn2 bit
  sjump NC,f3_d
    move  APC,#81h
    move  AP,#2
    cpl
    cpl
    add   #1
    addc  #0
f3_d:
  
    ; make Mnt1 signed
  move  C,A[5].1  ; Sgn1 bit
  sjump NC,f3_e
    move  APC,#81h
    cpl
    cpl
    add   #1
    addc  #0
f3_e:
    ; align Mnt1=A[1:0:3:2]
    ; align Mnt2=A[5:4:7:6]
    ; fill lsb with 0s
  move  A[4],A[2]
  move  A[5],A[3]
  move  A[2],#0
  move  A[3],#0
  move  A[6],#0
  move  A[7],#0

    ; skip shift if Exp1==Exp2
  sjump E,fa_add

    ; Align (shift to the right)
    ; LC[0]=shift count, GRL=AP (01 or 05)
  move  APC,#42h  ; auto-dec4
  move  AP,GRL
f3_f:
  sra ; preserve sign bit
  rrc
  rrc
  rrc
  djnz  LC[0],f3_f

fa_add:
    ; add aligned mantissas, sum in A[1:0:3:2]
  move  APC,#2
  move  AP,#2
  add   A[6]
  addc  A[7]
  addc  A[4]
  addc  A[5]
      ; check if sum==0
    move  AP,#1
    sjump NZ,fa_g
    move  AP,#0
    sjump NZ,fa_g
    move  AP,#3
    ret   Z ; return zero
fa_g:
    ; store sign bit Sgn0 at A[5].1
  move  AP,#1
  move  C,acc.15
  move  A[5],PSF
    ; store Exp0 at A[4]
  move  A[4],GRH
    ; make Mnt0 positive
  sjump NC,fa_h
    move  AP,#2
    cpl
    cpl
    cpl
    cpl
    add   #1
    addc  #0
    addc  #0
    addc  #0
fa_h:
    ; check if extra bit on the left appeared
  move  AP,#1
  move  C,acc.8
  sjump NC,fa_i
      ; shift right (>>1), increment Exp0
    move  APC,#42h
    sr
    rrc
    rrc
    rrc
    move  AP,#4
    add   #1
fa_i:
    ; check if normalized (msb=1)
  move  C,A[1].7
  jump  C,Q20_Float_Wrap  ; round, pack and exit

      ; shift left (<<1), decrement Exp0
    move  APC,#2
    move  AP,#2
    sla
    rlc
    rlc
    rlc
    move  AP,#4
    sub   #1
    sjump fa_i

 ENDMOD


;***************************************************************************** 
;; for float multiplication ?F_MUL_HW:
 ; input parameter 1 A[1] and A[0]
 ;   one float value high word in A[1] and low word in A[0]
 ; input parameter 2 A[3] and A[2]
 ;   one float value high word in A[3] and low word in A[2]
 ; the output result
 ; output product A[1] and A[0]
 ;   one float value high word in A[1] and low word in A[0]
;*****************************************************************************
 MODULE  ?F_MUL_HW
  EXTERN Q20_Float_Init, Q20_Float_Wrap
  EXTERN set_zero, set_inf, set_ind

?float_mul  MACRO
  PUBLIC ?F_MUL_HWM\1
?F_MUL_HWM\1:

; Algorithm description
; 1. Check if arg1==NaN or arg2==NaN, then return special (NaN).
; 2. Check if arg1==INF or ==0, or arg2==INF, or ==0;
;     then return special (INF or 0).
; 3. Unpack arg1 to (Sgn1,Exp1,Mnt1), unpack arg2 to (Sgn2,Exp2,Mnt2).
; 4. Calculate sign Sgn0=Sgn1^Sgn2, Exp0=Exp1+Exp2-127.
; 5. Calculate mantissa Mnt0=Mnt1*Mnt2
; 6  Normalize the result, i.e. make MSB=1, adjust Exp0.
; 6. Round the result (Mnt0) at 24-th bit. 
; 7. Pack and return res=(Sgn0,Exp0,Mnt0)

  call Q20_Float_Init
  sjump NC,fm_b\1 ; jump if not 0 or INF
  ret   S ; return special (NaN)

    ; one or both arg1, arg2 =INF or =0.
    ; return special (INF or 0)
    ; inf=81, zero=80, nn=00
  xor   A[4]
  cmp   #1
  jump  E,set_ind
  cmp   #80h
  jump  E,set_zero
  move  AP,#4
  cmp   #80h
  jump  E,set_zero
  jump  set_inf


fm_b\1:
    ; calculate Sgn0 in A[5].1
  move  AP,#5
  xor   A[7]
    ; calculate Exp0 in A[4]
  move  AP,#4
  add   A[6]
  sub   #(127-1)

    ; save interrupt status and disable interrupts
#if MAXQ68
  push  IC
#else
  ;move  @--DP[1],IC
  MOVE    @--DP[1],  IMR
#endif
  ;move  IC.0,0
  Move IMR,    #4

    ; multiply mantissas A[1:0]*A[3:2]
  move  GR,A[2]
  move  GRL,A[3]
  move  A[3],GRS
  move  GR,#0
  move  GRL,A[2]
  move  A[2],GRS
  move  MCNT,#(SUS+MMAC+CLD)
  move  MA,A[0]
  move  MB,A[2]
  move  MA,A[1] ; nop
  move  A[2],MC0
  move  MC0,MC1
  move  MC1,#0
  move  MB,MB
  move  MA,A[0]
  move  MB,A[3]
  move  MA,A[1] ; nop
  move  A[3],MC0
  move  MC0,MC1
  move  MC1,MC2
  move  MB,MB
  move  AP,#2 ; nop
  move  A[0],MC0
  move  A[1],MC1
  ; now product in A[1:0,3:2]
  
    ; restore interrupt status
#if MAXQ68
  pop   IC
#else
  move  DP[1],DP[1]
  ;move  IC,@DP[1]++
  Move IMR,    @DP[1]++
#endif

    ; check if normalized (msb=1)
  move  C,A[1].7
  jump  C,Q20_Float_Wrap
    ; shift left (<<1), decrement exp0
  move  APC,#2
  sla
  rlc
  rlc
  rlc
  move  AP,#4
  sub   #1
  jump  Q20_Float_Wrap  ; round, pack and exit
  ENDM

  RSEG CODE:CODE:REORDER:NOROOT
  ?float_mul 1
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_mul 2
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_mul 3
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_mul 5

 ENDMOD


;*****************************************************************************
;; for float division ?F_DIV_HW:
 ; input parameter 1 A[1] and A[0]
 ;   one float value high word in A[1] and low word in A[0]
 ; input parameter 2 A[3] and A[2]
 ;   one float value high word in A[3] and low word in A[2]
 ; the output result
 ; output quotient A[1] and A[0]
 ;   one float value high word in A[1] and low word in A[0]
;*****************************************************************************
 MODULE  ?F_DIV_HW
  EXTERN Q20_DivideRaw_sub, Q20_DivideRaw_add
  EXTERN Q20_Float_Init, Q20_Float_Wrap
  EXTERN set_zero, set_inf, set_ind

?float_div  MACRO
  PUBLIC ?F_DIV_HWM\1
?F_DIV_HWM\1:

; Algorithm description
; 1. Check if arg1==NaN or arg2==NaN, then return special (NaN).
; 2. Check if arg1==INF or ==0, or arg2==INF, or ==0;
;     then return special (INF or 0).
; 3. Unpack arg1 to (Sgn1,Exp1,Mnt1), unpack arg2 to (Sgn2,Exp2,Mnt2).
; 4. Calculate sign Sgn0=Sgn1^Sgn2, Exp0=Exp1-Exp2+127.
; 5. Calculate mantissa Mnt0=Mnt1/Mnt2
; 6  Normalize the result, i.e. make MSB=1, adjust Exp0.
; 6. Round the result (Mnt0) at 24-th bit. 
; 7. Pack and return res=(Sgn0,Exp0,Mnt0)

  call  Q20_Float_Init
  sjump NC,fd_b\1 ; jump if not 0 or INF
  ret   S ; return special (NaN)

    ; one or both arg1, arg2 =INF or =0.
    ; return special (INF or 0)
    ; inf=81, zero=80, nn=00
  cmp   A[4]
  jump  E,set_ind
  cmp   #80h
  jump  E,set_inf
  move  C,A[4].0
  jump  C,set_inf
  jump  set_zero

fd_b\1:
    ; calculate Sgn0 in PSF.3
  move  AP,#5
  xor   A[7]
  sla2
  move  PSF,A[5]
    ; calculate Exp0 in A[4]
  move  AP,#4
  sub   A[6]
  add   #(127)

    ; divide mantissas A[1:0]/A[3:2]

    ; pre-shift B<<8
  move  GR,A[2]
  move  GRL,A[3]
  move  A[3],GRS
  move  GR,#0
  move  GRL,A[2]
  move  A[2],GRS

    ; initialize iterations
  move  A[6],#0
  move  A[7],#7687h   ; init with 1.463-B/2
  move  APC,#1
  move  AP,#6
  sub   A[2]
  subb  A[3]
  move  LC[0],#3      ; iteration count

    ; save interrupt status and disable interrupts
#if MAXQ68
  push  IC
#else
  ;move  @--DP[1],IC
  MOVE    @--DP[1],  IMR                        ;Save of the SW stack as shown below example 
#endif
  ;move  IC.0,0
  Move IMR,    #4

fd_c\1:
    ; iterate X=X*(2-B*X)
    ; X=A[7:6], B=A[3:2]
  move  MCNT,#(SUS+MMAC+MSUB+CLD)
  move  MA,A[3]
  move  MB,A[6]
  move  MA,A[2]
  move  MB,A[7]
  move  MA,A[3] ; nop
  move  MC0,MC1
  move  GR,MC2
  move  MC1,GRXL
  move  MB,MB
  nop
  move  GR,MC0
  move  A[5],MC1

  move  MCNT,#(SUS+MMAC+CLD)
  move  MA,A[5]
  move  MB,A[6]
  move  MA,GR
  move  MB,A[7]
  move  MA,A[5] ; nop
  move  MC0,MC1
  move  MC1,MC2
  move  MB,MB
  nop
  move  A[6],MC0
  move  A[7],MC1

  sla
  rlc
  djnz  LC[0],fd_c\1
    ; now A[7:6] approx= 1/B

    ; get quotient as Q=A*(1/B)
    ; A=A[1:0], (1/B)=A[7:6]
  move  MCNT,#(SUS+MMAC+CLD)
  move  MA,A[0]
  move  MB,A[6]
  move  MA,A[1] ; nop
  move  MC0,MC1
  move  MC1,#0
  move  MB,A[6]
  move  MA,A[0]
  move  MB,A[7]
  move  MA,A[1] ; nop
  move  A[5],MC0
  move  MC0,MC1
  move  MC1,MC2
  move  MB,MB
  nop
  move  A[6],MC0
  move  A[7],MC1
    ; now A[7:6]=Q=quotient

    ; restore interrupt status
#if MAXQ68
  pop   IC
#else
  move  DP[1],DP[1]
  ;move  IC,@DP[1]++
  Move IMR,    @DP[1]++
#endif

    ; make msb=1
  move   C,A[7].7
  cpl    C
  sjump  NC,fd_d\1

      ; re-scale Q,A, dec Exp0
    move  AP,#0
    sla
    rlc
    move  AP,#4
    sub   #1
    sla
    move  AP,#6
    rlc
    rlc
fd_d\1:

    ; scale Q up (<<1)
  rlc
  rlc

    ; save interrupt status and disable interrupts
#if MAXQ68
  push  IC
#else
  ;move  @--DP[1],IC
  MOVE    @--DP[1],  IMR
#endif
  ;move  IC.0,0
  Move IMR,    #4 

    ; calculate remainder R=A-B*Q
    ; R=A[1:0,5:4]
  move  GR,A[4]
  move  A[4],#0
  move  A[5],#0
  move  AP,#4
  move  MCNT,#(SUS+MMAC+CLD)
  move  MA,A[6]
  move  MB,A[2]
  move  MA,A[7] ;  nop
  sub   MC0
  move  MC0,MC1
  move  MC1,#0
  move  MB,MB
  move  MA,A[6]
  move  MB,A[3]
  move  MA,A[7] ; nop
  subb  MC0
  move  MC0,MC1
  move  MC1,MC2
  move  MB,MB
  move  AP,#0 ; nop

  subb  MC0
  subb  MC1
    ; now R=A[1:0,5:4]

    ; restore interrupt status
#if MAXQ68
  pop   IC
#else
  move  DP[1],DP[1]
 ; move  IC,@DP[1]++
 Move IMR,    @DP[1]++
#endif

    ; make sure R>0
  sjump NC,fd_g\1

      ; R<0, decrement Q and exit
    move  AP,#6
    sub   #2
    subb  #0
    sjump fd_f\1
fd_g\1:
    ; calculate rounding:
    ; rounding up if R>B/2
    ; rounding eq if R=B/2
    ; rounding dn if R<B/2
    ; R=A[1:0,5:4] (scaled up 1bit)
    ; B/2=A[3:2]
  move  AP,#4
  sub   A[2]
  subb  A[3]
  move  AP,#0
  subb  #0
  sjump C,fd_0\1
  move  AP,#4
  sjump NZ,fd_f\1
  move  AP,#5
  sjump NZ,fd_f\1
    ; rounding eq
  move  A[3],#08000h
  move  A[2],#0
  sjump fd_e\1
fd_f\1:
    ; rounding up
  move  A[3],#0FFFFh
  sjump fd_e\1
fd_0\1:
    ; rounding dn
  move  A[3],#07FFFh
fd_e\1:
    ; scale Q back (>>1)
  move  AP,#7
  sr
  rrc
  move  A[0],A[6]
  move  A[1],A[7]
  move  A[4],GR
  move  C,PSF.3
  move  A[5],PSF
  jump  Q20_Float_Wrap  ; round, pack and exit
  ENDM
  
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_div 1
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_div 2
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_div 3
  RSEG CODE:CODE:REORDER:NOROOT
  ?float_div 5

 ENDMOD


;*****************************************************************************
;; Common floating-point routines
; These routines are shared by all float math (add, sub, mul, and div)
;*****************************************************************************
 MODULE  Float_Common
  PUBLIC Q20_Float_Init,Q20_Float_Wrap,Q20_Float_Final
  PUBLIC set_zero, set_inf, set_ind
  RSEG CODE:CODE:REORDER:NOROOT

  ; set A[1:0]=0 with sign=(A[1].15 ^ A[3].15)
set_zero:
  move  GR,#0
  sjump mix_sign

  ; set A[1:0]=INF with sign=(A[1].15 ^ A[3].15)
set_inf:
  move  GR,#0FFh
mix_sign:
  move  AP,#1
  xor   A[3]
  sla
set_sign:
  move  A[0],#0
  move  A[1],GRS
  rrc
  ret

  ; set A[1:0]=IND (invalid operation)
set_ind:
  move  A[0],#0
  move  A[1],#0FFC0h
  ret



  ; This subroutine will
  ; 1. check if A[1:0]=NaN,INF,0, or regular number;
  ; 2. check if A[3:2]=NaN,INF,0, or regular number;
  ; 3. If one of the above is detected NaN,
  ;     calculate the output NaN in A[1:0] and return with S=1.
  ; 4. If one of arguments is detected INF or 0,
  ;     calculate indicators A[4],A[5] and return with C=1.
  ; 5. If both arguments are detected regular numbers, unpack them:
  ;     Sgn1=A[5].1, Exp1=A[4], Mnt1=A[1:0] with msb at A[1].7;
  ;     Sgn2=A[7].1, Exp2=A[6], Mnt2=A[3:2] with msb at A[3].7;
  ;     and return with C=0
Q20_Float_Init:

  move  APC,#80h  ; should be redundant (APC=0 in IAR)!
  move  GR,#1 ; set GRS=0x0100
    ; check A[1:0]
  move  AP,#4 ; A[4] will be arg1 indicator
  move  acc,A[1]
  sla
  add   GRS ; will set C=1 if Exp=FF
  sjump NC,init_a
    or    A[0]
    sjump NZ,process_nan_1  ; jump if arg1=NaN
    move  acc,#81h  ; set indicator=0x81 (INF)
    sjump init_b
init_a:
  sub   GRS
  or    A[0]
  move  acc,PSF
  and   #80h  ; set indicator=0x80 (0) or =0x00 (regular)
init_b:
  ; inf=81, zero=80, nn=00

    ; check A[3:2]
  move  AP,#5 ; A[5] will be arg2 indicator
  move  acc,A[3]
  sla
  add   GRS ; will set C=1 if Exp=FF
  sjump NC,init_c
    or    A[2]
    sjump NZ,process_nan_2  ; jump if arg2=NaN
    move  acc,#81h  ; set indicator=0x81 (INF)
    sjump init_d
init_c:
  sub   GRS
  or    A[2]
  move  acc,PSF
  and   #80h  ; set indicator=0x80 (0) or =0x00 (regular)
init_d:
  ; inf=81, zero=80, nn=00

  move  C,A[4].7  ; bit7=1 if not a regular number
  or    acc.7  ; bit7=1 if not a regular number
  ret   C ; return with C=1 if one of args isnt regular number

    ; both args are regular numbers
    ; unpack
  move  AP,#1 ; arg1
  scall unpack
  move  A[4],A[6]
  move  A[5],A[7]
  move  AP,#3 ; arg2
  scall unpack
  move  C,#0  ; set C=0
  ret


; this subroutine will
; 1. unpack sign to A[7].1
; 2. unpach Exp to A[6]
; 3. unpack maantissa to A[AP:AP-1]
unpack:
  move  GR,acc
  sla
  xch
  and   #0FFh
  move  A[7],PSF  ; store sign
  sjump Z,unpack_denorm ; jump for denormalized
  move  A[6],acc  ; store exp
  move  acc,GRL
  or    #080h     ; set bit7 (1.f)
  ret

unpack_denorm:
  move  acc,GRL
  move  APC,#1
  move  LC[0],#1  ; will be exp
denorm_shft:
    ; shift mantissa left (<<1)
  sla
  sla
  move  acc.0,C
  move  C,acc.7
  sdjnz LC[0],denorm_a  ; decrement exp
denorm_a:
  sjump NC,denorm_shft  ; until msb=1
  move  APC,#0
  move  A[6],LC[0]  ; store exp
  ret

; this subroutine will calculate NaN output
; (IEEE 754 compliant, follow VC++ rules)
process_nan_1:
  move  acc,A[3]
  sla
  add   GRS
  sjump NC,nan_a
    or    A[2]
    sjump Z,nan_b
nan_a:
  move  acc,A[1]
  or    #40h
  sla
  move  A[6],acc
  move  acc,A[3]
  or    #40h
  sla
  sub   A[6]
  sjump C,nan_b
  sjump NZ,process_nan_2
  move  acc,A[2]
  sub   A[0]
  sjump C,nan_b
  sjump NZ,process_nan_2
  move  AP,#3  
  sjump S,nan_b
process_nan_2:
  move  A[0],A[2]
  move  A[1],A[3]
nan_b:
  move  AP,#1
  or    #40h
    ; set S=1 to signal NaN output
  move  AP,#4
  move  C,#1
  move  acc.15,C
  ret



; This subroutine will
; 1. Check if Exp>=0xFF, then output INF.
; 2. Check if Exp<(-24), then output 0.
; 3. Check if Exp<=0, then de-normalize mantissa, reset Exp to 0.
; 4. Round mantissa at 24-th bit (to nearest)
; 5. Pack (Sign,Exp,Mantissa) into output float A[1:0]

Q20_Float_Wrap:
  ; A[1:0,3:2]=mantissa, A[4]=Exp, A[5].1=Sign

    ; check if Exp>=FF
  move  APC,#0
  move  AP,#4
  sub   #0FFh
  sjump S,wrap_c

    ; return A[1:0]=INF
wrap_inf:
  move  A[1],#0FF00h
wrap_d:
  move  A[0],#0
  move  AP,#1
  move  C,A[5].1
  rrc
  ret
    ; return A[1:0]=0
wrap_zero:
  move  A[1],#0
  sjump wrap_d

wrap_c:
    ; check if Exp<(-24)
  add   #(0FFh+24)
  sjump S,wrap_zero
  sub   #24
    ; check if Exp<=0, then de-normalize
  sjump S,wrap_a
  sjump NZ,wrap_round

    ; de-normalize mantissa (shift rignht)
wrap_a:
  neg
  add   #1
  move  LC[0],acc ; shift count
  move  APC,#42h
  move  AP,#1
wrap_b:
    sr
    rrc
    rrc
    rrc
    sdjnz LC[0],wrap_b
  move  A[4],#0

  ; round at A[0].0 to nearest
  ; if A[3]==8000 then round to nearest with lsb=0
wrap_round:
  move  APC,#82h
  move  C,A[0].0
  move  AP,#2
  addc  #0FFFFh
  addc  #07FFFh
  addc  #0
  move  APC,#0
  addc  #0
    ; check if extra bit appeared after rounding
  move  C,acc.8
  move  AP,#4
  sjump NZ,wrap_e
  move  C,A[1].7  ; extra bit for denormalized
wrap_e:
  addc  #0  ; increment Exp with extra bit

Q20_Float_Final:
    ; pack Sign, Exp and return A[1:0]
  xch
  move  C,A[5].1
  rrc
  move  AP,#1
  and   #7Fh
  or    A[4]
  ret

 ENDMOD


;*****************************************************************************

