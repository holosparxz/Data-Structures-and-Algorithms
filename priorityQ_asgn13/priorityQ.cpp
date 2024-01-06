/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: Program checks and treats a given patient priortiy by the severity of their injuries 
Your name: Matt Acosta
Your programmer number: 1
Hours spent making this application: 15
Are you rejecting invalid inputs?: Yes
Any difficulties: program kept stopping at do while loop for some character issue and remembering that I had to compile it specially because of stoi() 
********************************************************/
#include <iostream>
#include <stdexcept>//for exception, invalid_argument
#include <string>//for stoi()
using namespace std;
#include "minHeap.h"
#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.

//I made a total of 5 functions in addition to main(). You can make as many functions as you need.
void showMenu();
int getNum();
int priority(int s, int n);

const int START = 1000; //assuming this number will not go over 9999
int num = 0;

int main()
{
  // variables for later use
  minHeap <int> a(9999);
  int num = 0; 
  int choice;

  //call showMenu() to show the menu
  do 
  {
    showMenu();
    choice = getNum();
    // when the choice is 1, user enters severity
    // and then increments
    if (choice == 1) 
    {
      int severity;
      cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
      cin >> severity;
      int c = priority(severity, num);
      a.insert(c);
      num++;
    }
    // if the user inputs 2, they remove pateint from queue so they can be treated
    // try catch is to see is there is any patients left to be treated
    else if (choice == 2) 
    {
      try 
      {
        int first = a.getMin();
        cout << first << " is going to be treated now" << endl;
      }
      catch (minHeap <int> :: BadIndex)
      {
        cout << "There are no patients waiting" << endl;
      }
    }
    cout << "The queue has " << a;
  } while (choice != 3); // goes through choices if user doesn't input 3
  return 0;
}


//Show the menu
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
}

//You don't need to use this function. If you decide to use it, compile your program using -std=c++11 (check my homework instructions)
//This function rejects non-integers. It returns an integer only.
int getNum()
{
   string choice; //For example, when asking for 10, the user enters ab 
   bool bad;
   int num;
   // end user enters a number 
   do
   {
     // userr enters a character that is not a number
     bad = false;
     cout << "Enter a number: ";
     cin >> choice; 

     try
     {
       num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
       // value is either less than 1 and greater than 3 
       // make user input a valid number (1 - 3)
       if (num < 1 || num > 3) 
       {
         cout << "Invalid choice. The choice should be 1, 2, or 3. ";
         bad = true;
       }
     }
     catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer
     {
       cout << "Your choice has to be a number. ";
       bad = true;
     }
   } while(bad == true);
  return num;
}

// s is severity
// n is number
// formula for calculating pateint priority
int priority (int s, int n) 
{
  int calc = (s * 10000 ) + START + n;
  return calc;
}
