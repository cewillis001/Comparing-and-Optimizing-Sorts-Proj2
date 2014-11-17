/*
    fgsort.cpp
    08/19/14
    Chris Lacher

    functionality test of generic sort algorithms

    gsort.h: g_selection_sort, g_insertion_sort, g_merge_sort, g_quick_sort 
    gheap.h: g_heap_sort

    Copyright 2014, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <cctype>

#include <vector.h>
#include <deque.h>
#include <list.h>
#include <genalg.h>
// #include <gheap.h>
// #include <gheap_basic.h>
#include <gheap_advanced.h>
#include <gheap_cormen.h>
#include <gsort.h>
#include <compare.h>
#include <insert.h>
#include <xstring.h>

typedef char ElementType; const char* e_t = "char"; const char ofc = '\0';
// typedef int ElementType; const char* e_t = "int"; const char ofc = ' ';
// #include <xstring.cpp>
// typedef fsu::String ElementType; const char* e_t = "String"; const char ofc = ' '; 

void SortHeader (const char* name)
{
  std::cout << "\n== " << name << " ==\n";
}

template <class C>
void Display
            (
	      C                 c,  // container
	      char           name,  // container name code
              std::ostream&    os,  // output stream
	      char            ofc   // output format character
            )
{
  os << name << ": ";
  c.Display(os,ofc);
  os << '\n';
}

template <typename T>
void Display
            (
	      T*                A,  // array variable
              size_t         size,  // size of array
	      char           name,  // array name 
              std::ostream&    os,  // output stream
	      char            ofc   // output format character
            )
{
  os << name << ": ";
  if (ofc == '\0')
    for (T* Aitr = A; Aitr != A + size; ++Aitr)
      os << *Aitr;
  else
    for (T* Aitr = A; Aitr != A + size; ++Aitr)
      os << *Aitr << ofc;
  os << '\n';
}

template <typename T>
void Restore
            (
              fsu::List       < T >& L,  // a list
	      fsu::Vector     < T >& V,  // a vector
	      fsu::Deque      < T >& Q,  // a deque
	      T                     * A,  // an array
	      const fsu::List < T >& source // source for restoration
            )
{
  g_copy (source.Begin(), source.End(), L.Begin());
  g_copy (source.Begin(), source.End(), V.Begin());
  g_copy (source.Begin(), source.End(), Q.Begin());
  g_copy (source.Begin(), source.End(), A);
}

int main(int argc, char* argv[])
{
  bool BATCH = 0; 
  char* comfile = 0;
  std::ifstream comstream;
  std::istream* comstreamPtr(&std::cin);
  if (argc < 2)
  {
    comstreamPtr = &std::cin;
    std::cout << " ** No command filename entered - starting in interactive mode\n"
              << "    To execute a file of commands, enter file name on command line\n\n";
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

  typedef fsu::LessThan <ElementType>    PredicateType1;
  typedef fsu::GreaterThan <ElementType> PredicateType2;
  fsu::List      < ElementType > L;  // a list
  fsu::Vector    < ElementType > V;  // a vector
  fsu::Deque     < ElementType > Q;  // a deque
  ElementType *                   A;  // an array

  // PredicateType1               lt; // predicate object
  PredicateType2               gt; // predicate object

  fsu::PushBackIterator < fsu::Vector < ElementType > > Vpbi(V); // = BackPusher(V);
  fsu::PushBackIterator < fsu::List   < ElementType > > Lpbi(L); // = BackPusher(L);
  fsu::PushBackIterator < fsu::Deque  < ElementType > > Qpbi(Q); // = BackPusher(Q);

  fsu::PushFrontIterator < fsu::Vector < ElementType > > Vpfi(V); // = FrontPusher(V);
  fsu::PushFrontIterator < fsu::List   < ElementType > > Lpfi(L); // = FrontPusher(L);
  fsu::PushFrontIterator < fsu::Deque  < ElementType > > Qpfi(Q); // = FrontPusher(Q);

  ElementType e, s; // entry, sentinal
  fsu::List      < ElementType > inputData; // store user input

  std::cout << "Begin test of generic sort algorithms < " << e_t << " >\n"
	    << "Enter sentinal (character): ";
  (*comstreamPtr) >> s;
  if (BATCH) std::cout << s << '\n';

  std::cout << "Enter data (\""
	    << s
	    << "\" to end): ";
  (*comstreamPtr) >> e;
  if (BATCH) std::cout << e;
  while (e != s)
  {
    inputData.PushBack(e);
    (*comstreamPtr) >> e;
    if (BATCH) std::cout << e;
  }
  if (BATCH) std::cout << '\n';
  if (BATCH) comstream.close();

  std::cout << "data as entered: ";
  Display(inputData,'B',std::cout,ofc);

  // copy to array
  size_t size = inputData.Size();
  A = new ElementType [size];
  fsu::g_copy (inputData.Begin(), inputData.End(), A);

  // push_back_copy to list, vector, deque
  fsu::g_copy (A, A + size, Lpbi);
  fsu::g_copy (L.Begin(), L.End(), Vpbi);        
  fsu::g_copy (V.Begin(), V.End(), Qpbi);

  std::cout << "data after copy: ";
  Display(A,size,'A',std::cout,ofc);
  std::cout << "                 ";
  Display(L,'L',std::cout,ofc);
  std::cout << "                 ";
  Display(Q,'Q',std::cout,ofc);
  std::cout << "                 ";
  Display(V,'V',std::cout,ofc);

  // g_selection_sort()
  SortHeader("g_selection_sort()");
  Restore(L,V,Q,A,inputData);
  fsu::g_selection_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_selection_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_selection_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  fsu::g_selection_sort(L.Begin(), L.End());
  Display(L,'L',std::cout,ofc);
  // */

  // g_selection_sort(>)
  SortHeader("g_selection_sort(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_selection_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_selection_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_selection_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  fsu::g_selection_sort(L.Begin(), L.End(), gt);
  Display(L,'L',std::cout,ofc);
  // */

  // g_insertion_sort()
  SortHeader("g_insertion_sort()");
  Restore(L,V,Q,A,inputData);
  fsu::g_insertion_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_insertion_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_insertion_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  fsu::g_insertion_sort(L.Begin(), L.End());
  Display(L,'L',std::cout,ofc);
  // */

  // g_insertion_sort(>)
  SortHeader("g_insertion_sort(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_insertion_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_insertion_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_insertion_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  fsu::g_insertion_sort(L.Begin(), L.End(), gt);
  Display(L,'L',std::cout,ofc);
  // */

  // g_heap_sort()
  SortHeader("g_heap_sort()");
  Restore(L,V,Q,A,inputData);
  fsu::g_heap_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_heap_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_heap_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_heap_sort(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // alt::g_heap_sort()
  SortHeader("alt::g_heap_sort()");
  Restore(L,V,Q,A,inputData);
  alt::g_heap_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  alt::g_heap_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  alt::g_heap_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // alt::g_heap_sort(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // cormen::g_heap_sort()
  SortHeader("cormen::g_heap_sort()");
  Restore(L,V,Q,A,inputData);
  cormen::g_heap_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  cormen::g_heap_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  cormen::g_heap_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // cormen::g_heap_sort(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_heap_sort(>)
  SortHeader("g_heap_sort(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_heap_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_heap_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_heap_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_heap_sort(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // alt::g_heap_sort(>)
  SortHeader("alt::g_heap_sort(>)");
  Restore(L,V,Q,A,inputData);
  alt::g_heap_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  alt::g_heap_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  alt::g_heap_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // alt::g_heap_sort(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // cormen::g_heap_sort(>)
  SortHeader("cormen::g_heap_sort(>)");
  Restore(L,V,Q,A,inputData);
  cormen::g_heap_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  cormen::g_heap_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  cormen::g_heap_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // cormen::g_heap_sort(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_merge_sort()
  SortHeader("g_merge_sort()");
  Restore(L,V,Q,A,inputData);
  fsu::g_merge_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_merge_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_merge_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_merge_sort(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_merge_sort(>)
  SortHeader("g_merge_sort(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_merge_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_merge_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_merge_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_merge_sort(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_merge_sort_opt()
  SortHeader("g_merge_sort_opt()");
  Restore(L,V,Q,A,inputData);
  fsu::g_merge_sort_opt(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_merge_sort_opt(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_merge_sort_opt(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_merge_sort_opt(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_merge_sort_opt(>)
  SortHeader("g_merge_sort_opt(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_merge_sort_opt(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_merge_sort_opt(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_merge_sort_opt(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_merge_sort_opt(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_merge_sort_bu()
  SortHeader("g_merge_sort_bu()");
  Restore(L,V,Q,A,inputData);
  fsu::g_merge_sort_bu(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_merge_sort_bu(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_merge_sort_bu(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_merge_sort_bu(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_merge_sort_bu(>)
  SortHeader("g_merge_sort_bu(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_merge_sort_bu(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_merge_sort_bu(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_merge_sort_bu(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_merge_sort_bu(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort()
  SortHeader("g_quick_sort()");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort(>)
  SortHeader("g_quick_sort(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort_opt()
  SortHeader("g_quick_sort_opt()");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort_opt(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort_opt(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort_opt(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort_opt(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort_opt(>)
  SortHeader("g_quick_sort_opt(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort_opt(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort_opt(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort_opt(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort_opt(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort_3w()
  SortHeader("g_quick_sort_3w()");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort_3w(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort_3w(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort_3w(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort_3w(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort_3w(>)
  SortHeader("g_quick_sort_3w(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort_3w(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort_3w(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort_3w(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort_3w(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort_3w_opt()
  SortHeader("g_quick_sort_3w_opt()");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort_3w_opt(A, A + size);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort_3w_opt(V.Begin(), V.End());
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort_3w_opt(Q.Begin(), Q.End());
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort_3w_opt(L.Begin(), L.End());
  // Display(L,'L',std::cout,ofc);
  // */

  // g_quick_sort_3w_opt(>)
  SortHeader("g_quick_sort_3w_opt(>)");
  Restore(L,V,Q,A,inputData);
  fsu::g_quick_sort_3w_opt(A, A + size, gt);
  Display(A,size,'A',std::cout,ofc);
  fsu::g_quick_sort_3w_opt(V.Begin(), V.End(), gt);
  Display(V,'V',std::cout,ofc);
  fsu::g_quick_sort_3w_opt(Q.Begin(), Q.End(), gt);
  Display(Q,'Q',std::cout,ofc);
  // fsu::g_quick_sort_3w_opt(L.Begin(), L.End(), gt);
  // Display(L,'L',std::cout,ofc);
  // */

  delete [] A;
  std::cout << "\nEnd test of generic sort algorithms < " << e_t << " >\n";

  return 0;
}
