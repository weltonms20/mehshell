#include <dirent.h> 
#include <stdio.h> 
#include<unistd.h> 
#include <string.h>

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"
#define RED  "\x1B[31m"
#define YEL "\x1B[33m"

int achou=0;

void printFind(char* object,int achou, char* path){
  if(achou){
    printf("\nAchou arquivo %s in %s\n\n", object, path);
  }
}

void procura(char * path, char * object)
{ 
  printf("tentando abrir %s, tentando achar %s\n",path,object );
  DIR * d = opendir(path); // abre path
  if(d==NULL){
    return; // se nao achou
  }
  struct dirent * dir; // para os diretorios de entrada
  while ((dir = readdir(d)) != NULL) // se a gente consegue ler
    {
      /*
      if(dir-> d_type != DT_DIR) // se não é diretório printa na cor amarelo:azul
        printf("%sfile  \t:\t%s%s\n",YEL,BLUE, dir->d_name);
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // se é pasta
      {
        printf("%sfolder\t:\t %s%s\n",RED,GREEN, dir->d_name); // print com nome da pasta red:green
      }*/
      if(strcmp(dir->d_name,object)==0){
        achou=1;
        printFind(object,achou,path);
        return;
      }else{
        char d_path[255]; // here I am using sprintf which is safer than strcat
        sprintf(d_path, "%s/%s", path, dir->d_name);
        procura(d_path,object); // atualiza path
      }
      if(achou){
        return;
      }
    }
    closedir(d); // finaliza
}

int main(int argc, char **argv)
{
  achou=1;
  char cwd[1024]; 
  if(argc<2){
    printf("Poucos argumentos patrão, digita 'help'\n");
    return(0);
  }
  if(argc==2){
    getcwd(cwd, sizeof(cwd)); 
  }else{
    strcpy(cwd,argv[1]);
  }

  printf("%s\n", NORMAL_COLOR);

  if(argc==2){
    procura(cwd,argv[1]);
    if(!achou){
      printf("\nNão achou %s nessa arvore de arquivos\n\n",argv[1] );
    }
  }else if(argc==3){
    procura(cwd,argv[2]);
    if(!achou){
      printf("\nNão achou %s nessa arvore de arquivos\n\n",argv[2] );
    }
  }

  printf("%s\n", NORMAL_COLOR);
  return(0);
}