#include <stdio.h>
#include <stdlib.h>

int main() {
  int NVertices = 0;
  int NArestas = 0;

  scanf("%d\n", NVertices);
  scanf("%d\n", NArestas);

  

  if(NVertices<2 && NArestas<1){
    return -1;
  }
  return 0;
}
