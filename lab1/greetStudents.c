#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
	//array of names
	char *args[4]={"./greeting", "Ann", "Bob", "Carl"};
	
	//forking
	int status, i, retpid;
	int pid[2];
	for(i = 0; i <= 2; i++){
		if((pid[i] = fork()) == 0){
			execlp(args[0], args[i+1]);
			exit(100+i);
		} else if (pid[i] < 0){
			printf("fork error: %s\n", strerror(errno));
		}
	}
	//reap children in order
	i = 0;
	while ((retpid = waitpid(pid[i++], &status, 0)) > 0) {
		if (!(WIFEXITED(status))){
			printf("child %d terminated abnormally\n", retpid);
		}
	}
	if (errno != ECHILD){
		printf("waitpid error");
	}
	printf("Parent Finished\n");
	exit(0);
	
}
