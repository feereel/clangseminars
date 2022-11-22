#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ll unsigned long
#define BASE 10

typedef union {
  struct {
    unsigned long right;
    unsigned long left;
  };
  struct{
    unsigned long rright;
    unsigned long rmid;
    unsigned long rleft;
  };
} bigint;

int GetLen(int number){
  int c = 0;
  while (number > 0){
    number/=10;
    c++;
  }
  return c;
}

int* GetNumbers(int numbers, int len){
  int* array = malloc(sizeof(int) * len);
  for(int i = 0; i < len; i++){
    array[len - 1 - i] = numbers % 10;
    numbers /= 10;
  }
  return array;
}

bigint KaratsubaMult(bigint inp, int n){
  int half = n/2;
  ll pll = inp.left / pow(10, half);
  ll plr = inp.left - pll * pow(10, half);
  ll prl = inp.right / pow(10, half);
  ll prr = inp.right - prl * pow(10,half);

  printf("pll: %lu plr: %lu prl: %lu prr: %lu\n", pll, plr, prl, prr);

  ll rl = pll * prl;
  ll rr = plr * prr;
  ll rm = (pll + plr) * (prl + prr) - rl - rr;

  inp.rleft = rl;
  inp.rright = rr;
  inp.rmid = rm;

  return inp;
}

void PrintBigint(bigint inp, size_t len){
  printf("\n");

  size_t rlen = GetLen(inp.rright);
  int* rarr = GetNumbers(inp.rright, rlen);
  for(int i = 0; i < 2 * len-rlen; i++){
    printf("_ ");
  }
  for(int i = 0; i < rlen; i++){
    printf("%d ", rarr[i]);
  }
  printf("\n");
  free(rarr);

  size_t mlen = GetLen(inp.rmid);
  int* marr = GetNumbers(inp.rmid, mlen);
  for(int i = 0; i < 2 * len - mlen - len / 2; i++){
    printf("_ ");
  }
  for(int i = 0; i < mlen; i++){
    printf("%d ", marr[i]);
  }
  for(int i = 0; i < len / 2; i++){
    printf("_ ");
  }
  printf("\n");
  free(marr);

  size_t llen = GetLen(inp.rleft);
  int k = 0;
  if (len&1)
    k = -1;

  int* larr = GetNumbers(inp.rleft, llen);
  for(int i = 0; i < len - llen - k; i++){
    printf("_ ");
  }
  for(int i = 0; i < llen; i++){
    printf("%d ", larr[i]);
  }
  for(int i = 0; i < len + k; i++){
    printf("_ ");
  }
  printf("\n");
  free(larr);
}

int main (int argc, char* argv[]){
  bigint bn;
  ll a, b;
  scanf("%lu %lu", &a, &b);
  bn.right = b;
  bn.left = a;
  
  size_t len = GetLen(a);

  printf("%lu %lu \n", bn.right, bn.left);
  
  bn = KaratsubaMult(bn, len);
  printf("%lu-%lu-%lu\n", bn.rleft, bn.rmid, bn.rright);
  PrintBigint(bn, len);
}
