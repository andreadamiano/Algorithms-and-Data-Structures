#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>  

#include "event_loop.h"

Server *createServer(int port) {
  char port_str[10];
  sprintf(port_str, "%d", port); //write formatted data inside a buffer 
  int sock;  //file descriptor 
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints)); //0 initialize the struct 


  hints.ai_family = AF_INET;      // IPv4
  hints.ai_socktype = SOCK_DGRAM; // UDP datagram
  hints.ai_flags = AI_PASSIVE;    // fill in my IP for me
  if (getaddrinfo(NULL, port_str, &hints, &res) != 0) {
    perror("getaddrinfo");
    exit(EXIT_FAILURE);
  }
  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sock == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  int reuse = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
      perror("setsockopt SO_REUSEADDR");
      exit(EXIT_FAILURE);
  }

  if (bind(sock, res->ai_addr, res->ai_addrlen) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  freeaddrinfo(res);
  Server *server = malloc(sizeof(Server));
  memset(server, 0, sizeof(Server));
  server->port = port;
  server->sockfd = sock;
  return server;
}

void on(Server *server, EventType event, void (*callback)(Request *)) {
  server->cb_array[event] = callback;
}

void startServer(Server *server) {
  struct epoll_event ev, events[MAX_EVENTS];
  int epollfd, nfds;
  int sock = server->sockfd;

  epollfd = epoll_create1(0);  //create an epoll instance which monitor multiple file descriptors 
  if (epollfd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  ev.events = EPOLLIN; //sets the epoll instance to monitor file descriptor for read availability
  ev.data.fd = sock; //store the socker file descripto in the even data 
  // the epoll monitor only the server socket sine in UDP the server soket monitor all incoming client 
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &ev) == -1) { //start monitor the socket file descriptor  
    perror("epoll_ctl: sockfd");
    exit(EXIT_FAILURE);
  }

  printf("Listening on port %d\n", server->port);

  // The event loop
  while (1) {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1); //block execution until events occur on monitored file descriptors 
    if (nfds == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nfds; i++) { //loop over all events that have occurred 
      if (events[i].events & EPOLLIN && events[i].data.fd == sock) {
        struct sockaddr_in  client_addr;
        socklen_t addr_size = sizeof(client_addr);
        char buf[BUF_SIZE];
        memset(buf, 0, BUF_SIZE);
        int bytes_read;
        bytes_read = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &addr_size); //receive data from the socket 

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("Received message from %s:%d\n", client_ip, ntohs(client_addr.sin_port));
        if (bytes_read == -1) {
          perror("recv");
          exit(EXIT_FAILURE);
        }
        // Run the callback
        Request req = {*(struct sockaddr*)&client_addr, addr_size, sock, buf, bytes_read};
        server->cb_array[EventTypeMessage](&req); //execute the callback function 
      }
    }
  }
}