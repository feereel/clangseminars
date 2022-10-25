#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}

int main(int argc, char* argv[]){
  Point p1, p2, p3, p4;
  Input(&p1);
  Input(&p2);

  printf("x: %d, y: %d", p1.x, p1.y);
}
