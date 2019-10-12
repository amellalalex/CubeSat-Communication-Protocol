/*
  master.c

  * Purpose:
    ** Handles the creation of the master pseudoterminal device.
    ** Sending messages to the slave.
*/

#include "SerialPorts.h"

// File static variables
static int port   = -1;
static int status = 0; // 0 = closed, 1 = open

// Creates master pseudoterminal device.
int master_create()
{
  // Open master pseudoterminal port
  port = getpt();

  if(port == -1) // getpt() failed
  {
    printf("[!] Failed to open master port.\n");
    return -1;
  }

  // Grant the master port a slave
  if(grantpt(port) == -1) // grantpt() failed
  {
    printf("[!] Failed to grant master a slave.\n");
    return -1;
  }

  // Unlock the slave port for the master
  if(unlockpt(port) == -1) // unlockpt() failed
  {
    printf("[!] Failed to unlock slave port for master.\n");
    return -1;
  }

  // Master device successfully created.
  printf("[*] Master pseudoterminal device created. Slave endpoint at %s.\n", ptsname(port));
  status = 1; // on
  return 0;
}

// Receive messages from the slave
void master_listen()
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot receive messages before master device is created.\n");
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
      printf("[(!)] Failed to read message from slave.\n");
      exit(1);
    }

    // Add string termination character
    buffer[read_bytes] = '\0';

    // Print message on the screen
    printf("\r[Slave]>> %s\n\n>> ", buffer);
    fflush(stdout);
  }

  // done
  pthread_exit(NULL);
}

// Send messages to the slave
void master_send(long *listen_tid)
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot send messages before master device is created.\n");
    exit(1);
  }

  // Create some placeholders
  int buff_len = 1024;
  char buffer[buff_len];

  // Keep sending messages until user types quit
  while(strcmp(buffer, "quit\n") != 0)
  {
    // Get message from user
    printf("\n>> ");
    fgets(buffer, buff_len, stdin);

    // Send message to slave
    if(write(port, (void *) buffer, strlen(buffer)) < strlen(buffer))
    {
      printf("[(!)] Failed to send message to slave.\n");
      exit(1);
    }
  }

  // done
  pthread_cancel(*listen_tid);
  pthread_exit(NULL);
}

// Receive messages from the slave (CPP wrapper)
void master_listen_cpp()
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot receive messages before master device is created.\n");
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
      printf("[(!)] Failed to read message from slave.\n");
      exit(1);
    }

    // Print message on the screen
    if(strcmp(buffer, "quit\n") == 0)
    {
      break;
    }
    else
    {
      // Add string termination character
      buffer[read_bytes] = '\0';
      printf("\r[Slave]>> %s\n\n>> ", buffer);
      fflush(stdout);
    }
  }

  // done
}

// Send messages to the slave (CPP wrapper)
void master_send_cpp()
{
  // Check status
  if(status != 1)
  {
    printf("[!] Cannot send messages before master device is created.\n");
    exit(1);
  }

  // Create some placeholders
  int buff_len = 1024;
  char buffer[buff_len];

  // Keep sending messages until user types quit
  while(strcmp(buffer, "quit\n") != 0)
  {
    // Get message from user
    printf("\n>> ");
    fgets(buffer, buff_len, stdin);

    // Send message to slave
    if(write(port, (void *) buffer, strlen(buffer)) < strlen(buffer))
    {
      printf("[(!)] Failed to send message to slave.\n");
      exit(1);
    }
  }

  // done
}
