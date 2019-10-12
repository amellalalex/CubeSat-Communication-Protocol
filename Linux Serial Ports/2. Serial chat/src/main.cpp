#include "SerialPorts.hpp"

#include <iostream>

// Custom C++ wrapper classes
using SerialPortsCPP::MasterPort;
using SerialPortsCPP::SlavePort;
using SerialPortsCPP::InvalidNArgs;

// Standard C++ classes
using std::cout;
using std::endl;
using std::exception;
using std::string;

int main(int argc, char *argv[])
{
  try
  {
    // Check argc
    if(argc < 2)
      throw *(new InvalidNArgs);

    //--- Create or join ---//
    //Create 'lobby'
    if(string(argv[1]) == "create")
    {
      // Create master serial port object
      MasterPort master;

      // Create master/slave pseudo-terminal pair.
      master.Open();

      // Start listening/transmitting to slave
      master.Listen();
      master.Transmit();

      // Wait until tranmitter thread terminates
      master.Join();

      // Close master port
      master.Close();
    }

    // Join 'lobby'
    else if(string(argv[1]) == "join")
    {
      // Check argc
      if(argc != 3)
        throw *(new InvalidNArgs);

      // Create slave serial port object
      SlavePort slave;

      // Open slave device at specified endpoint
      slave.Open(string(argv[2]));

      // Start listening/transmitting to master
      slave.Listen();
      slave.Transmit();

      // Wait until transmitter thread terminates
      slave.Join();

      // Close slave port
      slave.Close();
    }
  }
  catch(exception& e)
  {
    cout << e.what() << endl;
    exit(1);
  }

  // done
  return 0;
}
