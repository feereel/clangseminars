#include <stdio.h>

int powerOfTwo(int x) {
  int b = 1;
  int i = 0;
  while(x>b){
    b<<=1;
    i++;
  }
  if (x==b || x == 0)
    return i;
  else
    return -1;
}

int isPowerOfTwo(int x){ 
  return  x < 0 ? -2: powerOfTwo(x);
}

int main(int argc, char* argv[]){
  int inp;
  sscanf(argv[1], "%d", &inp);

  printf("%d\n", isPowerOfTwo(inp));
}
