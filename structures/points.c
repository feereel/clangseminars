#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER 64

typedef struct {
  int x;
  int y;
} Point;

void Input(Point* p){
  char line[BUFFER];
  char sep[] = " ";

  scanf("%[^\n]", line);

  char* ptr = strtok(line, sep);

  int a[] = {0,0};
  int i = 0;
  while(ptr != NULL){
    a[i] = atoi(ptr);
    ptr = strtok(NULL,sep);
    i++;
  }
  p->x = a[0];
  p->y = a[1];

  free(ptr);
  return;
}

int main(int argc, char* argv[]){
  Point p1, p2, p3, p4;
  Input(&p1);

  printf("x: %d, y: %d\n", p1.x, p1.y);
  printf("x: %d, y: %d\n", p2.x, p2.y);

  int len = sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
  printf("Segment lenght: %d\n", len);

  Input(&p2);

  return 1;
}
