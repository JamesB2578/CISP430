#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Node {
  string name;
  Node *prev;
  Node *next;
};

struct List {
  Node *head;
  Node *tail;
};

void insertNode(Node *&head, Node *&tail, string inputName) 
{
  Node *curNode = new Node;
 
  if (!head)
  {
    curNode->next = nullptr;
    curNode->name = inputName;
    curNode->prev = nullptr;
    head = curNode;
    tail = curNode;
  } 
  else if(inputName < head->name) 
  {
    curNode->name = inputName;
    curNode->next = head;
    head->prev = curNode;
    curNode->prev = nullptr;
    head = curNode;
  }
  else if(inputName > tail->name)
  {
    curNode->name = inputName;
    curNode->prev = tail;
    curNode->next = nullptr;
    tail->next = curNode;
    tail = curNode;
  }
  else
  {
    curNode = head;
    Node *inNode = new Node;
    Node *prevNode = new Node;
    inNode->name = inputName;
    while(inputName > curNode->name)
    {
      curNode = curNode -> next;
    }
    prevNode = curNode->prev;
    inNode->next = curNode;
    inNode->prev = prevNode;
    prevNode->next = inNode;
    curNode->prev = inNode;
  }
}

void deleteNode(Node *&head, Node *&tail, string inputName) 
{
  Node *curNode = new Node;
  curNode = head;

  while (curNode) 
  {
    if (curNode->name == inputName) 
    {
      if (curNode->prev) 
      {
        curNode->prev->next = curNode->next;
      } 
      else 
      {
        head->prev = nullptr;
      }
      if (curNode->next) 
      {
        curNode->next->prev = curNode->prev;
      } 
      else 
      {
        tail = curNode->prev;
      }
      delete curNode;
    }
    curNode = curNode->next;
  }
}

void printcontents(Node *&head, Node *&tail, ofstream &out) {
  Node *curNode = new Node;
  curNode = head;

  while (curNode) 
  {
    out << curNode->name << endl;
    curNode = curNode->next;
  }
  out << "=========" << endl;
  curNode = tail;
  while (curNode) 
  {
    out << curNode->name << endl;
    curNode = curNode->prev;
  }

  out << endl;
}

int main() 
{
  Node *head = nullptr;
  Node *tail = nullptr;
  ifstream in("input.txt");
  ofstream out("output.txt");
  string firstName;

  while (in >> firstName)
  {
    deleteNode(head, tail, firstName);
    insertNode(head, tail, firstName);
  }  
  in.close();  
  printcontents(head, tail, out);

  return 0;
}