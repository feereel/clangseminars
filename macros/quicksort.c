#include <stdio.h>
#include <stdlib.h>

#define CMP_BY(T) int cmp_##T(const void* a, const void* b) {return *(T*)a - *(T*)b;}

CMP_BY(int)
CMP_BY(float)

#define QUICK_SORT(T) void Sort_##T(T array[], T size) { \
  qsort(array, size, sizeof(T), cmp_##T); \
};

QUICK_SORT(int)
QUICK_SORT(float)

int main(){
  int a[4] = {2,3,3,1};
  Sort_int(a, 4);

  for(size_t i = 0; i < 4; i++){
    printf("%d\n", a[i]);
  }
}
