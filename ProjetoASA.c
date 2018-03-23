#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define newVertex_malloc (struct Vertex*)malloc(sizeof(Vertex))
#define newGraph_malloc (struct Graph*) malloc(sizeof(Graph))
#define newAdjList_malloc (struct ListOFAdja*) malloc((N_Vertices+1) * sizeof(ListOFAdja))

//> Global VARIABLES ///////////////////////////////////////////////////////////
int N_Vertices = 0;
int N_Edges = 0;
int vertexArray_POINTER = 0;
int visited = 0;
int current_scc = 0;
//> STRUCTS ////////////////////////////////////////////////////////////////////
typedef struct Vertex{
  int vIndex;
  int d;
  int low;
  int in_stack; //0 (it isn't) or 1 (it is)
  struct Vertex *next;
} Vertex;

typedef struct ListOFAdja{
  struct Vertex *head;
} ListOFAdja;

typedef struct Graph{
  int Nvert;
  struct ListOFAdja* arrayAdjList;
} Graph;
////////////////////////////////////////////////////////////////////////////////

//> addVertex //////////////////////////////////////////////////////////////////
struct Vertex* addVertex(struct Graph* graph, int V, struct Vertex* verticesArray){
  //struct Vertex* newVertex = newVertex_malloc;
  verticesArray[V].vIndex = V;
  verticesArray[V].d = -1; //NILL
  verticesArray[V].low = -1; //INFINITY
  verticesArray[V].in_stack = 0;
  verticesArray[V].next = NULL;
  graph->arrayAdjList[V].head = &verticesArray[V];
  return verticesArray;
}

//> addEdge ////////////////////////////////////////////////////////////////////
struct Vertex* addEdge(struct Graph* graph, int origin, int destiny, struct Vertex* verticesArray){
    struct Vertex* verticesArray_aux = verticesArray;
    if (graph->arrayAdjList[origin].head == NULL){
        verticesArray_aux = addVertex(graph, origin, verticesArray_aux);
    }
    if (graph->arrayAdjList[destiny].head == NULL){
        verticesArray_aux = addVertex(graph, destiny, verticesArray_aux);
    }
    struct Vertex* headORIGIN = graph->arrayAdjList[origin].head;
    struct Vertex* headORIGIN_new;
    while(headORIGIN->next != NULL){
        headORIGIN_new = headORIGIN->next;
    }
    headORIGIN_new->next = &verticesArray_aux[destiny];
    return verticesArray_aux;
}

//> newGraph ///////////////////////////////////////////////////////////////////
struct Graph* newGraph(int N_Vertices) {
  struct Graph* newGraph = newGraph_malloc;
  newGraph->Nvert = N_Vertices;
  newGraph->arrayAdjList = newAdjList_malloc;

  for (int i = 1; i <= N_Vertices; i++){
      newGraph->arrayAdjList[i].head = NULL;
  }
  return newGraph;
}

//> stackPush //////////////////////////////////////////////////////////////////
int stackPush (int vertexArray, int v_index) {
    if (vertexArray_POINTER < N_Vertices){
        vertexArray[&vertexArray_POINTER] = v_index;
        return vertexArray_POINTER++;
    }
    else{
        fprintf(stderr, "Stack is Full: Can't store vertex\n");
        exit(-1);
    }
}

//> stackPop ///////////////////////////////////////////////////////////////////
int stackPop(int vertexArray){
    if (vertexArray_POINTER >= 0){
        int vertexPOP = vertexArray[&vertexArray_POINTER-1]; //vertexArray_POINTER-1 porque a variavel global toma sempre o valor da proxima posicao vazia da lista
        vertexArray_POINTER--;
        return vertexPOP;
    }
    else{
        fprintf(stderr, "Stack is Empty: Can't remove vertex\n");
        exit(-1);
    }
}

//> readData ///////////////////////////////////////////////////////////////////
void readData() {
     scanf("%d", &N_Vertices);
     scanf("%d", &N_Edges);
 }

