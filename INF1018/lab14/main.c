#include <stdio.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))

#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

#define BIAS 127

typedef union { 
  float f;
  unsigned int i;
 } U;


float float2 (float f)
{
    U u;
    u.f = f;
    unsigned int repbin = u.i;
    unsigned int exp = getexp(repbin);
    exp++;
    unsigned int temp = makefloat(getsig(repbin), exp, getfrac(repbin));
    u.i = temp;
    return u.f;
}

float int2float(int i)
{
    U u;

    // Se o número for 0, retorna imediatamente
    if (i == 0) {
        u.i = 0;  // Representação IEEE de 0
        return u.f;
    }

    // Determina o sinal
    unsigned int sinal = (i < 0) ? 1 : 0;
    if (i < 0)
        i = -i;  // Trabalha com o valor absoluto

    // Encontra a posição do bit mais significativo
    unsigned int E = 31;
    while (!(i >> E)) {
        E--;
    }

    // O expoente no formato IEEE 754
    int exp = E + BIAS;  // Soma o viés (127) ao expoente

    // A fração após normalizar: remova o bit mais significativo (1)
    unsigned int frac = (i & ((1 << E) - 1));  // Pega os bits restantes após o bit mais significativo

    // Ajuste para a mantissa de 23 bits
    frac = frac << (23 - E);  // Desloca para a posição correta da fração (mantissa)

    // Monta a representação IEEE 754
    u.i = makefloat(sinal, exp, frac);

    return u.f;
}




int main(void)
{
    float numero = float2 (3.0);
    printf("Questão 1: \n");
    printf("%f\n", numero);

    printf("Questão 2:\n");
    int num = 12345;
    float f = int2float(num);
    printf("Inteiro: %d -> Float: %f\n", num, f);
    return 0;
}
