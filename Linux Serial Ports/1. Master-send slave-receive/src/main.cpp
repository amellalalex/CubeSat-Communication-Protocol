#include "../include/libserial_ext.hpp"

#include <libserial/SerialPort.h>

#include <iostream>
#include <string>

// C++ standard classes
using std::exception;
using std::cout;
using std::endl;

// LibSerial classes
using LibSerial::MasterPort;
using LibSerial::SerialPort;

int main()
{
  // Create master/slave serial objects
  MasterPort master;
  SerialPort slave;

  try
  {
    // Open master serial port
    master.Open();

    // Open slave serial port
    slave.Open(master.slave);

    // Send message to slave
    master.Write("yo this is message\n");

    // Read message from master
    string message;
    slave.ReadLine(message);

    // Print message to screen
    cout << "[*] Slave received: " << message << endl;

    // Send message to master
    slave.Write("yo im the slave\n");

    // Read message from slave
    string message2;
    master.ReadLine(message2);

    // Print message to screen
    cout << "[*] Master received: " << message2 << endl;

    // Close serial port pair
    master.Close();
    slave.Close();
  }
  catch(exception &e)
  {
    cout << e.what() << endl;
  }

  // done
  return 0;
}
