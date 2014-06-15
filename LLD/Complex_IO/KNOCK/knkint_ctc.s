	.file "knkint"
	.text
	.text_vle
	.align	4
	.global asm_knock_ABS_INT
	.global asm_Enable_SPE_APU

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; C calling convention ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; r0,      scratch register
; r1,      stack pointer
; r2,      global pointer to the small const area
; r3~r12   temp registers, not perserved by functions. r3~r10 are also used for parameter 
;          result passing
; r13,     global pointer to the small data area (SDA)
; r14~r31  preserved registers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;.globl asm_knock_ABS_INT
;unsigned int  asm_knock_ABS_INT( short int *LpData unsigned int num) 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; arguments ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; r3 = LpStruct                                                                          ;
; r4 = TableIndex                                                                        ;
; r1: stack pointer                                                                      ;   
;                                                                                        ;
; Locally used GPRs:                                                                     ;
;     r3 = LpStruct, and then used as return value                                       ;
;     r4 = TableIndex                                                                    ;
;                                                                                        ;
;     r5:  Index mask, e.g., 0x000F for table with length of 17                          ;                                               ;
;     r6:  divb: mod of fration, then used as delta                                      ;
;     r7:  index                                                                         ;
;     r8:  frac                                                                          ;
;     r9:  N[index]                                                                      ;
;     r0:  N[index+1]                                                                    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

asm_knock_ABS_INT:

	li           r5, 0
	evsplati     r8, 0

loop:
	evlwhosx     r7, r5, r3
	evabs        r7, r7
	evaddw       r8, r8, r7
	addi         r5, r5, 4
	cmpl         r5, r4
	blt          loop

	li           r5, 0
	evmergehi    r3, r5, r8
	add          r3,r3, r8

	blr

;__asm void Enable_SPE_APU(void)

asm_Enable_SPE_APU:

	mfmsr   r3            ; Read MSR value
	oris    r3,r3,0x200   ; Set SPE bit
	mtmsr   r3            ; Write MSR value

	blr
