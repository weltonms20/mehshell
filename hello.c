#include <stdio.h>
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main(){
	char* username;
	username = getenv("USER"); 
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know m\n", 
            username); 
	return 1;
}
