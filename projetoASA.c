#include <stdio.h>
#include <stdlib.h>


typedef struct {
  int v_index;
  int d_u;
  int low_u;
  int in_stack;
} vertice;

typedef struct {
  int vertice1;
  struct vertice *next;
} aresta;


void stackPush (int v_index){


}

int stackPop(){

}

void readData() {
    vertice stack_array = [];
    scanf("%d\n", &NVertices);
    scanf("%d\n", &NArestas);

    for (int i = 1; i <= NArestas; i++) {
      scanf("%d %d\n", &vertice1, &vertice2);
      addAresta(vertice1, vertice2);
    }
}

void testArguments(){

}

int main() {
  int NVertices = 0;
  int NArestas = 0;

  readData();

  testArguments();
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
