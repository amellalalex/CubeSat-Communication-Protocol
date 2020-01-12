// Standard libraries
#include <stdio.h>

// Local Performance Test
#include "csp_performance.h"
#include "client.h"
#include "server.h"

int main(int argc, char *argv[])
{
  //--- Initialise CSP ---//
  printf("[i] Initialising CSP...\r\n");

  // Init CSP buffers with 10 packets of 1000 bytes each
  csp_buffer_init(10, 1000);

  // Init CSP at address 1
  csp_init(1);

  // Start router task with 500 word stack, OS task priority 1
  csp_route_start_task(500, 1);

  /* Enable debug output from CSP */
  if((argc > 1) && (strcmp(argv[1], "-v") == 0))
  {
    printf("Debug enabed\r\n");
    csp_debug_toggle_level(3);
    csp_debug_toggle_level(4);

    printf("Conn table\r\n");
    csp_conn_print_table();

    printf("Route table\r\n");
    csp_route_print_table();

    printf("Interfaces\r\n");
    csp_route_print_interfaces();
  }

  printf("[i] Done!\n\n");

  //--- Initialise CSP threads ---//

  // Server
  printf("[i] Starting server thread...\n");
  csp_thread_handle_t handle_server;
  csp_thread_create(task_server, "SERVER", 1000, NULL, 0, &handle_server);
  printf("[i] Done!\n\n");

  // Client
  printf("[i] Starting client thread...\n");
  csp_thread_handle_t handle_client;
  csp_thread_create(task_client, "CLIENT", 1000, NULL, 0, &handle_client);
  printf("[i] Done!\n\n");

  // Wait for execution to end (ctrl+c)
  while(1) csp_sleep_ms(100000);

  // done
  return 0;
}
