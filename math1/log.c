#include <stdio.h>

int isPowerOf(int base,int val) {
  if (val<0)
    return -2;
    
  int t = 1;
  int k = 0;

  while (t<val){
    t *= base;
    ++k;
  }
  
  if (val == t)
    return k;
  else
    return -1;
}


int main(int argc, char* argv[]){
  int inp;
  sscanf(argv[1], "%d", &inp);

  printf("%d\n", isPowerOf(2,inp));
}
