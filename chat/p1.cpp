// server
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;


int main(void)
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  char buffer[256];
  int n;
  string txtserv;
    
  if(-1 == SocketFD)
  {
    perror("can not create socket");
    exit(EXIT_FAILURE);
  }

  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(45000);
  stSockAddr.sin_addr.s_addr = INADDR_ANY;
  
  std::cout<<"-------Servidor-------"<<std::endl;      

  if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    perror("error bind failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  if(-1 == listen(SocketFD, 10))
  {
    perror("error listen failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  for(;;)
  {
    int ClientFD = accept(SocketFD, NULL, NULL);
    do{
      if(0 > ClientFD )
      {
        perror("error accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

    
    bzero(buffer,256);   
    n = read(ClientFD ,buffer,255);

    
    if (n < 0) perror("ERROR reading from socket");
    printf("CLIENT: [%s]\n",buffer);
    cout<<"SERVER: ";
    cin >>txtserv;
    std::cout<<"size: "<<txtserv.length()<<std::endl;
    n = write(ClientFD,txtserv.c_str(),txtserv.length());
    if (n < 0) perror("ERROR writing to socket");
    }while(strncmp(buffer,"bye",3)!=0);
  

    shutdown(ClientFD , SHUT_RDWR);

    close(ClientFD);
  }

  close(SocketFD);
  return 0;
}
