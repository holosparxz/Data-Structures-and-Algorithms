/****************************
Templated created by Kazumi Slott
CS311

Your name: Matt Acosta
Your programmer number: 1
Hours spent: 13
Any difficulties?: The double pointers make it a little harder to track what the object is being pointed to, making it hard to trace what is exaclty where
following the Psuedocode was a little difficult.
Making sure that the verticies were visited and making sure that they were removed once done was hard.
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <stack>
#include "minHeap-graph.h"
using namespace std;

class edge
{                       // make graph a friend of edge
    friend class graph; // What do you need here if you want to access the private members of edge class from graph class
    int neighbor;       // adjacent vertex
    int wt;             // weight of edge
public:
    edge() { neighbor = -999, wt = -999; }; // -999/999 is used for infinity
    edge(int u, int w) { neighbor = u, wt = w; };
};

class graph
{
    int num_ver;          // total number of vertices in graph
    list<edge *> *ver_ar; // pointer to the dynamic array that holds linked lists.
    // The element of a node in a linked list is a pointer to an edge object
    // doubly linked list.
    int nextUnvisitedNodes(int *num, int start, int s);
    void DFT_helper(int v, int &i, int *num, queue<string> &q); 

public:
    graph(int V);
    ~graph();
    void addEdge(int v, int u, int w = 1); // If the weight is not given, 1 is used for wt.
    void BFT(int start);
    void DFT(int start);
    void DijkstraShortestPath(int start);
};

// constructor: num is the number of vertices
graph::graph(int num)
{
    // make a dynamic array with num slots where each slot holds a list object.
    // The element of a node in the linked list is a pointer to an edge object
    num_ver = num;
    // initiliaze number of vertices
    ver_ar = new list<edge *>[num_ver];
}

graph::~graph()
{
    // destroys all the edge objects created in heap
    // For each vertex in ver_ar
    // It goes through each node inside linked list.
    // Element field of each node points to an edge object created with "new".
    // Which will need to be deleted.
    // The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
    // https://www.cplusplus.com/reference/list/list/~list/
    // destroy the ver_ar dynamic array

    for (int i = 0; i < num_ver; i++)
    {
      for (list<edge *>::iterator u = ver_ar[i].begin(); u != ver_ar[i].end(); u++)
      {  
        delete *u;
      }
    }

    delete[] ver_ar;
}

// add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
    // We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
    // https://www.cplusplus.com/reference/list/list/
    // Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
    // I have one line of code in this function.
    edge *addedEdge = new edge(u, w);
    (ver_ar[v]).push_back(addedEdge);
}

// Displays the values present in the queue
template <class T>
void displayQueue(queue<T> &q)
{
    // When the list isnt empty
    // print out contents of array and pop it
    while (!q.empty())
    {
        cout << q.front() << ",";
        q.pop();
    }
}

// start Traversal at start
void graph::DFT(int start)
{
    // Num is a dynamic array needed for later use
    int *num = new int[num_ver];

    // for all vertices v num(v) = 0
    for (int v = 0; v < num_ver; v++)
    {
        num[v] = 0;
    }
    // queue object of string data type from the library's queue class to save all the paths.
    // That are present
    queue<string> q;

    // calls nextUnvisitedNodes() to see if there are more unvisited nodes.
    int i = 1;
    do
    {
        // DFT is called from the current vertex
        DFT_helper(start, i, num, q);
        // Check if there are more unvisited nodes
        start = nextUnvisitedNodes(num, start, start + 1);
    } while (start != -1);

    // You could call displayQueue() implemented above to display all the paths.
    displayQueue(q);
    // Don't forget to destroy the dynamic array
    delete[] num;
}

// I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.
// num is the array of vertices
// start is the start vertex
// s is the vertext right after the vertex we started last time
int graph::nextUnvisitedNodes(int *num, int start, int s)
{
    // function iterates through the num array from s in order to see
    // if you find a vertex with num = 0. If so, return the index.
    // Otherwise, If all vertices are visited, return -1.
    // Iterates through the num array from s to find the next unvisited vertex

    for (int i = s; i < num_ver; ++i)
    {
        if (num[i] == 0)
        {
            // Found an unvisited vertex, return the index
            return i;
        }
    }
    // Otherwise, All vertices have been visited
    return -1;
}

void graph::DFT_helper(int v, int &i, int *num, queue<string> &q)
{
    num[v] = i++;
    cout << v << " ";

    // The following shows how to iterate the library's linked list. You use an iterator.
    // https://www.cplusplus.com/reference/list/list/end/
    // iterator class is nested inside list class
    for (list<edge *>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
        // From the example on https://www.cplusplus.com/reference/list/list/end/
        // Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
        // Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.

        // push each path e.g. 0->1 into q. to_string(int) converts int to string.
        // to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp

        if (num[(*u)->neighbor] == 0)
        {
            q.push(to_string(v) + "->" + to_string((*u)->neighbor));
            DFT_helper((*u)->neighbor, i, num, q);
        }
    }

    /***********************************************************************************************
     **********************************************************************************************
      Compile with a c++11 option if you are using to_string()
          g++ -std=c++11 graphClient.cpp
     **********************************************************************************************
     ***********************************************************************************************/
}

