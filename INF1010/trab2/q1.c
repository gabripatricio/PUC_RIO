#include <stdlib.h>
#include <stdio.h>

#define TAM 5
#define VAZIO 0 

typedef struct vert Vertice;
struct vert
{
    int origem;
    int saida;
    int peso;
};

typedef struct unionfind UnionFind;
struct unionfind{
    int representante;
    int altura;
};

void mostraGrafo(int mat[TAM][TAM])
{
    for(int i = 0; i < TAM; i++)
    {
        printf("Vertice %d incide em:\n", i);
        for(int j = 0; j < TAM; j++)
        {
            if (mat[i][j] != VAZIO)
                printf("%d com peso: %d\n", j, mat[i][j]);
        }
        printf("\n");
    }
}

UnionFind* inicializaVetor(void)
{
    UnionFind* vetor = (UnionFind*)malloc(sizeof(UnionFind) * TAM );
    if(vetor == NULL)exit(1);

    for(int i = 0; i < TAM; i++)
    {
        vetor[i].representante = i;
        vetor[i].altura = 0;
    }
    return vetor;
}

int find(UnionFind* set, int i)
{
    //com compressao de caminho... 
    if (set[i].representante != i)
        set[i].representante = find(set, set[i].representante);
    return set[i].representante;
        
}


void unirSets(UnionFind set[], int elem1, int elem2) 
{
    //fazendo a uniao por altura...
    int rep1 = find(set, elem1);
    int rep2 = find(set, elem2);
    if (set[rep1].altura > set[rep2].altura) {
        set[rep2].representante = rep1;
    } else if (set[rep1].altura < set[rep2].altura) {
        set[rep1].representante = rep2;
    } else {
        set[rep2].representante = rep1;
        set[rep1].altura++;
    }
}

void troca(Vertice* x, Vertice* y)
{
    Vertice temp = *x;
    *x = *y;
    *y = temp;
}

int dividir(Vertice* vetor, int low, int high)
{
    int valorPivo = vetor[high].peso;
    int i = low;
    for(int j = low; j < high; j++)
    {
        if(vetor[j].peso <= valorPivo)
        {
            troca(&vetor[i], &vetor[j]);
            i++;
        }
    }
    troca(&vetor[i], &vetor[high]);
    return i;
}
void quicksort_recursao(Vertice* vetor, int low, int high)
{
    if (low > high)
        return;
    int pivo = dividir(vetor, low, high);
    quicksort_recursao(vetor, low, pivo-1);
    quicksort_recursao(vetor, pivo+1, high);
}

void quicksort(Vertice* vetor, int tamanho)
{
    quicksort_recursao(vetor, 0, tamanho-1);
}

void kruskal(int grafo[TAM][TAM])
{
    Vertice vertices[TAM * TAM];
    UnionFind vetor[TAM];

    int indice = 0;

    //transformando minha matriz num vetorzao que contem todas as arestas que sao diferentes de 0
    // isso, que nao tem conexao -- pode ter usado um pouco mais de memoria do que o necessario, mas 
    //acredito que isso nao sera um problema, pois esta dentro do escopo dessa funcao 
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(grafo[i][j] != VAZIO)
            {
               vertices[indice].origem = i;
               vertices[indice].peso = grafo[i][j];
               vertices[indice].saida = j;
               indice++;
            }
        }
    }

    quicksort(vertices, indice);
    
    //depois de organizar todo mundo, podemos simplesmente usar as estruturas de union find para garantir que nao havera ciclos nem duplicatas das arestas

    int pesoTotal = 0;
    for(int i = 0; i < TAM; i++)
    {
        vetor[i].representante = i;
        vetor[i].altura = 0; 
    }
    
   printf("Estradas a serem asfaltadas:\n");
   for (int i = 0; i < indice; i++) 
   {
        int u = vertices[i].origem;
        int v = vertices[i].saida;

        int set_u = find(vetor, u);
        int set_v = find(vetor, v);

        if (set_u != set_v) 
        {
            printf("De: %d para %d com PESO %d\n", u, v, vertices[i].peso);
            pesoTotal += vertices[i].peso;
            unirSets(vetor, set_u, set_v);
        }
    }

    printf("Custo total: %d km.\n", pesoTotal);
}

int main(void)
{
    printf("Questao 1:\n\n\n");

    int grafo[TAM][TAM] = {
            {VAZIO, 7, VAZIO, VAZIO, 1},
            {7, VAZIO, 4, VAZIO, 2},
            {VAZIO, 4, VAZIO, 5, 6},
            {VAZIO, VAZIO, 5, VAZIO, 6},
            {1, 2, 6, 6, VAZIO}
    };


    printf("Exibindo o grafo\n\n");
    mostraGrafo(grafo);  
    kruskal(grafo);

    return 0;
}
