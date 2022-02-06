/* Name: Savannah Scott
 * Date: 01/27/2022 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int health_level = 5; //holds between 0 and 5; assumes every player begins healthy
//decrease health_level by 1
void decrease_health(int sig){
	health_level--;
	printf("HEALTH: %d\n", health_level);
	if (health_level == 0){
		printf("Enemy %d killed\n", getpid());
		exit(0);
	}
	return;
}
//increase health_level by 1
void increase_health(int sig){
	if (health_level < 5){
		health_level++;
		printf("HEALTH: %d\n", health_level);
	}
	return;
}
//print pid and health level
void print_health(int sig){
	printf("PID: %d\n", getpid());
	printf("HEALTH: %d\n", health_level);
	return;
}

int main(){
	//register handlers
	if (signal(SIGUSR1, decrease_health) == SIG_ERR){
		printf("signal error");
	}
	else if(signal(SIGUSR2, increase_health) == SIG_ERR){
		printf("signal error");
	}
	else if (signal(SIGINT, print_health) == SIG_ERR){
		printf("signal error");
	}
	//loop until terminated by game_engine option 5
	while(1){
		pause();
	}
	return(0);
}
