#include <stdio.h>
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main(){
	char* username;
	username = getenv("USER"); 
        printf("\nOi %s.\nTá gostando do shell?."
            "\nDigita help se tiver perdido\n;)\n\n", 
            username); 
	return 1;
}
