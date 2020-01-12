/*
*   client component
*
*   author:   alex amellal
*   purpose:  defines client CSP task behaviour
*/

#ifndef CLIENT_H
#define CLIENT_H

#include "csp_performance.h"

// Define client CSP thread
CSP_DEFINE_TASK(task_client)
{
  // Create placeholders for connection and packet
  csp_conn_t * conn;
  csp_packet_t * packet;

  // Create placeholders for server connection
  int ms_timeout  = 1000;
  int address     = 1;
  int port        = 10;

  // Repeat test
  for(int x = 0; x < 10; x++)
  {
    // Connect to server
    conn = csp_connect(CSP_PRIO_NORM, address, port, ms_timeout, CSP_O_NONE);

    if(conn == NULL) // csp_connect() failed
    {
      printf("[!] Failed to connect client to server.\n");

      // Free packet buffer
      csp_buffer_free(packet);

      // done
      return CSP_TASK_RETURN;
    }

    for(int x = 0; x < 1000; x++)
    {
      // Get packet buffer
      packet = csp_buffer_get(1000);
      if(packet == NULL) // csp_buffer_get() failed
      {
        printf("[!] Failed to get buffer element for client\n");
        return CSP_TASK_RETURN;
      }

      // Put dummy data in packet
      char * message = "yoyoyo";
      strcpy((char *) packet->data, message);

      // Set packet data length
      packet->length = 1000;

      // Send packet
      if(!csp_send(conn, packet, ms_timeout)) // csp_send() failed
      {
        printf("[!] Failed to send packet from client to server.\n");
        return CSP_TASK_RETURN;
      }

      // Free packet buffer
      csp_buffer_free(packet);

      csp_sleep_ms(0.0001);
    }

    // Close connection
    csp_close(conn);

    csp_sleep_ms(1000);
  }

  // done
  return CSP_TASK_RETURN;
}

#endif /* end of include guard: CLIENT_H */
