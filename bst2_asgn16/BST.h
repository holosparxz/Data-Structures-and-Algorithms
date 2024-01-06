/****************
Template created by Kazumi Slott
CS311

Your name: Matt Acosta
Your programmer number: 1
Hours spent?: 9
Any difficulties?: I was getting compile errors on initialization that did not make sense
Reading the output on PuTTY was difficult due to the length of the output
Could not add an new line before BFTPrint() for some reason since it would change other lines
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>
class BST;

template <class T>
class Node;
//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>  //make it a template class
class Node
{
  friend class BST<T>; //BST wants to access private members of Node
private:
  T el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){ el = e; left = right = NULL;}; 
  T getEl() const {return el;} //returns el
};

//Make it a template class
template <class T>

// public functs call private
class BST
{
private:
  Node<T>* root; //check stack_L_T.h to see how to declare top

  //You will need 10 private functions here.  WHY private?
  void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p);
  void postOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  int getMinLength(Node<T>* p);
  int getNumNodes(Node<T>* p);
  int getEvenNodes(Node<T>* p);
  Node<T>* searchR(Node<T>* p, const T& e);
  void destroy(Node<T>* p);
  void remove(Node<T>*& p); 

 public:
  BST() {root = NULL;} //implement constructor here
  ~BST(); 
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);  //You need to make this function too.
  bool remove(const T& e);
  void BFTprint();
  void DFTprint();
};

//implement the member functions in the header if you are making a template class


//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
BST<T>::~BST()
{
  destroy(root);
}

template <class T>
void BST<T>::destroy(Node<T>* p) //private function. WHY?
{
  //destroy all nodes
  if (p == NULL) return;
  destroy(p -> left);
  destroy(p -> right);
  delete p;
}

//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()

template <class T>
void BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

template <class T>
void BST<T>::insertNodeR(Node<T>*& p, const T& e) //private function. WHY?
{
  if (p == NULL)
  {
    p = new Node<T>(e);
  }
  else if (e < p -> el)
  {
    insertNodeR(p -> left, e);
  }
  else 
  {
    insertNodeR(p -> right, e);
  }
}

//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void BST<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>(e); // make a new node.  Check stack_L_T.h to see how you made a new node.
  Node<T>* p = root;
  Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; 
      if(e < p -> el) 
	p = p -> left; 
      else //p->el <= e
	p = p -> right;
    }

  if(parent == NULL) //tree is empty
    root = newNode;
  else if(e < parent->el) //insert a child as the parent's left child
    parent -> left = newNode;
  else //parent->el <= e //insert a child as the parent's left child
    parent -> right = newNode;
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void BST<T>::inOrderPrint()
{
  return inOrderPrint(root);
}

template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if (p == NULL) 
    return;
  inOrderPrint(p -> left);
  cout << p -> el << "-->";
  inOrderPrint(p -> right); 
}

template <class T>
void BST<T>::preOrderPrint()
{
  //pre means print parent->left child ->right child
  return preOrderPrint(root);
}

template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if (p ==  NULL)
    return;
  cout << p -> el << "-->";
  preOrderPrint(p -> left);
  preOrderPrint(p -> right);
}

template <class T>
void BST<T>::postOrderPrint()
{
  //post means left->right->parent last
  return postOrderPrint(root);
}

template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if (p == NULL) return;
  postOrderPrint(p -> left);
  postOrderPrint(p -> right);
  cout << p -> el << "-->";
}

//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  return getNumNodes(root);  
}

template <class T>
int BST<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if (p == NULL) return (0);
  else
    return getNumNodes(p -> left) + getNumNodes(p -> right) + 1;
  int L = getNumNodes(p -> left);
  int R = getNumNodes(p -> right);
  return (L + R + 1);
}

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{
  return getMaxLength(root);
}

template <class T>
int BST<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if (p == NULL) return(0);

  int L = getMaxLength(p -> left);
  int R = getMaxLength(p -> right);

  return (L > R) ? L + 1 : R + 1;
}

template <class T>
int BST<T>::getMinLength()
{
  return getMinLength(root);  
}

template <class T>
int BST<T>::getMinLength(Node<T>* p) //private function. WHY?
{
  if( p == NULL )
    return(0);
  else if ( p->right == NULL )
    return(1 + getMinLength(p->left));
  else if ( p->left == NULL )
    return(1 + getMinLength(p->right));
  else
  {
    int count_left = 1 + getMinLength(p->left);
    int count_right = 1 + getMinLength(p->right);
    if ( count_left < count_right )
      return(count_left);
    else
      return(count_right);
  } 
}

//This function will return the number of even elements
template <class T>
int BST<T>::getEvenNodes()
{
  return getEvenNodes(root);
}

template <class T>
int BST<T>::getEvenNodes(Node<T>* p) //private function. WHY?                              
{                                               
  if (p == NULL) return(0);
  int L = getEvenNodes(p -> left);
  int R = getEvenNodes(p -> right); 
  
  if ((p -> el % 2) == 0) 
  {
    return (L + R + 1);
  }
  else 
  {
    return (L + R);
  }
}
                                                                                    
//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchI(const T& e)
{
  Node<T>* p = root;
  while(p != NULL)
  {
    if (e < p -> el) 
    {
      p = p -> left;
    }
    else if (e > p -> el)
    {
      p = p -> right;
    }
    else
    {
      return p;
    }
  } 
  //Where do you return NULL? 
  return NULL;
}

//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchR(const T& e)
{
  return searchR(root, e);
}

template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
{ 
  if (p == NULL) return NULL;
  else if (p -> el == e) return p;
  else if (e < p -> el)
  {
    return searchR(p -> left, e);
  }
  else if (e >= p -> el)
  {
    return searchR(p -> right, e);
  }
}

template <class T>
void BST<T>::BFTprint()  //Breadth First Traversal Print
{
  //Use the library's queue. https://cplusplus.com/reference/queue/queue/

  //Make sure to include <queue> at the top
  //create a queue obj of POINTERS to Nodes
  queue<Node<T>*> q;
  q.push(root);

  //algorithm is discussed in lecture
  Node<T>* p = root;
  //NOTICE
  //front() gives you the front element but it doesn't remove it from the queue.
  //pop() removes the front element

  while(!(q.empty()))
  {
    p = q.front();
    cout << p -> el << "-->";

    if(q.front() -> left != NULL)
    {
      q.push(q.front() -> left);
    }
    if(q.front() -> right != NULL)
    {
      q.push(q.front() -> right);
    }
    q.pop(); //remove front element
  }
}

template <class T>
void BST<T>::DFTprint()  //Depth First Traversal Print
{
  //Use the library's stack class. https://cplusplus.com/reference/stack/stack/

  //Make sure to include <stack> at the top
  //create a stack of POINTERS to Nodes
  stack<Node<T>*> s;
  s.push(root);

  Node<T>* p = root;
  //top() will give you the top element but it will not remove it from the stack.
  //pop() removes the top element.
  while(!(s.empty()))
  {
    p = s.top(); 
    cout << p -> el << "-->"; 
    s.pop(); //remove top element

    if(p->right != NULL)
    {
      s.push(p -> right); //push R kid if any
    }
    if(p->left != NULL)
    {
      s.push(p -> left); //push L kid if any 
    }
  }
}

//This function returns true if e was removed or false if not because it doesn't exist.
template <class T>
bool BST<T>::remove(const T& e) //public function
{
  Node<T>* del = root; //del will point to the node to be deleted
  Node<T>* parent = NULL; //parent will point to the parent of the node to be deleted 

  //look for e in the tree 
  while(del != NULL && del -> el != e) //If root is NULL, del is NULL to start with. While won't be entered and return false down below.
    {
      //parent follows del. In other words, del is ahead of parent. --> you did something similar in insertI()
      //del will eventually point to the node to be deleted.
      parent = del;
      (del -> el > e) ? del = del -> left : del = del -> right;
    }

  //e doesn't exist or tree is empty.
  if(del == NULL)
    return false;

  //check to see if root should be removed
  if(del == root)
    remove(root); //root will change. call the other remove function down below
  //We are deleting a node other than the root node. Figure out if del's node is left or right child of parent's node
  else if(parent -> left == del) //parent's left child to be removed
    remove(parent -> left);
  else //parent's right child to be removed
    remove(parent -> right);

  //deleted the node with e
  return true;
}

template <class T>
//p comes out of the parent node and points to the node to be deleted OR p points to root if root is the one to be deleted.                    
//p will point to the grandchild (child node of the node to be deleted) if the node to be deleted has only one child or will point to NULL if p is root or the node to be deleted has no children. p will change. That is why we need to use &.                                              
void BST<T>::remove(Node<T>*& p) //private function
{
  Node<T>* temp = p; //temp points to the node to be deleted initially
  Node<T>* t_parent; //t_parent will point to the parent node of temp's node

  //the node to be deleted has no right child (Check Diagram1-Right and Left in the homework document "HMWK BST - BFT, DFT and remove" under "Assignments")
  //If the node to be deleted has no children, the following if will be executed.(Check Diagram2-Right and Left) 
  if(p -> right == NULL)  
    p = p -> left; //p(The left or right coming out of parent of del's node) now points to the root of the left subtree under del's node. DONE.  If the node to be deleted has no children, p is set to NULL because p->left is NULL.
  //the node to be deleted has no left child (Check Diagram 3-Right and Left)
  else if(p -> left == NULL)
    p = p -> right;//p(The left or right coming out of parent of del's node) now points to the root of the right subtree under del's node. DONE.
  //If the node to be deleted has 2 children
  else
    {
      //we are going to replace e by the largest value in the left subtree
      temp = p -> left; //temp points to the root of the left subtree under the node to be deleted to start with
      t_parent = p; //t_parent points to the node to be deleted to start with

      //go to the largest value in the left subtree under the node to be deleted by going all the way down to right
      while(temp -> right != NULL)
      {
	t_parent = temp; //temp is ahead of t_parent
	temp = temp -> right; //temp will eventually point to the largest value
      }
      //copy the largest value into the node to be deleted 
      p -> el = temp -> el;   
  
      if(t_parent -> left == temp) //the largest value is the direct left child of the node whose value was replaced by the largest (Diagram 4-one child or no children)
	t_parent -> left = temp -> left; //connect the left of the node whose value was replaced by the largest value to the left child of the node that has the largest value
      else //the largest value is NOT the direct left child of the node whose value was replaced by the largest (Diagram 5-one child and no children)
	t_parent -> right = temp -> left; //If the node with the largest value doesn't have any children, t_parent->right is set to NULL.
    }
  //finally delete temp;
  delete temp;
}

#endif
