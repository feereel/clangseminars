#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int NODMod(int a,int b){
  while (a != 0 && b!= 0) {
    if (a > b)
      a = a % b;
    else
      b = b % a;
  }
  return a + b;
}

int NODRec(int a, int b){
  if (a == 0 || b == 0)
    return a+b;

  return a > b? NODRec(a%b,b): NODRec(a,b%a);
}

int NODBin(int a, int b){
  if (a == 0 || b == 0)
    return a + b;

  if (a % 2 == 0 && b % 2 == 0)
    return 2 * NODBin(a >> 1,b>>1);
  else if (a % 2 == 0)
    return NODBin(a >> 1,b);
  else if (b % 2 == 0)
    return NODBin(a,b >> 1);
  else if (a>b)
    return NODBin(a%b,b);
  else
    return NODBin(a,b%a);
}



int main(int argc, char* argv[]){
  int inp1,inp2;
  sscanf(argv[1], "%d", &inp1);
  sscanf(argv[2], "%d", &inp2);

  int answ = NODBin(inp1,inp2);

  printf("%d\n", answ);
}
