/*
  slave.c

  * Purpose:
    ** Handles the creation of the slave pseudoterminal device.
    ** Handles the reception of messages from the master device.
*/

#include "SerialPorts.h"

// File static variables
static int status = 0; // 0 = off, 1 = on.
static int port   = -1;

// Creates the slave pseudoterminal device.
int slave_create(const char *device)
{
  // Ensure device is non null
  if(device == NULL)
  {
    printf("[!] Cannot use null slave endpoint.\n");
    return -1;
  }

  // Open slave pseudoterminal port
  port = open(device, O_RDWR);

  if(port == -1) // open() failed
  {
    printf("[!] Failed to open slave port at %s.\n", device);
    return -1;
  }

  // successfully created slave device
  printf("[*] Slave pseudoterminal device created.\n");
  status = 1; // on
  return 0;
}

// Receive messages from the master
void slave_listen()
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot receive messages before slave device is created.\n");
    exit(1);
  }

  // Create some placeholders
  int buff_len = 1024;
  char buffer[buff_len];

  // Receive messages until quit is received
  while(strcmp(buffer, "quit\n") != 0)
  {
    int read_bytes = -1;

    // Read message from serial port
    if((read_bytes = read(port, buffer, buff_len)) < 0)
    {
      printf("[(!)] Failed to read message from master.\n");
      exit(1);
    }

    // Add string termination character
    buffer[read_bytes] = '\0';

    // Print message on the screen
    printf("\r[Master]>> %s\n\n>> ", buffer);
    fflush(stdout);
  }

  // done
  pthread_exit(NULL);
}

// Sends messages to master
void slave_send(long *listen_tid)
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot send messages before slave device is created.\n");
    exit(1);
  }

  // Create placeholders
  int buff_len = 1024;
  char buffer[buff_len];

  // Send messages until user sends quit
  while(strcmp(buffer, "quit\n") != 0)
  {
    // Get message from user
    printf("\n>> ");
    fgets(buffer, buff_len, stdin);

    // Send message to master
    if(write(port, buffer, strlen(buffer)) < strlen(buffer))
    {
      printf("[(!)] Failed to send message to master.\n");
      exit(1);
    }
  }

  // done
  pthread_cancel(*listen_tid);
  pthread_exit(NULL);
}

// Receive messages from the master
void slave_listen_cpp()
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot receive messages before slave device is created.\n");
    exit(1);
  }

  // Create some placeholders
  int buff_len = 1024;
  char buffer[buff_len];

  // Receive messages until quit is received
  while(strcmp(buffer, "quit\n") != 0)
  {
    int read_bytes = -1;

    // Read message from serial port
    if((read_bytes = read(port, buffer, buff_len)) < 0)
    {
      printf("[(!)] Failed to read message from master.\n");
      exit(1);
    }

    // Add string termination character
    buffer[read_bytes] = '\0';

    // Print message on the screen
    printf("\r[Master]>> %s\n\n>> ", buffer);
    fflush(stdout);
  }

  // done
}

// Sends messages to master
void slave_send_cpp()
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot send messages before slave device is created.\n");
    exit(1);
  }

  // Create placeholders
  int buff_len = 1024;
  char buffer[buff_len];

  // Send messages until user sends quit
  while(strcmp(buffer, "quit\n") != 0)
  {
    // Get message from user
    printf("\n>> ");
    fgets(buffer, buff_len, stdin);

    // Send message to master
    if(write(port, (void *) buffer, strlen(buffer)) < strlen(buffer))
    {
      printf("[(!)] Failed to send message to master.\n");
      exit(1);
    }
  }

  // done
}
