#include "matrix.h"
#include <time.h> 

Matrix InitMtr(size_t m, size_t n){
  Matrix mtr;
  mtr.m = m;
  mtr.n = n;
  mtr.self = (double**)malloc(sizeof(double*) * m);
  for(size_t i = 0; i < m; i++){
    mtr.self[i] = (double*)malloc(sizeof(double) * n);
  }
  return mtr;
}

void FreeMtr(Matrix mtr){
  for(size_t i = 0; i<mtr.m;i++)
    free(mtr.self[i]);
  free(mtr.self);
}

double RandDouble(double min, double max) 
{
  double range = (max - min); 
  double div = RAND_MAX / range;
  return min + (rand() / div);
}

double* ReadMtrRow(size_t lenght){
  double* row = (double*)malloc(sizeof(double) * lenght);
  for(size_t i = 0; i < lenght; i++){
    scanf("%lf", &row[i]);
  }
  return row;
}

Matrix CopyMtr(Matrix from){
  Matrix mtr = InitMtr(from.m, from.n);
  for(size_t i = 0; i < from.m; i++){
    for(size_t j = 0; j < from.n; j++){
      mtr.self[i][j] = from.self[i][j];
    }
  }
  return mtr;
}

Matrix IdentityMtr(size_t n){
  Matrix mtr = InitMtr(n,n); 
  for(size_t i = 0; i < n; i++){
    mtr.self[i][i] = 1;
  }
  return mtr;
}

void RandFillMtr(Matrix mtr, double borderA, double borderB){
  for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      mtr.self[i][j] = RandDouble(borderA, borderB);
    }
  }
}

void FillMtr(Matrix mtr){
  for(size_t i = 0; i < mtr.m; i++){
    double* row = ReadMtrRow(mtr.n);
    for(size_t j = 0; j < mtr.n; j++){
      mtr.self[i][j] = row[j];
    }
    free(row);
  }
}

void FillFFMtr(Matrix mtr, FILE* file){
   for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      fscanf(file,"%lf", &mtr.self[i][j]);
    }
  }
}

void PrintMtr(Matrix mtr){
 for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      printf("%.1lf\t", mtr.self[i][j]);
    }
    printf("\n");
  }
    printf("\n");
}

Matrix SumMtr(Matrix mtr1, Matrix mtr2){
  if(mtr1.m != mtr2.m || mtr1.n != mtr2.n){
    printf("Разные размеры матриц для суммирования");
    exit(0);
  }

  Matrix mtr = InitMtr(mtr1.m,mtr1.n);

  for(size_t i = 0; i < mtr1.m; i++){
    for(size_t j = 0; j < mtr1.n; j++){
      mtr.self[i][j] = mtr1.self[i][j] + mtr2.self[i][j];
    }
  }
  return mtr;
}

Matrix DifMtr(Matrix mtr1, Matrix mtr2){
  if(mtr1.m != mtr2.m || mtr1.n != mtr2.n){
    printf("Разные размеры матриц для разности");
    exit(0);
  }

  Matrix mtr = InitMtr(mtr1.m,mtr1.n);

  for(size_t i = 0; i < mtr1.m; i++){
    for(size_t j = 0; j < mtr1.n; j++){
      mtr.self[i][j] = mtr1.self[i][j] - mtr2.self[i][j];
    }
  }
  return mtr;
}

void ConstMulMtr(Matrix mtr, double value){ 
  for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      mtr.self[i][j] *= value;
    }
  }
}

Matrix MulMtr(Matrix mtr1, Matrix mtr2){
  if(mtr1.n != mtr2.m){
    printf("Матрицы не соответсвуют размеру m*n и n*k\n");
    exit(0);
  }

  Matrix mtr = InitMtr(mtr1.m,mtr2.n);


  double time_spent = 0.0;
  clock_t begin = clock();
  for(size_t i = 0; i < mtr1.m; i++){
    for(size_t j = 0; j < mtr2.n; j++){
      mtr.self[i][j] = 0;
      for(size_t k = 0; k < mtr1.n; k++)
        mtr.self[i][j] += mtr1.self[i][k] * mtr2.self[k][j];
    }
  }
  clock_t end = clock();

  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("The elapsed time is %f seconds\n", time_spent);
  return mtr;
}

Matrix TranspMtr(Matrix mtr){

  Matrix nmtr = InitMtr(mtr.n, mtr.m);

  for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      nmtr.self[j][i] = mtr.self[i][j];
    }
  }

  return nmtr;
}

Matrix MinorMtr(Matrix mtr, size_t pos_i, size_t pos_j){
  if (pos_i >= mtr.m || pos_j >= mtr.n){
    printf("Указаны неверные позиции (i,j) для вычисления минора\n");
    exit(0);
  }

  Matrix minor = InitMtr(mtr.m - 1, mtr.n - 1);
  for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      if (i < pos_i && j < pos_j){
        minor.self[i][j] = mtr.self[i][j];
      } else if (i < pos_i && j > pos_j){
        minor.self[i][j-1] = mtr.self[i][j];
      } else if (i > pos_i && j < pos_j){
        minor.self[i-1][j] = mtr.self[i][j];
      } else if ( i > pos_i && j > pos_j){
        minor.self[i-1][j-1] = mtr.self[i][j];
      }
    }
  }
  return minor;
}

double DetMtr(Matrix mtr){ 
  if(mtr.n != mtr.m){
    printf("Матрица не соответсвует размеру m*m\n");
    exit(0);
  }

  if (mtr.n == 1) {
    return mtr.self[0][0];
  } else if (mtr.n == 2) {
    return (mtr.self[0][0] * mtr.self[1][1]) - (mtr.self[0][1] * mtr.self[1][0]);
  }

  double res = 0;
  int sign = 1;
  for(size_t i = 0; i < mtr.n; i++){
    Matrix minor = MinorMtr(mtr, 0, i);
    res += sign * mtr.self[0][i] * DetMtr(minor);
    FreeMtr(minor);

    sign *= -1;
  }
  return res;
}

Matrix ReversedMtr(Matrix mtr){
  if(mtr.n != mtr.m){
    printf("Матрица не соответсвует размеру m*m\n");
    exit(0);
  }
  double detmtr = DetMtr(mtr);
  if (fabs(detmtr) < EPSELON){
    printf("Определить равен нулю!\n");
    exit(0);
  }

  Matrix revmtr = InitMtr(mtr.n, mtr.m); 
  for(size_t i = 0; i < mtr.m; i++){
    for(size_t j = 0; j < mtr.n; j++){
      Matrix minor = MinorMtr(mtr, i, j);
      revmtr.self[j][i] = pow(-1, i + j) * DetMtr(minor); 
      FreeMtr(minor);
    }
  }

  ConstMulMtr(revmtr, 1/detmtr);
  return revmtr;
}