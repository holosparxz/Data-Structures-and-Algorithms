/**********************************
CS311 Kazumi Slott

Your name: Matt Acosta
Your program number: 1
Hours spent: 10
Describe any difficulties here: 
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
*ls*******************************************************************/


//What is the runtime complexity of this algorithm? O(n^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
int algoA(const int a[], int sz)//Don't change the function headers
{
 // declares variables for later use
 int maxSum = 0;
 int tempSum = 0;
 // size of sub
 for (int i = 0 ; i <= sz; i++) {
  // fills subarray
  for (int j = 0; j < sz - i; j++) {
   tempSum = 0;
   // adds the sum of the subarrays
   for (int k = j; k <= i; k++) {
    tempSum += a[j + k];
    // sets temp sum to maxsum if the temporary sum is greater
    if (tempSum > maxSum) {
     maxSum = tempSum;
    }
   }
  }
 }
 return maxSum;
}

//What is the runtime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoB(const int a[], int sz)
{
 // declares variables for later use
 int sum, biggest_sum = 0;
 
 // goes through the array
 for (int i = 0; i < sz; i++) {
  // if the max sum  plus the array of i is less than the initial value then add biggest sum
  // otherwise set the biggest sum equal to the array of i
  a[i] <= biggest_sum + a[i] ? biggest_sum += a[i] : biggest_sum = a[i];
  if (biggest_sum > sum) {
   sum = biggest_sum;
  }  
 } 
 return sum;
}

//What is the runtime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoC(const int a[], int sz)
{
 // declares variables for later use
 int startIndex;
 int sum, subArrSum = 0;
 
 // goes through array
 for (int i = 0; i < sz; i++) {
  subArrSum += a[startIndex];
  
  // prevents negative numbers
  if (subArrSum < 0) {
   startIndex = i++;
   subArrSum = 0;
  }

  // sets the sum equal to subarray sum if the subarray sum is greater than sum
  if (subArrSum > sum) {
  sum = subArrSum;
  }
 }
 return sum; 
}
