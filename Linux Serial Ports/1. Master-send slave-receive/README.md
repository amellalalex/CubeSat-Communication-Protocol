# Example 1: Master-send, slave-receive
In this primitive example, a master pseudo-terminal device is created and sends a single message to its respective slave device.

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

## Usage
### Creating the master device
`./pseudo-terminal master` :
* Creates the master pseudoterminal port.
* Returns the designated slave serial port.

### Creating the corresponding slave device
`./pseudo-terminal slave <slave serial port>`
* Creates the slave pseudoterminal port.

## Prompts
All prompts are fronted with specific specifiers, described as follows:
* `[*]`     Signifies a generic prompt.
* `[!]`     Signifies an error message.
* `[(!)]`   Signifies a non-critical error message (execution continues anyway).
