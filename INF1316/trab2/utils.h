#ifndef UTILS_H
#define UTILS_H

int conta_linhas(char* nome_arquivo);
int calcula_shift(int tamanho_pagina);
void gera_estatisticas(int falta_pagina, int pagina_escrita);
int encontra_maximo(int* v, int tamanho);
#endif 