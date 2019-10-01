/*
  slave.c

  * Purpose:
    ** Handles the creation of the slave pseudoterminal device.
    ** Handles the reception of messages from the master device.
*/

#include "SerialPorts.h"

// Global variables
int slave_status  = 0; // 0 = off, 1 = on.
int slave_port = -1;


// Creates the slave pseudoterminal device.
int slave_create(char *device)
{
  // Ensure device is non null
  if(device == NULL)
  {
    printf("[!] Cannot use null slave endpoint.\n");
    return -1;
  }

  // Open slave pseudoterminal port
  slave_port = open(device, O_RDWR);

  if(slave_port == -1) // open() failed
  {
    printf("[!] Failed to open slave port at %s.\n", device);
    return -1;
  }

  // successfully created slave device
  printf("[*] Slave pseudoterminal device created.\n");
  slave_status = 1; // on
  return 0;
}

// Checks and returns one message from the master
int slave_read(int maxc, char *msgout)
{
  // Check slave device status
  if(slave_status == 0) // slave is off
  {
    printf("[(!)] Cannot send a message to the master if the slave device is off.\n");
    return 0;
  }

  // Create placeholder
  int bytes_read = -1;

  // Read message from master
  bytes_read = read(slave_port, msgout, maxc);

  if(bytes_read < 0) // read() failed
  {
    printf("[!] Failed to send message to master.\n");
    return -1;
  }

  // done
  printf("[*] Read %d byte message from master.\n", bytes_read);
  return 0;
}
