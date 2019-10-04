#ifndef LIBSERIAL_EXT_HPP
#define LIBSERIAL_EXT_HPP

#include <exception>
#include <string>

// C++ standard strings
using std::string;

// Extends the LibSerial namespace
namespace LibSerial
{
  // Introduce master pseudo-terminal device class
  class MasterPort
  {
  public:
    string slave;

    void Open();
    void Write(string str);
    void Read(size_t maxlen, string & str);
    void ReadLine(string & str);
    void Close();

  private:
    int port;
  };

  // Add a few exceptions
  class MasterOpenFailed : public std::exception
  {
    virtual const char *what() const throw()
    {
      return "[!] Failed to open master port.";
    }
  };

  class MasterGrantFailed : public std::exception
  {
    virtual const char *what() const throw()
    {
      return "[!] Failed to grant master device a slave.";
    }
  };

  class MasterUnlockFailed : public std::exception
  {
    virtual const char *what() const throw()
    {
      return "[!] Failed to unlock slave port for the master device.";
    }
  };

  class MasterWriteFailed : public std::exception
  {
    virtual const char *what() const throw()
    {
      return "[!] Failed to write string to master device.";
    }
  };

  class MasterReadFailed : public std::exception
  {
    virtual const char *what() const throw()
    {
      return "[!] Failed to read string from master device.";
    }
  };
}


#endif /* end of include guard: LIBSERIAL_EXT_HPP */
