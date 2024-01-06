//Written by Kazumi Slott
//CS311
//This program will compare the 3 functions' runtime

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
#include "big-O.h"

void runAlgo(char algo, const int ar[], int s)
{
  clock_t start, end;

  cout << "============ Testing algo " << algo << " =============== " << endl;
  switch(algo)
    {
    case 'A':  start = clock(); //current time
               cout << algoA(ar, s) << endl;
	       end = clock(); //current time
	       break;
    case 'B':  start = clock();
               cout << algoB(ar, s) << endl;
	       end = clock();
	       break;
    case 'C':  start = clock();
               cout << algoC(ar, s) << endl;
	       end = clock();
	       break;
    }
  cout << "Elapsed time: " << (end - start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;
}  

int main()
{
  const int MAX = 10000; //the input file has 10000 numbers
  int ar[MAX];
  int n;
  cout << "How many numbers do you want to put into the array?: ";
  cin >> n;

  cout << "========== Testing with a file with " << n << " numbers ===========" << endl;
  
  ifstream fin;
  fin.open("big-O.in");

  //fill the array
  for(int i = 0; i < n; i++)
    fin >> ar[i]; 
  fin.close();

  runAlgo('A', ar, n);
  runAlgo('B', ar, n);
  runAlgo('C', ar, n);

  return 0;
}

