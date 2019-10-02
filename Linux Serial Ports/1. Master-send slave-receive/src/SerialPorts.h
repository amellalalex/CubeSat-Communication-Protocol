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

////////////////////
//    master.c    //
////////////////////

// Create master pseudoterminal device
int master_create();
int master_send(int msgc, char *msg);

//////////////////
//    slave.c   //
//////////////////

// Create slave pseudoterminal device at specified endpoint (/dev/pts/*)
int slave_create(char *device);
int slave_read(int maxc, char *msgout);

#endif /* end of include guard: SERIAL_PORTS_H */
