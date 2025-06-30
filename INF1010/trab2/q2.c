#include <stdlib.h>
#include <stdio.h>

#define INF 99999
#define ARESTAS 7
#define VERTICES 5
#define TRUE 1
#define FALSE 0

typedef struct _viz Vizinhos;
typedef struct _grafo Grafo;
typedef struct _no No;
typedef struct _heap Heap; //no caso eh um min heap pois queremos a MENOR distancia

struct _viz {
    int numeroRep;
    int peso;
    Vizinhos* prox;
};

struct _grafo {
    int numVertices;           /* numero de nos ou vertices */
    int numArestas;           /* numero de arestas */
    Vizinhos** vizinhos;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

struct _no {
    int vertice;
    int distancia;
};

struct _heap {
    int max;
    int pos;
    No** vetor;
};

Vizinhos* criaVizinho(Vizinhos* lista, int numero, int peso)
{
    Vizinhos* novo = (Vizinhos*)malloc(sizeof(Vizinhos));
    if (novo == NULL)return NULL;
    novo->numeroRep = numero;
    novo->peso = peso;
    novo->prox = lista;
    return novo;
}

void libera_heap(Heap* heap)
{
    if(heap)
    {
        for(int i = 0; i < heap->pos; i++)
        {
            free(heap->vetor[i]);
        }
        free(heap->vetor);
        free(heap);
    }
}

void libera_grafo(Grafo* g)
{
    if(g)
    {
        for(int i = 0; i < g->numVertices; i++)
        {
            Vizinhos* atual = g->vizinhos[i];
            while(atual)
            {
                Vizinhos* temp = atual;
                atual=atual->prox;
                free(temp);
            }
        }
    }
    free(g->vizinhos);
    free(g);
}

void mostraGrafo(Grafo* grafo)
{
    if (!grafo)return;

    printf("Numero de Vertices: %d, Numero de arestas: %d\n", grafo->numVertices, grafo->numArestas);
    for (int i = 0; i < grafo->numVertices; i++)
    {
        Vizinhos* viz = grafo->vizinhos[i];
        printf("Vertice %d aponta para -> ", i);
        while (viz)
        {
            printf(" (Vertice: %d, Peso: %d) ->", viz->numeroRep, viz->peso);
            viz = viz->prox;
        }
        printf(" NULL;");
        printf("\n");
    }
}

No* criaNoHeap(int vertice, int distancia)
{
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL)return NULL;

    novo->distancia = distancia;
    novo->vertice = vertice;

    return novo;
}

static void troca(int a, int b, No** v)
{
    No* aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

Heap* criaHeap(int max)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL)exit(1);

    heap->max = max;
    heap->pos = 0;
    heap->vetor = (No**)malloc(sizeof(No*) * max);
    if (heap->vetor == NULL)exit(1);

    return heap;
}

static void corrige_acima(Heap* heap, int pos)
{
    while (pos > 0)
    {
        int pai = (pos - 1) / 2;
        if (heap->vetor[pai]->distancia > heap->vetor[pos]->distancia)
            troca(pos, pai, heap->vetor);
        else
            break;

        pos = pai;
    }
}

void heap_insere(Heap* heap, int distancia, int vertice)
{
    if (heap->pos < heap->max)
    {
        No* novo = criaNoHeap(vertice, distancia);
        heap->vetor[heap->pos] = novo;
        corrige_acima(heap, heap->pos);
        heap->pos++;
    }
    else
    {
        printf("HEAP CHEIO.\n");
    }
}

static void corrige_abaixo(Heap* heap)
{
    int pai = 0;
    while (2 * pai + 1 < heap->pos)
    {
        int fesq = 2 * pai + 1;
        int fdir = 2 * pai + 2;

        int filho;

        if (fdir >= heap->pos)
            fdir = fesq;

        if (heap->vetor[fesq]->distancia <= heap->vetor[fdir]->distancia)
            filho = fesq;
        else
            filho = fdir;

        if (heap->vetor[pai]->distancia > heap->vetor[filho]->distancia)
        {
            troca(pai, filho, heap->vetor);
        }
        else
            break;
        pai = filho;
    }
}

