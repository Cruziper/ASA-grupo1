#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define newVertex_malloc (struct Vertex*)malloc(sizeof(Vertex))
#define newGraph_malloc (struct Graph*) malloc(sizeof(Graph))
#define newAdjList_malloc (struct ListOFAdja*) malloc((N_Vertices+1) * sizeof(ListOFAdja))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

//> Global VARIABLES ///////////////////////////////////////////////////////////
int N_Vertices = 0;
int N_Edges = 0;
int stackPointer = 1;
int visited = 0;
int current_scc = 0;
int stack;
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
    graph->arrayAdjList[V].head = newVertex_malloc;
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

//> stackPop ///////////////////////////////////////////////////////////////////
int stackPop(int vertexArray){
    if (stackPointer > 0){
        int vertexPOP = vertexArray[&stackPointer-1]; //vertexArray_POINTER-1 porque a variavel global toma sempre o valor da proxima posicao vazia da lista
        stackPointer--;
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

void tarjan_visit(struct Graph* graph, int vertexVisit, int* vectorSCC){
    visited++;
    //low e d tomam o valor do vertice
    graph->arrayAdjList[vertexVisit].head->low = visited;
    graph->arrayAdjList[vertexVisit].head->d = visited;
    //o index do vertice e colocado na stack
    stackPush(stack, graph->arrayAdjList[vertexVisit].head->vIndex);
    //flag de estado in_stack passa a 1
    graph->arrayAdjList[vertexVisit].head->in_stack = 1;

    //percorre as arestas de vertexVisit ate encontrar a ultima da arrayAdjList
    for (Vertex* currentVertex = graph->arrayAdjList[vertexVisit].head; currentVertex!=NULL; currentVertex = currentVertex->next){
        //ao encontrar o ultimo vertice da lista de adjacencia
        if (currentVertex->next == NULL && currentVertex != graph->arrayAdjList[vertexVisit].head && currentVertex->in_stack == 0){
            //repete o processo para um vertice novo
            tarjan_visit(graph, currentVertex->vIndex, vectorSCC);
        }
        //se o proximo vertice ja estiver Visitado
        else if (currentVertex->next->in_stack == 1){
            if (currentVertex->d == currentVertex->next->low){
                vectorSCC[currentVertex->vIndex] = currentVertex->vIndex;
            }
            //o vertice atual toma o valor menor de low
            currentVertex->low = MIN(currentVertex->low, currentVertex->next->low);
            //retiramos o ultimo elemento da stack (coincide com o currentVertex->next)
            stackPop(stack);
            //o vertice atual passa a ser o que corresponde ao ultimo na stack
            currentVertex = graph->arrayAdjList[stack[&stackPointer]].head;
        }
    }
}

void scc_tarjan(struct Graph* graph, int* vectorSCC){
  for (int  j = 0; graph->arrayAdjList[j].head != NULL; j++) {
    vectorSCC[j] = -1;
  }

  for (int i = 0; graph->arrayAdjList[i].head != NULL; i++) {
    if (graph->arrayAdjList[i].head->next->d == -1) {
      tarjan_visit(graph, graph->arrayAdjList[i].head->next->vIndex, vectorSCC);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////

void printGraph(struct Graph*graph){
    for(int i=1; i<=N_Vertices; i++){
        printf("%d: ", i);
        struct Vertex* vertexAUX_next = graph->arrayAdjList[i].head->next;
        while(vertexAUX_next != NULL){
            printf("%d --- ", vertexAUX_next->vIndex);
            vertexAUX_next = vertexAUX_next->next;
        }
        printf("\n");
    }
}
//> MAIN FUNCTION //////////////////////////////////////////////////////////////
int main() {
    readData();
    testArguments(N_Vertices, N_Edges);
    struct Graph* graph = newGraph(N_Vertices);
    graph = readEdges(graph, N_Edges);
    printGraph(graph);
    int vectorSCC[N_Vertices];
    scc_tarjan(graph, vectorSCC);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
