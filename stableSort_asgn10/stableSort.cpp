/***************************************                                           
Template prepared by Kazumi Slott                                                  
CS311                                                                              
This program sorts an array of persons.                                            
                                                                                   
Your name: Matt Acosta                                                                   
Your programmer number: 1                                                      
Hours spent: 7                                                                
Any difficulties?: Kept getting an out of bounds error and segfaulting but I managed to fix iteventually by changing some variables in my stableSort() function                        
****************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "swap.h"  //<=== include your swap.h if you made it so you can call your mySwap() in stableSort(). 
                      //     If you didn't make it, you can make a swap function in this file or call the library's swap(). 
using namespace std;

const int SIZE = 13;

struct person
{
  string fN;
  string lN;
  int grade;
};

// Helper functions meant comparison
// Prints them out in order
bool firstName(person p1, person p2);
bool LastName(person p1, person p2);
bool compareGrades(person p1, person p2);

bool fillAr(person a[])
{
  ifstream fin;
  fin.open("/cs/slott/cs311/stableSort3.in");

  if(!fin)
    {
      cout << "You don't have the input file" << endl;
      return false;
    }
  string f, l;
  int g;
  int i = 0;

  fin >> f >> l >> g;
  while(fin)
    {
      a[i].fN = f;
      a[i].lN = l;
      a[i++].grade = g;
      fin >> f >> l >> g;
    }
  fin.close();
  return true;
}

void printAr(const person a[])
{
  for(int i = 0; i < SIZE; i++)
    cout << a[i].grade << "  " << left << setw(10) << a[i].lN << setw(10) << a[i].fN << endl;
}

//You need to create some functions here, which will be called from stableSort()

void stableSort(person ar[], bool (&func)(person, person))
{
  //You can use a stable sort algorithm of your choice                             
  //use the technique shown in my lecture notes "Lec on passing functions"         
  //Include your swap.h at the top so you can call your mySwap() to swap persons in this function.           
  //If you didn't make swap.h, you can make a swap function in this file or call the library's swap().
  
  // I used insertion sort for this stable sort algorithm

  //call swap
  for(int i = 1; i < SIZE; i++)
  {
    // variables used for swapping in insertion sort
    int right = i; // 1 for now
    int left = i - 1; // 0 for now

 
    // loop sorts until everything is in order
    // func gives a segfault error, dont know how to fix it 
    while (func(ar[right], ar[left]) &&  right > 0)
    {
      // swaps elements in array and decreases array size until its sorted
      swap(ar[right], ar[left]);
      left--;
      right--;
    }
  }
}

// Compares the first names and returns them in order
bool firstName(person p1, person p2) 
{
  return p1.fN <= p2.fN;
}

// Compares last names and returns them in order
bool lastName(person p1, person p2)
{
  return p1.lN >= p2.lN;
}

// Sorts grades in order through comparison
bool compareGrades(person p1, person p2)
{
  return p1.grade <= p2.grade;
}


int main()
{
  person ar[SIZE];
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      //You need to sort the array here
      //HINT: call stableSort multiple times.
      stableSort(ar, firstName);
      stableSort(ar, lastName);
      stableSort(ar, compareGrades);

      cout << "--- result ---" << endl;
      printAr(ar);
    }
  return 0;
}
