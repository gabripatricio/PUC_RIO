#include <stdio.h>


/*
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	89 f8                	mov    %edi,%eax
   6:	83 c0 01             	add    $0x1,%eax
   9:	c9                   	leave
   a:	c3                   	ret
    
    

    Segunda Funcao:

   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	e8 00 00 00 00       	call   9 <foo+0x9>
   9:	c9                   	leave
   a:	c3                   	ret

 */

typedef int (*funcp) (int x);

int add(int x)
{
    return x+1;
}

int main(void)
{
    unsigned char codigo[] = {
        0x55,                   // push   %rbp
        0x48, 0x89, 0xe5,      // mov    %rsp, %rbp
        0xe8, 0x00, 0x00, 0x00, 0x00,   // call add
        0xc9,                   // leave
        0xc3                    // ret
    };

   //  eu fiz esse codigo que acho que eh isso:
    funcp ponteiro_funcao = (funcp) add;
    funcp ponteiro_codigo = (funcp) codigo;
    int diff = (funcp)ponteiro_funcao - (funcp)ponteiro_codigo;
    printf("%02X\n", diff);
    for (int i = 0; i < 4; i++) {
        codigo[3 + i] = (diff >> (i * 8)) & 0xFF; // little-endian
    }  
    funcp f = (funcp) codigo;
    
    int i = (*f)(10);
    printf("%d\n", i);
    return 0;
}
