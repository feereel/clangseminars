#include <stdio.h>
#include <string.h>


int GetBinLen(int number);


int main(){
  char key[256];
  char filename[80];
  scanf("%s %s", filename, key);

  FILE* fptr = fopen(filename, "r+");
  FILE* tmp = tmpfile();

  size_t len = strlen(key);


  char c;
  int i = 0;
  while((c = fgetc(fptr)) != EOF){
    putc(c ^ key[i], tmp);
    i = (i + 1) % len;
  }

  fseek(tmp, -ftell(tmp), SEEK_CUR);

  fptr = fopen(filename, "w");
  while((c = fgetc(tmp)) != EOF){
    fputc(c, fptr);
  }
  fclose(tmp);
  fclose(fptr);
}
