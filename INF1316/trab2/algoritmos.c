#include "acesso.h"
#include "memoria.h"
#include <stdio.h>

void algoritimo_clock(Frame *memoria_fisica, Acesso *acessos, int shift, int numero_quadros, int quantidade_acessos, int *page_faults, int *paginas_escritas)
{
    int tempo = 0;
    int quantidade_inserida = 0;
    int ponteiro = 0;
    int endereco_pagina;

    for (int i = 0; i < quantidade_acessos; i++)
    {
        endereco_pagina = acessos[i].endereco >> shift;

        char bit_rw = acessos[i].rw;

        int indice = busca_pagina(memoria_fisica, endereco_pagina, numero_quadros);

        if (indice != -1)
        {
            // pagina esta presente
            memoria_fisica[indice].referenciada = 1;
            if (bit_rw == 'W')
                memoria_fisica[indice].modificada = 1;
        }
        else
        {
            // tem page-fault pq ainda estamos preenchendo ou pq eh realmente um page-fault com substituicao
            (*page_faults)++;
            if (quantidade_inserida < numero_quadros)
            {
                substitui_pagina(memoria_fisica, endereco_pagina, quantidade_inserida, tempo, bit_rw);
                quantidade_inserida++;
            }
            else
            {
                // nesse caso, eh um page-fault "verdadeiro", temos que rodar o relogio ate encontrar a pagina pra excluir
                while (1)
                {
                    if (memoria_fisica[ponteiro].referenciada == 0)
                    {
                        if (memoria_fisica[ponteiro].modificada)
                        {
                            (*paginas_escritas)++;
                        }
                        // encontramos a pagina a ser excluida
                        substitui_pagina(memoria_fisica, endereco_pagina, ponteiro, tempo, bit_rw);
                        ponteiro++;
                        ponteiro = ponteiro % numero_quadros;
                        break;
                    }
                    else
                    {
                        memoria_fisica[ponteiro].referenciada = 0; // resetamos o bit r p/ 0
                        ponteiro++;
                        ponteiro = ponteiro % numero_quadros;
                    }
                }
            }
        }
        tempo++;
    }
}

void algoritmo_LRU(Frame *memoria_fisica, Acesso *acessos, int shift, int numero_quadros, int quantidade_acessos, int *page_faults, int *paginas_escritas)
{
    // Observacao: como eh um simulador, nos preferimos nao ordenar o vetor como eh feito (no caso nao usam LRU) na pratica
    // Ou seja, nos simplesmente buscamos pela pagina mais velha a cada iteracao

    int tempo = 0;
    int quantidade_inserida = 0;

    for (int i = 0; i < quantidade_acessos; i++)
    {
        int endereco_pagina = acessos[i].endereco >> shift;
        char bit_rw = acessos[i].rw;

        // priemiro vemos se a pagina esta em memoria
        int indice = busca_pagina(memoria_fisica, endereco_pagina, numero_quadros);

        if (indice != -1) // esta em memoria
        {
            memoria_fisica[indice].ultimo_acesso = tempo;
            if (bit_rw == 'W')
                memoria_fisica[indice].modificada = 1;
        }
        else
        {
            (*page_faults)++;

            if (quantidade_inserida < numero_quadros)
            {
                substitui_pagina(memoria_fisica, endereco_pagina, quantidade_inserida, tempo, bit_rw);
                quantidade_inserida++;
            }
            else
            {
                indice = encontra_pagina_mais_velha(memoria_fisica, numero_quadros);

                if (memoria_fisica[indice].modificada)
                    (*paginas_escritas)++;

                substitui_pagina(memoria_fisica, endereco_pagina, indice, tempo, bit_rw);
                // nesse caso, procuramos a pagina mais velha para tirar
            }  
        }
        tempo++;
    }
}

