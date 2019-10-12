#ifndef SERIAL_PORTS_H
#define SERIAL_PORTS_H

// Required for pseudoterminal functions to work
#define _XOPEN_SOURCE 1
#define _GNU_SOURCE   1

////////////////////////////
//    Relevant headers    //
////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

////////////////////
//    master.c    //
////////////////////

// Create master pseudoterminal device
int master_create();
void master_listen();
void master_send(long *listen_tid);

// C++ wrapper functions
void master_listen_cpp();
void master_send_cpp();

//////////////////
//    slave.c   //
//////////////////

// Create slave pseudoterminal device at specified endpoint (/dev/pts/*)
int slave_create(const char *device);
void slave_listen();
void slave_send(long *listen_tid);

// C++ wrapper functions
void slave_listen_cpp();
void slave_send_cpp();

#endif /* end of include guard: SERIAL_PORTS_H */
