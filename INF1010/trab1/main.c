#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "heap.h"
#include "arvore.h"

#define N 256
#define MAX(a,b) ((a > b) ? (a) : (b))
#define REPMAX 30

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
char** criar_dicionario(int tam)
{
    char** dicionario = (char**)malloc(sizeof(char*) * tam);
    if (dicionario == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa.\n");
        exit(1);
    }
    for (int i = 0; i < tam; i++)
    {
        dicionario[i] = (char*)malloc(sizeof(char) * REPMAX);
    }
    return dicionario;
}

void libera_dicionario(char** dicionario, int tam) {
    for (int i = 0; i < tam; i++) {
        free(dicionario[i]);
    }
    free(dicionario);
}

void preenche_dicionario(char** dicionario, Huffman* arv, Dados* dados, int len)
{
    for (int i = 0; i < len; i++)
    {
        strcpy(dicionario[i], encontrar_representacao(arv, dados[i].c));
    }
}


void compactar(FILE* ent, char** dicionario, Dados* dados, int tam)
{
    FILE* arquivo = fopen("compactado.bin", "wb");
    if (arquivo == NULL)
    {
        printf("Arquivo nao pode ser gerado. Abortando programa.\n");
        exit(1);
    }

    char c = fgetc(ent);
    unsigned char byte = 0;
    int pos = 0; // Posição atual no byte
    while (c != EOF)
    {
        int i;
        int indice_tabela = (int)c;
        for (i = 0; i < tam; i++)
        {
            if (dados[i].c == c)
            {
                break;
            }
        }

        int j = 0;
        while (dicionario[i][j] != '\0')
        {
            if (dicionario[i][j] == '1')
            {
                byte = byte | (1 << (7 - pos)); // Inserindo o bit na posição correta
            }
            j++;
            pos++;

            if (pos == 8) // Se o byte esta completo
            {
                fwrite(&byte, sizeof(unsigned char), 1, arquivo);
                byte = 0;
                pos = 0;
            }
        }

        c = fgetc(ent);
    }

    // Se sobrarem bits para escrever
    if (pos > 0)
    {
        fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    }

    fclose(arquivo);
    return;
}



void descompactar(FILE* compactado, FILE* descompactado, Huffman* arvore)
{
    Huffman* atual = arvore;

    unsigned char byte;
    int bit_pos = 7; // Inicia com o bit mais significativo do byte

    while (fread(&byte, sizeof(unsigned char), 1, compactado) > 0)
    {
        while (bit_pos >= 0)
        {
            if (byte & (1 << bit_pos)) // Se o bit atual é 1
            {
                atual = atual->dir;
            }
            else // Se o bit atual é 0
            {
                atual = atual->esq;
            }

            if (atual->esq == NULL && atual->dir == NULL) // Se chegou a uma folha
            {
                fputc(atual->dados.c, descompactado);
                atual = arvore; 
            }

            bit_pos--;

            if (feof(compactado)) // Se chegou ao final do arquivo compactado
            {
                break;
            }
        }

        bit_pos = 7; // Reinicia para o próximo byte
    }
}



int main(void) {
    FILE* entrada = fopen("C:\\Users\\gabri\\Desktop\\HUFFMAN\\arquivo.txt", "r");
    if (entrada == NULL)
    {
        printf("Erro na abertura do arquivo. Abortando programa.");
        exit(1);
    }
    // criando a tabela de frequencia dos caracteres que compoe o arquivo
    int* tabela_frequencia = cria_tabela();
    preenche_zero(tabela_frequencia);
    preenche_tabela_arq(tabela_frequencia, entrada);
    exibe_tabela(tabela_frequencia);
    int tam_tabela = tamanho_tabela(tabela_frequencia); // fiz isso para economizar memoria, e facilitar na hora de fazer o heap...

    // criando um heap para facilitar a insercao na arvore de huffman, alem de poder usar o heap sort
    Heap* heap = cria_heap(tam_tabela);
    Dados* vetor_dados = cria_vetor_dados(tam_tabela); // criando o vetor de dados
    preenche_vetor_dados(vetor_dados, tabela_frequencia);

    //inserindo os elementos no heap
    for (int i = 0; i < tam_tabela; i++)
    {
        heap_insere(heap, &vetor_dados[i]);
    }

    Dados* vetor_ordenado; // esse vetor sera o vetor resultado do heapsort com o min heap que eu criei 
    vetor_ordenado = heap_sort(heap, tam_tabela);
    //for (int i = 0; i < tam_tabela; i++)
    //{
    //    printf("%d\n", vetor_ordenado[i].frequencia);
    //}

    // montando a arvore de huffman ----------------------------- //
    Huffman* arvore = NULL;
    Huffman** nos_huffman = criar_no_huffman(vetor_ordenado, tam_tabela);
    arvore = criar_arvore_huffman(nos_huffman, tam_tabela);
    char* a = encontrar_representacao(arvore, ' ');

    //criando um dicionario

    char** dicionario = criar_dicionario(tam_tabela);
    preenche_dicionario(dicionario, arvore, vetor_ordenado, tam_tabela);
    printf("\n\n----------------Representacao dos caracteres em binario:-------------------\n\n");
    for (int i = 0; i < tam_tabela; i++)
    {
        printf("Caracter: %c ", vetor_ordenado[i].c);
        for (int j = 0; dicionario[i][j] != '\0'; j++)
        {
            printf("%c", dicionario[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
    printf("Comecando a compactacao do arquivo...\n\n");

    //compactando o arquivo
    rewind(entrada); //retomando o arquivo, para que possam ser feitas as operacoes de compressao

    compactar(entrada, dicionario, vetor_ordenado, tam_tabela);
    printf("Arquivo compactado com sucesso!\n\n");


    FILE* compactado = fopen("compactado.bin", "rb");
    FILE* descompactado = fopen("descompactado.txt","w");
    printf("Comecando descompactacao do arquivo...\n\n");
    descompactar(compactado, descompactado, arvore);
    printf("Arquivo descompactado com sucesso...\n\n");

    printf("Liberando memoria alocada dinamicamente...\n\n");

    //liberando memoria
    libera_dicionario(dicionario, tam_tabela);
    libera_tabela(tabela_frequencia);
    libera_heap(heap);
    liberar_arvore_huffman(arvore);
    return 0;
}