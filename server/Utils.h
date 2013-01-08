#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Utils
{
 public:
  static std::string int2str(int in);
  static int str2int(std::string in);
  static int randEx(int range_min, int range_max);
};

#endif