//> readEdges //////////////////////////////////////////////////////////////////
 struct Vertex* readEdges(struct Graph* graph, int N_Edges, struct Vertex* verticesArray){
     int vertex_1, vertex_2;
     struct Vertex* verticesArray_aux [N_Vertices];
     for (int i = 1; i <= N_Edges; i++) {
         scanf("%d %d", &vertex_1, &vertex_2);
         memcpy(verticesArray_aux, addEdge(graph, vertex_1, vertex_2, verticesArray), sizeof(verticesArray_aux));
     }
     return verticesArray_aux;
 }

//> testArguments //////////////////////////////////////////////////////////////
 void testArguments(int N_Vertices, int N_Edges){
   if(N_Vertices < 2 || N_Edges < 1){
       fprintf(stderr, "Invalid Input\n");
       exit(-1);
   }
}

//> Tarjan Algorithm ///////////////////////////////////////////////////////////
void scc_tarjan(struct Graph* graph, int *vetSCC){
  for (int  j = 0; graph->arrayAdjList[j].head != NULL; j++) {
    vetSCC[j] = -1;
  }

  for (int i = 0; graph->arrayAdjList[i] != NULL; i++) {
    if (graph->arrayAdjList[i].head->next->d == -1) {
      tarjan_visit(graph, graph->arrayAdjList[i].head->next->vIndex, vetSCC);
    }
  }
}

void tarjan_visit(struct Graph* graph, int u, int *vetSCC){
  visited++;
  graph->arrayAdjList[u].head->low = visited;
  graph->arrayAdjList[u].head->d = visited;
  stackPush(graph->arrayAdjList[u], graph->arrayAdjList[u].head->vIndex);
  graph->arrayAdjList[u].head->in_stack = 1;
  for (int i = 0; graph->arrayAdjList[u].head != NULL; i++) {
    if (graph->arrayAdjList[i].head->d == -1) {
        tarjan_visit(graph, i);
        graph->arrayAdjList[u].head->low = min(graph->arrayAdjList[u].head->low, graph->arrayAdjList[v].head->low);
      }
      else if (graph->arrayAdjList[u].head->in_stack == 1){
          graph->arrayAdjList[u].head->low = min(graph->arrayAdjList[u].head->low, graph->arrayAdjList[v].head->low);
      }
      graph->arrayAdjList[u].head->low = min(graph->arrayAdjList[u].head->d, graph->arrayAdjList[v].head->d);
    }
  }
  if (graph->arrayAdjList[u].head->d == graph->arrayAdjList[u].head->low) {
    int index;
    while (graph->arrayAdjList[u].head->vIndex != graph->arrayAdjListv[v].head->vIndex) {
      index = pilha.top();
      stackPop(graph->arrayAdjList[v].head->vIndex);
      graph->arrayAdjList[v].head->in_stack = 0;
      vetSCC[v] = current_scc;
    }
    current_scc++;
  }
}
////////////////////////////////////////////////////////////////////////////////

void printGraph(struct Graph*graph){
    for(int i=1; i<=N_Vertices; i++){
        printf("%d: ", i);
        struct Vertex* vertexAUX = graph->arrayAdjList[i].head;
        while(vertexAUX->next != NULL){
            printf("%d --- ", vertexAUX->vIndex);
            vertexAUX = vertexAUX->next;
        }
        printf("\n");
    }
    printf("Over\n");
}
//> MAIN FUNCTION //////////////////////////////////////////////////////////////
int main() {
  readData();
  testArguments(N_Vertices, N_Edges);
  struct Graph* graph = newGraph(N_Vertices);
  struct Vertex verticesArray[N_Vertices+1];
  memcpy(verticesArray, readEdges(graph, N_Edges, verticesArray), sizeof(verticesArray));
  //verticesArray = readEdges(graph, N_Edges, verticesArray);
  printGraph(graph);

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
