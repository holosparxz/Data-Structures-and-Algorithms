#include <stdio.h>
#include <iostream>
#include "big-O.h"

using namespace std;

int main() {
 int x[6] = {-1,12,-3,14,-4,3};
 int n = 6;

 cout<< algoA(x,n) << "\n";
 cout<< algoB(x,n) << "\n";
 cout<< algoC(x,n) << "\n";
 return 0;
}
