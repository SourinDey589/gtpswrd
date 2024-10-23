#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>     //server side code 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[100];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(2567);

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listenfd, 10);

    printf("Server is listening...\n");

    connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);

    while (1) {
        bzero(buff, 100);

        // Read from the client
        read(connfd, buff, 100);

        // If the client sends an empty message, exit the loop
        if (strlen(buff) == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Received from client: %s\n", buff);

        // Reverse the string
        reverseString(buff);

        // Send the reversed string back to the client
        write(connfd, buff, strlen(buff) + 1);
    }

    close(connfd);
    close(listenfd);
    return 0;
}
