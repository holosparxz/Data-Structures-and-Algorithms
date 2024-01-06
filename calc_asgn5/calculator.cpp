// Matt Acosta
// CS 311 - Kazumi Slott

// includes necessary libraries for code to run properly
#include <string>
#include <iostream>
#include "stack_L_T.h"

using namespace std;

// defines functions for later use
int chartoInt (char c);
int operatorPriority(char c);
bool isOperator(char c);
bool isOperand(char c); 
string infixToPostfix(string s);
double evaluatePostfix(const string str);
double doMath(double a, double b, char c);
 
// checks operator to return and get precedence of a given operator by end user
int operatorPriority(char c) 
{
  // priority order of operators:
  // 1. / or *
  // 2. + or -
  // greater value = higher precedence so *,/ is always greater than +,-
  // if either +,-,*, or / are typed in return priority
  if (c == '+' || c == '-')
  {
    return 1;
  }
  if (c == '*' || c == '/') 
  {
    return 2;
  }
  // Otherwise, return 0
  return 0;
}

// isOperator() validates if a symbol is considered an operator
bool isOperator(char c)
{
  // checks if the user inputs a valid operator
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') 
  {
    // return true if so
    return true;
  }
  // otherwise false
  return false;
}

// isOperand() validates if a character is a proper operand
bool isOperand(char c)
{
  // defines numbers, if not return false
  if (c >= '0' && c <= '9')
  {
    return true;
  }
  // when user doesn't enter a valid operand, return false
  return false;
}

// converts infix notation to postfix notation
string infixToPostfix(string s) 
{
  // creates stack from stack.h
  // checks if it is either an operator or operand
  Stack <char> post;
  string postfix;
  for (int i = 0; i < s.length(); i++) 
  {
    // if it is an operand add it to postfix
    if (isOperand(s[i])) 
    {
      postfix += s[i];
    }
    // if operator check if the post is higher than priority funct
    else if (isOperator(s[i])) 
    {
      while (!post.empty() && isOperator(post.getTop()) && operatorPriority(post.getTop()) >= operatorPriority(s[i])) {
        // top is higher than priority, then just add it 
        postfix += post.getTop();
        post.pop();
      }
      // push it to the post 
      post.push(s[i]);
    }
    // if open parentheisis is present, push it
    else if (s[i] == '(')
    {
      post.push(s[i]);
    }
    // if closed parentheisis is present pop it to stack
    else if (s[i] == ')')
    {
      // when it's not an open parenthesis
      // add it get the top of the postfix and pop it
      while (post.getTop() != '(')
      {
        postfix += post.getTop();
        post.pop();
      }
      post.pop();
    }
    // otherwise throw an exception
    else 
    {
      throw "The expression is in the wrong format]\n";
    }
  }
  // when the post isnt empty get the top and pop it
  while (!post.empty()) 
  {
    postfix += post.getTop();
    post.pop();
  }
  // return converted value
  return postfix;
}

// mundande code ignore

int charToInt(char c) 
{
  return c - 48;
}

double doMath(double a, double b, char c)
{
  switch(c)
  {
    case '+':
      return (a + b);
    case '-':
      return (a - b);
    case '*':
      return (a * b);
    case '/':
      return(a / b);
  } 
}


// evaluates the converted postfix notation
double evaluatePostfix(const string str)
{
  // code doesnt work ignore
  // was done with tuan @ stem center but doesnt work lol
  /* 
  Stack <double> post;
  double a, b;
  
  for (int i = 0; i < str.length(); i++) 
  {
    if (isOperand(str[i])) 
    {
      post.push(charToInt(str[i]));
    }
    else if (isOperator(str[i])) 
    {
      if (!post.empty()) 
      {
        a = post.getTop();
        post.pop(); 
        if (!post.empty())
        {
          b = post.getTop();
          post.pop();
          double x = doMath(a, b, str[i]);
          post.push(x);
        }
        else 
        {
          throw "The expression is in a wrong format\n";
        }
      }
      else 
      {
        throw "The expression is in a wrong format\n";
      }
    }
    else 
    {
      throw "The expression is in a wrong format\n";
    }
    double answer;
    if (!post.empty()) 
    {
      answer = post.getTop();
      post.pop();
      if (!post.empty())
      {
        throw "The expression is in a wrong format\n";
      }
      else 
      {
        return answer;
      }
    }
  */
  
  // creates variables for later use
  Stack <double> post;
  double a, b;
	
  for (int i = 0; i < str.size(); i++)
  {
    // if operand go through function
    if (isOperand(str[i]))
    {
      int charToInt = str[i] - '0';
      double IntToDouble = static_cast<double>(charToInt);
      post.push(IntToDouble);
    }
    // when it is an operator, pop it and do math
    if (isOperator(str[i]))
    {
      // gets the top and pops it for math variables
      a = post.getTop();
      post.pop();
      b = post.getTop();
      post.pop();
      // statement does mathematical calculations
      switch (str[i])
      {
        case '+': post.push(b + a);
	  break;
	case '-': post.push(b - a);
	  break;
	case '*': post.push(b * a);
	  break;
	case '/': post.push(b / a);
	  break;
      }
    }
  }
  // return math calculations 
  return post.getTop();   
}

// driver code
int main()
{
  // Handles error exceptions 
  try 
  {
  cout << infixToPostfix("(55+3)/4") << endl;
  cout << evaluatePostfix(infixToPostfix("(55+3)/4"));
  }
  catch (Stack<char>::Underflow) 
  {
    cout << "The expression is in the wrong format" << endl;
  }
  catch (Stack<double>::Underflow) 
  {
    cout << "The expression is in the wrong format" << endl;
  }
  catch (const char* msg)
  {
    cout << msg; 
  }
}
