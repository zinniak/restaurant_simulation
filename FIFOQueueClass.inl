//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Project 5 - Class member function definitions of FIFOQueueClass

#include <iostream>
using namespace std;


template <class T>
FIFOQueueClass<T>::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

template <class T>
FIFOQueueClass<T>::~FIFOQueueClass()
{
  clear();
}

template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem)
{
  LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(tail, newItem, 0);
  newNode->setBeforeAndAfterPointers();
  tail = newNode;
  if (head == 0)
  {
    head = newNode;
  }
}

template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem)
{
  if (head == 0)
  {
    return false;
  }
  outItem = head->getValue();
  if (head->getNext())
  {
    head = head->getNext();
    delete head->getPrev();
    head->setPreviousPointerToNull();
  }
  else
  {
    delete head;
    head = 0;
    tail = 0;
  }
  return true;
}

template <class T>
void FIFOQueueClass<T>::print() const
{
  if (head != 0)
  {
    LinkedNodeClass<T> *temp = head;
    while (temp != tail)
    {
      cout << temp->getValue() << " ";
      temp = temp->getNext();
    }
    cout << temp->getValue() << endl;
    cout << '\n' << endl;
  }
  else
  {
    cout << "No contents in list" << endl;
  }
}

template <class T>
int FIFOQueueClass<T>::getNumElems() const
{
  int numElems = 0;
  LinkedNodeClass<T> *temp = head;
  if (head == 0)
  {
    return numElems;
  }
  else
   {
     numElems = 1;
     while (temp != tail)
     {
       temp = temp->getNext();
       numElems += 1;
     }
   }
   return numElems;
 }

template <class T>
void FIFOQueueClass<T>::clear()
{
  int listNum = getNumElems();
  T current;
  for (int i = 0; i < listNum; i++)
  {
    dequeue(current);
  }
  head = 0;
  tail = 0;
}
