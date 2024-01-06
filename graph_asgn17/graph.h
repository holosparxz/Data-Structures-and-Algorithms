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
using namespace std;

class edge
{   //make graph a friend of edge
    friend class graph;  //What do you need here if you want to access the private members of edge class from graph class
    int neighbor; //adjacent vertex
    int wt; //weight of edge
public:
    edge() { neighbor = -999, wt = -999; }; // -999/999 is used for infinity
    edge(int u, int w) { neighbor = u, wt = w; };
};

class graph
{
    int num_ver; //total number of vertices in graph
    list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. 
    //The element of a node in a linked list is a pointer to an edge object 
    //doubly linked list. 
    int nextUnvisitedNodes(int* num, int start, int s);
    void DFT_helper(int v, int& i, int* num, queue<string>& q);
public:
    graph(int V);
    ~graph();
    void addEdge(int v, int u, int w = 1);  //If the weight is not given, 1 is used for wt.
    void BFT(int start);
    void DFT(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
    //make a dynamic array with num slots where each slot holds a list object. 
    //The element of a node in the linked list is a pointer to an edge object 
    num_ver = num; 
    //initiliaze number of vertices
    ver_ar = new list<edge*>[num_ver];

}

graph::~graph()
{
    //destroys all the edge objects created in heap                                                     
    //For each vertex in ver_ar
    //It goes through each node inside linked list. 
    //Element field of each node points to an edge object created with "new". 
    //Which will need to be deleted.  
    //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
    //https://www.cplusplus.com/reference/list/list/~list/
    //destroy the ver_ar dynamic array

    for (int i = 0; i < num_ver; i++)
    {
        for (auto it = (ver_ar[i]).begin(); it != (ver_ar[i]).end(); it++)
        {
            delete *it;
        }
        (ver_ar[i]).clear();
    }

    delete [] ver_ar;

}

//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
    //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
    //https://www.cplusplus.com/reference/list/list/
    //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
    //I have one line of code in this function.
    edge* addedEdge = new edge(u, w);
    (ver_ar[v]).push_back(addedEdge); 
}

// Displays the values present in the queue                                
template<class T>
void displayQueue(queue<T>& q)
{
    // When the list isnt empty
    // print out contents of array and pop it
    while (!q.empty())
    {
        cout << q.front() << ",";
        q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
    //Num is a dynamic array needed for later use
    int* num = new int[num_ver];

    //for all vertices v num(v) = 0
    for (int v = 0; v < num_ver; ++v) {
       num[v] = 0;
    }
    //queue object of string data type from the library's queue class to save all the paths.
    //That are present
    queue<string> q;
    
    //calls nextUnvisitedNodes() to see if there are more unvisited nodes.
    int i = 1;
    do {
        // DFT is called from the current vertex
        DFT_helper(start, i, num, q);
        // Check if there are more unvisited nodes
        start = nextUnvisitedNodes(num, start, start + 1);
    } while (start != -1);

    //You could call displayQueue() implemented above to display all the paths. 
    displayQueue(q);
    //Don't forget to destroy the dynamic array
    delete[] num;

}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertext right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
    //function iterates through the num array from s in order to see 
    //if you find a vertex with num = 0. If so, return the index. 
    //Otherwise, If all vertices are visited, return -1.
    //Iterates through the num array from s to find the next unvisited vertex
    
    for (int i = s; i < num_ver; ++i) {
        if (num[i] == 0) {
            //Found an unvisited vertex, return the index
            return i;
        }
    } 
    //Otherwise, All vertices have been visited
    return -1;
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
    num[v] = i++;
    cout << v << " ";

    //The following shows how to iterate the library's linked list. You use an iterator.
    //https://www.cplusplus.com/reference/list/list/end/ 
    //iterator class is nested inside list class
    for (list< edge* >::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
        //From the example on https://www.cplusplus.com/reference/list/list/end/
        //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
        //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  

        //push each path e.g. 0->1 into q. to_string(int) converts int to string. 
        //to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp 

        if (num[(*u)->neighbor] == 0) {
            DFT_helper((*u)->neighbor, i, num, q);
            q.push(to_string(v) + "->" + to_string((*u)->neighbor));
        }
    }
    
    /***********************************************************************************************
     **********************************************************************************************
      Compile with a c++11 option if you are using to_string()
          g++ -std=c++11 graphClient.cpp
     **********************************************************************************************
     ***********************************************************************************************/
}

//start is the index for the start vertex
void graph::BFT(int start)
{
    //Use the queue class from the c++ library 

    //do-while loop is meant to visit all unconnected graphs that are left. 
    //Calls nextUnvisitedNodes() in order to see if there are any more unvisited vertices.

    //Check the specification to figure out what member functions of the queue class you need to use.
    // https://www.cplusplus.com/reference/queue/queue/

    //You could call show all paths by calling displayQueue()
    int* num = new int[num_ver];
    for (int v = 0; v < num_ver; ++v) {
        num[v] = 0;
    }
    queue<int> q;
    queue<string> edges;
    int i = 1; // first vertex gets 1
    do
    {
        num[start] = i++;
        q.push(start);
        //when queue isnt empty
        //print out contents
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
            //vertex goes in queue only once and then goes to next unvisited node
            for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
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
    //Don't forget to destroy the dynamic array if you used one
}

#endif
