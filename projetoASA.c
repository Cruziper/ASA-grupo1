#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define newVertex_malloc (struct Vertex*)malloc(sizeof(Vertex))
#define newGraph_malloc (struct Graph*) malloc(sizeof(Graph))
#define newAdjList_malloc (struct ListOFAdja*) malloc((N_Vertices+1) * sizeof(ListOFAdja))
#define newSubList_malloc (struct SubList*) malloc((N_Vertices+1) * sizeof(SubList))

/*> Global VARIABLES /////////////////////////////////////////////////////////*/
int N_Vertices = 0;
int N_Edges = 0;
int stackPointer = 1;
int visited = 0;
int current_scc = 0;
int stack;
/*> STRUCTS //////////////////////////////////////////////////////////////////*/
typedef struct Vertex{
  int vIndex;
  int d;
  int low;
  int in_stack; /*/0 (it isn't) or 1 (it is)*/
  struct SubList* listVert;
} Vertex;

typedef struct SubList{
  Vertex* sVertex;
  struct SubList * next;
}SubList;

typedef struct ListOFAdja{
  struct Vertex *head;
} ListOFAdja;

typedef struct Graph{
  int Nvert;
  struct ListOFAdja* arrayAdjList;
} Graph;
/*////////////////////////////////////////////////////////////////////////////*/


/*> min //////////////////////////////////////////////////////////////////////*/
int min(int X, int Y){
  if (X < Y) {
    return X;
  }
  else {
    return Y;
  }
}

/*> addVertex ////////////////////////////////////////////////////////////////*/
 struct Graph* addVertex(struct Graph* graph, int V){
    graph->arrayAdjList[V].head = newVertex_malloc;
    graph->arrayAdjList[V].head->vIndex = V;
    graph->arrayAdjList[V].head->d = -1; /*NILL*/
    graph->arrayAdjList[V].head->low = -1; /*INFINITY*/
    graph->arrayAdjList[V].head->in_stack = 0;
    graph->arrayAdjList[V].head->listVert = newSubList_malloc;
    graph->arrayAdjList[V].head->listVert->sVertex = NULL;
    graph->arrayAdjList[V].head->listVert->next = NULL;
    return graph;
}

/*> addEdge //////////////////////////////////////////////////////////////////*/
struct Graph* addEdge(struct Graph* graph, int origin, int destiny){

    if (graph->arrayAdjList[origin].head == NULL){
        graph = addVertex(graph, origin);
    }
    if (graph->arrayAdjList[destiny].head == NULL){
        graph = addVertex(graph, destiny);
    }
    /*struct Vertex* headORIGIN = graph->arrayAdjList[origin].head;*/
    struct SubList* current = graph->arrayAdjList[origin].head->listVert;
    while(current->next != NULL) {
        current = current->next;
    }

    current->next = newSubList_malloc;
    current->sVertex = graph->arrayAdjList[destiny].head;
    current->next->next = NULL;

    return graph;
}

/*> newGraph /////////////////////////////////////////////////////////////////*/
struct Graph* newGraph(int N_Vertices) {
  struct Graph* newGraph = newGraph_malloc;
  newGraph->Nvert = N_Vertices;
  newGraph->arrayAdjList = newAdjList_malloc;
  int i;
  for (i = 1; i <= N_Vertices; i++){
      newGraph->arrayAdjList[i].head = NULL;
  }
  return newGraph;
}

/*> stackPush ////////////////////////////////////////////////////////////////*/
void stackPush (int vertexArray, int v_index) {
    if (stackPointer <= N_Vertices){
        vertexArray[&stackPointer] = v_index;
        stackPointer++;
    }
    else{
        fprintf(stderr, "Stack is Full: Can't store vertex\n");
        exit(-1);
    }
}

/*> stackPop /////////////////////////////////////////////////////////////////*/
int stackPop(int vertexArray){
    if (stackPointer > 0){
        int vertexPOP = vertexArray[&stackPointer-1]; /*vertexArray_POINTER-1 porque a variavel global toma sempre o valor da proxima posicao vazia da lista*/
        stackPointer--;
        return vertexPOP;
    }
    else{
        fprintf(stderr, "Stack is Empty: Can't remove vertex\n");
        exit(-1);
    }
}

/*> readData /////////////////////////////////////////////////////////////////*/
void readData() {
     scanf("%d", &N_Vertices);
     scanf("%d", &N_Edges);
 }

