#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#define _POSIX_C_SOURCE 200112L
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define EVENT_TYPES_LEN 1
#define BUF_SIZE 1024
#define MAX_EVENTS 10

typedef enum EventType { EventTypeMessage } EventType;

typedef struct Request {
  struct sockaddr client_addr;
  socklen_t addr_size;
  int server_sockfd;
  char *msg;
  int bytes_send; 
} Request;

typedef struct Server {
  int port;
  int sockfd;
  void (*cb_array[EVENT_TYPES_LEN]) (Request *); //array of fuction pointer 
} Server;

Server *createServer(int port);
void on(Server *server, EventType event, void (*callback)(Request *));
void startServer(Server *server);


#endif