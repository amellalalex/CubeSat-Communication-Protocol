#include "libserial_ext.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <string>

using std::string;

// Extend the LibSerial namespace
namespace LibSerial
{
  // Open master serial device and assign slave
  void MasterPort::Open()
  {
    // Master device ID placeholder
    port = -1;

    // Open master pseudoterminal port
    if((port = getpt()) == -1) // getpt() failed
    {
      MasterOpenFailed error;
      throw error;
    }

    // Grant the master port a slave
    if(grantpt(port) == -1) // grantpt() failed
    {
      MasterGrantFailed error;
      throw error;
    }

    // Unlock the slave port for the master
    if(unlockpt(port) == -1) // unlockpt() failed
    {
      MasterUnlockFailed error;
      throw error;
    }

    // Set slave device path
    slave = ptsname(port);
  }

  // Write string to master serial device
  void MasterPort::Write(string str)
  {
    // Write str to master serial port
    if(write(port, str.c_str(), str.length()) < str.length())
    {
      // write() failed
      MasterWriteFailed error;
      throw error;
    }
  }

  // Read string up to maxlen size from master serial device
  void MasterPort::Read(size_t maxlen, string & str)
  {
    // Create placeholder for incoming serial data
    char buffer[maxlen];

    // Read str from master serial port
    if(read(port, buffer, maxlen) < 0)
    {
      MasterReadFailed error;
      throw error;
    }

    // Copy C type string buffer into str_out
    str = buffer;
  }

  // Read incoming string until a newline character reached
  // INCOMPLETE
  void MasterPort::ReadLine(string & str)
  {
    // Create buffer for serial data
    char buffer[1024];
    int bytes_read = -1;

    while((bytes_read = read(port, buffer, 1024)) > 0)
    {
      for(int x = 0; x < bytes_read; x++)
      {
        if(buffer[x] == '\n')
        {
          buffer[x+1] = '\0';
          str += buffer;
          return;
        }
      }

      str += buffer;
    }

    str += buffer;
    str += '\0';
  }

  // Close master pseudoterminal serial device
  void MasterPort::Close()
  {
    // Close master port
    close(port);
  }

}
