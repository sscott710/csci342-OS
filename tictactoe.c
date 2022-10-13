#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
//struct
struct threadInfo {
        char board[3][4];
        char currentPlayer;
        bool gameOver;
        bool winner;
        int dash;
};
void printBoard(char[3][4]);
bool gameOver(int dash);
bool checkWinner(char[3][4]);
void* playerX1(void *vargp);
void* playerO2(void *vargp);

int main(int argc, char **argv){
        printf("Let's play tic tac toe\n");
        struct threadInfo info;
        info.board;
        info.currentPlayer = 'X';
        info.gameOver = false;
        info.winner = false;
        info.dash = 9;
        int p = 0;
        int u = 0;
        for (; p <3; p++){
                for (; u <3; u++){
                        info.board[p][u] = '-';
                }
                u =0;
        }
        pthread_t tx, to;

        printBoard(info.board);

        //create X and O thread
        if ((pthread_create(&tx, NULL, playerX1, &info)) != 0){
                printf("error creating thread\n");
                exit(0);
        }
        if ((pthread_create(&to, NULL, playerO2, &info)) != 0){
                printf("error creating thread\n");
                exit(0);
        }

        //wait for threads to finish game
        if((pthread_join(tx, NULL)) != 0){
                printf("error reaping thread\n");
        }
        if((pthread_join(to, NULL)) != 0){
                printf("error reaping thread\n");
        }

        //end of game- print results
        printf("Results:\n");
        printBoard(info.board);
        if (info.gameOver && !info.winner){
                printf("tie\n");
        }
        else if (info.currentPlayer == 'X'){
                printf("Player 2 won\n");
        }
        else if(info.currentPlayer == 'O'){
                printf("Player1 won\n");
        }
        printf("End of Game\n");
        exit(1);


}

