#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// * maximum application buffer
#define APP_MAX_BUFFER 1024
#define PORT 8081

int main()
{
  printf("Web Server in C");

  // * define client & server file descriptors
  int server_fd, client_fd;

  // * define the socket address

  //define the socket address
  struct sockaddr_in address;
  int address_len = sizeof(address);

  // * Define the application buffer where we receive the requests
  // * data will be removed from receive buffer to here
  char buffer[APP_MAX_BUFFER] = {0};

  // * Create socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("Socket Failed");
    exit(EXIT_FAILURE);
  }

  // * Bind Socket
  address.sin_family = AF_INET;         // * ipv4
  address.sin_addr.s_addr = INADDR_ANY; // * listen 0.0.0.0 interfaces
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind Failed");
    exit(EXIT_FAILURE);
  }

  // * Creates the queues
  // * Listen for clients, with 10 backlog (10 connections in accept queue)
  // * This defines how many client can server accept in a queue
  if (listen(server_fd, 1) < 0)
  {
    perror("Listen Failed");
    exit(EXIT_FAILURE);
  }

  // * [C,C,C,C,C,C,C,C,C,C] -> 10 backlog connections

  // * We loop forever
  while (1)
  {
    printf("\n Waiting for a connection... \n");

    // * Following code show the backend application will accept the connection from the server and creates the instance of that connection
    // * Accept a client connection client_fd == connection
    // * this blocks
    // * If the accept queue is empty, we are stuck here...
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&address_len)) < 0)
    {
      perror("Accept Failed");
      exit(EXIT_FAILURE);
    }

    /*
      * Read data from the OS receive buffer to the application (buffer)
      * This is essentially reading the HTTP request
      * Don't bite more than you chew 'APP_MAX_BUFFER'
     */
    read(client_fd, buffer, APP_MAX_BUFFER);
    printf("%s\n", buffer);

    // * We send the request by writing to the socket send buffer in the OS
    char *http_response = "HTTP/1.1 200 OK\n"
                          "Content-Type: text/plain\n"
                          "Content-Length: 14\n\n"
                          "Hello World!\n";
    // * Write to the socket (From OS to Send Buffer)
    write(client_fd, http_response, strlen(http_response));

    write(client_fd, "!", 1);

    // * Close the client socket (Terminate the TCP Connection)
    close(client_fd);
  }

  return 0;
}