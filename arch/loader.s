.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern kernel_main
.extern _gp

.global loader
loader:
	mov $kernel_stack, %esp
	push %eax			#Push multiboot_stuct  
	push %ebx			#Push Magic number
	call kernel_main

.global gdt_flush
gdt_flush:
	lgdt (gp)          # Load the GDT. _gp is a pointer to it
	mov %ax, 0x10        # Offset to the data segment
	mov %ds, %ax
	mov %es, %ax
	mov %fs, %ax
	mov %gs, %ax
	mov %ss, %ax
	ret

_stop:
	cli
	hlt
	jmp _stop

.section .bss
.space 2*1024*1024 # 2mb
kernel_stack:
