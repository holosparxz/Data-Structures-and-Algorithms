/******************************************
Template prepared by Kazumi Slott
CS311

Description of this program:
house.cpp is meant to read the inputs given by house_info and house_function. It also does the matrix calculation for the given values.

Your name: Matt Acosta
Your programmer number: 1
Number of hours you spent: 2
Any difficulties?: Mainly with what to put in the input file but once I figured that out everything was fine
*******************************************/
//What do you need to include? HINT: What are you using in main()?
//include your matrix.h

#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
  // Creates the matricies for house info and house function
  Matrix<double> m1(4, 4);//4 rows x 4 columns
  Matrix<double> m2(4, 3);//4 rows x 3 columns

  /*
  Your matrices need to be of the same data type.  When you do multiplication, the data types of the 2 matrices need to be the same.

  //Create 2 input files yourself. You need to name them house_info.in and house_func.in, otherwise my auto-grader will not run your program.

  //Check matrixClient.cpp to see an example
  create fin
  */

  ifstream fin;  

  /*
  open the first file (which file should be the first? You need to figure it out.)
  load the data into the first matrix
  close fin
  */

  fin.open("house_info.in");
  fin >> m1;
  fin.close();
  
  /*
  open the second file
  load the data into the second matrix
  close fin
  */

  fin.open("house_func.in");
  fin >> m2;
  fin.close();

  /*
  use try and catch
  In catch, show the following message.
  cout << "SIZE ERROR" << endl;
  */
  try {
     Matrix<double> m3 = m1 * m2;
     cout << m3;
  }
  catch(Matrix<double>:: size_error) {
     cout << "SIZE ERROR" << endl;
  }

  return 0;
}
