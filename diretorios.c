#include <dirent.h> 
#include <stdio.h> 
#include<unistd.h> 
#include <string.h>

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"
#define RED  "\x1B[31m"
#define YEL "\x1B[33m"

void printTab(int tab){
  int i;
  for (i = 0; i < tab; ++i)
  {
    printf("\t");
  }
}


void show(char * path, int tab)
{
  DIR * d = opendir(path); // abre path
  if(d==NULL) return; // se nao abriu
  struct dirent * dir; // para os diretorios de entrada
  while ((dir = readdir(d)) != NULL) // se a gente consegue ler
    {
      if(dir-> d_type != DT_DIR){ // se não é diretório printa na cor amarelo:azul
        printf("%sfile   :",YEL);
        printTab(tab);
        printf("\t%s%s\n",BLUE, dir->d_name);
      }
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // se é pasta
      {
        printf("%sfolder :",RED); // print com nome da pasta red:green
        printTab(tab);
        printf("\t%s%s\n",GREEN, dir->d_name);
        char d_path[255]; // here I am using sprintf which is safer than strcat
        sprintf(d_path, "%s/%s", path, dir->d_name);
        show(d_path, tab+1); // atualiza path
      }
    }
    closedir(d); // finaliza
}

int main(int argc, char **argv)
{
  //printf("argc = %d\n", argc);
    int tab=0;
    char cwd[1024]; 
  if(argc==1){
    getcwd(cwd, sizeof(cwd)); 
  }else{
    strcpy(cwd,argv[1]);
  }

  printf("%s\n", NORMAL_COLOR);

  show(cwd,tab);

  printf("%s\n", NORMAL_COLOR);
  return(0);
}