#include <iostream>
#include <fstream>
#include <vector.h>
#include <genalg.h>


typedef char ElementType; const char* e_t = "char"; const char ofc = '\0';
// typedef int ElementType; const char* e_t = "int"; const char ofc = ' ';
// #include <xstring.cpp>
// typedef fsu::String ElementType; const char* e_t = "String"; const char ofc = ' '; 

template <typename T>
size_t Partition (fsu::Vector<T>& v, size_t first, size_t last)
// closed range [first,last]
{
  std::cout << "Partition[" << first << "," << last << "]\n";
  std::cout << "  before = (";
  for (size_t i = 0; i < v.Size() - 1; ++i)
    std::cout <<  v[i] << ',';
  std::cout <<  v[v.Size() - 1] << ")\n";

  size_t pivot = first;  // initially the pivot position is first position
  for (size_t j = first; j != last; ++j)
  {
    if (!(v[last] < v[j])) // if (v[j] <= v[last])
    {
      fsu::Swap(v[pivot],v[j]);
      ++pivot;
    }
  }
  fsu::Swap (v[pivot],v[last]);
  std::cout << "   after = (";
  for (size_t i = 0; i < v.Size() - 1; ++i)
    std::cout <<  v[i] << ',';
  std::cout <<  v[v.Size() - 1] << ")\n";
  return pivot;
}

template <typename T>
void quick_sort_demo (fsu::Vector<T>& v, size_t beg, size_t end)
{
  if (beg != end && beg != --end)
  {
    size_t pivot = Partition(v, beg, end);
    quick_sort_demo(v, beg, pivot);
    quick_sort_demo(v, ++pivot, ++end);
  }
}

int main(int argc, char* argv[])
{
  int BATCH = 0; 
  char* comfile = 0;
  std::ifstream comstream;
  std::istream* comstreamPtr(&std::cin);
  if (argc < 2)
  {
    comstreamPtr = &std::cin;
    BATCH = 0;
  }
  else if (argc == 2)
  {
    comfile = argv[1];
    comstream.open(comfile);
    if (comstream.fail())
    {
      std::cout << " ** Error: unable to open command file \"" << comfile << "\"\n";
      return (EXIT_FAILURE);
    }
    comstreamPtr = dynamic_cast<std::ifstream*>(&comstream);
    BATCH = 1;
  }
  else 
  {
    std::cout << " ** Error: too many command line arguments\n"
	      << "    for INTERACTIVE mode enter no arguments\n"
	      << "    for BATCH mode enter command file name\n";
    return (EXIT_FAILURE);
  }

  fsu::Vector < ElementType > v;
  ElementType s,e;

  std::cout << "\nThis quick_sort_demo consists of an implementation of QuickSort running\n"
	    << "on a vector of input data. Each call to Partition is displayed on screen,\n"
	    << "along with the state of the entire vector before and after the call.\n"
	    << "This version of QuickSort always uses the last element of the range as the\n"
	    << "pivot value.\n\n"
	    << "It is helpful to keep in mind that calls to Partition require\n"
	    << "the first and last indices of the range, that is, a closed\n"
	    << "interval of index values. For example, the first call on a vector v\n"
	    << "will be with index values [0,v.Size() - 1].\n\n"
	    << "For this reason the call to Partition is displayed with square brackets.\n\n"
	    << "ElementType = " << e_t << "\n\n";

  std::cout << "Enter sentinal: ";
  (*comstreamPtr) >> s;
  if (BATCH) std::cout << s << '\n';

  std::cout << "Enter data (\""
	    << s
	    << "\" to end): ";
  (*comstreamPtr) >> e;
  if (BATCH) std::cout << e;
  while (e != s)
  {
    v.PushBack(e);
    (*comstreamPtr) >> e;
    if (BATCH) std::cout << e;
  }
  if (BATCH) std::cout << '\n';
  if (BATCH) comstream.close();

  std::cout << "Before: ";
  v.Display(std::cout, ofc);
  std::cout << '\n';
  quick_sort_demo(v, 0, v.Size());
  std::cout << "After:  ";
  v.Display(std::cout, ofc);
  std::cout << '\n';
  std::cout << "\nEnd demo of quick sort < " << e_t << " >\n";
  return 0;
}

