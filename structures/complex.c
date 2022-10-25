#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER 64

typedef struct {
  double x;
  double y;
} Complex;

typedef struct {
  double z;
  double sinf;
  double cosf;
} Polar;

void Input(Complex* p){
  char line[BUFFER];
  char sep[] = " ";

  fgets(line,BUFFER,stdin);

  char* ptr = strtok(line, sep);

  double a[] = {0,0};
  int i = 0;
  while(ptr != NULL){
    a[i] = atof(ptr);
    ptr = strtok(NULL,sep);
    i++;
  }
  p->x = a[0];
  p->y = a[1];
}

Complex ComplexSum(Complex a, Complex b){
  Complex c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return c;
}

Complex ComplexMul(Complex a, Complex b){
  Complex c;
  c.x = a.x*b.x - a.y*b.y;
  c.y = a.x*b.y + a.y*b.x;
  return c;
}

Complex ComplexDiv(Complex a, Complex b){
  Complex c;
  c.x = (a.x*b.x - a.y*b.y)/(b.x*b.x+b.y*b.y);
  c.y = (a.x*b.y + a.y*b.x)/(b.x*b.x+b.y*b.y);
  return c;
}

Polar ComplexPolar(Complex c){
  Polar p;
  p.z = sqrt(c.x*c.x + c.y*c.y);
  p.cosf = c.x/p.z;
  p.sinf = c.y/p.z;  
  return p;
} 


int main(int argc, char* argv[]){
  Complex a, b;
  Input(&a);
  Input(&b);

  printf("C1: z = %.2f + (%.2f)i\n", a.x, a.y); 
  printf("C2: z = %.2f + (%.2f)i\n", b.x, b.y);

  Complex cs = ComplexSum(a,b);
  Complex cm = ComplexMul(a,b);
  Complex cd = ComplexDiv(a,b);
  Polar pa = ComplexPolar(a);
  Polar pb = ComplexPolar(a);

  printf("C1 + C2 = %.2f + (%.2f)i\n", cs.x, cs.y);
  printf("C1 * C2 = %.2f + (%.2f)i\n", cm.x, cm.y);
  printf("C1 / C2 = %.2f + (%.2f)i\n", cd.x, cd.y);

  printf("\n'z = r * (cosf + i * sinf')\n");
  printf("C1: z = %.2f * (%.2f + i * %.2f)\n", pa.z, pa.cosf, pa.sinf);
  printf("C2: z = %.2f * (%.2f + i * %.2f)\n", pb.z, pb.cosf, pb.sinf);
}
