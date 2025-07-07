#ifndef ACESSO_H
#define ACESSO_H

#define INFINITO 1000000000

typedef struct
{
    unsigned int endereco;
    char rw; // 'r' para read, 'w' para write
} Acesso;

void preenche_vetor(Acesso* v, char* nome_arquivo);
Acesso* acesso_init(int num_linhas);
int calcula_distancia(Acesso* acessos, int inicio, int tamanho, int pagina_virtual, int shift);

#endif 