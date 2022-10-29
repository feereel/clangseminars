#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int NODBinw(int a, int b){
  int res = 1;
  while(!(a&1) && !(b&1)){
      res <<= 1;
      a >>= 1;
      b >>= 1;
  }
  while(!(a&1))
    a>>=1;
  while(!(b&1))
    b>>=1;

  while(a !=0 && b != 0){
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  return res * (a+b);
}

int main(int argc, char* argv[]){
  int inp1,inp2;
  sscanf(argv[1], "%d", &inp1);
  sscanf(argv[2], "%d", &inp2);

  int answ2 = NODBinw(inp1,inp2);

  printf("%d\n", answ2);
}
