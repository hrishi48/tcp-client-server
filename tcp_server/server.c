#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8181

int main() {
  int s, c;
  socklen_t addrlen;
  struct sockaddr_in srv, cli;
  char buff[512];
  char *data;

  memset(&srv, 0, sizeof(srv));
  memset(&cli, 0, sizeof(cli));

  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s < 0) {
    printf("socket() failed \n");
    return -1;
  }

  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = 0;
  srv.sin_port = htons(PORT);

  if(bind(s, (struct sockaddr *)&srv, sizeof(srv)) != 0) {
    printf("bind() failed\n");
    close(s);
    return -1;
  }

  int connectionQueue = 5;    // number of allowed connections
  if(listen(s, connectionQueue)) {
    printf("listen() failed\n");
    close(s);
    return -1;
  }
  printf("Listening on 0.0.0.0:%d\n", PORT);

  c = accept(s , (struct sockaddr *)&srv, &addrlen);

  if(c < 0) {
    printf("accept() failed\n");
    close(s);
    return -1;
  }

  printf("Client connected\n");
  read(c, buff, 511);

  data = "httpd v1.0\n";

  write(c, data, strlen(data));

  close(c);
  close(s);

  return 0;
}