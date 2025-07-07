#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <stdlib.h>
#include "acesso.h"
#include "memoria.h"

void algoritmo_LRU(Frame* memoria_fisica, Acesso* acessos, int shift, int numero_quadros, int quantidade_acessos, int* page_faults, int* paginas_escritas);
void algoritimo_segunda_chance(Frame* memoria_fisica, Acesso* acessos, int shift, int numero_quadros, int quantidade_acessos, int* page_faults, int* paginas_escritas);

void algoritimo_clock(Frame* memoria_fisica, Acesso* acessos, int shift, int numero_quadros, int quantidade_acessos, int* page_faults, int* paginas_escritas);
void algoritimo_otimo(Frame* memoria_fisica, Acesso* acessos, int shift, int numero_quadros, int quantidade_acessos, int* page_faults, int* paginas_escritas);


#endif // ALGORITMO_H