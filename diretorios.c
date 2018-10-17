#include <dirent.h> 
#include <stdio.h> 
#include<unistd.h> 
#include <string.h>

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"
#define RED  "\x1B[31m"
#define YEL "\x1B[33m"



void show(char * path)
{
  DIR * d = opendir(path); // abre path
  if(d==NULL) return; // se nao abriu
  struct dirent * dir; // para os diretorios de entrada
  while ((dir = readdir(d)) != NULL) // se a gente consegue ler
    {
      if(dir-> d_type != DT_DIR) // se não é diretório printa na cor amarelo:azul
        printf("%sfile  \t:\t%s%s\n",YEL,BLUE, dir->d_name);
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // se é pasta
      {
        printf("%sfolder\t:\t %s%s\n",RED,GREEN, dir->d_name); // print com nome da pasta red:green
        char d_path[255]; // here I am using sprintf which is safer than strcat
        sprintf(d_path, "%s/%s", path, dir->d_name);
        show(d_path); // atualiza path
      }
    }
    closedir(d); // finaliza
}

int main(int argc, char **argv)
{
  char cwd[1024]; 
  getcwd(cwd, sizeof(cwd)); 

  printf("%s\n", NORMAL_COLOR);

    show(cwd);

  printf("%s\n", NORMAL_COLOR);
  return(0);
}