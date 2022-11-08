#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEAD 0
#define ALIVE 1
#define DIEDNOW -1
#define ALIVENOW 2

void RandFillMtr(int** mtr, int mtrSize, int lifesCount) {
  srand(time(NULL));

  for(size_t i = 0; i < lifesCount; i++){
    int a,b;
    do {
      a = rand() % mtrSize;
      b = rand() % mtrSize;
    } while (mtr[a][b] != 0);

    mtr[a][b] = ALIVE;
  }
}

int CheckNearbyAlive(int **mtr, int mtrSize, int x, int y){
  int count = 0;
  for(int i = x-1; i <= x + 1; i++){
    for(int j = y-1; j <= y + 1; j++){
      if(i >= mtrSize || i < 0 || j >= mtrSize || j < 0 || (i == x && j == y))
        continue;

      if(mtr[i][j] == ALIVE || mtr[i][j] == DIEDNOW)
        count++;
    }
  }
  return count;
}

void EndOfCycle(int** mtr, int mtrSize){
  for(size_t i = 0; i < mtrSize; i++){
    for(size_t j = 0; j < mtrSize; j++){
      if (mtr[i][j] == DIEDNOW)
        mtr[i][j] = DEAD;
      if (mtr[i][j] == ALIVENOW)
        mtr[i][j] = ALIVE;
    }
  }
}

void Cycle(int** mtr, int mtrSize){
  for(size_t i = 0; i < mtrSize; i++){
    for(size_t j = 0; j < mtrSize; j++){
      int countNearby = CheckNearbyAlive(mtr, mtrSize, i, j);

      if (mtr[i][j] == DEAD && countNearby == 3){
        mtr[i][j] = ALIVENOW;
      }
      if (mtr[i][j] == ALIVE && countNearby != 2 && countNearby != 3){
        mtr[i][j] = DIEDNOW;
      }
    }
  }
  EndOfCycle(mtr, mtrSize);
}

void PrintNearbyCount(int** mtr, int mtrSize){
  for(size_t i = 0; i < mtrSize; i++){
    for(size_t j = 0; j < mtrSize; j++){
      printf("%d ", CheckNearbyAlive(mtr, mtrSize, i, j));
    }
    printf("\n");
  }
  printf("\n");

}

void PrintMtr(int** mtr, int mtrSize) {
  for(size_t i = 0; i < mtrSize; i++){
    for(size_t j = 0; j < mtrSize; j++){
      if(mtr[i][j] == 0)
        printf("_ ");
      else
        printf("* ");
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char* argv[]){

  int mtrSize = atoi(argv[1]), lifesCount = atoi(argv[2]), cicleCount = atoi(argv[3]);

  int** mtr;
  mtr = (int**)malloc(sizeof(int*) * mtrSize);

  for(int i = 0; i < mtrSize; i++){
    mtr[i] = (int*)malloc(sizeof(int) * mtrSize);
    for(int j = 0; j < mtrSize; j++){
      mtr[i][j] = DEAD;
    }
  }

  RandFillMtr(mtr, mtrSize, lifesCount);
  PrintMtr(mtr, mtrSize);

  for(int i = 0; i < cicleCount; i++){
    //PrintNearbyCount(mtr, mtrSize);
    Cycle(mtr, mtrSize);
    PrintMtr(mtr, mtrSize);
  }

  for(int i = 0; i < mtrSize;i++)
    free(mtr[i]);
  free(mtr);

}
