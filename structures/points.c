#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER 64
#define delta 0.1e-7

typedef struct {
  double x;
  double y;
} Point, Vector;

void Input(Point* p){
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

  free(ptr);
}

Vector GetVector(Point p1,Point p2){
  Vector nv;
  nv.x = p2.x-p1.x;
  nv.y = p2.y-p1.y;
  return nv;
}

//returns z coordinate, because vector has only 2 directions
double GetVectorProduct(Vector v1, Vector v2){
  return v1.x*v2.y-v2.x*v1.y;
}

int main(int argc, char* argv[]){
  Point p1, p2, p3, p4;
  Input(&p1);
  Input(&p2);

  //printf("x: %f, y: %f\n", p1.x, p1.y);
  //printf("x: %f, y: %f\n", p2.x, p2.y);

  //task 1
  double len = sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
  printf("Segment lenght: %f\n", len);

  //task 2
  Input(&p3);
  Vector vA, vB, vC;
  vA = GetVector(p1,p2);
  vB = GetVector(p2,p3);
  vC = GetVector(p3,p1);

  double vpr = GetVectorProduct(vA,vB);
  if (fabs(vpr) < delta)
    printf("Points on the same line\n");
  else
    printf("Point not on the same line\n");
  
  //task 3
  Input(&p4);
  Vector vA4, vB4, vC4;
  vA4 = GetVector(p1,p4);
  vB4 = GetVector(p2,p4);
  vC4 = GetVector(p3,p4);

  double vpr1 = GetVectorProduct(vA, vA4);
  double vpr2 = GetVectorProduct(vB, vB4);
  double vpr3 = GetVectorProduct(vC, vC4);

  if ((vpr1 < 0 && vpr2 < 0 && vpr3 < 0) || (vpr1 > 0 && vpr2 > 0 && vpr3 > 0))
    printf("Point inside the triangle\n");
  else
    printf("Point outside the triangle\n");

  return 0;
}
