/****************
Template created by Kazumi Slott
CS311

Your name: Matt Acosta
Your programmer number: 1
Hours spent?: 10
Any difficulties?: I was getting compile errors on initialization that did not make sense
Reading the output on PuTTY was difficult due to the length of the output
Could not add an new line before BFTPrint() for some reason since it would change other lines
Roation wasnt rotating correctly numerically
RL rotation was giving me issues by 1 number
*****************/

#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// forward declaration of BST class. We need this because BST class is used as a friend in Node.
// Check your stack_L_T.h if you don't know what to put here.
template <class T>
class AVL;

template <class T>
class Node;
// Make Node and BST template classes.
// You put the class definition and member function implementations in .h when you use template.
// If you don't know how to make them template,
// Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
// Also you made stack_L_T.h using template at the beginning of this semester.

template <class T> // make it a template class
class Node
{
  friend class AVL<T>; // BST wants to access private members of Node
private:
  T el;
  Node *right;
  Node *left;
  int BF;
  Node *up;

public:
  Node() { right = left = up = NULL; }; // default constructor. set right and left to NULL
  Node(const T &e)
  {
    el = e;
    left = right = up = NULL;
    BF = 0;
  };
  T getEl() const { return el; } // returns el
};

// Make it a template class
template <class T>

// public functs call private
class AVL
{
private:
  Node<T> *root; // check stack_L_T.h to see how to declare top
  // You will need 10 private functions here.  WHY private?
  void inOrderPrint(Node<T> *p);
  int getMaxLength(Node<T> *p);
  Node<T> *rightRotation(Node<T> *p);
  Node<T> *leftRotation(Node<T> *p);
  Node<T> *updateBF(Node<T> *Q);
  void balanceTree(Node<T> *P);
  void destroy(Node<T> *p);

public:
  AVL() { root = NULL; } // implement constructor here
  ~AVL();
  void insertNodeI(const T &e);
  void inOrderPrint();
  int getMaxLength();
  void BFTprint();
};

// implement the member functions in the header if you are making a template class

// destructor.
// If you don't know how to make the destructor, check the following
// CS211 Lec notes on BST recursive functions - destroy and in order traversal
// CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
AVL<T>::~AVL()
{
  destroy(root);
}

template <class T>
void AVL<T>::destroy(Node<T> *p) // private function. WHY?
{
  // destroy all nodes
  if (p == NULL)
    return;
  destroy(p->left);
  destroy(p->right);
  delete p;
}

// This is an insert function using iteration.
// You will see insert function using iteration is unwieldy compared to that using recursion above.
// The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void AVL<T>::insertNodeI(const T &e)
{
  Node<T> *newNode = new Node<T>(e); // make a new node.  Check stack_L_T.h to see how you made a new node.
  Node<T> *p = root;
  Node<T> *parent = NULL; // points to the parent of p.

  // move p to NULL
  while (p != NULL)
  {
    // parent points to the parent node while p points to the left or right child.
    parent = p;
    if (e < p->el)
      p = p->left;
    else // p->el <= e
      p = p->right;
  }

  if (parent == NULL) // tree is empty
    root = newNode;
  else if (e < parent->el) // insert a child as the parent's left child
    parent->left = newNode;
  else // parent->el <= e //insert a child as the parent's left child
    parent->right = newNode;

  newNode->up = parent;
  balanceTree(newNode);
}

// If you don't how to make this, check the following
// CS211 Lec notes on BST recursive functions - destroy and in order traversal
// CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void AVL<T>::inOrderPrint()
{
  return inOrderPrint(root);
}

template <class T> // private function. WHY?
void AVL<T>::inOrderPrint(Node<T> *p)
{
  if (p == NULL)
    return;
  inOrderPrint(p->left);
  cout << p->el << "-->";
  inOrderPrint(p->right);
}

// This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int AVL<T>::getMaxLength()
{
  return getMaxLength(root);
}

template <class T>
int AVL<T>::getMaxLength(Node<T> *p) // private function. Why?
{
  if (p == NULL)
    return (0);

  int L = getMaxLength(p->left);
  int R = getMaxLength(p->right);

  return (L > R) ? L + 1 : R + 1;
}

template <class T>
void AVL<T>::BFTprint() // Breadth First Traversal Print
{
  // Use the library's queue. https://cplusplus.com/reference/queue/queue/

  // Make sure to include <queue> at the top
  // create a queue obj of POINTERS to Nodes
  queue<Node<T> *> q;

  // algorithm is discussed in lecture
  if (root != NULL)
  {
    q.push(root);
  }

  // NOTICE
  // front() gives you the front element but it doesn't remove it from the queue.
  // pop() removes the front element

  while (!(q.empty()))
  {
    cout << q.front()->el << ' ' << q.front()->BF << ' ';
    if (q.front()->up != NULL)
    {
      cout << q.front()->up->el << "-->";
    }
    else
    {
      cout << "-->";
    }
    if (q.front()->left != NULL)
    {
      q.push(q.front()->left);
    }
    if (q.front()->right != NULL)
    {
      q.push(q.front()->right);
    }
    q.pop(); // remove front element
  }
}

template <class T>
void AVL<T>::balanceTree(Node<T> *P)
{
  Node<T> *nodeP = updateBF(P);
  Node<T> *tmp;
  if (nodeP == NULL)
    return;

  // LL Violation
  if (nodeP->BF == 2 && nodeP->left != NULL && nodeP->left->BF == 1)
  {
    tmp = rightRotation(nodeP);
  }

  // RR Violation
  else if (nodeP->BF == -2 && nodeP->right != NULL && nodeP->right->BF == -1)
  {
    tmp = leftRotation(nodeP);
  }

  // LR Violation
  else if (nodeP->BF == 2 && nodeP->left != NULL && nodeP->left->BF == -1)
  {
    tmp = leftRotation(nodeP->left);
    nodeP->left = tmp;
    tmp = rightRotation(nodeP);
  }

  // RL Violation
  else // if the (nodeP -> BF == -2 && nodeP -> right != NULL && nodeP -> right -> BF == 1)
  {
    tmp = rightRotation(nodeP->right);
    nodeP->right = tmp;
    tmp = leftRotation(nodeP);
  }
  // sets variable ro tem in order to change root
  Node<T> *parent = tmp->up;
  if (nodeP == root)
  {
    root = tmp;
  }
  // sets it to left
  else if (nodeP == parent->left)
  {
    parent->left = tmp;
  }
  // sets it to right
  else
  {
    parent->right = tmp;
  }
}

template <class T>
Node<T> *AVL<T>::updateBF(Node<T> *Q)
{
  Node<T> *P = Q->up;

  if (Q->up == NULL)
    return NULL;

  if (Q == P->left) // if Q is the left child of P
  {
    P->BF++;
  }
  else // if Q is the right child
  {
    P->BF--;
  }
  while ((P != root) && ((P->BF != 2) && (P->BF != -2)))
  {
    Q = P;
    P = P->up;

    if (Q->BF == 0)
    {
      return NULL;
    }
    // increments
    if (Q == P->left)
    {
      P->BF++;
    }
    // decrements
    else
    {
      P->BF--;
    }
  }
  if ((P->BF == 2) || (P->BF == -2))
  {
    return P;
  }
  return NULL;
}

template <class T>
Node<T> *AVL<T>::rightRotation(Node<T> *p)
{
  Node<T> *L = p->left;
  // root = p -> left;
  Node<T> *tmp = L->right;

  L->up = p->up;
  p->up = L;

  if (tmp != NULL)
  {
    tmp->up = p;
  }

  L->right = p;
  p->left = tmp;

  // responsible for rotation of nodes
  p->BF = getMaxLength(p->left) - getMaxLength(p->right);
  L->BF = getMaxLength(L->left) - getMaxLength(L->right);

  return L;
}

template <class T>
Node<T> *AVL<T>::leftRotation(Node<T> *p)
{
  Node<T> *R = p->right;
  Node<T> *tmp = R->left;

  R->up = p->up;
  p->up = R;

  if (tmp != NULL)
  {
    tmp->up = p;
  }

  R->left = p;
  p->right = tmp;

  // responsible for rotation of nodes
  p->BF = getMaxLength(p->left) - getMaxLength(p->right);
  R->BF = getMaxLength(R->left) - getMaxLength(R->right);

  return R;
}

#endif
