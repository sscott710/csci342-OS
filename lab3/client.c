#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "box.h"

extern int errno;
static int sockfd;

void print_error(char *);

int main(int argc, char *argv[]) {
        struct addrinfo *host_ai;
        struct addrinfo hint;
        int err;

        if (argc != 2) {
                print_error("usage: client hostname");
    }

        hint.ai_flags = 0;
        hint.ai_family = AF_INET;
        hint.ai_socktype = SOCK_STREAM;
        hint.ai_protocol = 0;
        hint.ai_addrlen = 0;
        hint.ai_canonname = NULL;
        hint.ai_addr = NULL;
        hint.ai_next = NULL;

        if ((err = getaddrinfo(argv[1], "tokenserver", &hint, &host_ai)) != 0) {
                printf("getaddrinfo error: %s\n", gai_strerror(err));
                return 0;
        }

        printf("creating socket\n");
        if ((sockfd = socket(host_ai->ai_addr->sa_family, SOCK_STREAM, 0)) < 0) {
                print_error("Error creating socket");
        }
        printf("socket created\n");

        printf("attempting Connection\n");
        if (connect(sockfd, host_ai->ai_addr, host_ai->ai_addrlen) != 0) {
                close(sockfd);
                printf("can't connect to %s\n", argv[1]);
                print_error("Error connecting to server");
 	}
        printf("connection made...\n");
        freeaddrinfo(host_ai);

        //int n;
        //task 1
        char *name = "savannah";
        send(sockfd, name, strlen(name), 0);
        printf("sent name [savannah]\n");
        //task 2
        int value;
        recv(sockfd, &value, 4, 0);
        printf("received [%d]\n", value);
        value = value + 1;
        send(sockfd, &value, 4, 0);
        printf("sent integer + 1 [%d]\n", value);
        //task 3
        int arr[4];
        recv(sockfd, arr, 20, 0);
        printf("received array [");
        int min = arr[0];
        int i;
        for (i =0; i < 5; i++){
                if (i ==4){
                        printf("%d,", arr[i]);
                } else{
                        printf("%d,", arr[i]);
                }
                if (arr[i] < min){
                        min = arr[i];
                }
        }
        printf("]\n");
        send(sockfd, &min, 4, 0);
        printf("sent smalled value [%d]\n", min);
        //task 4
        struct box box1;
        recv(sockfd, &box1, sizeof(struct box), 0);
        printf("received box (%d, %d, %d)\n", box1.width, box1.height, box1.length);
        int volume = box1.width * box1.height * box1.length;
        send(sockfd, &volume, 4, 0);
        printf("send volume\n");
 	//n = recv(sockfd, &token, 4, 0);

/*      if (n > 0)
                printf("from server [%d]\n", token);
        else {
                printf("recv error:  %d\n", n);
        }*/

        close(sockfd);
        return 0;
}


void print_error(char *str) {
        printf("%s: %s\n", str, strerror(errno));
        exit(1);
}