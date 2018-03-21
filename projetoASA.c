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

void readData() {
    scanf("%d\n", &N_vertices);
    scanf("%d\n", &N_links);
}

void readData_Links(N_links){
  for (int i = 1; i <= N_links; i++) {
    scanf("%d %d\n", &vertice1, &vertice2);
    addVertice(vertice1);
    addVertice(vertice2);
    addAresta(vertice1, vertice2);
  }
}

void testArguments(N_vertices, N_links){
  if(N_vertices < 2 || N_links < 1){
    printf("Input incorreto\n", );
    return 0;
  }
}

void stackPush (int v_index){


}

int stackPop(){

}

int main() {
  int N_vertices = 0;
  int N_links = 0;

  readData();

  struct vertice stack_array [N_vertices];

  testArguments();

  printf("%d\n", N_vertices );
  printf("%d\n", N_links);
  //for (int i = 1; i <= ??; i++) {
  //  printf("%s\n", ??);
  //}

  return 0;
}
