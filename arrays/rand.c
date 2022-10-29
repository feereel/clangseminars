#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
  srand(time(NULL));
  
  int n = atoi(argv[1]);
  int mod = atoi(argv[2]);
  int x = atoi(argv[3]);

  int* a;
  
  a = malloc(sizeof(int)*n);

  for(size_t i = 0; i < n; i++){
    a[i] = rand() % mod;
    printf("%d\t", a[i]);
  }
  printf("\n");

  int k = 0;
  for(size_t i = 0; i < n; i++){
    if (a[i] < x){
      k++;
      printf("%d\t",(int)(i+1));
    }
    else{
      printf("_\t");
    }
  }
  printf("\nTotal: %d\n", k);


  free(a);
  return 0;
  
}
