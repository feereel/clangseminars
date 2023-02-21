#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXVALUE 10
#define MAXMTRSIZE 10
#define MAXMATRIKSCOUNT 128
#define EPSELON 10e-5

typedef struct {
  size_t m;
  size_t n;
  double** self;
} Matrix;

typedef struct {
  char name[64];
  Matrix mtr;
} nMatrix;

Matrix InitMtr(size_t m, size_t n);
void FreeMtr(Matrix mtr);

Matrix CopyMtr(Matrix from);
Matrix IdentityMtr(size_t n);

void RandFillMtr(Matrix mtr, double borderA, double borderB);
void FillMtr(Matrix mtr);
void FillFFMtr(Matrix mtr, FILE* file);
void PrintMtr(Matrix mtr);

Matrix SumMtr(Matrix mtr1, Matrix mtr2);
Matrix DifMtr(Matrix mtr1, Matrix mtr2);
void ConstMulMtr(Matrix mtr, double value);
Matrix MulMtr(Matrix mtr1, Matrix mtr2);
Matrix TranspMtr(Matrix mtr);
Matrix MinorMtr(Matrix mtr, size_t pos_i, size_t pos_j);
double DetMtr(Matrix mtr);
Matrix ReversedMtr(Matrix mtr);

#endif /*MATRIX*/