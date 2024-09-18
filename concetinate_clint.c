#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main() {
    int sockfd;
    char sendline[100], recvline[100];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2567);
    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    while (1) {
        bzero(sendline, 100);
        bzero(recvline, 100);

        printf("\r>> ");
        fgets(sendline, 100, stdin);

        // Remove newline character from input
        sendline[strcspn(sendline, "\n")] = 0;

        // Example: Enter two strings separated by '|'
        // For example: "Hello|World"
        
        write(sockfd, sendline, (strlen(sendline) + 1));
        read(sockfd, recvline, 100);
        printf("CSE-CN-Lab [from Server] >> %s\n", recvline);
    }

    return 0;
}
