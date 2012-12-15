#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

class Exception
{
  std::string message;
 public:
  Exception(std::string message);
  Exception();
  ~Exception();
  std::string toString();
};

#endif
