/*
  main.c

  * The objective of this program is to demonstrate:
    ** Creation of master/save pseudoterminal port pairs.
    ** Usage and communication between them.
    ** Error and exception handling of the functions relevant to
        completing the above.

  * Program usage:
    ** ./a.out master :
      *** Creates the master pseudoterminal port.
      *** Returns the designated slave serial port.
    ** ./a.out slave <slave serial port>
      *** Creates the slave pseudoterminal port.

  * Prompts:
    ** [*]    Signifies a generic message.
    ** [!]    Signifies an error message.
    ** [(!)]  Signifies a non-critical error message.
*/

#include "SerialPorts.h"

int main(int argc, char *argv[])
{
  // Check argc
  if(argc < 2)
  {
    printf("[!] Invalid number of arguments. EXITING\n");
    exit(1);
  }

  // Master or slave?
  if(strcmp(argv[1], "master") == 0) // master
  {
    // Create master device
    if(master_create() == -1)
    {
      // master_create() failed
      printf("[!] Failed to create master pseudoterminal device. EXITING\n");
      exit(1);
    }

    // Prompt for message to slave
    printf("[*] Type any message to send to the slave device: \n");
    printf(">> ");

    // Get message from stdin
    char buffer[1024];
    fgets(buffer, 1024, stdin);

    // Send message to slave
    if(master_send(strlen(buffer), buffer) == -1)
    {
      // master_send() failed
      printf("[!] Failed to send message to slave. EXITING\n");
      exit(1);
    }

    // Halt until enter or ctrl-c is pressed
    printf("[*] Press ENTER or CTRL-C to quit.\n");
    char a[2];
    fgets(a, 2, stdin);
    exit(0);
  }

  else if(strcmp(argv[1], "slave") == 0) // slave
  {
    // Check argc
    if(argc != 3)
    {
      printf("[!] Invalid number of arguments. EXITING\n");
      exit(1);
    }

    // Create slave device
    if(slave_create(argv[2]) == -1)
    {
      // slave_create() failed
      printf("[!] Failed to create slave pseudoterminal device at endpoint %s. EXITING\n", argv[2]);
      exit(1);
    }

    // Halt until enter is pressed
    printf("[*] Press ENTER when ready to receive a message from the master device: \n");
    char a[2];
    fgets(a, 2, stdin);

    // Create msg placeholder
    char msg[1024];

    // Read message from master device
    if(slave_read(1024, msg) == -1)
    {
      // slave_read() failed
      printf("[!] Failed to read message from master. EXITING\n");
      exit(1);
    }

    // Print message
    printf("[*] Message received from master: \n");
    printf(">> %s\n", msg);

    // Halt until enter or ctrl-c is pressed
    printf("[*] Press ENTER or CTRL-C to quit.\n");
    fgets(a, 2, stdin);
  }

  else // Invalid argument
  {
    printf("[!] Invalid option. EXITING\n");
    exit(1);
  }

  // done
  return 0;
}
