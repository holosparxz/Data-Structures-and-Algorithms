/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: Matt Acosta
Your programmer number here: 1
Hours spent: 10
Any problems you had? Explain here: I had trouble figuring out how to move to the next node after deleting it
###### Don't forget to specify the complexity above each function. ######
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template < class T > //forward declaration needed so we can make stack class a friend of node
class Stack;

template < class T > //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template < class T >
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem;
  Node<T>* next;  //check how right and left pointers are declared in BST class --> /cs/slott/cs211/BST_T.h
 public:
  Node(){next = NULL;} //default constructor
  Node(const T& e){elem = e; next = NULL;} //You should set next to NULL too.
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack

 private:
  Node<T>* top;
 
 //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);

 public:
  Stack() {top = NULL;} //Implement a small function inside the class definition 
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const{return (top == NULL) ? true : false;} //implement a small function inside the class definition
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function

  //Make an empty exception class here. Underflow or/and Overflow? - You need to figure out where to throw an exception - I am throwing in 3 functions.
 class Underflow{};
};

//Complexity of this operation: O(1)
template <class T>
void Stack<T>::push(const T& val)
{
   //FYI, I have 3 lines of code here. You may have less or more.
   //To make a new Node when the Node class is a template class, check insertNode() in /cs/slott/cs211/BST_T.h   // Creates a new node and sets the top to the new node 
   Node<T>* n = new Node<T> (val);
   n -> next = top;
   top = n; 
}

//Complexity of this operation: O(1)
template <class T>
void Stack<T>::pop()
{
  //throw an exception if the stack is empty. (You shouldn't call pop if the stack is empty.)
  if (empty()) {
     throw Underflow();
  }
  // If the stack isnt empty, set new node value to top  and then delete each node
  Node <T>* t = top;
  top = top -> next;
  delete t;
}

//Complexity of this operation: O(1)
template <class T>
T& Stack<T>::getTop()
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
  if (empty()) {
     throw Underflow();
  }
  return top -> elem; //return the top element. Since the return type is T&, the client can change the top.
}

//Complexity of this operation: O(1)
template <class T>
const T& Stack<T>::getTop() const
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
  if (empty()) {
     throw Underflow();
  }
  return top -> elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}

//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj); 
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object). 
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(n)
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //make a temporary node for later use
  Node<T>* temp = s.top;
  
  //print from top to bottom. 
  cout << "--- Top ---" << endl;
  
  // When the temp value isn't null, shift the value and then increment it 
  while (temp != NULL) {
      o << temp -> elem << endl;
      temp = temp -> next;
  }

  cout << "--- Bottom ---" << endl;
 
}

template <class T>
Stack<T>::~Stack()
{
  destroy(); 
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(n)
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  //destroy all nodes
  while (!empty()) {
      // Increments to next node and then deletes it
      Node<T>* deleteNode = top;
      top = top -> next;
      delete deleteNode;
      deleteNode = top;
  } 
}

//Complexity of this operation: O(1)
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  //Notice that the returned reference is not declared const (Stack<T>&). 
  //This can be a bit confusing, because it allows you to write crazy stuff like this: (s1 = s2) = s3;


  //deep copy
  if(this != &rhs) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
              //You copy only if the left object is not the same as the right object.
    {
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //call copy
      this -> destroy();
      this -> copy(rhs);
    }
    return *this; //return the "this" object (not the address of the "this" object). Notice the return type is not void. 
                  //By returning the this object, we can use multiple assignment operators. 
                  //s1 = s2 = s3; same as s1 = s2.operator=(s3);  Now you can see why operator=() needs to return the this object (s2). 
}

//Complexity of this operation: O(n)
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  //"this" object ends up having the same values from source
  //Make sure this function won't crush when the source stack is empty. If the source stack is empty, "this" stack is also empty 
  //The complexity of this function should be O(n). If you implement this function by calling push(), the complexity will probably be O(n^2).
  //Make this function without calling push().
  if (source.empty()) {
     this -> top = NULL;
  }
  // If the source isn't empty, create new node values and set each value to "this" in order to handle incrementing to next spot 
  else {
     Node<T>* a = source.top;
     Node<T>* b = new Node<T>(a -> elem);
     this -> top = b;
    
     // Handles exception case if the area is completely empty 
     while (a != NULL) {
        a = a -> next;
        if (a != NULL) {
           b -> next = new Node<T> (a -> elem);
           b = b -> next;
        }
     }
  }
}

//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data member, top.
  this -> top = NULL;
  //Then you can call the copy function 
  this -> copy(other);
}

#endif // end the definition here
