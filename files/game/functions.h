#include <stdio.h>

#define DEAD 0
#define ALIVE 1
#define DIEDNOW -1
#define ALIVENOW 2

void WriteMtr(int** mtr, int mtrSize, FILE* fout);
int GetSize(FILE* fptr);
void Fill(int** mtr, size_t mtrSize, FILE* fptr);
int CheckNearbyAlive(int **mtr, int mtrSize, int x, int y);
void EndOfCycle(int** mtr, int mtrSize);
void Cycle(int** mtr, int mtrSize);
