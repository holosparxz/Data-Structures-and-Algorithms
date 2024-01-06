/**************************************
Template created by Kazumi Slott
CS311

Your name: Matt Acosta
Your programmer number: 1
Hours spent: 3
Any difficulties?: Just replicating what I saw in the given video
**************************************/

#include <iostream>
using namespace std;

//responsible for swapping elements
void swap(int& data1, int& data2)
{
  int temp = data1;
  data1 = data2;
  data2 = temp;
}

//prints out array
void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}

//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
void insertionSort(int ar[], int n)
{
  //call swap
  for(int i = 0; i < n; i++) 
  {
    // loop sorts until everything is in order
    while (ar[i] > ar[i + 1]) 
    {
      // swaps elements in array and decreases array size until its sorted
      swap(ar[i], ar[i + 1]);
      i--;
    }
  }
}

//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document
void selectionSort(int array[], int N)
{
  //the index of the smallest value
  int smlIndx; 
  //last is the last index in unsorted part
  for(int first = 0; first <= N - 2; first++)
    {
      //assume the first item is the smallest
      smlIndx = first; 
      //find the smallest in unsorted part ([0..last])
      for(int i = first + 1; i <= N - 1; i++)
	{
	  if(array[i] < array[smlIndx]) //The current item is smaller
	    smlIndx = i;
	}
      //swap the smallest with the first item in the unsorted part
      swap(array[smlIndx],array[first]);
    }
}

//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
void bubbleSort(int ar[], int s)
{
  //true if there was swapping in the current iteration, false otherwise 
  bool swapped = false;
  //last is the index of the left element of the last pair to be checked in the current iteration.            
  int last = s - 2; 
  //swapping required in the previous iteration or the first iteration starts
  while (!swapped)         
  {
    //no swapping has happened yet when a new iteration starts.
    swapped = true;
    //check each adjacent pair of items in the unsorted part                              
    for(int i = 0; i <= last; i++)                  
    {
      //If pair is out of order go through loop until pair is ordered
      if(ar[i] > ar[i + 1])                          
      {
        //swap the elements in array and increment
	swap(ar[i], ar[i + 1]);
	swapped = false;             
      }
    }
    //area checked shrinks down after each iteration
    last--;          
  }
}

int partition(int a[], int start, int end)
{
  //copy and paste partition() from your quickSort.cpp
  //I have 3 variables: pivot, i and swap_index. You may have any local variables.
  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).
  swap(a[(start + end) / 2], a[end]);
  int pivot = a[end];  
  int red = start;
  //For implementation of this function, refer to my lecture notes "quick sort". 
  for (int green = start; green < end; green++)
  //If you used a different algorithm, I would assume you cheated and give you zero points.
  {
    //if green is less than pivot go through loop
    if (a[green] <= pivot)
    {
      //swaps elenebts in array and increments
      swap(a[red], a[green]);
      red++;
    }
  }
  //This function returns the index where the pivot value went in.
  swap(a[red], a[end]);
  return (red);
}

void quickSort(int ar[], int start, int end)
{
  //copy and paste merge() from your mergeSort.cpp
  //If the partition has only one element or none, return.
  //In other words, if the partition has at least 2 elements, go inside the if.
  //use start and end to figure out how many elements you have in the partition.
  if(start < end)
  {
    //call partition.
    int part = partition(ar, start, end);
    //quickSort on the left partition
    quickSort(ar, start, part - 1);
    //quickSort on the right partition
    quickSort(ar, part + 1, end);
  }
}