void algoritimo_segunda_chance(Frame *memoria_fisica, Acesso *acessos, int shift, int numero_quadros, int quantidade_acessos, int *page_faults, int *paginas_escritas)
{
    // bem como na lru, nos preferimos nao fazer um lisa encadeada. nos fizemos um uma fila circular (PARA SIMULAR UMA FILA!!!!!!!) que NAO EH O CLOCK!!!!
    // OU SEJA, nos simplesmente damos a segunda chance para a pagina, sem andar com o ponteiro, so andamos com o ponteiro apos uma substituicao
    int ponteiro = 0;
    int tempo = 0;
    int quantidade_inserida = 0;
    int i = 0;
    while(i < quantidade_acessos)
    {
        int endereco_pagina = acessos[i].endereco >> shift;
        char bit_rw = acessos[i].rw;

        // priemiro vemos se a pagina esta em memoria
        int indice = busca_pagina(memoria_fisica, endereco_pagina, numero_quadros);

        if (indice != -1)
        {
            memoria_fisica[indice].referenciada = 1;
            if (bit_rw == 'W')
                memoria_fisica[indice].modificada = 1;
            
            i++;
        }
        else
        {
            // PODERIA GERAR DUPLICATAS DO JEITO QUE NOS IMPLEMENTAMOS O CODIGO, ENTAO TIRAMOS DAQUI... 
            //(*page_faults)++;

            if (quantidade_inserida < numero_quadros)
            {
                // ainda tem espaco
                substitui_pagina(memoria_fisica, endereco_pagina, quantidade_inserida, tempo, bit_rw);
                (*page_faults)++;
                quantidade_inserida++;
                i++;
            }
            else
            {
                if (memoria_fisica[ponteiro].referenciada == 0)
                {
                    //nao da a segunda chance
                    (*page_faults)++;
                    if (memoria_fisica[ponteiro].modificada)
                        (*paginas_escritas)++;

                    substitui_pagina(memoria_fisica, endereco_pagina, ponteiro, tempo, bit_rw);
                    ponteiro++;
                    ponteiro = ponteiro % numero_quadros;
                    i++;
                }
                else
                {
                    // nesse caso, damos a segunda chance (zerando o bit R) e "colocamos (reinserimos)" a pagina no "final" (ao andar o ponteiro)
                    // observacao! como a pagina ainda nao foi substituida, podemos simplesmente nao aumentar o i, ate encontrar uma pagina a ser substituida...

                    memoria_fisica[ponteiro].referenciada = 0;
                    ponteiro++;
                    ponteiro = ponteiro % numero_quadros;
                }
            }
        }
        tempo++; // obs: tecnicamente nem usamos tempo aqui, mas como nossa funcao pede...
    }
}

void algoritimo_otimo(Frame *memoria_fisica, Acesso *acessos, int shift, int numero_quadros, int quantidade_acessos, int *page_faults, int *paginas_escritas)
{
    int tempo = 0; // tambem nao usa tempo
    int quantidade_inserida = 0;

    for(int i = 0; i < quantidade_acessos; i++)
    {
        int endereco_pagina = acessos[i].endereco >> shift;
        char bit_rw = acessos[i].rw;


        int indice = busca_pagina(memoria_fisica, endereco_pagina, numero_quadros);

        if (indice != -1)
        {
            // ou seja, a pagina esta em memoria
            if (bit_rw == 'W')
            {
                memoria_fisica[indice].modificada = 1;
            }
        }
        else
        {
            (*page_faults)++;

            if (quantidade_inserida < numero_quadros)
            {
                // Ainda há espaço na memória
                substitui_pagina(memoria_fisica, endereco_pagina, quantidade_inserida, tempo, bit_rw);
                quantidade_inserida++;
            }
            else
            {
                // ocorreu um page-fault, nesse caso, a pagina a ser substituida sera a pagina cuja distancia eh a maior
                int maior_distancia = -1;
                int indice_maior_distancia = -1;

                for (int j = 0; j < numero_quadros; j++)
                {
                    int pagina = memoria_fisica[j].pagina_virtual;
                    int distancia = calcula_distancia(acessos, i, quantidade_acessos, pagina, shift);

                    if (distancia > maior_distancia)
                    {
                        maior_distancia = distancia;
                        indice_maior_distancia = j;
                    }
                }
                if (memoria_fisica[indice_maior_distancia].modificada)
                (*paginas_escritas)++;

                substitui_pagina(memoria_fisica, endereco_pagina, indice_maior_distancia, tempo, bit_rw);
                
            }
        }
        tempo++; // mesmo que a gente nao use vamos aumentar
    }
}