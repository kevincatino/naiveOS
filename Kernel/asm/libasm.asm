GLOBAL cpuVendor
GLOBAL getRTC

GLOBAL kbReadUntilCode

GLOBAL getKbCode

GLOBAL keyboardActivated


; GLOBAL getStack

EXTERN updateRegs

EXTERN getRegs

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro pushStateNoRax 0
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popStateNoRax 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
%endmacro


	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

kbd_wait_till_data:
.loop:	in al, 64h			; We bring status register to AL
		and al, 00000001	; We clear all but the lowest bit
		jz .loop
		; If it's 0, we repeat.

.iscomplete:
		xor rax, rax
		in al, 60h
		test al, 0x80
		jnz .iscomplete
		ret

kbReadUntilCode:
		pushStateNoRax
		mov al, 0D0h
		out 64h, al
		call kbd_wait_till_data	; We wait until there's data to read
		; mov rax, 0			
		; in al, 60h
		popStateNoRax			
		ret

getKbCode:
	mov rax, 0
    in al, 60h
	ret

; -----------------------------------
; Detecta si hay un codigo de teclado en el buffer.
; Retorna 1 de haber, 0 si no.
; -----------------------------------
keyboardActivated:
    mov rax, 0
    in al, 64h
    and al, 01h 
    ret


getRTC:
	push rbp	
	mov rbp, rsp
	mov rax, rdi
	out 70h, al
	in al, 71h
	mov rsp, rbp
    pop rbp
    ret

; getStack:
; 	mov rax, rsp
; 	ret

GLOBAL infoReg

infoReg:
	pushState
	; mov [regs], rax
	; mov [regs+8], rbx
	; mov [regs+8*2], rcx
	; mov [regs+8*3], rdx
	; mov [regs+8*4], rbp
	; mov [regs+8*5], rdi
	; mov [regs+8*6], rsi
	; mov [regs+8*7], r8
	; mov [regs+8*8], r9
	; mov [regs+8*9], r10
	; mov [regs+8*10], r11
	; mov [regs+8*11], r12
	; mov [regs+8*12], r13
	; mov [regs+8*13], r14
	; mov [regs+8*14], r15
	; mov [regs+8*15], rsp
	; mov [regs+8*16], rsp ;rip
	mov [ptr], rdi
	mov rdi, rsp
	call updateRegs
	mov rdi, [ptr]
	call getRegs
	popState
	ret

section .bss
ptr resq 1
regs resq 17