No* heap_remove(Heap* heap)
{
    if (!heap->pos)
    {
        printf("Nao ha elementos,\n");
        return NULL;
    }

    No* menor = heap->vetor[0];

    heap->vetor[0] = heap->vetor[heap->pos - 1]; // nunca se deleta o primeiro elemento de cara, tem que trocar com o mais a direita
    heap->pos--;
    corrige_abaixo(heap);

    return menor;
}

Grafo* criaGrafo(int numeroVertices, int numeroArestas)
{
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL)exit(1);

    grafo->numVertices = numeroVertices;
    grafo->numArestas = numeroArestas;
    grafo->vizinhos = (Vizinhos**)malloc(sizeof(Vizinhos*) * numeroVertices);

    for (int i = 0; i < numeroVertices; i++)
    {
        grafo->vizinhos[i] = NULL;
    }
    return grafo;
}

void dijkistra(Grafo* g, int inicio)
{
    int* distancias = (int*)malloc(sizeof(int) * g->numVertices);
    if (!distancias)exit(1);

    int* visitados = (int*)malloc(sizeof(int) * g->numVertices);
    if (!visitados)exit(1);

    for (int i = 0; i < g->numVertices; i++)
    {
        distancias[i] = INF; //todas as distancias comecam como INFINITO
        visitados[i] = FALSE; // NENHUM FOI VISITADO AINDA
    }

    distancias[inicio] = 0;
    Heap* heap = criaHeap(g->numVertices);
    heap_insere(heap, 0, inicio);

    int passadas = 0;
    printf("\n");
    printf("Passada: %d \n", passadas);

    for (int i = 0; i < g->numVertices; i++)
    {
        if(distancias[i] == INF)
        {
            printf("Distancia de %d ate %d: INFINITO \n", inicio, i);
        }
        else
        {
            printf("Distancia de %d ate %d: %d \n", inicio, i, distancias[i]);
        } 
    } 
    
    while (heap->pos > 0)
    {
        No* elemento = heap_remove(heap);
        int u = elemento->vertice;

        if (visitados[u]) continue;

        visitados[u] = TRUE;

        Vizinhos* vizinho = g->vizinhos[u];
        while (vizinho)
        {
            int v = vizinho->numeroRep;
            int alt = distancias[u] + vizinho->peso;
           
            if (alt < distancias[v])
            {
                printf("\nPassada: %d\n", (passadas++)+1);
                distancias[v] = alt;
                heap_insere(heap, alt, v);  
                for (int i = 0; i < g->numVertices; i++)
                {
                    if(distancias[i] == INF)
                    {
                        printf("Distancia de %d ate %d: INFINITO \n", inicio, i);
                    }
                    else
                    {
                        printf("Distancia de %d ate %d: %d \n", inicio, i, distancias[i]);
                    }
                    
                } 
            }
            vizinho = vizinho->prox;
        }
    }   
}

int main(void)
{
    Grafo* grafo = criaGrafo(VERTICES, ARESTAS);

    //Representacao do grafo por lista de adjacencias
    grafo->vizinhos[0] = criaVizinho(grafo->vizinhos[0], 1, 2);
    grafo->vizinhos[0] = criaVizinho(grafo->vizinhos[0], 4, 1);

    grafo->vizinhos[1] = criaVizinho(grafo->vizinhos[1], 2, 3);
    grafo->vizinhos[1] = criaVizinho(grafo->vizinhos[1], 4, 7);

    grafo->vizinhos[2] = criaVizinho(grafo->vizinhos[2], 3, 4);

    grafo->vizinhos[3] = criaVizinho(grafo->vizinhos[3], 4, 5);

    grafo->vizinhos[4] = criaVizinho(grafo->vizinhos[4], 2, 6);

    mostraGrafo(grafo);

    dijkistra(grafo, 0);

    return 0;
}
