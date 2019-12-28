#include "SerialPorts.h"

int main(int argc, char *argv[])
{
  // Check arguments
  if(argc < 2)
  {
    printf("[!] Not enough arguments\n");
    exit(1);
  }

  // Master (create chat room)
  if(strcmp(argv[1], "create") == 0)
  {

    printf("[*] Creating new chat room...\n");

    // Create master serial device
    int err = -1;
    if((err = master_create()) != 0)
    {
      printf("[!] Failed to create master pseudo-terminal device\n");
      exit(1);
    }

    // Start threads to send and listen
    long send_tid = -1, listen_tid = -1;
    if(pthread_create(&listen_tid, NULL, (void *) master_listen, NULL) != 0)
    {
      printf("[!] Failed to create listening thread.\n");
      exit(1);
    }
    if(pthread_create(&send_tid, NULL, (void *) master_send, (void *) &listen_tid) != 0)
    {
      printf("[!] Failed to create sending thread.\n");
      pthread_cancel(listen_tid);
      exit(1);
    }

    // done
    pthread_exit(NULL);
  }

  // Slave (join chat room)
  else if(strcmp(argv[1], "join") == 0)
  {
    // Check argc
    if(argc != 3)
    {
      printf("[!] Invalid number of arguments.\n");
      exit(1);
    }

    // Create slave device
    int err = -1;
    if((err = slave_create(argv[2])) != 0)
    {
      printf("[!] Failed to join chat room\n");
      exit(1);
    }

    // Start threads to send and listen
    long send_tid = -1, listen_tid = -1;
    if(pthread_create(&listen_tid, NULL, (void *) slave_listen, NULL) != 0)
    {
      printf("[!] Failed to start sending thread for slave.\n");
      exit(1);
    }
    if(pthread_create(&send_tid, NULL, (void *) slave_send, (void *) &listen_tid) != 0)
    {
      printf("[!] Failed to start sending thread for slave.\n");
      pthread_cancel(listen_tid);
      exit(1);
    }

    // done
    pthread_exit(NULL);
  }

  // done
  return 0;
}
