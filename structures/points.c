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

int main(int argc, char* argv[]){
  Point p1, p2, p3, p4;
  Input(&p1);
  Input(&p2);

  printf("x: %f, y: %f\n", p1.x, p1.y);
  printf("x: %f, y: %f\n", p2.x, p2.y);

  //task 1
  double len = sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
  printf("Segment lenght: %f\n", len);

  //task 2
  Input(&p3);
  Vector vA, vB, vC;
  vA = GetVector(p1,p2);
  vB = GetVector(p2,p3);
  vC = GetVector(p3,p1);

  double vectProductZ = vA.x*vB.y-vB.x*vA.y;
  if (fabs(vectProductZ) < delta)
    printf("Points on the same line");
  else
    printf("Point not on the same line");
  
  //task 3

  return 0;
}
