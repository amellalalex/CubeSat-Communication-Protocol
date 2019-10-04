# Example 1: Master-send, slave-receive
In this primitive example, a master pseudo-terminal device is created and sends a single message to its respective slave device. The slave then answers to the master with another message.

## LibSerial library
This example was made thanks to the LibSerial C++ library which can be found here: https://github.com/crayzeewulf/libserial.

Since LibSerial lacks any pseudo-terminal capabilities (specifically, the creation of a master pseudo-terminal device), I extended the LibSerial namespace to include a MasterPort class, which contains and operates very similarly to the SerialPort class provided by LibSerial.

### Downloading the distribution package
```
sudo apt install libserial-dev
```
For debian based installations, of course :)

### Compiling LibSerial by hand
The LibSerial library requires a few packages to be compiled. The following command should install the required packages for Debian/Ubuntu users:
```
sudo apt update
sudo apt install g++ git autogen autoconf build-essential cmake graphviz \
                 libboost-dev libboost-test-dev libgtest-dev libtool \
                 python-sip-dev doxygen python-sphinx pkg-config \
                 python3-sphinx-rtd-theme
```

Clone the repository to your folder of choice, then proceed as follows:
```
$ ./compile.sh
$ cd build/
$ sudo make install
```

NOTE: I had some issues with the default installation directory for the shared library objects. To fix this, I had to change the `cmake_install.cmake` file to specify the installation directory to /usr instead of /usr/local. Hope this helps!

For more (and probably better) information regarding the LibSerial library, checkout their repo!

## Objective
The objective of this example is to demonstrate:
* Creation of master/slave pseudoterminal port pairs.
* Usage and communication between them.
* Error and exception handling of the functions relevant to the aforementioned tasks.

## Compiling the example
Using the terminal in the example directory, run:
```
$ cmake src/
$ make
```

You'll need the LibSerial library installed in your /usr directory on linux. See the instructions above on how to do that.

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
