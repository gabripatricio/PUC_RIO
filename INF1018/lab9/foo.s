.text

.globl foo

foo:
    
    pushq %rbp
    movq %rsp, %rbp

    movl $0, %ebx
    movl $0, %ecx

    loop:
    cmpl %edi, %ecx
    jge end_for
    

    cmpl $0, (%rdi)
    je dentro

    dentro:

    jmp loop


    end_for:
    leave
    ret
