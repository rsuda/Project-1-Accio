#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
  int port = 4000;
  char* host = "127.0.0.1";
  char* filename ="";
  if (argc != 4)
  {
        std::cerr << "ERROR: You should have 3 arguments, example ./client <port> <host> <filename>\n";
        return 0;
  }
  port = atoi(argv[1]);
  if (port < 1024)
  {
        std::cerr << "ERROR: Cannot use a port that is less than 1024\n";
        return 0;
  }
  if (host != "127.0.0.1")
  {
        std::cerr << "ERROR: Must use either localhost or 127.0.0.1 for <host>\n";
        return 0;
  }
  host = argv[2];
  filename = argv[3];
  // create a socket using TCP IP
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // struct sockaddr_in addr;
  // addr.sin_family = AF_INET;
  // addr.sin_port = htons(40001);     // short, network byte order
  // addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  // memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
  // if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
  //   perror("bind");
  //   return 1;
  // }

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);     // short, network byte order
  serverAddr.sin_addr.s_addr = inet_addr(host);
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

  // connect to the server
  if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    perror("connect");
    return 2;
  }

  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  if (getsockname(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
    perror("getsockname");
    return 3;
  }

  char ipstr[INET_ADDRSTRLEN] = {'\0'};
  inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
  std::cout << "Set up a connection from: " << ipstr << ":" <<
    ntohs(clientAddr.sin_port) << std::endl;


  // send/receive data to/from connection
  bool isEnd = false;
  std::string input;
  char buf[100] = {' '};
  std::stringstream ss;
/**TTTTTTTEEEEEEEESSSSSSSTTTTTT
  while (!isEnd) {
    memset(buf, '\0', sizeof(buf));
*/
/**
    std::cout << "send: ";
    std::cin >> input;
    if (send(sockfd, input.c_str(), input.size(), 0) == -1) {
      perror("send");
      return 4;
    }


    if (recv(sockfd, buf, 20, 0) == -1) {
      perror("recv");
      return 5;
    }
    ss << buf << std::endl;
    std::cout << "echo: ";
    std::cout << buf << std::endl;
*/
FILE *fd = fopen(filename, "rb");
int bytes_read;
while (!feof(fd)) {
    if ((bytes_read = fread(&buf, 1, 100, fd)) > 0)
        send(sockfd, buf, bytes_read, 0);
    else
        break;
}
    fclose(fd);
  std::cout << "Socket closed\n";

  close(sockfd);

  return 0;
}