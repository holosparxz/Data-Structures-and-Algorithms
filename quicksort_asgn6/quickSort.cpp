/**********************************
Templated created by Kazumi Slott
CS311

Your name: Matt Acosta
Your programmer number: 1
Hours spent: 2
Any difficulties?: Only difficulty was figuring out what exactly the
lecture notes wanted us to do
***********************************/
#include <iostream>
#include "swap.h"
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

int partition(int ar[], int start, int end)
{
  //I have 3 variables: pivot, i and swap_index. You may have any local variables.

  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).
  mySwap(ar[(start + end) / 2], ar[end]);
  int pivot = ar[end];  
  int red = start;

  //For implementation of this function, refer to my lecture notes "quick sort". 
  for (int green = start; green < end; green++)
  
  //If you used a different algorithm, I would assume you cheated and give you zero points.
  {
    if (ar[green] <= pivot)
    {
      mySwap(ar[red], ar[green]);
      red++;
    }
  }
  //This function returns the index where the pivot value went in.
  mySwap(ar[red], ar[end]);
  return (red); 
}

void quickSort(int ar[], int start, int end)
{
  
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

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
