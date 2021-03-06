// client  
#include <sys/types.h>
#include <iostream>
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
  int Res;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
  int n;
  char buffer[1000];

  if (-1 == SocketFD)
  {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }
  string txt;
    

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(50001); //45001
  Res = inet_pton(AF_INET, "190.232.168.71", &stSockAddr.sin_addr);  

 
  if (0 > Res)
  {
    perror("error: first parameter is not a valid address family");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  else if (0 == Res)
  {
    perror("char string (second parameter does not contain valid ipaddress");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
    //end of validation of assining

  if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    perror("connect failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  do{
    cout<<"CLIENT: ";
    cin >>txt;
    n = write(SocketFD, txt.c_str(),txt.length());
//     std::cout<<"size: "<<txt.length()<<std::endl;
    n = read(SocketFD,buffer, 100);
    printf("SERVER: [%s]\n",buffer);
  }while (strncmp(buffer,"bye",3) !=0);

  shutdown(SocketFD, SHUT_RDWR);

  close(SocketFD);
  return 0;
}
