#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define newVertex_malloc (struct Vertex*)malloc(sizeof(struct Vertex))
#define newGraph_malloc (struct Graph*)malloc(sizeof(struct Graph))
#define MAX_VERTEX 1000

int vIndexGlobal = 0;

typedef struct {
  int vIndex;
  int discoveryTime;
  int lowDiscoveryTime;
  int in_stack;  //0 (it isn't) or 1 (it is)
  struct Vertex *next;
} Vertex;

typedef struct {
  struct vertice *head;
} ListaAdja;

typedef struct {
  int Nvert;
  struct listaAdja* arrayAdjList;
} Graph;

struct vertice* criar_novo_vertice(int V){
  struct vertice* novoVer = novo_vertice;
  novoVer->vIndex = V;
  novoVer->discoveryTime = -1;
  novoVer->in_stack = 0;
  novoVer->next = NULL;
  return novoVer;
}

struct Graph* criar_novo_grafo(int NumVertex) {
  struct Grafo* novoGrafo = novo_grafo;
  grafo->Nvert = NumVertex;
  grafo->arrayAdjList = (struct listaAdja*)malloc(NumVertex * sizeof(struct listaAdja));
  for (int i = 0; i < NumVertex; i++)
    novoGrafo->arrayAdjList[i].head = NULL;
    return novoGrafo;
}

void adiciona_aresta(int origem, int destino, struct Graph* grafo){
  struct Vertex* novoVer = criar_novo_vertice(origem);
  novoVer->next = grafo->arrayAdjList[destino].head;
  grafo->arrayAdjList[origem].head = novoVer;
}

int stackPush (int v_index, int pilha[], int NumVertexs){
  if pilha[NumVertex] < MAX_TAMANHO {
    return pilha[NumVertex++];
  }
  else {
    printf(stderr,"Erro pilha cheia.\n");
  }
}

int stackPop(int pilha[], int NumVertexs){
  if (pilha[NumVertexs] = 0) {
    printf(stderr,"Erro pilha vazia\n");
  }
  else
    return pilha[NumVertexs--];
}


void scc_tarjan(Graph graph){
  int visited = 0;
  int L = NULL;
  for (int i = 0; i < graph->Nvert; i++) {
    if(Vertex->discoveryTime = -1){
      tarjan_visit(i);
    }
  }
}

void tarjan_visit(int v){


}


int main() {
  int NVertices = 0;
  int NArestas = 0;
  int pilha[NVertices]


  scanf("%d\n", &NVertices);
  scanf("%d\n", &NArestas);

  struct vertice *listaAdja[NVertices], *p;
  struct Pilha* novaPilha = nova_pilha;

  for( i = 1 ; i <= NVertices ; i++ )
		listaAdja[i] = NULL;

  for (int i = 1; i <= NArestas; i++) {
    scanf("%d %d\n", &vertice1, &vertice2);
    addAresta(vertice1, vertice2);
  }

  if(NVertices < 2 && NArestas < 1){
    return -1;
  }

  for (int i = 0; i < NVertices; i++) {
    if (v_index(i) == -1) {
      tarjan(i);
    }
  }




  return 0;
}
