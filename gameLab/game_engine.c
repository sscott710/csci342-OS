/* Name: Savannah Scott
 * Date: 01/30/2022 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
	int userOption; //holds user's choice for menu
	//these variables help with execution, and holding pids
	int status, i, retpid, player; 
	int pos = 0;
	int pid[100]; //100 is arbitrary, can be changed to anything
	while(1){
		//print menu and get user input
		printf("1. Spawn player\n");
		printf("2. Injure player\n");
		printf("3. Heal player\n");
		printf("4. List player\n");
		printf("5. Quit\n");
		printf("Enter your option: ");
		scanf("%d",&userOption); 
		
		//option 1
		if (userOption == 1){
			int x = pos;
			pos++;
			//make child process, run player.c, checks for error
			if ((pid[x] = fork()) == 0){
				execv("./player1", NULL);
			} else if (pid[x] < 0){
				printf("fork error: %s\n", strerror(errno));
			}
		}

		//option 2
		if (userOption == 2){
			printf("current players\n"); 
			//display active players for user to choose
			for (i = 0; i < pos; i++){
				printf("ID: %d\n", pid[i]);
			}
			printf("pick a player and enter their ID: ");
			scanf("%d", &player);
			//decrement health by 1, check for error
			if ((kill(player, SIGUSR1)) == -1){
				printf("kill error: %s\n", strerror(errno));
			}
			sleep(1);
		}

		//option 3
		if (userOption == 3){
			printf("current players\n");
			//display active players for user
			for (i = 0; i< pos; i++){
				printf("ID: %d\n", pid[i]);
			}
			printf("pick a player and enter their ID: ");
			scanf("%d", &player);
			//increment health by 1, check for errors
			if ((kill(player, SIGUSR2)) == -1){
				printf("kill error: %s\n", strerror(errno));
			}
			sleep(1);
		}
		
		//option 4
		if (userOption == 4){
			printf("all players and their health\n");
			//prints info for all children, checks for errors
			for (i = 0; i < pos; i++){
				if((kill(pid[i], SIGINT)) == -1){
					printf("kill error: %s\n", strerror(errno));
				}
			}
			sleep(1);
		}

		//option 5
		if (userOption == 5){
			//kill child processes, check for errors
			for (i = 0; i < pos; i++){
				if ((kill(pid[i], SIGKILL)) == -1){
					printf("kill error: %s\n", strerror(errno));
				}
				if ((kill(getpid(), SIGCHLD)) == -1){
					printf("kill error: %s\n", strerror(errno));
				}
			}
			i = 0;
			//reap the child processes
			//error check assumes child was terminated by SIGKILL (normal and intended result)
			while((retpid = waitpid(pid[i++], &status, 0)) > 0){
				if (!(WIFEXITED(status))){
					if((WTERMSIG(status)) != 9){
						printf("child %d terminated abnormally\n", pid);
					}
				}
			}	
			if (errno != ECHILD){
				printf("waitpid error\n");
			}
			printf("GAME OVER\n");
			exit(0);
		}
	}
	return(0);
		
}
