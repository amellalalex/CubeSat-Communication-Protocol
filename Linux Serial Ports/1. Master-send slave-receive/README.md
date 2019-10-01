# Example 1: Master-send, slave-receive
In this primitive example, a master pseudo-terminal device is created and sends a single message to its respective slave device.

## Objective
The objective of this example is to demonstrate:
* Creation of master/save pseudoterminal port pairs.
* Usage and communication between them.
* Error and exception handling of the functions relevant to the aforementioned tasks.

## Usage
### Creating the master device
`./a.out master` :
* Creates the master pseudoterminal port.
* Returns the designated slave serial port.
    
### Creating the corresponding slave device
`./a.out slave <slave serial port>`
* Creates the slave pseudoterminal port.

## Compiling
Using the terminal, run:
```
make
```
The code should compile without any errors. Keep in mind it was written for a linux machine (and uses several linux-only headers), but I am curious to know of any errors or improvements that could be made!

## Prompts
All prompts are fronted with specific specifiers, described as follows:
* `[*]`     Signifies a generic prompt.
* `[!]`     Signifies an error message.
* `[(!)]`   Signifies a non-critical error message (execution continues anyway).
