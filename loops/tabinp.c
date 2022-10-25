#include <stdio.h>

int main(int argc, char* argv[]){
  
  for(int i = 1; i < argc; ++i) {
    if (i % 2 == 1)
      printf("%d. %s\n", i, argv[i]);
    else 
      printf("\t%d. %s\n", i, argv[i]);
  }
}
