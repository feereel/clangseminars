#include <stdio.h>
#include <stdlib.h>

#define QUICK_SORT(T) void Sort_##T(T array[], int size) { \
  qsort(array, size, sizeof(T), cmp); \
};

int cmp(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

QUICK_SORT(int)
QUICK_SORT(float)

int main(){
  int a[4] = {2,3,3,1};
  Sort_int(a, 4);

  for(size_t i = 0; i < 4; i++){
    printf("%d\n", a[i]);
  }
}
