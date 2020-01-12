/*
*   server component
*
*   author:   alex amellal
*   purpose:  defines server CSP task behaviour
*/

#ifndef SERVER_H
#define SERVER_H

#include "csp_performance.h"

// Define CSP server thread
CSP_DEFINE_TASK(task_server)
{
  // Create socket without any socket options
  csp_socket_t * socket = csp_socket(CSP_SO_NONE);

  // Bind all ports to socket
  csp_bind(socket, CSP_ANY);

  // Create single conneciton backlog
  csp_listen(socket, 1);

  // Create connection and packet placeholders
  csp_conn_t * conn;
  csp_packet_t * packet;

  // Process incoming connections
  while(1)
  {
    // Wait for incoming connection with 1000ms timeout
    if((conn = csp_accept(socket, 1000)) == NULL) // csp_accept() failed to receive incoming connection
      continue;

    // Create placeholders for performance test
    bool first_packet = false;
    clock_t start, end;
    int n_packets = 0;

    // Read packets if incoming connection found (100ms timeout or MAX PING)
    while((packet = csp_read(conn, 100)) != NULL)
    {
      // printf("[csp_server] Received packet from client containing: %s\n", (char *) packet->data);

      // Check if first packet received yet
      if(!first_packet)
      {
        // Start timer
        start = clock();

        // Set first_packet passed to true
        first_packet = true;
      }

      n_packets++;
    }

    // Stop timer
    end = clock();

    // Calculate time elapsed
    double time_elap = (double) (end - start) / CLOCKS_PER_SEC; // 100ms removed for timeout

    // Calculate transmission speed @ 1 KB per packet
    double trans_speed = (double) n_packets / time_elap;

    printf("[i] Time required to receive %d packets (%.3lf MB) is %lfs\n", n_packets, (double) n_packets / (double) 1000, time_elap);
    printf("[i] Thus, transmission speed is %lf KB/s\n\n", trans_speed);

    // Close connection
    csp_close(conn);
  }
}

#endif /* end of include guard: SERVER_H */
