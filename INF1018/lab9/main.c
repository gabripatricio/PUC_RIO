#include <stdio.h>
void foo(int* a, int n); 
int main()
{
    int a[5] = {2,2,0,4,0};
    int n = 5;
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", a[i]);
    }

    foo(a,n);
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
    return 0;
}
