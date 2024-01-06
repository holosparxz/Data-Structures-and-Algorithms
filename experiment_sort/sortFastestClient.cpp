/**************************************************
Implemented by Kazumi Slott
CS311

This client tests your fastest sort with a string array
**************************************************/

#include <fstream>
#include <time.h>
#include "/cs/slott/cs211/checkInput.h"
#include "sort.h"

int main()
{
  const int MAX = 10000000; //the input file has 1000000 numbers                                                                                
  string ar[MAX];

  clock_t start, end;
  ifstream fin;

  cout << "How many numbers do you want to put into the array?: ";
  //the number of elements we can accept is 1 to 1 million. The input file has 1 million numbers. You might want to open it to see.           \
                                                                                                                                               
  int s = getData(1, 1000000, "Please enter a number between 1 and 1000000: ");//getData() is in /cs/slott/cs211/checkInput.h                \
                                                                                                                                               

  fin.open("sortString1mil.in");
  if(!fin)
    {
      cout << "The input file doesn't open" << endl;
      return 0; //program ends here                                                                                                                  
    }

  //fill the array                                                                                                                             
  for(int i = 0; i < s; i++)
    fin >> ar[i];
  fin.close();

  cout << "\n============ Testing your fastest sort";
  start = clock();
  quickSort(ar, 0, s - 1);
  end = clock();
  cout << " with " << s << " numbers" << endl;
  cout << "Elapsed time: " << (end - start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;

  return 0;
}
