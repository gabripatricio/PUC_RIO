.text

.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp
    call add
    leave
    ret
