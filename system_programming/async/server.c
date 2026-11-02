#include <stdio.h>
#include <stdlib.h>

#include "event_loop.h"

void handleMessage(Request *req) {
  if (sendto(req->server_sockfd, req->msg, req->bytes_send, 0, &req->client_addr, req->addr_size) == -1) {
    perror("send");
    exit(EXIT_FAILURE);
  }
}

int main() {
  Server *s = createServer(41234);

  on(s, EventTypeMessage, handleMessage);

  startServer(s);
}