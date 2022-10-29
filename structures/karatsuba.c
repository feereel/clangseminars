#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ui unsigned int
#define BASE 10

typedef union {
  struct {
    unsigned int right;
    unsigned int left;
  };
  unsigned long v;
}bigint;

bigint KaratsubaMult(bigint a, size_t n, int reci){
  //reci++;
  //for(size_t i = 0; i<reci;i++)
  //  printf("\t");
  //printf("n: %d, l: %d r:%d\n", (int)n, a.left, a.right);
  if (n <= 1 || a.left < 10 || a.right < 10){
    a.v = a.right * a.left; 
    return a;
  }

  if (n&1)
    n+=1;

  size_t half = n - n/2;

  ui ll = a.left / pow(BASE,half);
  ui lr = a.left - ll * pow(BASE,half);
  
  ui rl = a.right / pow(BASE,half);
  ui rr = a.right - rl * pow(BASE,half);


  //for(size_t i = 0; i<reci;i++)
  //  printf("\t");
  //printf("\\ll: %d lr: %d rl: %d rr:%d\n",ll,lr,rl,rr);

  bigint k1;
  k1.left = ll;
  k1.right = rl;
  k1 = KaratsubaMult(k1, n - half, reci);
  
  bigint k3;
  k3.left = lr;
  k3.right = rr;
  k3 = KaratsubaMult(k3, half, reci);

  bigint k2;
  k2.left = ll + lr;
  k2.right = rl + rr;
  k2 = KaratsubaMult(k2, half, reci);

  a.v = k1.v * pow(10, n) + (k2.v - k1.v - k3.v)*pow(10,half) + k3.v;
  //printf("%lu\n", a.v);
  return a;
}

int main (int argc, char* argv[]){

  bigint bn;
  bn.right = atoi(argv[1]);
  bn.left = atoi(argv[2]);

  int i = 0;
  ui a = bn.right;
  ui b = bn.left;
  while (a != 0 && b != 0){
    i++;
    a /= 10;
    b /= 10;
  }

  bn = KaratsubaMult(bn,i, -1);
  printf("%lu\n", bn.v);
  
}
