.text

.globl fat

fat:
    

    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -16(%rbp)
        
    cmpl $0, %edi
    je end

    subl $1, %edi
    call fat
    movq -16(%rbp),%r12 
    imull %r12d, %eax
    leave
    ret

    

    end:
    movl $1, %eax
    leave
    ret
