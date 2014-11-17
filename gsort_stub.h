// students: be sure to supply your own file header in place of the one below!

/*
    gsort_stub.h
    08/21/14
    Chris Lacher

    generic sort algorithms applicable to a range specified by iterators

    includes these generic sort algorithms:

      g_selection_sort
      g_merge_sort
      g_insertion_sort
      g_quick_sort
 
    note that g_heap_sort (all versions) are located in gheap_*.h

    stub version
      - has missing code in a number of places
      - has some code provided to help get started

    Copyright 2014, R. C. Lacher
*/

#include <genalg.h> // Swap, g_copy
#include <gset.h>   // g_set_merge

namespace fsu
{

  template < class ForwardIterator >
  void g_selection_sort (ForwardIterator beg, ForwardIterator end)
  {
    ForwardIterator i, j, k;
    for (i = beg; i != end; ++i)
    {
      k = i;
      for (j = i; j != end; ++j)
        if (*j < *k)
          k = j;
      Swap (*i, *k);
    }
  }

  template < class ForwardIterator, class Comparator >
  void g_selection_sort (ForwardIterator beg, ForwardIterator end, Comparator& cmp)
  {
    // to be supplied
  }

  template < class BidirectionalIterator >
  void g_insertion_sort (BidirectionalIterator beg, BidirectionalIterator end)
  {
    BidirectionalIterator i, j, k;
    typename BidirectionalIterator::ValueType t;
    for (i = beg; i != end; ++i)
    {
      t = *i;
      for (k = i, j = k--; j != beg && t < *k; --j, --k)
        *j = *k;
      *j = t;
    }
  }

  template < class BidirectionalIterator, class Comparator >
  void g_insertion_sort (BidirectionalIterator beg, BidirectionalIterator end, Comparator& cmp)
  {
    BidirectionalIterator i, j, k;
    typename BidirectionalIterator::ValueType t;
    for (i = beg; i != end; ++i)
    {
      t = *i;
      for (k = i, j = k--; j != beg && cmp(t,*k); --j, --k)
        *j = *k;
      *j = t;
    }
  }

  // specialization for pointers
  template < typename T >
  void g_insertion_sort (T* beg, T* end)
  {
    // fsu::Debug ("g_insertion_sort");
    T *i, *j, *k;
    T t;
    for (i = beg; i != end; ++i)
    {
      t = *i;
      for (k = i, j = k--; j != beg && t < *k; --j, --k)
        *j = *k;
      *j = t;
    }
  }

  // specialization for pointers
  template < typename T , class Comparator >
  void g_insertion_sort (T* beg, T* end, Comparator& cmp)
  {
    T *i, *j, *k;
    T t;
    for (i = beg; i != end; ++i)
    {
      t = *i;
      for (k = i, j = k--; j != beg && cmp(t,*k); --j, --k)
        *j = *k;
      *j = t;
    }
  }

  namespace mergesort
  // note: These are supplied complete and ready for use
  {

    // these are the special "merge" functions supporting merge sort
    // note that these are complete and can be used as is

    // for random access iterators and default order
    template < typename RAIterator >
    void Merge(RAIterator beg, RAIterator mid, RAIterator end)
    {
      typename RAIterator::ValueType  B [end - beg];   // temp space for merged copy of A
      g_set_merge(beg, mid, mid, end, B);      // merge the two parts of A to B
      g_copy(B, B+(end-beg), beg);             // copy B back to A[p,r)
    }

    // for random access iterators and order determined by a predicate object
    template < typename RAIterator , class Comparator >
    void Merge(RAIterator beg, RAIterator mid, RAIterator end, Comparator& cmp)
    {
      typename RAIterator::ValueType  B [end - beg];
      g_set_merge(beg, mid, mid, end, B, cmp);
      g_copy(B, B+(end-beg), beg);
    }

    // specialization for pointers and default order
    template < typename T >
    void Merge(T* beg, T* mid, T* end)
    {
      T B [end - beg];                     // temp space for merged copy of A
      g_set_merge(beg, mid, mid, end, B);  // merge the two parts of A to B
      g_copy(B, B+(end-beg), beg);         // copy B back to A[p,r)
    }

    // specialization for pointers and predicate order
    template < typename T , class Comparator >
    void Merge(T* beg, T* mid, T* end, Comparator& cmp)
    {
      T B [end - beg];
      g_set_merge(beg, mid, mid, end, B, cmp);
      g_copy(B, B+(end-beg), beg);
    }

  } // namespace mergesort

  template < class RAIterator >
  void g_merge_sort (RAIterator beg, RAIterator end)
  {
    // recursive
    // calls mergesort::Merge (beg, mid, end);
  }

  template < class RAIterator , class Comparator >
  void g_merge_sort (RAIterator beg, RAIterator end, Comparator& cmp)
  {
    // recursive
    // calls mergesort::Merge (beg, mid, end, cmp);
  }

  // Note: specializations of mergesort::Merge are needed to handle pointer
  // cases, but specializations are not needed for g_merge_sort itself

  namespace quicksort
  {

    // namespace supporting quicksort
    // NOTE that inside this namespace iterators define closed ranges [p,r]

    template < class IterType >
    IterType Partition (IterType first, IterType last) // closed range [first,last]
    {
      // this code is complete
      IterType pivot = first;  // initially the pivot position is first position
      for (IterType j = first; j != last; ++j)
      {
        if (!(*last < *j)) // if (*j <= *last)
        {
          Swap(*pivot,*j);
          ++pivot;
        }
      }
      Swap (*pivot,*last);
      return pivot;
    }

    template < class IterType , class P >
    IterType Partition (IterType first, IterType last, P& cmp) // closed range [first,last]
    {
      IterType pivot = first;
      // .. needs code here
      return pivot;
    }

  } // namespace

  template < class IterType >
  void g_quick_sort (IterType beg, IterType end)
  {
    // recursive
    // calls quicksort::Partition(beg, end);
  }

  template < class IterType , class Comparator >
  void g_quick_sort (IterType beg, IterType end, Comparator& cmp)
  {
    // recursive
    // calls quicksort::Partition(beg, end, cmp);
  }

  // following are the optimized versions

  template < class IterType >
  void g_quick_sort_opt (IterType beg, IterType end)
  {
    // implementation required
  }

  template < class IterType , class Comparator >
  void g_quick_sort_opt (IterType beg, IterType end, Comparator& cmp)
  {
    // implementation required
  }

  template < typename T >
  void g_quick_sort_3w (T* beg, T* end)
  {
    // implementation required
  }

  template < typename T , class Comparator >
  void g_quick_sort_3w (T* beg, T* end, Comparator& cmp)
  {
    // implementation required
  }

  template < class IterType >
  void g_quick_sort_3w (IterType beg, IterType end)
  {
    // implementation required
  }

  template < class IterType , class Comparator >
  void g_quick_sort_3w (IterType beg, IterType end, Comparator& cmp)
  {
    // implementation required
  }

  // note: missing are g_merge_sort_opt, g_merge_sort_bu, g_quick_sort_3w_opt

} // namespace fsu
