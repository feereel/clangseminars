#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define CICLECOUNT 5

int main(int argc, char* argv[]){

  FILE* finp;
  finp = fopen("./input.txt", "r");

  if (finp == NULL){
    printf("Не удалось открыть файл для чтения");
    return 1;
  }

  int** mtr;
  size_t mtrSize = GetSize(finp);

  mtr = (int**)malloc(sizeof(int*) * mtrSize);

  for(int i = 0; i < mtrSize; i++){
    mtr[i] = (int*)malloc(sizeof(int) * mtrSize);
    for(int j = 0; j < mtrSize; j++){
      mtr[i][j] = DEAD;
    }
  }
 
  //RandFillMtr(mtr, mtrSize, lifesCount);
  Fill(mtr, mtrSize, finp);

  FILE* fout;
  fout = fopen("./output.txt", "w");
  WriteMtr(mtr, mtrSize, fout);

  for(int i = 0; i < CICLECOUNT; i++){
    //PrintNearbyCount(mtr, mtrSize);
    Cycle(mtr, mtrSize);
    WriteMtr(mtr, mtrSize, fout);
  }

  for(int i = 0; i < mtrSize;i++)
    free(mtr[i]);
  free(mtr);

}
