.text

.globl foo

foo:   
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, %eax
    addl $1, %eax
    leave
    ret
