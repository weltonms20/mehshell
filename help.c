
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 


int main(){
	puts("\n***HELP***(noob)"
        "\nLista de comandos:"
        "\n>cd \t-- era pra entrar em um determinado path a partir do atual"
        "\n>diretorios \t-- lista os diretorios do path atual"
        "\n>exit \t-- sai do shell"
        "\n>help \t-- essa tela aqui"
        "\n"); 
	return 1;
}