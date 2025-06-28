  .data
  nums: .int 3, -5, 7, 8, -2
  s1:   .string "%d\n"

  .text
  .globl main
  main:
  /* prologo */
     pushq %rbp
     movq  %rsp, %rbp
     subq  $16, %rsp
     movq  %rbx, -8(%rbp)
     movq  %r12, -16(%rbp)

  /* coloque seu codigo aqui */
   
     movq $nums, %rbx # rbx = &nums[0] 
     movl $0, %r12d

     loop:
     cmpl $5, %r12d
     jge end_loop
     

     movl (%rbx), %edi
     movl $1, %esi
     call filtro

     movl %eax, %esi
     movq $s1, %rdi
     call printf
     addq $4, %rbx
     addl $1, %r12d

     jmp loop

  /* finalizacao */
     end_loop:
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret
