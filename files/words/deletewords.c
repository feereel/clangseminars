#include <stdio.h>



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
