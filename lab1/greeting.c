#include <stdio.h>

int main(int argc, char *argv[]){
	//only works for single input
	if(argc == 2){
		printf("Hello %s\n", argv[1]);
	} else if(argc > 2){
		printf("too many arguments supplied.\n");
	} else{
		printf("one argument expected.\n");
	}

}