/*> readEdges ////////////////////////////////////////////////////////////////*/
 struct Graph* readEdges(struct Graph* graph, int N_Edges){
     int vertex_1, vertex_2, i;
     for (i = 1; i <= N_Edges; i++) {
         scanf("%d %d", &vertex_1, &vertex_2);
         graph = addEdge(graph, vertex_1, vertex_2);
     }
     return graph;
 }

/*> testArguments ////////////////////////////////////////////////////////////*/
 void testArguments(int N_Vertices, int N_Edges){
   if(N_Vertices < 2 || N_Edges < 1){
       fprintf(stderr, "Invalid Input\n");
       exit(-1);
   }
}

/*> Tarjan Algorithm /////////////////////////////////////////////////////////*/

void tarjan_visit(struct Graph* graph, int vertexVisit, int* vectorSCC) {
    visited++;
    /*low e d tomam o valor do vertice*/
    graph->arrayAdjList[vertexVisit].head->low = visited;
    graph->arrayAdjList[vertexVisit].head->d = visited;
    printf("- %d\n", graph->arrayAdjList[vertexVisit].head->vIndex);
    /*o index do vertice e colocado na stack*/
    stackPush(stack, graph->arrayAdjList[vertexVisit].head->vIndex);
    /*flag de estado in_stack passa a 1*/
    graph->arrayAdjList[vertexVisit].head->in_stack = 1;

    /*percorre as arestas de vertexVisit ate encontrar a ultima da arrayAdjList*/
    Vertex* currentVertex;
    for (currentVertex = graph->arrayAdjList[vertexVisit].head; currentVertex->listVert->sVertex!=NULL; currentVertex->listVert = currentVertex->listVert->next){
        /*ao encontrar o ultimo vertice da lista de adjacencia*/
        if (currentVertex->listVert->next == NULL && currentVertex != graph->arrayAdjList[vertexVisit].head && currentVertex->in_stack == 0){
            /*repete o processo para um vertice novo*/
            printf("aaaa");
            tarjan_visit(graph, currentVertex->vIndex, vectorSCC);
        }
        /*se o proximo vertice ja estiver Visitado*/
        else if (currentVertex->listVert->next->sVertex->in_stack == 1){
            if (currentVertex->d == currentVertex->listVert->next->sVertex->low){
              vectorSCC[currentVertex->vIndex] = currentVertex->vIndex;
              printf("aaaa");
            }
        }
    }
    if (graph->arrayAdjList[vertexVisit].head->low == graph->arrayAdjList[vertexVisit].head->d){
        /*vectorSCC[currentVertex->vIndex] = currentVertex->vIndex;*/
        current_scc++;
        while (graph->arrayAdjList[vertexVisit].head->vIndex != graph->arrayAdjList[vertexVisit].head->listVert->sVertex->vIndex) {
            stackPop(stack);
            graph->arrayAdjList[vertexVisit].head->listVert->sVertex->in_stack = 0;

            /*o vertice atual passa a ser o que corresponde ao ultimo na stack*/
            graph->arrayAdjList[vertexVisit].head = graph->arrayAdjList[stack[&stackPointer]].head;
        }
    }
}

void scc_tarjan(int N_Vertices, struct Graph* graph, int* vectorSCC){
    int j, i;
    for (j = 1; j <= N_Vertices; j++) {
        vectorSCC[j] = -1;
    }

    for (i = 1; i <= N_Vertices; i++) {
        if (graph->arrayAdjList[i].head->listVert->sVertex != NULL) {
            if (graph->arrayAdjList[i].head->listVert->sVertex->d == -1) {
                tarjan_visit(graph, i, vectorSCC);
            }
        }
    }
 }
/*////////////////////////////////////////////////////////////////////////////*/

void printGraph(struct Graph*graph){
    int i;
    for(i=1; i<=N_Vertices; i++){
        printf("%d: ", i);
        struct Vertex* current = graph->arrayAdjList[i].head;
        struct SubList* ccurrent = current->listVert;
        while(ccurrent != NULL){
            printf("%d --- ", ccurrent->sVertex->vIndex);
            ccurrent = ccurrent->next;
        }
        printf("\n");
    }
}
/*> MAIN FUNCTION ////////////////////////////////////////////////////////////*/
int main() {
    readData();
    testArguments(N_Vertices, N_Edges);
    struct Graph* graph = newGraph(N_Vertices);
    graph = readEdges(graph, N_Edges);
    /*printGraph(graph);*/
    int vectorSCC[N_Vertices];
    /*printf("%d", graph->arrayAdjList[5].head->vIndex);*/
    scc_tarjan(N_Vertices,graph, vectorSCC);

    return 0;
}
/*////////////////////////////////////////////////////////////////////////////*/