// start is the index for the start vertex
void graph::BFT(int start)
{
    // Use the queue class from the c++ library

    // do-while loop is meant to visit all unconnected graphs that are left.
    // Calls nextUnvisitedNodes() in order to see if there are any more unvisited vertices.

    // Check the specification to figure out what member functions of the queue class you need to use.
    //  https://www.cplusplus.com/reference/queue/queue/

    // You could call show all paths by calling displayQueue()
    int *num = new int[num_ver];
    for (int v = 0; v < num_ver; ++v)
    {
        num[v] = 0;
    }
    queue<int> q;
    queue<string> edges;
    int i = 1; // first vertex gets 1
    do
    {
        num[start] = i++;
        q.push(start);
        // when queue isnt empty
        // print out contents
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
            // vertex goes in queue only once and then goes to next unvisited node
            for (list<edge *>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
            {
                if (num[(*u)->neighbor] == 0)
                {
                    num[(*u)->neighbor] = i++;
                    q.push((*u)->neighbor);
                    edges.push(to_string(v) + "->" + to_string((*u)->neighbor));
                }
            }
        }
        start = nextUnvisitedNodes(num, start, start + 1);
    } while (start != -1);
    displayQueue(edges);
    delete[] num;
    // Don't forget to destroy the dynamic array if you used one
}

// dijkstra's algorithm calculates the shortest distance from start to every other vertex
// This stand alone function shows the shortest path from start to destination in the following format.
//   The shortest path from 3 to 5 is 3 0 4 5
//   The distance is 8
void showShortestDistance(int *curDist, int *predecessor, int start)
{
    int dest; // destination
    cout << "Enter the destination: ";
    cin >> dest;

    // trace the shortest path from dest back to start
    // I suggest you use either library's stack or queue. Which one will work?
    stack<int> shortdist;
    int getdist = curDist[dest]; // gets distance from where were at to where we need to go

    cout << "The shortest path from " << start << " to " << dest << " is ";
 
    // as long the destination is not the beginning
    while (dest != start) 
    {
      shortdist.push(dest);
      //pushes to stack
      dest = predecessor[dest];
    }
    shortdist.push(start);

    // stack is not empty, pop
    while (!shortdist.empty()) 
    {
      cout << shortdist.top() << " ";
      shortdist.pop();
    }

    cout << "\nThe distance is " << getdist << endl;
}

// You don't need to change the following function.
// This function is for checking the heap and all the arrays. You may want to call it while you are developing Dijkstra's function
// This is not part of the graph class.  It is made for testing anyway.
void printHeapArrays(const minHeap<int> &h, int *curDist, int *locator, int *predecessor, int num_ver)
{
    cout << "heap ------" << endl;
    cout << h << endl; // This works if you made operator<<() to display a heap

    cout << "locator ------" << endl;
    for (int i = 0; i < num_ver; i++)
        cout << locator[i] << " ";
    cout << endl;

    cout << "curDist ------- " << endl;
    for (int i = 0; i < num_ver; i++)
        cout << curDist[i] << " ";
    cout << endl << endl;

    cout << "Predecessor ------- " << endl;
    for (int i = 0; i < num_ver; i++)
        cout << predecessor[i] << " ";
    cout << endl << endl;
}

// Dijkstra's shortest path. This function will generate a table that contains the shortest distance from start to every other vertex and the predecessor of each vertex.
void graph::DijkstraShortestPath(int start)
{
    minHeap<int> toBeChecked(num_ver); //the top of this heap has the vertex with the shortest distance
    // declare a dynamic array called curDist; contains the current shortest distance from start to every other vertex
    int *curDist = new int[num_ver];
    // declare a dynamic array called predecessor; contains the predecessor of each vertex
    int *predecessor = new int[num_ver];
    // declare a dynamic array called locator; tells where each vertex exists within the heap. e.g. heap [v3, v1, v2, v4, v0] locator [4, 1, 2, 0, 3] <== vertex 0 can be found at index 4 in heap, vertex 3 can be found at index 0 in heap
    int *locator = new int[num_ver]; 

    // The algorithm is in my lecture notes. Make sure you understand how each array and heap changes by reading my homework document posted on Canvas.
    // variable moves around graph holds minimum distance/ value
    int s = start;

    // initialize each array
    for (int i = 0; i < num_ver; i++) 
    {
      // curDist should be 999 for all vertices to start with
      curDist[i] = 999;
    }   
    
    for (int j = 0; j < num_ver; j++) 
    {
      // populate toBeChecked heap
      // inserts the number distances into the heap
      toBeChecked.insert(curDist, locator, j);
        
      // gets index
      locator[j] = j;
      predecessor[j] = -1;
    }

    curDist[start] = 0;
   
    while (toBeChecked.getNum() > 0) 
    {
      toBeChecked.fixHeap(curDist, locator, locator[s]);
      s = toBeChecked.getMin(curDist, locator);

      // vertex goes in queue only once and then goes to next unvisited node
      for (list<edge *>::iterator u = ver_ar[s].begin(); u != ver_ar[s].end(); u++)
      {
        // insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...] the numbers are vertex numbers
        // to start with, locator [0, 1, 2, 3, 4, ...]
        // Initialize predecessor for each vertex to -1                 
        if (locator[(*u)-> neighbor] < toBeChecked.getNum()) 
        {
          if (curDist[(*u)-> neighbor] > ((*u)-> wt + curDist[s])) 
          {
            curDist[(*u)-> neighbor] = ((*u)-> wt + curDist[s]);
            predecessor[(*u)-> neighbor] = s;
            toBeChecked.fixHeap(curDist, locator, (*u)-> neighbor);
          }
        }
      } 
    }
    // A lof of code here - check the algorithm in my lecture notes

    // Now currDist and predecessor have the info about the shortest distance from start to every other vertex and the predecessor of each vertex
    showShortestDistance(curDist, predecessor, start); // print the result
    
    // deletes dynamic arrays
    delete [] curDist;
    delete [] predecessor;
    delete [] locator;
}

#endif
