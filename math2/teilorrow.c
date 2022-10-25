#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define DELTA 0.1e-5

int main(int argc, char* argv[]){

  double a = atof(argv[1]);
  double b = atof(argv[2]);
  double step = atof(argv[3]);
  double accuracy = DBL_EPSILON;
  if (argc == 5)
    accuracy = atof(argv[4]);

  
  printf("_____________________________\n");
  printf("| x\t\t| f(x)\t\t| n\t| arcsin(x)\t|\n");
  
  int k = 0;
  double x = a;
  while (x-DELTA <= b && x<=1 && x>=-1){
    k++; 

    int n = 0;
    double arcsin = x;
    double teilor = x;

    while (fabs(teilor *= ((x*x*(2*n+1)*(2*n+1))/(2*(2*n+3)*(n+1)))) > accuracy){
      arcsin += teilor;
      n++;
    }

    printf("| %.10f\t| %.10f\t| %d\t| %.10f\t|\n", x, arcsin, n, asin(x)); 
    x = a + step*k;
  }
}
