/*
*   main.c
*
*   author:   alex amellal
*   purpose:  demonstrate usage of named pipes with CSP
*/

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

// Cubesat space protocol
#include <csp/csp.h>
#include <csp/csp_interface.h>

// Settings
#define BUF_SIZE    250   // packet buffer size in bytes
#define CLIENT_ADDR 1     // client address according to CSP internal network
#define SERVER_ADDR 2     // server address according to CSP internal network
#define CLIENT_TYPE 1     // client type of task
#define SERVER_TYPE 2     // server type of task
#define PORT        10    // port used for communications

// Function to be used by the CSP library to route packets to the named pipe (FIFO)
static int fifo_tx(csp_iface_t * ifc, csp_packet_t * packet, uint32_t timeout);

// Function to be used by the CSP library to route packets from the named pipe (FIFO)
// into the CSP internal network
static void * fifo_rx(void * parameters);

// Define CSP named pipe interface
static csp_iface_t csp_if_fifo = {
  .name     =  "fifo",
  .nexthop  =  fifo_tx,
  .mtu      =  BUF_SIZE
};

// FIFO channel placeholders
static int rx_channel, tx_channel;

// Define FIFO transmission function
static int fifo_tx(csp_iface_t * ifc, csp_packet_t * packet, uint32_t timeout)
{
  // Write packets to FIFO
  if(write(tx_channel, &packet->length, packet->length + sizeof(uint32_t) + sizeof(uint16_t)) < 0) // write() failed
    printf("[!] Failed to write frame.\n");

  // Free packet buffer
  csp_buffer_free(packet);

  // Return default CSP return value
  return CSP_ERR_NONE;
}

// Define FIFO receiving function
static void * fifo_rx(void * parameters)
{
  // Allocate buffer for incoming packet
  csp_packet_t * packet = csp_buffer_get(BUF_SIZE);

  // Wait for incoming packet from FIFO
  while(read(rx_channel, &packet->length, BUF_SIZE) > 0)
  {
    // Inject received packet into CSP internal network
    csp_new_packet(packet, &csp_if_fifo, NULL);
    packet = csp_buffer_get(BUF_SIZE);
  }

  // done
  return NULL;
}

int main(int argc, char * argv[])
{
  // Create placeholders
  int type = 0, address = 0, peer = 0;
  char * tx_channel_name, * rx_channel_name;

  // Run as server or client
  if(argc != 2)
  {
    printf("[i] Usage: %s <server/client>\n", argv[0]);
    return -1;
  }

  // Setup according to server settings
  if(strcmp(argv[1], "server") == 0)
  {
    type    = SERVER_TYPE;
    address = SERVER_ADDR;
    peer    = CLIENT_ADDR;
    tx_channel_name = "server_to_client";
    rx_channel_name = "client_to_server";
  }

  // Setup according to client settings
  else if(strcmp(argv[1], "client") == 0)
  {
    type    = CLIENT_TYPE;
    address = CLIENT_ADDR;
    peer    = SERVER_ADDR;
    tx_channel_name = "client_to_server";
    rx_channel_name = "server_to_client";
  }

  else
  {
    printf("[!] Invalid argument %s\n", argv[1]);
    return -1;
  }

  //--- Init CSP and CSP buffer ---//
  if(csp_init(address) != CSP_ERR_NONE) // csp_init() failed
  {
    printf("[!] Failed to init CSP\n");
    return -1;
  }

  if(csp_buffer_init(10, 300) != CSP_ERR_NONE) // csp_buffer_init() failed
  {
    printf("[!] Failed to init CSP buffer\n");
    return -1;
  }

  //--- Open FIFO tx/rx channels ---//
  if((tx_channel = open(tx_channel_name, O_RDWR)) < 0) // open() failed
  {
    printf("[!] Failed to open TX channel\n");
    return -1;
  }

  if((rx_channel = open(rx_channel_name, O_RDWR)) < 0) // open() failed
  {
    printf("[!] Failed to open RX channel\n");
    return -1;
  }

  //--- Init threads ---//

  // Create thread placeholders
  pthread_t rx_thread;
  pthread_create(&rx_thread, NULL, fifo_rx, NULL);

  //--- Configure CSP router ---//
  // Designate FIFO interface as the default route
  csp_route_set(CSP_DEFAULT_ROUTE, &csp_if_fifo, CSP_NODE_MAC);
  // Start router with 500 word stack and OS priority 1
  csp_route_start_task(500, 1);

  //--- Listen for incoming connections ---//
  csp_socket_t * socket;
  if(type == SERVER_TYPE)
  {
    socket = csp_socket(CSP_SO_NONE); // create socket
    csp_bind(socket, PORT);             // bind port to socket
    csp_listen(socket, 5);              // Listen for up to 5 incoming connections at once
  }

  // Super loop
  csp_conn_t * conn;
  while(1)
  {
    if(type == SERVER_TYPE)
    {
      // Process incoming connection
      conn = csp_accept(socket, 1000); // accept incoming connections with 1000ms timeout
      if(conn)
      {
        // Parse packets incoming from connection with 10ms timeout between packets
        csp_packet_t * packet;
        while((packet = csp_read(conn, 10)) != NULL)
        {
          if(packet)
          {
            // Prompt with incoming packet data
            printf("[i] Incoming packet: %s\n", packet->data);
          }
          // Free packet buffer
          csp_buffer_free(packet);
        }
        // Close connection
        csp_close(conn);
      }
    }

    else // type = CLIENT_TYPE
    {
      // Allocate buffer for new packet
      csp_packet_t * packet = csp_buffer_get(strlen("yoyoyo"));

      if(packet)
      {
        // Get message from user
        char msg[BUF_SIZE];
        printf("[?] Enter a message to send to the server: ");
        fgets(msg, BUF_SIZE, stdin);

        // Copy string into packet data
        strcpy((char *) packet->data, msg);

        // Set packet length
        packet->length = strlen(msg);

        // Connect to server with 1000ms timeout
        conn = csp_connect(CSP_PRIO_NORM, peer, PORT, 1000, CSP_O_NONE);
        printf("Sending: %s\r\n", msg);
        if (!csp_send(conn, packet, 1000)) // csp_send() failed
        {
          printf("[!] Failed to send packet to server\n");
          return -1;
        }

        // Close connection
        csp_close(conn);
      }
      // Impose 1ms delay between each packet to give CSP time to free buffers
      sleep(1);
    }
  }

  // done
  close(rx_channel);
  close(tx_channel);
  return 0;
}
