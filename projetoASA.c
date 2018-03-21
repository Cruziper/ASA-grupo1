#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define newVertexertex_malloc (struct Vertex*)malloc(sizeof(struct Vertex))
#define newGraph_malloc (struct Graph*) malloc(sizeof(struct Graph))

//> STRUCTS ////////////////////////////////////////////////////////////////////
typedef struct {
  int vIndex;
  int d;
  int low;
  int in_stack; //0 (it isn't) or 1 (it is)
  struct Vertex *next;
} Vertex;

typedef struct {
  int vertex;
  struct Vertex *next;
} Edge;

typedef struct {
  struct Vertex *head;
} ListaAdja;

typedef struct {
  int Nvert;
  struct ListaAdja* arrayAdjList;
} Graph;
////////////////////////////////////////////////////////////////////////////////

//> addVertex //////////////////////////////////////////////////////////////////
struct Vertex* addVertex(int V){
  struct Vertex* newVertex = newVertex_malloc;
  newVertex -> vIndex = V;
  newVertex -> d = NULL;
  newVertex -> low = INFINITY;
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
  newGraph -> arrayAdjList = (struct listaAdja*) malloc(V * sizeof(struct listaAdja));

  int i;
  for (i=0; i < V; i++)
    newGraph->arrayAdjList[i].head = NULL;

    return newGraph;
  }

void stackPush (int v_index){


}

int stackPop(){

}

void readData() {
     scanf("%d\n", &N_Vertices);
     scanf("%d\n", &N_Edges);
 }

 void readEdges(struct Graph* graph, int N_Edges){
   for (int i = 1; i <= N_Edges; i++) {
     scanf("%d %d\n", &vertex_1, &vertex_2);
     addVertex(vertex_1);
     addVertex(vertex_2);
     addEdge(graph, vertex_1, vertex_2);
   }
 }

 void testArguments(int N_Vertices, int N_Edges){
   if(N_Vertices < 2 || N_Edges < 1){
       fprintf(stderr, "Invalid Input\n");
       exit(-1);
   }
}

int main() {
  int N_Vertices = 0;
  int N_Edges = 0;
  readData();
  testArguments(N_Vertices, N_Edges);
  struct Graph* graph = newGraph(N_Vertices);
  readEdges(graph, N_Edges);

  int vertexArray [N_Vertices];

  printf("%d\n", N_Vertices );
  printf("%d\n", N_Edges);
  //for (int i = 1; i <= ??; i++) {
  //  printf("%s\n", ??);
  //}

  return 0;
}
