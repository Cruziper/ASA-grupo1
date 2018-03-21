#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define novo_vertice (struct vertice*)malloc(sizeof(struct vertice))
#define novo_grafo (struct Graph*) malloc(sizeof(struct Graph))

typedef struct {
  int dest;
  int v_origem;
  int na_pilha;
  int descoberta;
  struct vertice *next;
} vertice;

typedef struct {
  int vertice1;
  struct vertice *next;
} aresta;

typedef struct {
  struct vertice *head;
} listaAdja;

typedef struct {
  int Nvert;
  struct listaAdja* arrayAdjList;
} Grafo;

struct vertice* criar_novo_vertice(int V){
  struct vertice* novoVer = novo_vertice;
  novoVer -> dest = dest;
  novoVer -> next = NULL;
  novoVer -> descoberta = INFINITY;
  novoVer -> v_origem = NULL
  return novoVer;
}

struct Grafo* criar_novo_grafo(int V) {
  struct Grafo* novoGrafo = novo_grafo;
  grafo -> V = V;

  grafo -> arrayAdjList = (struct listaAdja*) malloc(V * sizeof(struct listaAdja));

  int i;
  for (i=0; i < V; i++)
    grafo->arrayAdjList[i].head = NULL;

    return grafo;
  }

void adiciona_aresta(struct Grafo* grafo, int origem, int destino){
  struct vertice* novoVer = criar_novo_vertice(destino);
  novoVer->next = grafo->arrayAdjList[origem].head;
  grafo->arrayAdjList[destino].head = novoVer;
}

void stackPush (int v_index){


}

int stackPop(){

}


int main() {
  int NVertices = 0;
  int NArestas = 0;

  scanf("%d\n", &NVertices);
  scanf("%d\n", &NArestas);

  struct vertice *listaAdja[NVertices], *p;

  for( i = 1 ; i <= NVertices ; i++ )
		listaAdja[i] = NULL;

  for (int i = 1; i <= NArestas; i++) {
    scanf("%d %d\n", &vertice1, &vertice2);
    addAresta(vertice1, vertice2);
  }

  if(NVertices<2 && NArestas<1){
    return -1;
  }

  printf("%d\n", NVertices );
  printf("%d\n", NArestas);
  //for (int i = 1; i <= ??; i++) {
  //  printf("%s\n", ??);
  //}

  return 0;
}
