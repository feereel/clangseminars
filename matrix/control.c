#include "matrix.h"
#include <time.h>
#include <string.h>

Matrix InputMtr() {
  printf("Выбери способ  ввода:\n"
         "0 - консоль\n"
         "1 - файл\n"
         "2 - случайное заполнение матрицы\n"
         "3 - случайная матрица\n"
         "-> "); 
  int inp = 3;
  scanf("%d", &inp);

  int m,n = 0;
  FILE* file;
  if(inp == 0 || inp == 2){
    printf("ВВедите размер матрицы m*n (Если m = n = 0 - случайная матрица): ");
    scanf("%d %d", &m, &n);
  } else if (inp == 3){
      m = rand() % MAXMTRSIZE + 1;
      n = rand() % MAXMTRSIZE + 1;
  } else if (inp == 1){
    printf("ВВедите название файла: ");
    char fname[256];
    scanf("%s", fname);
    file = fopen(fname, "r");
    fscanf(file,"%d %d", &m, &n);
  }

  if (m == 0 || n == 0){
    printf("Неверные значения размеры матрицы: m=%d n=%d\n", m, n);
    exit(-1);
  }

  Matrix mtr = InitMtr(m,n);

  double a,b;
  switch(inp){
    case 3:
      a = -MAXVALUE;
      b = MAXVALUE;
      RandFillMtr(mtr, a, b);
      break;
    case 2:
      printf("Введите диапазон значений a-b: ");
      scanf("%lf %lf", &a, &b);
      RandFillMtr(mtr, a, b);
      break;
    case 1:
      FillFFMtr(mtr, file);
      break;
    default:
      FillMtr(mtr);
      break;
  }

  if (file == NULL)
    fclose(file);

  return mtr;
}


int AddMtr(nMatrix* mtrs, size_t count, Matrix mtr){
  if(count >= MAXMATRIKSCOUNT){
    printf("Достигнуто максимальное кол-во матриц\n");
  } else {
    printf("Введите название матрицы: ");
    scanf("%s", mtrs[count].name);
    mtrs[count++].mtr = mtr;
  }
  return count;
}

int FindMtr(nMatrix* mtrs, size_t count, char* name){
  int index = -1;
  for(int i = 0; i < count; i++){
    if(strcmp(mtrs[i].name, name) == 0){
      return i;
    }
  }
  return index;
}

void ShownMtrs(nMatrix* mtrs, size_t count){
  printf("Матрицы:\n");
  for(size_t i = 0; i < count; i++){
    printf("%s\t", mtrs[i].name);
  }
  printf("\n");
}

void ShowMtrs(nMatrix* mtrs, size_t count){
  ShownMtrs(mtrs, count);
  while(1){
    printf("Чтобы вывести матрицу введите название или q для выхода:\n-> ");
    char name[64];
    scanf("%s", name);

    if(strcmp(name,"q") == 0)
      break;
      
    int ind = FindMtr(mtrs, count, name);
    if (ind >= 0){
      PrintMtr(mtrs[ind].mtr);
    }
  }
}

void DeleteMtrfp(nMatrix* mtrs, size_t count, int ind){
  FreeMtr(mtrs[ind].mtr);
  for(size_t i = ind; i < count-1; i++){
    strcpy(mtrs[i].name, mtrs[i+1].name);
    mtrs[i].mtr = mtrs[i+1].mtr;
  }
}

size_t DeleteMtr(nMatrix* mtrs, size_t count){
  while(1){
    ShownMtrs(mtrs, count);
    printf("Чтобы удалить матрицу введине название или q для выхода:\n-> ");
    char name[64];
    scanf("%s", name);

    if(strcmp(name,"q") == 0)
      break;
    
    int ind = FindMtr(mtrs, count, name);
    if (ind >= 0){
      DeleteMtrfp(mtrs, count, ind);
      count -= 1;
    }
  }
  return count;
}

int ArifmeticMtr(nMatrix* mtrs, size_t count){
  printf("Сложение: A + B\n"
         "Вычитание: A - B\n"
         "Умножение: A * B\n"
         "Транспонирование: ! A\n"
         "Определитель: $ A\n"
         "Обратная матрица: ^ A\n\n");

  enum Operation {Add = 0, Sub = 1, Mul = 2, Trn = 3, Rev = 4};
  while(1){
    ShownMtrs(mtrs,count);
    printf("Введите арифметическое выржание или q для выхода:\n-> ");
    char p1[64];
    char p2[64];
    char p3[64];
    scanf("%s", p1);

    if(strcmp(p1, "q") == 0)
      break;

    Matrix mtr;
    if (p1[0] == '^') { 
      scanf("%s", p2);
      int ind = FindMtr(mtrs, count, p2);
      if (ind >= 0){
        mtr = ReversedMtr(mtrs[ind].mtr);
      } else {
        continue;
      }
    } else if (p1[0] == '!') {
      scanf("%s", p2);
      int ind = FindMtr(mtrs, count, p2);
      if (ind >= 0){
        mtr = TranspMtr(mtrs[ind].mtr);
      } else {
        continue;
      }
    } else if (p1[0] == '$'){
      scanf("%s", p2);
      int ind = FindMtr(mtrs, count, p2);
      if (ind >= 0){
        printf("Опредитель матрицы '%s' = %lf\n", mtrs[ind].name ,DetMtr(mtrs[ind].mtr));
      }
      continue;
    } else {
      scanf("%s", p2);
      scanf("%s", p3);
      int indA = FindMtr(mtrs, count, p1);
      int indB = FindMtr(mtrs, count, p3);

      if (indA < 0 || indB < 0)
        continue;

      if (strcmp(p2, "+") == 0) {
        mtr = SumMtr(mtrs[indA].mtr, mtrs[indB].mtr);
      } else if (strcmp(p2, "-") == 0) {
        mtr = DifMtr(mtrs[indA].mtr, mtrs[indB].mtr);
      } else if (strcmp(p2, "*") == 0) {
        mtr = MulMtr(mtrs[indA].mtr, mtrs[indB].mtr);
      }
      else {
        continue;
      }
    }
    count = AddMtr(mtrs, count, mtr);
  }
  return count;
}

int main(int argc, char* argv[]){
  srand(time(NULL));

  nMatrix mtrs[MAXMATRIKSCOUNT];
  size_t count = 0;
  int flag = 1;
  while(flag){
    printf("\n___\n");
    printf("Выберите команду:\n"
           "1 - просмотреть матрицы\n"
           "2 - добавить матрицу\n"
           "3 - удалить матрицу\n"
           "4 - операции с матрицами\n"
           "0 - выйти\n"
           "-> ");
    int mode;
    scanf("%d", &mode);
    Matrix mtr;
    switch(mode){
      case 1:
        ShowMtrs(mtrs, count);
        break;
      case 2:
        mtr = InputMtr();
        count = AddMtr(mtrs, count, mtr);
        break;
      case 3:
        count = DeleteMtr(mtrs, count);
        break;
      case 4:
        count = ArifmeticMtr(mtrs, count);
        break;
      default:
        flag = 0;
    }
  }

  for(size_t i = 0; i < count; i++)
  {
    FreeMtr(mtrs[i].mtr);
  }
}
