#include "functions.h"
#include <stdio.h>

void WriteMtr(int** mtr, int mtrSize, FILE* fout) {
  for(size_t i = 0; i < mtrSize; i++){
    char line[mtrSize*2 + 1];
    for(size_t j = 0; j < mtrSize*2; j+=2){
      if(mtr[i][j] == 0){
        line[j] = '_';
        line[j+1] = ' ';
      }
      else{
        line[j] = '*';
        line[j+1] = ' ';
      } 
    }
    line[mtrSize*2] = '\n';
    fputs(line, fout);
  }
  
  fputc('\n', fout);
}

int GetSize(FILE* fptr){
  char symb;
  int n = 0;
  while((symb = fgetc(fptr)) != '\n'){
    if (symb == '*' || symb == '_'){
      n+=1;
    }
  }
  fseek(fptr, -(n*2), SEEK_CUR);
  return n;
}


void Fill(int** mtr, size_t mtrSize, FILE* fptr){

  printf("\n");
  int i = 0;
  int k = 0;
 
  char symb;
  while ((symb = fgetc(fptr)) != EOF && k < mtrSize){
    if (symb == '*') {
      mtr[k][i] = ALIVE;
      //printf("d: %d i: %i\n", k, i);
      i++;
    }
    if (symb == '_')
      i++;
    if (i >= mtrSize) {
      i = 0;
      k++;
    }
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
