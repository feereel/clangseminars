#include <stdio.h>
#include <string.h>


int main(){

  char filename[80];
  char symb;
  scanf("%s %c", filename, &symb);

  FILE* inp = fopen(filename, "r+");  
  FILE* tmp = tmpfile();

  char word[80];
  while(fscanf(inp, "%s", word) != EOF){ 
    if(word[0] != symb){
      fputs(word, tmp);
      fputs(" ", tmp);
    }
    else if(word[strlen(word)-1] == '.'){
      fputc('.', tmp);
    }
  }

  fseek(tmp, -ftell(tmp), SEEK_CUR);

  inp = fopen(filename, "w");

  char c = fgetc(tmp); 
  while (c != EOF)
  {
    fputc(c, inp);
    c = fgetc(tmp);
  }

  fclose(tmp);
  fclose(inp);
}
