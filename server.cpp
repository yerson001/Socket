  /* Server code in C */
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

int main(void)
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  char buffer[256];
  int n;
 
  if(-1 == SocketFD)
  {
    std::cout<<"can not create socket"<<std::endl;
    exit(EXIT_FAILURE);
  }
 
  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(45000);
  stSockAddr.sin_addr.s_addr = INADDR_ANY;
 
  if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    std::cout<<"error bind failed"<<std::endl;
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
 
  if(-1 == listen(SocketFD, 10))
  {
    std::cout<<"error listen failed"<<std::endl;
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
 
  for(;;)
  {
    int ConnectFD = accept(SocketFD, NULL, NULL);
 
    if(0 > ConnectFD)
    {
      std::cout<<"error accept failed"<<std::endl;
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
 
    bzero(buffer,256);
    n = read(ConnectFD,buffer,255);
    if (n < 0) std::cout<<"ERROR reading from socket"<<std::endl;
    printf("El mensaje: [%s]\n",buffer);
    n = write(ConnectFD,"I got your message",18);
    if (n < 0) std::cout<<"ERROR writing to socket"<<std::endl;
 
    /* perform read write operations ... */
 
    shutdown(ConnectFD, SHUT_RDWR);
 
    close(ConnectFD);
  }
 
  close(SocketFD);
  return 0;
}
