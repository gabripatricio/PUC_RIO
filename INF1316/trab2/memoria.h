#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdlib.h>
#include "acesso.h"
#define VAZIA -1


typedef struct
{
    int pagina_virtual; 
    char referenciada;     
    char modificada;       
    int ultimo_acesso;    
} Frame;

Frame* frame_init(int numero_quadros);
int busca_pagina(Frame* vetor, int endereco, int tamanho);
void substitui_pagina(Frame* vetor, int endereco, int indice, int tempo, char bit_rw);
int encontra_pagina_mais_velha(Frame* vetor, int tamanho_vetor);



#endif // MEMORIA_H