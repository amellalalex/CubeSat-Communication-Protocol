# Example 1: Master-send, slave-receive
In this primitive example, a master pseudo-terminal device is created and sends a single message to its respective slave device. The slave then answers to the master with another message.

## LibSerial library
This example was made thanks to the LibSerial C++ library which can be found here: https://github.com/crayzeewulf/libserial .

Since LibSerial lacks any pseudo-terminal capabilities (specifically, the creation of a master pseudo-terminal device), I extended the LibSerial namespace to include a MasterPort class, which contains and operates very similarly to the SerialPort class provided by LibSerial.

## Objective
The objective of this example is to demonstrate:
* Creation of master/slave pseudoterminal port pairs.
* Usage and communication between them.
* Error and exception handling of the functions relevant to the aforementioned tasks.

## Compiling
Using the terminal, run:
```
make
```

You'll need the LibSerial library installed in your /usr directory on linux. Refer to the link above to obtain the source code.

## Usage
`./LibserialCXX` :
* Creates the master/slave pseudo-terminal ports.
* Master sends serial data to the slave.
* Slave answers with more data.
* The pseudo-terminal master/slave pair is closed.

## Prompts
All prompts are fronted with specific specifiers, described as follows:
* `[*]`     Signifies a generic prompt.
* `[!]`     Signifies an error message.
* `[(!)]`   Signifies a non-critical error message (execution continues anyway).
