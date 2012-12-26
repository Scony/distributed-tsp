#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
  int port;
  scanf("%d",&port);
  int sd = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int cd = connect(sd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  printf("%d %d\n",sd,cd);
  close(sd);
  return 0;
}
