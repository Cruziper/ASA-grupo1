#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define newVertex_malloc (struct Vertex*)malloc(sizeof(Vertex))
#define newGraph_malloc (struct Graph*) malloc(sizeof(Graph))

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

typedef struct Edge{
  int vertex;
  struct Vertex *next;
} Edge;

typedef struct ListOFAdja{
  struct Vertex *head;
} ListOFAdja;

typedef struct Graph{
  int Nvert;
  struct ListOFAdja* arrayAdjList;
} Graph;
////////////////////////////////////////////////////////////////////////////////

//> addVertex //////////////////////////////////////////////////////////////////
struct Vertex* addVertex(int V){
  struct Vertex* newVertex = newVertex_malloc;
  newVertex -> vIndex = V;
  newVertex -> d = 0;
  newVertex -> low = -1;
  newVertex -> in_stack = 0;
  newVertex -> next = NULL;
  return newVertex;
}

//> addEdge ////////////////////////////////////////////////////////////////////
void addEdge(struct Graph* graph, int origin, int destiny){
  struct Vertex* newVertex = addVertex(destiny);
  newVertex->next = graph->arrayAdjList[origin].head;
  graph->arrayAdjList[destiny].head = newVertex;
}

//> newGraph ///////////////////////////////////////////////////////////////////
struct Graph* newGraph(int N_Vertices) {
  struct Graph* newGraph = newGraph_malloc;
  newGraph -> Nvert = N_Vertices;
  newGraph -> arrayAdjList = (struct ListOFAdja*) malloc(N_Vertices * sizeof(ListOFAdja));

  for (int i=0; i < N_Vertices; i++){
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
     scanf("%d\n", &N_Vertices);
     scanf("%d\n", &N_Edges);
 }

//> readEdges //////////////////////////////////////////////////////////////////
 void readEdges(struct Graph* graph, int N_Edges){
     int vertex_1, vertex_2;
     for (int i = 1; i <= N_Edges; i++) {
         scanf("%d %d\n", &vertex_1, &vertex_2);
         addVertex(vertex_1);
         addVertex(vertex_2);
         addEdge(graph, vertex_1, vertex_2);
     }
 }

//> testArguments //////////////////////////////////////////////////////////////
 void testArguments(int N_Vertices, int N_Edges){
   if(N_Vertices < 2 || N_Edges < 1){
       fprintf(stderr, "Invalid Input\n");
       exit(-1);
   }
}

//> MAIN FUNCTION //////////////////////////////////////////////////////////////
int main() {
  readData();
  testArguments(N_Vertices, N_Edges);
  struct Graph* graph = newGraph(N_Vertices);
  readEdges(graph, N_Edges);

  //int vertexArray [N_Vertices];

  printf("%d\n", N_Vertices );
  printf("%d\n", N_Edges);
  //for (int i = 1; i <= ??; i++) {
  //  printf("%s\n", ??);
  //}

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
