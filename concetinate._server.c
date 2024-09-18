#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main() {
    char str[200]; // Increase buffer size for concatenated strings
    char response[200]; // Buffer for the response
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    // Network Config & Details
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(2567);

    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 10);
    comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);

    while (1) {
        bzero(str, 200);
        read(comm_fd, str, 200);
        printf("CSE-CN-Lab [from Client] >> %s", str);

        // Split the received string into two parts
        char *token = strtok(str, "|"); // Assuming strings are separated by '|'
        char *firstString = token;
        char *secondString = strtok(NULL, "|");

        if (secondString != NULL) {
            // Concatenate the strings
            snprintf(response, sizeof(response), "%s%s", firstString, secondString);
        } else {
            snprintf(response, sizeof(response), "Error: Second string missing");
        }

        write(comm_fd, response, strlen(response) + 1);
    }
    return 0;
}
