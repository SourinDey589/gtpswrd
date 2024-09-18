//>> Server_Side.c
//--------------------------------------------------------------------

#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
int main()
{
  char str[100];
  int i,listen_fd, comm_fd;
  struct sockaddr_in servaddr; // IP PORT

  listen_fd = socket(AF_INET, SOCK_STREAM, 0); // Listening config
  bzero( &servaddr, sizeof(servaddr)); // for clearing the address

  // Network Config & Details
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(2567); // 0 < port < 2^16 
  
  bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)); // bind
  listen(listen_fd, 10); // start listening 
  comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); // for accepting the connection

  while(1)
  {
    bzero( str, 100);
    read(comm_fd,str,100);
    printf("CSE-CN-Lab [from Client] >> %s",str);

    // str updation ABCD -> BCDE
    for(i=0; i<strlen(str);i++)
    {   str[i] = str[i]+1;   }
    str[i] = '\0';

    write(comm_fd, str, strlen(str)+1);
  }
  return 0;
}
