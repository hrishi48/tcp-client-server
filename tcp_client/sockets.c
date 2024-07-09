#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP "98.137.11.164"  // www.yahoo.com
#define PORT 80             // http

int main() {

  int s;
  struct sockaddr_in sock;
  char buff[512];
  char *data;

  data = "HEAD / HTTP/1.0\r\n\r\n";
  memset(buff, 0, 512);

  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s < 0) {
    printf("socket() error\n");
    return -1;
  }

  sock.sin_addr.s_addr = inet_addr(IP);
  sock.sin_port = htons(PORT);
  sock.sin_family = AF_INET;

  if(connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0) {
    printf("connect() error\n");
    close(s);
    return -1;
  }
  
  write(s, data, strlen(data));
  read(s, buff, 511);
  close(s);

  printf("\n%s\n", buff);

  return 0;
}