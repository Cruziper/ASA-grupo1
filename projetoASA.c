#include <stdio.h>
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
Vertex* addEdge(struct Graph* graph, int origin, int destiny, struct Vertex* verticesArray){
    struct Vertex* verticesArray_aux = verticesArray;
    if (graph->arrayAdjList[origin].head == NULL){
        verticesArray_aux = addVertex(graph, origin, verticesArray_aux);
    }
    if (graph->arrayAdjList[destiny].head == NULL){
        verticesArray_aux = addVertex(graph, destiny, verticesArray_aux);
    }
  graph->arrayAdjList[origin].head->next = &verticesArray_aux[destiny];
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
 void readEdges(struct Graph* graph, int N_Edges, struct Vertex* verticesArray){
     int vertex_1, vertex_2;
     for (int i = 1; i <= N_Edges; i++) {
         scanf("%d %d", &vertex_1, &vertex_2);
         addEdge(graph, vertex_1, vertex_2, verticesArray);
     }
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

//> MAIN FUNCTION //////////////////////////////////////////////////////////////
int main() {
  readData();
  testArguments(N_Vertices, N_Edges);
  struct Graph* graph = newGraph(N_Vertices);
  struct Vertex verticesArray[N_Vertices+1];
  readEdges(graph, N_Edges, verticesArray);

  printf("%d\n", graph->arrayAdjList[1].head->next->vIndex);
  //for (int i = 1; i <= ??; i++) {
  //  printf("%s\n", ??);
  //}

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