void merge(int ar[], int first, int last)
{
  //copy and paste merge() from your mergeSort.cpp
  //creates the slots
  //creates temp array
  int size = (last - first) + 1;
  int* temp = new int [size];
  //creates the halves necesssary to preform merge sort algorithm
  int leftHalf = first;
  int rightHalf = (first + last) / 2 + 1;
  int middle = (first + last) / 2;
  int index = 0;
  //fill temp array with all numbers from left and right arrays in order
  while (leftHalf <= middle && rightHalf <= last)
  {
    //when the left side of the array is greater than the right half
    //copy temp index remainder to right half value and increment
    if (ar[leftHalf] > ar[rightHalf])
    {
      temp[index] = ar[rightHalf];
      ++rightHalf;
      ++index;
    }
    //otherwise make it equal to left half and increment
    else
    {
      temp[index] = ar[leftHalf];
      ++leftHalf;
      ++index;
    }
  }
  //when the left half is less than or equal to the middle value
  //copy temp remainder to left half and increment
  while (leftHalf <= middle)
  {
    temp[index] = ar[leftHalf];
    ++leftHalf;
    ++index;
  }
  //when the right half is less than or equal to the last value
  //copy temp remainder to the right half and increment
  while (rightHalf <= last)
  {
    temp[index] = ar[rightHalf];
    ++rightHalf;
    ++index;
  }
  //loop responsible setting array to temp value
  for(int i = first, j = 0; i <= last; ++i, ++j)
  {
    //index j from 0 to end AND i from first til last
    ar[i] = temp[j];
  }
  //deletes temp array from memory
  delete [] temp;
}

void mergeSort(int ar[], int first, int last)
{
  //copy and paste mergeSort()from your mergeSort.cpp
  //if there is only 1 element present, just return it; it's sorted.
  if (first == last)
  {
    //returns to caller immediately
    return;
  }
  //otherwise, there are at least 2 elements
  int middle = (first + last) / 2; //does math for the middle of array
  mergeSort(ar, first, middle); //left side, middle inclusive
  mergeSort(ar, middle + 1, last); //right side, middle exclusive
  merge(ar, first, last); //once the recursive call is finished, this merge function will be called once
}

//called from max_heapify and heapSort
void exchange(int& p, int& c)//??
{
    //I have 3 lines of code here.
    //swapping array element based on index
    int temp;
    temp = c;
    c = p;
    p = temp;

}

//turns a heap rooted at i into a max-heap, assuming the left and right subtrees are already max-heaps.
//n is the number of elements in the heap
void max_heapify(int ar[], int n, int i)
{

    int l = 2 * i + 1; //the index of the left child of i
    int r = 2 * i + 2; //the index of the right child of i
    int largest = i; //the index of the largest value amoung the values at i, l and r

    //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
    //Make sure l and r don't go over the heap's range.
    //I have 4 lines of code here. You can have more or less.
    int lc = ar[l];
    int rc = ar[r];
    int node = ar[largest];
    //cout << node << " " << lc << " " << rc << endl;

    if (l < n && ar[largest] < ar[l])
    {
        largest = l;
    }
    if (r < n && ar[largest] < ar[r])
    {
        largest = r;
    }

    //The largest is either the right or left child. We need to exchange the parent with it.
    if (largest != i)
    {
        //exchange the 2 values
        //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
        exchange(ar[i], ar[largest]);
        max_heapify(ar, n, largest);

    }

}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
void build_max_heap(int ar[], int n)
{
    //2 lines of code in this function
    /*
    for each non-leaf node
       call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
    */
    // half of nodes are leafes 
    for (int i = n / 2; i >= 0; i--)
    {
        max_heapify(ar, n, i);
    }
}

//a is an unordered list to start with
//use max_heapify to sort a
//n is the number of elements in the array
void heapSort(int a[], int n)
{
    //I have 6 lines of code in this function. You can have more or less.

    //build max heap from an unordered list
    //call build_max_heap
    build_max_heap(a, n);


    int size = n; //size of the unsorted portion of the array

    while (size > 0) //repeat until heap is empty
    {
        exchange(a[0], a[size - 1]);
        //swap max element with last element - max element is now the last element
        size--;
        //discard the last element from the heap

        //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.
        max_heapify(a, size, 0);
    }
}
