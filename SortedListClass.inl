//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Project 5 - Class member function definitions of SortedListClass


template <class T>
SortedListClass<T>::SortedListClass()
{
  //initialize to empty list, which is defined by null head and tail
  head = 0;
  tail = 0;
}

template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs)
{
  //make this list empty if rhs is also empty
  if (rhs.head == 0)
  {
    head = 0;
    tail = 0;
  }
  else
  {
    //oldIter helps to iterate through the nodes in the list being copied.
    LinkedNodeClass<T> *oldIter = rhs.head;
    //newIter helps to iterate through the new list being created
    LinkedNodeClass<T> *newIter = new LinkedNodeClass<T>( 0, \
                                      oldIter->getValue(), 0);
    head = newIter;
    while (oldIter->getNext() != 0)
    {
     //oldIter goes to the next node in reference list
     oldIter = oldIter->getNext();
     //points to next node in new list
     LinkedNodeClass<T> *newIterNext = new LinkedNodeClass<T>(newIter, \
                                           oldIter->getValue(), 0);
     newIterNext->setBeforeAndAfterPointers();
     newIter = newIterNext;
    }
    tail = newIter;
  }
}

template <class T>
SortedListClass<T>::~SortedListClass()
{
  clear();
}

template <class T>
void SortedListClass<T>::clear()
{
  int listNum = getNumElems();
  T current;
  for (int i = 0; i < listNum; i++)
  {
    removeFront(current);
  }
  head = 0;
  tail = 0;
}

template <class T>
void SortedListClass<T>::insertValue(const T &valToInsert)
{
  LinkedNodeClass<T> *temp = head;
  LinkedNodeClass<T> *newNode;
  if (head == 0)
  {
    newNode = new LinkedNodeClass<T>(0, valToInsert, 0);
    head = newNode;
    tail = newNode;
    return;
  }
  //move temp pointer to next node if value being inserted is larger than the
  //node temp is pointing to
  while ((temp != tail) && (valToInsert >= temp->getValue()))
  {
    temp = temp->getNext();
  }
  //insert the value and set it to head if it is smaller than the first node
  if ((temp == head) && (valToInsert < temp->getValue()))
  {
    newNode = new LinkedNodeClass<T>(0, valToInsert, head);
    head = newNode;
  }
  //insert the value and set it to tail if it is larger than the last node
  else if ((temp == tail) && (valToInsert >= temp->getValue()))
  {
    newNode = new LinkedNodeClass<T>(tail, valToInsert, 0);
    tail = newNode;
  }
  else
  {
    newNode = new LinkedNodeClass<T>(temp->getPrev(), valToInsert, temp);
  }
  newNode->setBeforeAndAfterPointers();
}

template <class T>
void SortedListClass<T>::printForward() const
{
  if (head != 0)
  {
    cout << "Forward List Contents Follow:" << endl;
    LinkedNodeClass<T> *temp = head;
    while (temp != tail)
    {
      cout << "  " << temp->getValue() << endl;
      temp = temp->getNext();
    }
    cout << "  " << temp->getValue() << endl;
    cout << "End Of List Contents" << endl;
  }
  else
  {
    cout << "No contents in list" << endl;
  }
}

template <class T>
void SortedListClass<T>::printBackward() const
{
  if (tail != 0)
  {
    cout << "Backward List Contents Follow:" << endl;
    LinkedNodeClass<T> *temp = tail;
    while (temp != head)
    {
      cout << "  " << temp->getValue() << endl;
      temp = temp->getPrev();
    }
    cout << "  " << temp->getValue() << endl;
    cout << "End Of List Contents" << endl;
  }
  else
  {
    cout << "No contents in list" << endl;
  }
}

template <class T>
bool SortedListClass<T>::removeFront(T &theVal)
{
  if (head == 0)
  {
    return false;
  }
  theVal = head->getValue();
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
  }
  return true;
}

template <class T>
bool SortedListClass<T>::removeLast(T &theVal)
{
  if (tail == 0)
  {
    return false;
  }
  theVal = tail->getValue();
  if (tail->getPrev())
  {
    tail = tail->getPrev();
    delete tail->getNext();
    tail->setNextPointerToNull();
  }
  else
  {
    delete tail;
    tail = 0;
  }
  return true;
}

template <class T>
int SortedListClass<T>::getNumElems() const
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
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const
{
  LinkedNodeClass<T> *temp = head;
  if (head == 0)
  {
    return false;
  }
  for (int i = 0; i < index; i ++)
  {
    if ((temp->getNext()) == 0)
    {
      return false;
    }
    temp = temp->getNext();
  }
  outVal = temp->getValue();
  return true;
}