void* playerX1(void *vargp) {
        //create space last marked variable
        int row, col;
        srand(time(0));
        row = rand() % (2 +1 - 0) + 0;
        col = rand() % (2 + 1 -0) +0;
        struct threadInfo* info = (struct threadInfo*) vargp;
        //int d = info->dash;
        //loop until turn
        while((!info->gameOver) && (!info->winner)){
                while(info->currentPlayer != 'X'){
                        sleep(2); //add error catch?
                }
                printf("Player1\n");
                //first move random so not same result every time
                if (info->dash == 9){
                        info->board[row][col] = 'X';
                }
                if (info->dash == 7){
                if ((col == 0) || (col== 1)){
                                col = col +1;
                        }
                        else if (col== 2){
                                col = col -1;
                        }
                        info->board[row][col] = 'X';
                }
                if (info->dash < 6){
                        //defense
                        if ((info->board[0][0] == 'O') && ((info->board[0][0] == info->board[0][1]) || (info->board[0][0] == info->board[0][2]) || (info->board[0][1] == info->board[0][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[0][i] == '-' && info->board[0][i] != 'O'){
                                                info->board[0][i] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }

                        else if ((info->board[0][0] == 'O') && ((info->board[0][0] == info->board[1][0]) || (info->board[0][0] == info->board[2][0]) || (info->board[1][0]== info->board[2][0]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][0] == '-' && info->board[i][0] != 'O'){
                                                info->board[i][0] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'O') && ((info->board[0][0] == info->board[1][1]) || (info->board[0][0] == info->board[2][2]) || (info->board[1][1]== info->board[2][2]))){
                                if (info->board[0][0] == '-'&& info->board[0][0] != 'O'){
                                        info->board[0][0] = 'X';
                                }
                                else if (info->board[1][1] == '-' && info->board[1][1] != 'O'){
                                        info->board[1][1] = 'X';
                                }
                                else if (info->board[2][2] == '-' && info->board[2][2] != 'O'){
                                        info->board[2][2] = 'X';
                                }
                        }
                        else if ((info->board[0][2] == 'O') && ((info->board[0][2] == info->board[1][1]) || (info->board[0][2] == info->board[2][0]) || (info->board[0][2]== info->board[2][0]))){
                                if (info->board[0][2] == '-' && info->board[0][2] != 'O'){
                                        info->board[0][2] = 'X';
                                }
                                else if (info->board[1][1] == '-' && info->board[1][1] != 'O'){
                                        info->board[1][1] = 'X';
                                  }
                                else if (info->board[2][0] == '-' && info->board[2][0] != 'O'){
                                        info->board[2][0] = 'X';
                                }

                        }
                        else if ((info->board[1][0] == 'O') && ((info->board[1][0] == info->board[1][1]) || (info->board[1][0] == info->board[1][2]) || (info->board[1][1]== info->board[1][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[1][i] == '-'&& info->board[1][i] != 'O'){
                                                info->board[1][i] = 'X';
                                                row = 1;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[2][0] == 'O') && ((info->board[2][0] == info->board[2][1]) || (info->board[2][0] == info->board[2][2]) || (info->board[2][1]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[2][i] == '-'&& info->board[2][i] != 'O'){
                                                info->board[2][i] = 'X';
                                                row = 2;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][1] == 'O') && ((info->board[0][1] == info->board[1][1]) || (info->board[0][1] == info->board[2][1]) || (info->board[1][1]== info->board[2][1]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][1] == '-' && info->board[i][1] != 'O'){
                                                info->board[i][1] = 'X';
                                        }
                                }
                        }
                        else if ((info->board[0][2] == 'O') && ((info->board[0][2] == info->board[1][2]) || (info->board[0][2] == info->board[2][2]) || (info->board[1][2]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][2] == '-'&& info->board[2][i] != 'O'){
                                                info->board[1][2] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        //offence
                        else if ((info->board[0][0] == 'X') && ((info->board[0][0] == info->board[0][1]) || (info->board[0][0] == info->board[0][2]) || (info->board[0][1] == info->board[0][2]))){
                                int i =0;
                                for(; i<3;i++){
                                  if (info->board[0][i] == '-'&& info->board[0][i] != 'O'){
                                                info->board[0][i] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'X') && ((info->board[0][0] == info->board[1][0]) || (info->board[0][0] == info->board[2][0]) || (info->board[1][0]== info->board[2][0]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][0] == '-'&& info->board[i][0] != 'O'){
                                                info->board[i][0] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'X') && ((info->board[0][0] == info->board[1][1]) || (info->board[0][0] == info->board[2][2]) || (info->board[1][1]== info->board[2][2]))){
                                if (info->board[0][0] == '-'&& info->board[0][0] != 'O'){
                                        info->board[0][0] = 'X';
                                }
                                else if (info->board[1][1] == '-' && info->board[1][1] != 'O'){
                                        info->board[1][1] = 'X';
                                }
                                else if (info->board[2][2] == '-' && info->board[2][2] != 'O'){
                                        info->board[2][2] = 'X';
                                }
                        }
                        else if ((info->board[0][2] == 'X') && ((info->board[0][2] == info->board[1][1]) || (info->board[0][2] == info->board[2][0]) || (info->board[0][2]== info->board[2][0]))){
                                if (info->board[0][2] == '-' && info->board[0][2] != 'O'){
                                        info->board[0][2] = 'X';
                                }
                                else if (info->board[1][1] == '-' && info->board[1][1] != 'O'){
                                        info->board[1][1] = 'X';
                                }
                                else if (info->board[0][2] == '-' && info->board[0][2] != 'O'){
                                        info->board[0][2] = 'X';
                                }
                        }
                        else if ((info->board[1][0] == 'X') && ((info->board[1][0] == info->board[1][1]) || (info->board[1][0] == info->board[1][2]) || (info->board[1][1]== info->board[1][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[1][i] == '-' && info->board[1][i] != 'O'){
                                                info->board[1][i] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                           }
                        else if ((info->board[2][0] == 'X') && ((info->board[2][0] == info->board[2][1]) || (info->board[2][0] == info->board[2][2]) || (info->board[2][1]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[2][i] == '-'&& info->board[2][i] != 'O'){
                                                info->board[2][i] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][1] == 'X') && ((info->board[0][1] == info->board[1][1]) || (info->board[0][1] == info->board[2][1]) || (info->board[1][1]== info->board[2][1]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][1] == '-'&& info->board[i][1] != 'O'){
                                                info->board[i][1] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][2] == 'X') && ((info->board[0][2] == info->board[1][2]) || (info->board[0][2] == info->board[2][2]) || (info->board[1][2]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][2] == '-'&& info->board[i][2] != 'O'){
                                                info->board[i][2] = 'X';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                }
                printBoard(info->board);
                info->dash = info->dash-1;
                info->currentPlayer = 'O';
                info->gameOver =gameOver(info->dash);
                info->winner = checkWinner(info->board);

        }
        return NULL;
}

void* playerO2(void *vargp) {
        int row, col;
        srand(time(0));
        row = rand() % (2 +1 - 0) + 0;
        col = rand() % (2 + 1 -0) +0;
        struct threadInfo* info = (struct threadInfo*) vargp;
  // int d = info->dash;
        while((!info->gameOver) && (!info->winner)){
                while(info->currentPlayer != 'O'){
                        sleep(2);
                }
                printf("Player2\n");
                if (info->dash == 8){
                        if (info->board[row][col] =='-'){
                                info->board[row][col] = 'O';
                        }
                        else {
                                row = rand() % (2 +1 - 0) + 0;
                                col = rand() % (2 + 1 -0) +0;
                                if (info->board[row][col] != 'X'){
                                        info->board[row][col] = 'O';
                                }
                        }
                }
                if (info->dash <=6){
                        if ((info->board[0][0] == 'X') && ((info->board[0][0] == info->board[0][1]) || (info->board[0][0] == info->board[0][2]) || (info->board[0][1] == info->board[0][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[0][i] == '-'){
                                                info->board[0][i] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'X') && ((info->board[0][0] == info->board[1][0]) || (info->board[0][0] == info->board[2][0]) || (info->board[1][0]== info->board[2][0]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][0] == '-'){
                                                info->board[i][0] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'X') && ((info->board[0][0] == info->board[1][1]) || (info->board[0][0] == info->board[2][2]) || (info->board[1][1]== info->board[2][2]))){
                                if (info->board[0][0] == '-'){
                                        info->board[0][0] = 'O';
                                }
                                else if (info->board[1][1] == '-'){
                                        info->board[1][1] = 'O';
                                }
                                else if (info->board[2][2] == '-'){
                                        info->board[2][2] = 'O';
                                   }
                        }
                        else if ((info->board[0][2] == 'X') && ((info->board[0][2] == info->board[1][1]) || (info->board[0][2] == info->board[2][0]) || (info->board[0][2]== info->board[2][0]))){
                                if (info->board[0][2] == '-'){
                                        info->board[0][2] = 'O';
                                }
                                else if (info->board[1][1] == '-'){
                                        info->board[1][1] = 'O';
                                }
                                else if (info->board[0][2] == '-'){
                                        info->board[0][2] = 'O';
                                }
                        }
                        else if ((info->board[1][0] == 'X') && ((info->board[1][0] == info->board[1][1]) || (info->board[1][0] == info->board[1][2]) || (info->board[1][1]== info->board[1][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[1][i] == '-'){
                                                info->board[1][i] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[2][0] == 'X') && ((info->board[2][0] == info->board[2][1]) || (info->board[2][0] == info->board[2][2]) || (info->board[2][1]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[2][i] == '-'){
                                                info->board[2][i] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][1] == 'X') && ((info->board[0][1] == info->board[1][1]) || (info->board[0][1] == info->board[2][1]) || (info->board[1][1]== info->board[2][1]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][1] == '-'){
                                                info->board[i][1] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][2] == 'X') && ((info->board[0][2] == info->board[1][2]) || (info->board[0][2] == info->board[2][2]) || (info->board[1][2]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][2] == '-'){
                                                info->board[i][2] = 'O';
                                          row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'O') && ((info->board[0][0] == info->board[0][1]) || (info->board[0][0] == info->board[0][2]) || (info->board[0][1] == info->board[0][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[0][i] == '-'){
                                                info->board[0][i] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }

                        else if ((info->board[0][0] == 'O') && ((info->board[0][0] == info->board[1][0]) || (info->board[0][0] == info->board[2][0]) || (info->board[1][0]== info->board[2][0]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][0] == '-'){
                                                info->board[i][0] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][0] == 'O') && ((info->board[0][0] == info->board[1][1]) || (info->board[0][0] == info->board[2][2]) || (info->board[1][1]== info->board[2][2]))){
                                if (info->board[0][0] == '-'){
                                        info->board[0][0] = 'O';
                                }
                                else if (info->board[1][1] == '-'){
                                        info->board[1][1] = 'O';
                                }
                                else if (info->board[2][2] == '-'){
                                        info->board[2][2] = 'O';
                                }
                        }
                         else if ((info->board[0][2] == 'O') && ((info->board[0][2] == info->board[1][1]) || (info->board[0][2] == info->board[2][0]) || (info->board[0][2]== info->board[2][0]))){
                                if (info->board[0][2] == '-'){
                                        info->board[0][2] = 'O';
                                }
                                else if (info->board[1][1] == '-'){
                                        info->board[1][1] = 'O';
                                }
                                else if (info->board[2][0] == '-'){
                                        info->board[2][0] = 'O';
                                }
                           }
                        else if ((info->board[1][0] == 'O') && ((info->board[1][0] == info->board[1][1]) || (info->board[1][0] == info->board[1][2]) || (info->board[1][1]== info->board[1][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[1][i] == '-'){
                                                info->board[1][i] = 'O';
                                                row = 1;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[2][0] == 'O') && ((info->board[2][0] == info->board[2][1]) || (info->board[2][0] == info->board[2][2]) || (info->board[2][1]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[2][i] == '-'){
                                                info->board[2][i] = 'O';
                                                row = 2;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][1] == 'O') && ((info->board[0][1] == info->board[1][1]) || (info->board[0][1] == info->board[2][1]) || (info->board[1][1]== info->board[2][1]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][1] == '-'){
                                                info->board[i][1] = 'O';
                                        }
                                }
                        }
                         else if ((info->board[0][2] == 'O') && ((info->board[0][2] == info->board[1][2]) || (info->board[0][2] == info->board[2][2]) || (info->board[1][2]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][2] == '-'){
                                                info->board[1][2] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }

                        /*else if ((info->board[1][0] == 'X') && ((info->board[1][0] == info->board[1][1]) || (info->board[1][0] == info->board[1][2]) || (info->board[1][1]== info->board[1][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[1][i] == '-'){
                                                info->board[1][i] = 'O';
                                                row = 0;
                                                col = i;
                                                }
                                }
                        }
                        else if ((info->board[2][0] == 'X') && ((info->board[2][0] == info->board[2][1]) || (info->board[2][0] == info->board[2][2]) || (info->board[2][1]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[2][i] == '-'){
                                                info->board[2][i] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][1] == 'X') && ((info->board[0][1] == info->board[1][1]) || (info->board[0][1] == info->board[2][1]) || (info->board[1][1]== info->board[2][1]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][1] == '-'){
                                                info->board[i][1] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        }
                        else if ((info->board[0][2] == 'X') && ((info->board[0][2] == info->board[1][2]) || (info->board[0][2] == info->board[2][2]) || (info->board[1][2]== info->board[2][2]))){
                                int i =0;
                                for(; i<3;i++){
                                        if (info->board[i][2] == '-'){
                                                info->board[i][2] = 'O';
                                                row = 0;
                                                col = i;
                                        }
                                }
                        } */
                }
                printBoard(info->board);
                info->dash = info->dash-1;
                info->currentPlayer = 'X';
                info->gameOver =gameOver(info->dash);
                info->winner = checkWinner(info->board);
        }

        return NULL;
}

void printBoard(char board[3][4]){
        printf("Board:\n");
        int i =0;
        int j =0;
for(; i < 3; i++){
                for(; j <3; j++){
                        printf("%c", board[i][j]);
                }
                j =0;
                printf("\n");
        }
}

bool gameOver(int dash){
        if (dash == 0){
                return true;
        }
        return false;
}

bool checkWinner(char board[3][4]){
        if ((board[0][0] != '-') && (board[0][0] == board[1][0]) && (board[0][0] == board[2][0])){
                return true;
        }
        else if ((board[0][0] != '-') && (board[0][0] == board[0][1]) && (board[0][0] == board[0][2])){
                return true;
        }
        else if ((board[0][0] != '-') && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2])){
                return true;
        }
        else if ((board[1][0] != '-') && (board[1][0] == board[1][1]) && (board[1][0] == board[1][2])){
                return true;
        }
        else if ((board[2][0] != '-') && (board[2][0] == board[2][1]) && (board[2][0] == board[2][2])){
                return true;
        }
        else if ((board[0][1] != '-') && (board[0][1] == board[1][1]) && (board[0][1] == board[2][1])){
                return true;
        }
        else if ((board[0][2] != '-') && (board[0][2] == board[1][2]) && (board[0][2] == board[2][2])){
                return true;
        }
        else if ((board[0][2] != '-') && (board[0][2] == board[1][1]) && (board[0][2] == board[2][0])){
                return true;
        }
        return false;
}
