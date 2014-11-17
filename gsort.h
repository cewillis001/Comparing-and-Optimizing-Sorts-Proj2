/*
    gsort.h
    10/4/14
    Caroline Willis

	This was a project for Data Structures 2, in which the students were supposed 
	to implement various comparison sorts and use the supplied test harnesses
	to optimize them.
	
	There are several versions of each sort, implemented for default ordering of <,
	ordering using a comparator passed as a parameter, iterators used to navigate
	the data structure, and pointers used to navigate the data structure.

	g_selection_sort (only the three parameter version),
	g_merge_sort,
	g_merge_sort_bu,
	g_merge_sort_opt,
	Partition,
	g_quick_sort,
	g_quick_sort_opt,
	g_quick_sort_3w,
	g_quick_sort_3w_opt
	
	were all implemented by Caroline Willis. In the code, these are identified
	by the comment "implemented by CW".
	
	Remaining code is copyright 2014, R. C. Lacher
*/

#include <genalg.h> // Swap, g_copy
#include <gset.h>   // g_set_merge

int cutoff = 16;

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
	// implemented by CW
	// from Selection Sort slide in course notes
    ForwardIterator i, j, k;
    for (i = beg; i!= end; ++i)
    {
      k = i;
      for (j = i; j!= end; ++j)
        if (cmp(*j, *k))
          k = j;
      Swap (*i, *k);
    }
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
	// implemented by CW
	//find middle
    RAIterator mid = beg + ((end - beg)/2);
    
    if(end-beg > 1) //if last and first iter are not identical
    {
      if((mid-beg) > 1) //if the diff between mid and beg is greater than 1
      {
        g_merge_sort(beg, mid); //recursive call
      }
      if((end-mid) > 1) //if the diff between mid and beg is greater than 1
      {
        g_merge_sort (mid, end); //recursive call
      }
    }
    mergesort::Merge(beg, mid, end); //does actual moving of stuff
  }

  template < class RAIterator , class Comparator >
  void g_merge_sort (RAIterator beg, RAIterator end, Comparator& cmp)
  {
	// implemented by CW
    // recursive
    // calls mergesort::Merge (beg, mid, end, cmp);

    RAIterator mid = beg + ((end - beg)/2);
    if(end-beg > 1)
    {
      if((mid-beg) > 1)
      {
        g_merge_sort (beg, mid, cmp);
      }
      
      if((end-mid) > 1)
      {
        g_merge_sort(mid, end, cmp);
      } 
    }
    mergesort::Merge (beg, mid, end, cmp);
  }

  template < class RAIterator > 
  void g_merge_sort_opt (RAIterator beg, RAIterator end)
  {
	// implemented by CW	
    // recursive  
    // calls mergesort::Merge (beg, mid, end);  
    // "the top-down version with 'cutoff' and conditional calls to merge"
    // "typical cutoff size is between 4 and 16

    cutoff = 8;

    RAIterator mid = beg + ((end - beg)/2);
    if(end-beg > 1)
    {
      if((mid-beg) > cutoff)
      { 
        g_merge_sort_opt (beg, mid);   
      }
      else
      {
        g_insertion_sort(beg, mid);
      }             
      
      if((end-mid) > cutoff)          
      {               
        g_merge_sort_opt (mid, end);    
      }                   
      else
      {
        g_insertion_sort(mid, end);
      }
    }

    //merge ranges b,m and m,e to b,e 
    if(*(mid-1) < *mid)
    {
      //do nothing
    }
    else
    {
      mergesort::Merge (beg, mid, end);
    }
  } 

  template < class RAIterator , class Comparator > 
  void g_merge_sort_opt (RAIterator beg, RAIterator end, Comparator& cmp)
  {
	// implemented by CW
    // recursive  
    // calls mergesort::Merge (beg, mid, end, cmp);     
    // "the top-down version with 'cutoff' and conditional calls to merge"  
    // "typical cutoff size is between 4 and 16     
        
    cutoff = 8;
    RAIterator mid = beg + ((end - beg)/2); 

    if(end-beg > 1)
    {
      if((mid-beg) > cutoff)
      {                           
        g_merge_sort_opt(beg, mid, cmp);       
      }                          
      else 
      {                                 
        g_insertion_sort(beg, mid, cmp);                                   
      }                                            
                            
      if((end-mid) > cutoff)                                               
      {                                                       
        g_merge_sort_opt(mid, end, cmp); 
      }
      else               
      {                     
        g_insertion_sort(mid, end, cmp);             
      }                           
    }

    if(cmp(*(mid-1),*mid))
    {
      //do nothing and drink to forget, nightvale
    }
    else
    {
      mergesort::Merge (beg, mid, end, cmp);   
    }
  } 

  template < class RAIterator  > 
  void g_merge_sort_bu (RAIterator beg, RAIterator end)
  {
	// implemented by CW
    // recursive  
    // calls mergesort::Merge (beg, mid, end);  
    size_t n = end - beg;
    if(n< 2) return;
    for(size_t i = 1; i < n; i = i+i)
    {
      for(size_t j = 0; j < n-i; j+= i+i)
      {
        if (n < j+i+i)
          mergesort::Merge (beg + j, beg + j+i, beg + n);
        else
          mergesort::Merge (beg + j, beg + j+i, beg + j+i+i);
      }
    }

  } 

  template < class RAIterator , class Comparator > 
  void g_merge_sort_bu (RAIterator beg, RAIterator end, Comparator& cmp)
  {
	// implemented by CW
    // recursive  
    // calls mergesort::Merge (beg, mid, end, cmp);  
    size_t n = end - beg;
    if(n< 2) return; 
    for(size_t i = 1; i < n; i = i+i)
    {
      for(size_t j = 0; j < n-i; j+= i+i) 
      {
        if (n < j+i+i)
          mergesort::Merge (beg + j, beg + j+i, beg + n, cmp);  
        else 
          mergesort::Merge (beg + j, beg + j+i, beg + j+i+i, cmp);
      } 
    }
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
      // implemented by CW

      for(IterType j = first; j!= last; ++j)
      {
        if(!(cmp(*last, *j)))
        {
          Swap(*pivot, *j);
          ++pivot;
        }
      }
      Swap(*pivot,*last);
      return pivot;
    }

  } // namespace

  template < class IterType >
  void g_quick_sort (IterType beg, IterType end)
  {
	// implemented by CW
    // recursive
    // calls quicksort::Partition(beg, end);
    if(end-beg > 1)
    {
      IterType q = quicksort::Partition(beg, end-1);
      g_quick_sort(beg, q);
      g_quick_sort(q+1, end);
    }
  }

  template < class IterType , class Comparator >
  void g_quick_sort (IterType beg, IterType end, Comparator& cmp)
  {
	// implemented by CW
    // recursive
    // calls quicksort::Partition(beg, end, cmp);
    if(end - beg > 1)
    {
      IterType q = quicksort::Partition(beg, end-1, cmp);
      g_quick_sort(beg, q, cmp);
      g_quick_sort(q+1, end, cmp);
    }
  }

  // following are the optimized versions

  template < class IterType >
  void g_quick_sort_opt (IterType beg, IterType end)
  {
	// implemented by CW
    cutoff = 11;
    if(end - beg > 1)
    {
      if(end - beg > cutoff)
      {
        IterType q = quicksort::Partition(beg, end-1); 
        g_quick_sort_opt(beg, q);
        g_quick_sort_opt(++q, end);
      }
      else
      {
        g_insertion_sort(beg, end);
      }
    }
  }

  template < class IterType , class Comparator >
  void g_quick_sort_opt (IterType beg, IterType end, Comparator& cmp)
  {
    // implemented by CW
    cutoff = 11;     
    if(end - beg > 1)
    {   
      if(end - beg > cutoff) 
      { 
        IterType q = quicksort::Partition(beg, end-1, cmp);
        g_quick_sort_opt(beg, q, cmp);
        g_quick_sort_opt(++q, end, cmp); 
      }
      else 
      { 
        g_insertion_sort(beg, end, cmp);
      }  
    }
  }

  template < typename T >
  void g_quick_sort_3w (T* beg, T* end)
  {
    // implemented by CW
    if(end-beg > 1)
    {
      T* low = beg;
      T* hih = end;
      T v = *beg;
      T* i = beg;
      while(i != hih)
      {
        if(*i < v) Swap(*low++, *i++);
        else if (*i > v) Swap(*i, *--hih);
        else ++i;
      }
      g_quick_sort_3w(beg, low);
      g_quick_sort_3w(hih, end);
    }
  }

  template < typename T , class Comparator >
  void g_quick_sort_3w (T* beg, T* end, Comparator& cmp)
  {
    // implemented by CW
    if(end-beg >1)
    {
      T* low = beg;
      T* hih = end; 
      T v = *beg; 
      T* i = beg;
      while(i != hih) 
      {
        if(cmp(*i,v)) Swap(*low++, *i++);
        else if (!cmp(*i,v)) //greater than or equal to 
        {      
          if(*i == v) ++i;
          else Swap(*i, *--hih);
        }
      } 
      g_quick_sort_3w(beg, low, cmp);
      g_quick_sort_3w(hih, end, cmp);
    }
  }

  template < class IterType >
  void g_quick_sort_3w (IterType beg, IterType end)
  {
    // implemented by CW
    if(end-beg >1)
    {  
      IterType low = beg;
      IterType hih = end;
      //if having problems with this, check for v issues
      typename IterType::ValueType v = *beg;
      IterType i = beg;
      while(i != hih)
      {
        if(*i < v) Swap(*low++, *i++);
        else if(*i > v) Swap(*i, *--hih);
        else ++i;
      }
      g_quick_sort_3w(beg, low);
      g_quick_sort_3w(hih, end);
    }
  }

  template < class IterType , class Comparator >
  void g_quick_sort_3w (IterType beg, IterType end, Comparator& cmp)
  {
	// implemented by CW
    if(end-beg >1)
    {
      IterType low = beg;
      IterType hih = end;
      //if having problems with this, check v for issues
      typename IterType::ValueType v = *beg;
      IterType i = beg;
      while(i != hih)
      {
        if(cmp(*i, v)) Swap(*low++, *i++);
        else if(!(cmp(*i,v)))
        {
          if(*i == v)
          {
            ++i;
          }
          else Swap(*i, *--hih);
        }
      }
      g_quick_sort_3w(beg, low, cmp);
      g_quick_sort_3w(hih, end, cmp);
    }
  }

  template < class IterType >
  void g_quick_sort_3w_opt (IterType beg, IterType end)
  {
    // implemented by CW
    cutoff = 13;
    if(end-beg > 1)
    {
      if(end-beg > cutoff)                  
      { 
        IterType low = beg; 
        IterType hih = end;  
        //if having problems with this, check v for issues  
        typename IterType::ValueType v = *beg;                          
        IterType i = beg;                            
        while(i != hih)   
        {
          if(*i < v) Swap(*low++, *i++);        
          else if(*i > v) Swap(*i, *--hih); 
          else ++i;
        }  
        g_quick_sort_3w(beg, low); 
        g_quick_sort_3w(hih, end); 
      }
      else if(end-beg > 1 && end-beg <= cutoff)
      {
      //better algorithm
        g_insertion_sort(beg, end);
      }
    }
  }

  template <class IterType, class Comparator >
  void g_quick_sort_3w_opt (IterType beg, IterType end, Comparator& cmp)
  {
	// implemented by CW
    cutoff = 13;
    if(end-beg > 1)
    {
      if(end-beg > cutoff)
      { 
        IterType low = beg; 
        IterType hih = end;  
        //if having problems with this, check v for issues  
        typename IterType::ValueType v = *beg;                          
        IterType i = beg;                            
        while(i != hih)   
        {
          if(cmp(*i, v)) Swap(*low++, *i++);        
          else if(!(cmp(*i,v))) 
        {     
          if(*i == v) 
          { 
            ++i;  
          } 
          else Swap(*i, *--hih);   
        } 
      }  
        g_quick_sort_3w_opt(beg, low, cmp); 
        g_quick_sort_3w_opt(hih, end, cmp); 
      }
      else if(end-beg > 1 && end-beg <= cutoff)
      {
        g_insertion_sort(beg, end, cmp);
      }
    }
  }// quicksort3wopt cmp

  template < typename T > 
  void g_quick_sort_3w_opt (T* beg, T* end)
  {
	// implemented by CW
    int cutoff = 13;       

    if(end-beg > cutoff)
    {
      T* low = beg;
      T* hih = end;
      T v = *beg;
      T* i = beg;
      while(i != hih)
      {
        if(*i < v) Swap(*low++, *i++);
        else if (!(*i < v)) //greater than or equal to 
        {
          if(*i == v) ++i;
          else Swap(*i, *--hih); 
        }  
      }
      g_quick_sort_3w(beg, low);
      g_quick_sort_3w(hih, end);
    }
    else if(end-beg > 1 && end-beg <= cutoff)                                                            
    {                                                                                                    
      g_insertion_sort(beg, end); 
    } 
  }//end quick sort 3w opt no cmp pointer

  template < typename T , class Comparator >
  void g_quick_sort_3w_opt (T* beg, T* end, Comparator& cmp)
  {                  
    // implemented by CW
    cutoff =13;
    if(end-beg > cutoff)
    {
      T* low = beg; 
      T* hih = end;
      T v = *beg;
      T* i = beg;               
      while(i != hih)                                                                       
      { 
        if(cmp(*i,v)) Swap(*low++, *i++);
        else if (!cmp(*i,v)) //greater than or equal to 
        {
          if(*i == v) ++i;
          else Swap(*i, *--hih);
        } 
      } 
      g_quick_sort_3w(beg, low, cmp);
      g_quick_sort_3w(hih, end, cmp);
    }
    else if(end-beg > 1 && end-beg <= cutoff)                                                            
    { 
      g_insertion_sort(beg, end, cmp);                                                                   
    } 
  }// end of quick sort 3w opt cmp with pointers


} // namespace fsu
