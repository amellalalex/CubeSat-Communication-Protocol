extern "C" {
  #include "SerialPorts.h"
}

#include <string>
#include <exception>
#include <thread>

// C++ standard classes
using std::string;
using std::exception;
using std::thread;

namespace SerialPortsCPP
{
  class MasterPort
  {
  public:
    string slave;
    thread *transmitter = NULL;
    thread *listener    = NULL;

    void Open();
    void Listen();
    void Transmit();
    void Close();
    void Join();
  };

  class SlavePort
  {
  public:
    thread *transmitter = NULL;
    thread *listener    = NULL;

    void Open(string path);
    void Listen();
    void Transmit();
    void Close();
    void Join();

    // TODO: continue working on slave port
  };

  // Exception thrown when serial port fails to open
  class PortOpenFailed : public exception
  {
  public:
    virtual const char *what() const throw()
    {
      return "[!] Failed to open serial port.";
    }
  };

  // Exception thrown when an invalid number of arguments provided
  class InvalidNArgs : public exception
  {
  public:
    virtual const char *what() const throw()
    {
      return "[!] Invalid number of arguments.";
    }
  };
}
