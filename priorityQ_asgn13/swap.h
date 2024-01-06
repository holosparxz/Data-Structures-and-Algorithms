/********************************
The following mySwap works like the swap function in the library.

Your name: Matt Acosta
Your programmer number: 1
Hours spent: 6
Any difficulties?: Wasn't a 100% sure on what to write on swap.h.
I was confused on if wee needed to change the types or not also as it wasn't clear.
Sources: https://stackoverflow.com/questions/31902655/swap-two-objects-of-class#31902702
********************************/
template<class T>

void mySwap(T& a, T& b)
{
T c = a;
a = b;
b = c;
}
