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
struct Graph* addVertex(struct Graph* graph, int V){
    graph->arrayAdjList[V].head->vIndex = V;
    graph->arrayAdjList[V].head->d = -1; //NILL
    graph->arrayAdjList[V].head->low = -1; //INFINITY
    graph->arrayAdjList[V].head->in_stack = 0;
    graph->arrayAdjList[V].head->next = NULL;
    return graph;
}

//> addEdge ////////////////////////////////////////////////////////////////////
struct Graph* addEdge(struct Graph* graph, int origin, int destiny){
    if (graph->arrayAdjList[origin].head == NULL){
        graph = addVertex(graph, origin);

    }
    if (graph->arrayAdjList[destiny].head == NULL){
        graph = addVertex(graph, destiny);
    }

    struct Vertex* headORIGIN = graph->arrayAdjList[origin].head;
    while(headORIGIN->next != NULL){
        headORIGIN = headORIGIN->next;
    }

    headORIGIN->next = graph->arrayAdjList[destiny].head;
    return graph;
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
 struct Graph* readEdges(struct Graph* graph, int N_Edges){
     int vertex_1, vertex_2;
     for (int i = 1; i <= N_Edges; i++) {
         scanf("%d %d", &vertex_1, &vertex_2);
         graph = addEdge(graph, vertex_1, vertex_2);
     }
     return graph;
 }

//> testArguments //////////////////////////////////////////////////////////////
 void testArguments(int N_Vertices, int N_Edges){
   if(N_Vertices < 2 || N_Edges < 1){
       fprintf(stderr, "Invalid Input\n");
       exit(-1);
   }
}

//> Tarjan Algorithm ///////////////////////////////////////////////////////////
void scc_tarjan(struct Graph* graph){

}

void tarjan_visit(int v){

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
  graph = readEdges(graph, N_Edges);
  printGraph(graph);

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
