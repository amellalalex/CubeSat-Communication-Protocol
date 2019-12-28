# Example 2: Serial Chat
Building on what was explored in the previous example, simple serial port I/O is expanded into multithreaded and asynchronous exchanges between a master and slave pseudo-terminal device pair.

## Why wrap C code in C++ ?
The linux serial port framework was originally written in C, making it more intuitive to write the underlying serial port handlers in the same language. In addition, C facilitates the manipulation of low-level instructions, but sacrifices code readability and team contributions. For these reasons (among others), writing low-level C handlers and wrapping them in C++ offers the best of both worlds.

With this said, the C++ version of the main function is found in `src/main.cpp`. The C version is found in `src/main.c`. Either way they work the same, but each of them demonstrates the example's objective.

## Compiling
Compiling this example requires cmake. It should go something like this:
```
$ cmake src/
$ make
```

The resulting binary assumes the C++ main function will be initiated.

### Compiling the C version only
Change the `${src-files}` entry for `"main.cpp"` to `"main.c"` in the `src/CMakeLists.txt` file. Just make sure to run `cmake src/` before running the makefile.

## Objective
The objective of this example was to better simulate how serial ports may be used within the context of a satellite and a ground station.

The first example, although helpful, knows exactly when and in which order data will be sent/received via serial ports.

As a step up, this example undertakes the following:
* Asynchronous reading and writing of data via one serial port.
* Achieving this through the use of a 'chat room' like UI.

## Usage
`$ ./chat create `
* Creates the master/slave pseudo-terminal pair (aka chat room).
* Prompts user with the slave device's endpoint path (/dev/pts/\*).
* Enters the 'chat room' and prompts user for input to send to the slave.
* Listens for incoming data from the slave and prints it to the screen.

`$ ./chat join <slave endpoint path>`
* Opens the slave serial device's endpoint (aka joining the chat room).
* Prompts user for input and sends it to the master.
* Listens for incoming data from the master and prints it to the screen.

## Prompts
Prompts are fronted with custom specifiers, described as follows:
* `[*]`     Signifies a generic prompt.
* `[!]`     Signifies an error message.
* `[(!)]`   Signifies a non-critical error message (execution continues anyway).
