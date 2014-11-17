/*
    ranuint.cpp
    10/19/13
    Chris Lacher

    creates random string data for testing 

    Copyright 2013, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <climits>

#include <xran.h>
#include <xran.cpp> // in lieu of makefile

int main( int argc , char * argv[] )
{
  if (argc != 4)
  {
    std::cout << " ** required arguments:\n"
	      << "     1: filename\n"
	      << "     2: upper bound on size ('0' means no upper bound)\n"
	      << "     3: count of items\n"
	      << " ** try again\n";
    return 0;
  }

  char* outfile     = argv[1];
  size_t upperBound = atoll(argv[2]);
  size_t count      = atoll(argv[3]);
  if (upperBound == 0)
  {
    upperBound = UINT_MAX;
  }

  std::ofstream out1(outfile);
  if (out1.fail())
  {
    std::cout << " ** cannot open file " << outfile << '\n'
	      << " ** try again\n";
    return 0;
  }

  fsu::Random_unsigned_int ranuint;

  for (size_t i = 0; i < count; ++i)
  {
    out1 << ranuint(0, upperBound) << '\n';
  }
  out1.close();

  std::cout << "Results stored in file " << outfile << '\n'
	    << "  range: " << 0 << " .. " << upperBound - 1 << '\n'
	    << "  count: " << count << '\n';
  return 0;
}
