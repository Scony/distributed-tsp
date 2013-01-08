#include "Utils.h"

using namespace std;

string Utils::int2str(int var)
{
  char buff[16];
  sprintf(buff,"%d",var);
  return string(buff);
}

int Utils::str2int(string in)
{
  int out;
  sscanf(in.c_str(),"%d",&out);
  return out;
}
