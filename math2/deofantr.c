#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pair{
  int gcd;
  int x;
  int y;
};

struct pair ExtGCD(int a, int b, int x1, int y1, int x2, int y2){
   
  if (a == 0 || b == 0){
    struct pair answ = {.gcd = a+b, .x = x1, .y = y1};
    return answ;
  }
 
  int q;
  if (b > a){
    q = b/a;
    b = b - a * q;
  } else {
    q = a/b;
    a = a - b * q;
  }

  return ExtGCD(a,b,x2,y2,x1-x2*q,y1-y2*q);
}

int main(int argc, char* argv[]){

  
  int r0 = atoi(argv[1]);
  int x0 = 1;
  int y0 = 0;

  int r1 = atoi(argv[2]);
  int x1 = 0;
  int y1 = 1;

  int c = atoi(argv[3]);

  struct pair answ = ExtGCD(abs(r0),abs(r1),x0,y0,x1,y1);

  if (c%answ.gcd != 0){
    printf("No solution\n");
    return -1;
  }

  if (abs(r0) < abs(r1) && (
     r0 < 0 || r1 < 0 || (r0 > 0 && r1 > 0))){
    int t = answ.x;
    answ.x = answ.y;
    answ.y = t;
  }
  if (r0 < 0) answ.x *= -1;
  if (r1 < 0) answ.y *= -1; 

  int q = c/answ.gcd;
  answ.x *=q;
  answ.y *=q;

  //printf("%d * %d +  %d * %d = %d == %d  |x| + |y| = %d   %d\n",
  //       r0, answ.x, r1, answ.y, c,
  //        r0 * answ.x + r1*answ.y,
  //        abs(answ.x) + abs(answ.y), answ.gcd);

  //find minimux |x| + |y|
  int current = abs(answ.x) + abs(answ.y);

  int minusb = 0;
  while ((minusb = abs(answ.x - r1) + abs(answ.y + r0)) < current){
    answ.x -= r1;
    answ.y += r0;
    current = abs(answ.x) + abs(answ.y);
  }

  int plusp = 0;
  while ((plusp = abs(answ.x + r1) + abs(answ.y - r0)) < current){
    answ.x += r1;
    answ.y -= r0;
    current = abs(answ.x) + abs(answ.y);
  }
  //end

  printf("%d * %d +  %d * %d = %d\n", r0, answ.x, r1, answ.y, c);
  return 0;
}
