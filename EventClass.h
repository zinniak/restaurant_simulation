//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Project 5 - Class definition of EventClass

#include <iostream>
using namespace std;

#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_
#include "constants.h"


//the class EventClass describes an event using the time the event occurs and
//the type of the event
class EventClass
{
  private:
    int eventTime;
    int eventType;
  public:
    //constructors
    EventClass();
    EventClass(int inEventType, int inEventTime);
    //getter functions
    int getEventTime() const; //return event start time
    int getEventType() const; //return event event
    //overloading operators
    EventClass& operator=(const EventClass& event);
    bool operator<(const EventClass& event) const;
    bool operator>(const EventClass& event) const;
    bool operator>=(const EventClass& event) const;
    ~EventClass();
};
//operator overloading
ostream& operator<<(ostream &os, const EventClass& event);


#endif
