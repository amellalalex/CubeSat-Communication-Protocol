#include "SerialPorts.hpp"

namespace SerialPortsCPP
{
  //////////////////////
  //    Master Port   //
  //////////////////////

  void MasterPort::Open()
  {
    // Create master pseudo-terminal device
    if(master_create() != 0)
    {
      throw *(new PortOpenFailed);
    }
  }

  void MasterPort::Listen()
  {
    // Run master_listen on new thread
    listener = new thread(master_listen_cpp);
  }

  void MasterPort::Transmit()
  {
    // Run master_send on a new thread
    transmitter = new thread(master_send_cpp);
  }

  void MasterPort::Close()
  {
    // Terminate listener and transmitter threads
    exit(0);
  }

  void MasterPort::Join()
  {
    // Join listener and transmitter threads
    if(transmitter != NULL) transmitter->join();

  }

  //////////////////////
  //    Slave Port    //
  //////////////////////

  void SlavePort::Open(string path)
  {
    // Open slave device at specified endpoint
    if(slave_create(path.c_str()) != 0)
    {
      throw *(new PortOpenFailed);
    }
  }

  void SlavePort::Listen()
  {
    // Initiate slave_listen on new thread
    listener = new thread(slave_listen_cpp);
  }

  void SlavePort::Transmit()
  {
    // Initiate slave_send on new thread
    transmitter = new thread(slave_send_cpp);
  }

  void SlavePort::Close()
  {
    // Terminate listener and tranmitter threads
    exit(0);
  }

  void SlavePort::Join()
  {
    // Await auto-termination of transmitter thread
    if(transmitter != NULL) transmitter->join();
  }
}
