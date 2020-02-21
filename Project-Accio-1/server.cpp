#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <fstream>

int
main(int argc, char** argv)
{
  // create a socket using TCP IP
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  //Invalid socket RS
 // if (sockfd == INVALID_SOCKET)
  //{
        //cerr << "CAN'T CREATE A SOCKET! QUITTING" << endl;
//      return;
 // }

  // allow others to reuse the address
  int yes = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    return 1;
  }

  // bind address to socket
  int x = atoi(argv[1]);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(x);     // short, network byte order, changed 40000 to 54000
  addr.sin_addr.s_addr = INADDR_ANY; //changed inet_addr("127.0.0.1") to INADDR_ANY
  memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

  if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind");
    return 2;
  }

  // set socket to listen status
  if (listen(sockfd, 1) == -1) {
    perror("listen");
    return 3;
  }

  // accept a new connection
  struct sockaddr_in clientAddr;
  socklen_t clientAddrSize = sizeof(clientAddr);
  int clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);

  if (clientSockfd == -1) {
    perror("accept");
    return 4;
  }

  char ipstr[INET_ADDRSTRLEN] = {'\0'};
  inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
  std::cout << "Accept a connection from: " << ipstr << ":" <<
    ntohs(clientAddr.sin_port) << std::endl;

  // read/write data from/into the connection
  bool isEnd = false;
  char buf[100] = {' '};
  std::stringstream ss;

  FILE *fp;
read(clientSockfd,buf,100);
fp=fopen("/saved/newfile.txt","w");
fprintf(fp,"%s",buf);
printf("the file was received successfully\n");
printf("the new file created is add1.txt\n");

// TTTTTEEEEEEEESSSSSSSSSSTTTTTTTTTTT
/**
  while (!isEnd) {
    memset(buf, '\0', sizeof(buf));

    int bytesRecieved = recv(clientSockfd, buf, 20, 0); //RS bytes recieved
    if (bytesRecieved == -1) {  //Changed recv(clientSockfd, buf, 20, 0) to bytesRecieved
      //cerr << "ERROR IN RECV(). QUITTING" >>endl;
      perror("recv");
      return 5;
    }
    //RS client disconnect
    if (bytesRecieved == 0) {
      std::cout << "Client disconnected\n";
      break;
        }

    //Might try instead of 20 to use bytesReceived + 1
    if (send(clientSockfd, buf, bytesRecieved + 1, 0) == -1) {
      perror("send");
      return 6;
    }

    if (ss.str() == "close\n")
      break;

        ss.str("");


        std::ifstream input("");
        size_t datasize;
        FILE* fd = fopen("recfile.txt", "wb");

        while (!isEnd)
        {
        datasize = recv(clientSockfd, buf, 20, 0);
        fwrite(&buf, 1, datasize, fd);
        }
        fclose(fd);
        }
*/
  close(clientSockfd);
return 0;
}