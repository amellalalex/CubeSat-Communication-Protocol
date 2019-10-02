/*
  master.c

  * Purpose:
    ** Handles the creation of the master pseudoterminal device.
    ** Sending messages to the slave.
*/

#include "SerialPorts.h"

// File-static variables
static int port  = -1;
static int status       = 0; // 0 = closed, 1 = open

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

// Send a message to the slave
int master_send(int msgc, char *msg)
{
  // Check status
  if(status == 0) // master device is off
  {
    printf("[(!)] Cannot send a message to the slave if the master device is off.\n");
    return 0;
  }

  // Create placeholders
  int bytes_written = -1;

  // Write message to slave
  bytes_written = write(port, msg, msgc);

  if(bytes_written <= 0) // write() failed
  {
    printf("[!] Failed to send message to slave.\n");
    return -1;
  }

  if(bytes_written < msgc) // write() did not completely send message
  {
    printf("[(!)] Failed to completely send message to slave.\n");
    return 0;
  }

  // done
  printf("[*] Sent %d bytes to slave.\n", bytes_written);
  return 0;
}
