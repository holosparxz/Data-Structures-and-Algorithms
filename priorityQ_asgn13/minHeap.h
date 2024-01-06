/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: Matt Acosta
Your programmer number: 1
Hours spent making and testing your min heap class: 8
Any difficulties?: ostream was giving me output troubles 
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

// created helper functions for later use
template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int i);
  //void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();

  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

// min heap helper class
// creates variables for later use
template <class T>
minHeap <T> :: minHeap (int c)
{
  capacity = c;
  ar = new T[c]; 
  num = 0;
}

// same as max_heapify but does the minimum instead
template <class T>
void minHeap <T> :: min_heapify(int i)
{
  int l = (2 * i) + 1; //the index of the left child of i
  int r = (2 * i) + 2; //the index of the right child of i
  int smallest = i; //the index of the largest value amoung the values at i, l and r

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  //I have 4 lines of code here. You can have more or less.
  if (l < num && ar[l] < ar[smallest])
  {
    smallest = l;
  }
                        
  if (r < num && ar[r] < ar[smallest])
  {
    smallest = r;
  }  

  //The smallest is either the right or left child. We need to exchange the parent with it.
  if(smallest != i)
  {
    //exchange the 2 values
    mySwap(ar[i], ar[smallest]);
    //There might be a violation at the position that was exchanged. Call min_heapify to fix it.
    min_heapify(smallest);
  }
}

//this function corrects a violiation at i by bubbling it up to the correct place                             
//ar is a heap                                                                                                
template <class T>
void minHeap <T> :: bubbleUp(int i)
{
  //Write this function after you made insert() and while you are making remove().
  int parent = (i - 1) / 2;
  while (ar[parent] > ar[i])
  {
    //exchanges values 
    mySwap(ar[parent], ar[i]);
    i = parent;
    parent = (i - 1) / 2;
  }
}

//ar is a min heap                                                                                            
//capacity is the capacity of the heap                                                                            
//num is the number of elements the heap currently has before insertion                                        
//el is the new element to be inserted                                                                       
template <class T>
void minHeap <T> :: insert(const T& el)
{
  //refer to lecture notes
  //throw "The array is full" if the array is full.
  if (num == capacity) 
  {
    throw Overflow();
  }
  
  else
  {
    ar[num++] = el;
    bubbleUp(num - 1);
  }
  //write this function without calling bubbleUp() first. When you work on remove(), you will notice you will
  //have to have the same code there. Move the code into bubbleUp() and call it to avoid redundancy. 
}
                                                           
//This function returns the index where key was found or throws an exception if key is not found.                                   
//ar is a min heap.                                                                                 
//num is the number of elements in the heap.                                                                                
//key is the element we are looking for.                                                      //
template <class T>                                       
int minHeap <T> :: find(const T& key) const
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < num; i++)                                                                      if(ar[i] == key)
       return i;
  throw NotFound(); 
}

//ar is a min heap                                                                                            
//num is the number of elements the heap currently has before deletion, then decrememted after deletion                                         
//i is the index of the element to be removed.     
template <class T>                                        
void minHeap <T> :: remove(int i)
{
  //refer to lecture notes
  //throw "The index to be removed is invalid" if i is an invalid index.
  //Call bubbleUp or max_heapify (the lecture notes show 2 possibilities).
  //FYI, I have a total of 8 lines of code in this function. You can have more or less.
                          
  // throws exception if it is out of bounds 
  if (i < 0 || i > num - 1) 
  {
    throw BadIndex();
  }
  else 
  {                            
    //p grabs index and exchanges it with last one
    mySwap(ar[num - 1], ar[i]);
    num--;
                                                  
    // bubbling up & down if it is a subtree
    int p = (i - 1) / 2;
    if (ar[p] > ar[i] && i > 0) 
    {
      bubbleUp(i);
    }
    else 
    {
      min_heapify(i);
    }
  }
}

template <class T>
T minHeap <T>:: getMin()
{
  //This function removes the top element and returns it.
  //You should be calling remove()
  T value = ar[0];
  remove(0);
  return value;
}

// checks if the queue has no patients
// returns none if that is the case
// otherwise it just goes through the array like normal
template <class T>
ostream& operator << (ostream& o, const minHeap <T>& h) 
{
  if (h.num == 0)
  {
    o << "none";
  } 
 
  for (int i = 0; i < h.num; i++) 
  { 
    o << h.ar[i] << " ";
  }
  
  o << endl;
  return o;
}

#endif
