# Named Pipe (FIFO) Routing
This folder is dedicated to demonstrating the usage of named pipes with the CSP.

## Motivation
The CSP has an internal networking system characterized by 8 arbitrary addresses (int 0-7). All connection sockets and packets are routed in accordance to this structure.

The problem lies in how to export or pipe packet traffic from this internal network to an external process or device, which would extend the scope of possible connections. As it turns out, this can be achieved via named pipes or FIFO.

## Prerequisites
- Cubesat Space Protocol Library
- Cmake

### CSP Library
To obtain the CSP library, head over to their repo:
https://github.com/libcsp/libcsp

Once you've cloned the repo, head over to https://waf.io/ to download the waf signed executable file. Use it to replace the `waf` executable provided by the libcsp repo, since I get issues when I use that one.

Once replaced, head into a terminal and run:
```
$ ./waf configure
$ ./waf build install
```

Then, copy the `csp_autoconfig.h` file found in `libcsp/build/include/csp` into the `libcsp/include/csp` folder.

Once the automatically configured header is placed with the rest of the header files, copy the entier `libcsp/include/csp` folder into your computer's C/C++ include directory.

TIP: On linux, this is typically found in `/usr/include`.

You'll find instructions similar on how to install the library inside the repo's INSTALL file.

## Compiling
To compile the Named Pipe (FIFO) routing code, run the following commands in a terminal:
```
$ cmake src/
$ make
```

### Creating the named pipe
For this program to work, two named pipes need to be available. Run the following command to create them:
```
$ mkfifo client_to_server server_to_client
```

This should create two files named `client_to_server` and `server_to_client`. These will act as the file descriptor for the named pipe that the program uses. 

## Usage
To run the program, run:
```
$ ./CSP_fifo_routing <server/client>
```

2 Terminal windows must open either the server or client version respectively. You will be prompted by the client version to enter a message to be sent to the server via a named pipe
