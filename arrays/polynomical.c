#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024
#define KOEFSIZE 32 //for integer

#define OUT 0
#define IN  1

size_t readline(char** str,size_t* len){

  char e;
  int wc = 0;

  int state = OUT;
  int i = 0; 
  while ((e = getchar()) != '\n'){

    if (e == ' '){
      if (state == OUT) continue;
      
      state = OUT;
    
    } else if (state == OUT){
      state = IN;
      wc += 1;
    }
    
    (*str)[i] = e;
    i++;
  }
  *len = i;
  return wc;
}

// [ a_n, a_n-1, ... , a_1] - equation
// [x^0, x^1, ... , x^(n-1)] - indices
char** splitline(char* str, size_t len, size_t n, char sep){
  
  char** eq;
  eq = malloc(sizeof(char*) * n);
  for (size_t i = 0; i < n; i++){
    eq[i] = malloc(sizeof(char) * KOEFSIZE);
  }

  int state = OUT;
  int k = -1;
  int ki = 0;
  for(size_t i = 0; i < len;i++){
    if (str[i] == ' '){
      if (state == OUT) continue;

      state = OUT;

    } else if (state == OUT){
      state = IN;
      k++;
      ki = 0;
    }
    if (k >= n) break;

    eq[k][ki] = str[i];
    ki++;
  }

  return eq;
}

int* multiplyeq(char** eq1, size_t n1, char** eq2, size_t n2){

  int* eq;
  size_t size = n1+n2;
  eq = malloc(sizeof(int) * size);
  for (size_t i = 0; i < size; i++){
    eq[i] = 0; 
  }

  for (size_t i = 0; i < n1; i++){
    for (size_t j = 0; j < n2; j++){ 
      //printf("i: %d j: %d eq1[i]: %d eq2[j]: %d koef: %d\n", (int)i, (int)j, atoi(eq1[i]), atoi(eq2[j]),eq[i+j]);
      eq[i+j] += atoi(eq1[i])*atoi(eq2[j]); 
    }
  }
  return eq;
}


int main(int argc, char* arhv[]){

  char* str1;
  char* str2;
  size_t bufSize = BUFSIZE;
  size_t wc1,wc2;
  size_t len1,len2;

  str1 = malloc(sizeof(char) * bufSize);
  str2 = malloc(sizeof(char) * bufSize);

  wc1 = readline(&str1, &len1);
  wc2 = readline(&str2, &len2);

  //printf("%s wc: %zu len: %zu\n", str1,wc1,len1);

  char** eq1;
  eq1 = splitline(str1, len1, wc1, ' ');

  char** eq2;
  eq2 = splitline(str2, len2, wc2, ' ');

  //for(size_t i = 0; i < wc1;i++){
  //  printf("%s\n", eq1[i]); 
  //}
  //printf("\n");


  int* eq;
  eq = multiplyeq(eq1,wc1,eq2,wc2);
  
  if (wc1+wc2 > 0 && eq[0] != 0)
    printf("%d ", eq[0]);

  for(size_t i = 1; i < wc1+wc2;i++){
    if (eq[i] == 0) continue;

    printf("+ (%d*x^[%d]) ", eq[i], (int)i);
  }
  printf("\n");


  //free memory
  free(str1);
  free(str2);

  for(size_t i = 0; i < wc1;i++){
    free(eq1[i]);
  }
  free(eq1);
  
  for(size_t i = 0; i < wc2;i++){
    free(eq2[i]);
  }
  free(eq2);

  free(eq);
  

}
