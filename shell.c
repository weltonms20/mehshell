
// C Program to design a shell in Linux 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
  
#define MAXCOM 1000
#define MAXLIST 100 // max numeros de comandos
  
#define clear() printf("\033[H\033[J") 

void contagem(int n){
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d\n",n-i );
        sleep(1);
    }
}
  
void init_shell() 
{ 
    clear();
    printf("\n\n\n\n\t\tCOMPUTAÇÃO\n\n\nEPISÓDIO DE HOJE: 'HELTER E WELTON SE UNIRAM PRA FABRICAR UM SHELL!!!!\n\t\t   O QUE SERÁ QUE DEU?'\n\n"); 
    char* username = getenv("USER"); 
    printf("\n\n\nOlá senhor(a): @%s", username); 
    printf("\nBoa sorte aí em usar isso ae.\n");
    contagem(10);
    clear(); 
} 
  
int takeInput(char* str) 
{ 
    char* buf; 
  
    buf = readline("\nDALHESHELL>> "); 
    if (strlen(buf) != 0) { 
        add_history(buf); 
        strcpy(str, buf); 
        return 0; 
    } else { 
        return 1; 
    } 
} 

void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDirretorio : %s", cwd); 
} 
  
void execArgs(char** parsed) 
{ 
    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 
    } else { 
        wait(NULL);  
        return; 
    } 
} 

  

int ownCmdHandler(char** parsed) 
{ 
    int NoOfOwnCmds = 5, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username; 
  
    ListOfOwnCmds[0] = "exit"; //ok
    ListOfOwnCmds[1] = "cd"; //ok
    ListOfOwnCmds[2] = "help"; //ok
    ListOfOwnCmds[3] = "hello"; //ok
    ListOfOwnCmds[4] = "diretorios"; //ok
    ListOfOwnCmds[5] = "findIn";
  
    for (i = 0; i < NoOfOwnCmds; i++) { 
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
            switchOwnArg = i + 1; 
            break; 
        } 
    } 
  
    switch (switchOwnArg) { 
    case 1: 
        printf("\nObrigado por usar nossar produções\n"); 
        exit(0); 
    case 2: 
        chdir(parsed[1]); 
        return 1; 
    case 3:
        parsed[0]="./help"; 
        return 1; 
    case 4: 
        parsed[0]="./hello";
        return 1; 
    case 5: 
        parsed[0]="./diretorios"; 
        return 1; 
    case 6: 
        parsed[0]="./findIn"; 
        return 1; 
    default: 
        break; 
    } 
  
    return 0; 
} 

  
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
  
int processString(char* str, char** parsed) 
{ 
  
    char* strpiped[2]; 
  
    parseSpace(str, parsed); 
  
    if (ownCmdHandler(parsed)) 
        return 0; 
    else
        return 1; 
} 
  
int main() 
{ 
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    int execFlag = 0; 
    init_shell(); 
  
    while (1) { 
        // print shell line 
        printDir(); 
        // take input 
        if (takeInput(inputString)) 
            continue; 
        // process 
        execFlag = processString(inputString, 
        parsedArgs); 
        // execflag returns zero if there is no command 
        // or it is a builtin command, 
        // 1 if it is a simple command 
        // 2 if it is including a pipe. 

        execArgs(parsedArgs); 

    } 
    return 0; 
} 
