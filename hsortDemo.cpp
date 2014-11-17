#include <iostream>
#include <fstream>
#include <vector.h>
#include <genalg.h>
#include <gheap_advanced.h>
#include <cmath>

typedef char ElementType; const char* e_t = "char"; const char ofc = '\0';
// typedef int ElementType; const char* e_t = "int"; const char ofc = ' ';
// #include <xstring.cpp>
// typedef fsu::String ElementType; const char* e_t = "String"; const char ofc = ' '; 

namespace fsu
{

  template <class I>
  void PrintHeap (I beg, I loc, I end, char ofc = '\0', std::ostream& os = std::cout)
  {
    size_t n = end - beg;
    size_t k = loc - beg;
    size_t i = 0;  // current index
    size_t p = 2;  // current power of 2
    // initialize i,p
    while (i < k)
    {
      i+= 1;
      if (i + 1 == p)
        p <<= 1;
    }
    if (k + 1 == p) // k is the beginning of this level - start there
      i = k;
    else // k is in the previous level - start at thebeginning of that level
      i = (p >> 1) - 1;

    if (ofc == '\0')
    {
      while (i < n)
      {
        (i < k ? os << ' ' : os << beg[i]); // shoot blanks til we get to k
        i += 1;
        if (i + 1 == p || i == n) // if at the end of a level, go to next level
        {
          os << '\n';
          p <<= 1;
        }
      }
    }
    else
    {
      while (i < n)
      {
        (i < k ? os << ofc << ' ' : os << ofc << beg[i]);
        i += 1;
        if (i + 1 == p || i == n)
        {
          os << '\n';
          p <<= 1;
        }
      }
    }
    os << '\n';
  }

  //-------------------------------------
  // g_build_heap_demo (iter, iter, bool)
  //-------------------------------------

  template <class I>
  void g_build_heap_demo (I beg, I end, bool verbose)
  // default order version
  {
    size_t size = end - beg;
    if  (size < 2) return;
    if (verbose) PrintHeap(beg, beg+size/2,end);
    for (size_t i = size/2; i > 0; --i)
    {
      fsu::g_heap_repair(beg,beg+(i-1),end);
      if (verbose) PrintHeap(beg,beg+(i-1),end);
    }
  }

  //-------------------------------------
  // g_heap_sort (iter, iter, pred)
  //-------------------------------------

  template <class I>
  void g_heap_sort_demo (I beg, I end, bool verbose)
  // the default order version with all intermediate heaps displayed
  {
    if (end - beg <= 1)
      return;
    size_t size = end - beg;
    size_t i; 
    if (verbose) std::cout << "1: build heap loop:\n\n";
    g_build_heap_demo(beg,end,verbose);
    if (verbose) std::cout << "2: pop heap loop:\n\n";
    if (verbose) fsu::PrintHeap(beg, beg, end, ofc);
    for (i = size; i > 1; --i)
    {
      g_pop_heap(beg, beg + i);
      if (verbose) fsu::PrintHeap(beg, beg, beg + (i - 1), ofc);
    }
  } // end g_heap_sort_demo()

} // namespace fsu

namespace alt
{
  template <class I>
  void g_heap_sort_demo (I beg, I end, bool verbose)
  // the default order version with all intermediate heaps displayed
  {
    if (end - beg <= 1)
      return;
    size_t size = end - beg;
    size_t i; 
    if (verbose) std::cout << "1: push heap loop:\n\n";
    if (verbose) fsu::PrintHeap(beg, beg, beg + 1, ofc);
    for (i = 1; i < size; ++i)
    {
      fsu::g_push_heap(beg, beg + (i + 1));
      if (verbose) fsu::PrintHeap(beg, beg, beg + i+1, ofc);
    }
    if (verbose) std::cout << "2: pop heap loop:\n\n";
    if (verbose) fsu::PrintHeap(beg, beg, end, ofc);
    for (i = size; i > 1; --i)
    {
      fsu::g_pop_heap(beg, beg + i);
      if (verbose) fsu::PrintHeap(beg, beg, beg + (i - 1), ofc);
    }
  } // end g_heap_sort_demo()

} // alt

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

  std::cout << "\nThis heap_sort_demo consists of an implementations of HeapSort running on a vector of input data.\n"
	    << "Each call to call to an atomic heap operation is displayed on screen,\n"
	    << "along with the state of the entire vector before and after the call.\n"
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

  fsu::Vector<ElementType>v1(v);

  // demo fsu version
  std::cout << "\nfsu::g_heap_sort\n";
  std::cout << "----------------\n";
  std::cout << "data as entered: ";
  v.Display(std::cout, ofc);
  std::cout << '\n';
  fsu::g_heap_sort_demo(v.Begin(), v.End(), 1);
  std::cout << "data after sort: ";
  v.Display(std::cout, ofc);
  std::cout << '\n';
  // */

  // demo alt version
  std::cout << "\nalt::g_heap_sort\n";
  std::cout << "----------------\n";
  std::cout << "data as entered: ";
  v1.Display(std::cout, ofc);
  std::cout << '\n';
  alt::g_heap_sort_demo(v1.Begin(), v1.End(), 1);
  std::cout << "data after sort: ";
  v1.Display(std::cout, ofc);
  std::cout << '\n';
  // */

  std::cout << "\nEnd demo of heap sort < " << e_t << " >\n";
  return 0;
}

