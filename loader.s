.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

;# This is the multiboot header, it is the first thing in the file
.section multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text
.extern kernelMain
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax   ;# multiboot magic no
    push %ebx ; #address of multiboot info struct
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop  ;# loop forever

.section .bss
.space 2*1024*1024    ;# 2MB of space, we need it for the kernel stack, otherwise it will overwrite 
kernel_stack:
