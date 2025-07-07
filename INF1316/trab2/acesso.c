#include "acesso.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Acesso* acesso_init(int num_linhas)
{
    Acesso* acesso = (Acesso*)malloc(sizeof(Acesso) * num_linhas);

    if (!acesso)
    {
        perror("Erro na alocacao de memoria para o Acesso*");
        return NULL;
    }

    return acesso;
}

void preenche_vetor(Acesso* v, char* nome_arquivo)
{
    FILE* arq = fopen(nome_arquivo, "r");

    if (arq == NULL)
    {
        perror("Erro na abertura do arquivo.\n");
        return;
    }

    int i = 0;
    unsigned int endereco;
    char rw;

    while (fscanf(arq, "%x %c", &endereco, &rw) == 2)
    {
        v[i].endereco = endereco;
        v[i].rw = rw;
        i++;
    }

    fclose(arq);
    return;   
}

int calcula_distancia(Acesso* acessos, int inicio, int tamanho, int pagina_virtual, int shift)
{
    for (int i = inicio + 1; i < tamanho; i++)
    {
        int pagina = acessos[i].endereco >> shift;
        if (pagina == pagina_virtual)
        {
            return i - inicio;
        }
    }
    return INFINITO; // nunca mais será usada
}