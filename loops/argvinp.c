#include <stdio.h>

int main(int argc, char* argv[])
{
  int s = 0;

  if(argc > 2){
    s = argc-1;
    for(int i = 0; i <= 10;++i){
      s += i;
    }
  } else if (argc == 2) {
    for(int i = 0; i <= 50;++i){
      s += i;
    }
  } else{
    printf("sad");
    return 0;
  } 

  printf("%d\n",s);
  return 0;
}

