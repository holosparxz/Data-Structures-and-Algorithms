/**********************************
Templated created by Kazumi Slott
CS311

Your name: Matt Acosta
Your programmer number: 1
Hours spent: 1
Any difficulties?: Just making sure my code matches the psuedocode
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

void merge(int array[], int first, int last)
{
  // creates the slots
  // creates temp array
  int size = (last - first) + 1;
  int* temp = new int [size];

  // creates the halves necesssary to preform merge sort algorithm 
  int leftHalf = first;
  int rightHalf = (first + last) / 2 + 1;
  int middle = (first + last) / 2;
  int index = 0;

  //fill temp array with all numbers from left and right arrays in order
  while (leftHalf <= middle && rightHalf <= last) 
  {
    // when the left side of the array is greater than the right half
    // copy temp index remainder to right half value and increment
    if (array[leftHalf] > array[rightHalf]) 
    {
      temp[index] = array[rightHalf];
      ++rightHalf;
      ++index;
    }

    // otherwise make it equal to left half and increment
    else 
    {
      temp[index] = array[leftHalf];
      ++leftHalf;
      ++index;
    }
  } 
  
  // when the left half is less than or equal to the middle value
  // copy temp remainder to left half and increment
  while (leftHalf <= middle)
  {
    temp[index] = array[leftHalf];
    ++leftHalf;
    ++index;
  }
  
  // when the right half is less than or equal to the last value
  // copy temp remainder to the right half and increment
  while (rightHalf <= last)
  {
    temp[index] = array[rightHalf];
    ++rightHalf;
    ++index; 
  }

  // loop responsible setting array to temp value
  for(int i = first, j = 0; i <= last; ++i, ++j)
  {
    // index j from 0 to end AND i from first til last
    array[i] = temp[j]; 
  }

  // deletes temp array from memory
  delete [] temp;
}

void mergeSort(int array[], int first, int last)
{
  // if there is only 1 element present, just return it; it's sorted.
  if (first == last) 
  {
    // returns to caller immediately
    return;
  }
  // otherwise, there are at least 2 elements
  int middle = (first + last) / 2; // does math for the middle of array
  mergeSort(array, first, middle); // left side, middle inclusive
  mergeSort(array, middle + 1, last); // right side, middle exclusive
  merge(array, first, last); // once the recursive call is finished, this merge function will be called once 
}

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
