//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Class member function definitions of EventClass

#include "EventClass.h"


EventClass::EventClass()
{
}

EventClass::EventClass(int inEventType, int inEventTime)
{
  eventTime = inEventTime;
  eventType = inEventType;
}

int EventClass::getEventTime() const
{
  return eventTime;
}

int EventClass::getEventType() const
{
  return eventType;
}

//to sort events
EventClass& EventClass::operator=(const EventClass& event)
{
  eventTime = event.eventTime;
  eventType = event.eventType;
  return *this;
}

bool EventClass::operator<(const EventClass& event) const
{
  if (eventTime < event.eventTime)
  {
    return true;
  }
  return false;
}

bool EventClass::operator>(const EventClass& event) const
{
  if (eventTime > event.eventTime)
  {
    return true;
  }
  return false;
}

bool EventClass::operator>=(const EventClass& event) const
{
  if (eventTime >= event.eventTime)
  {
    return true;
  }
  return false;
}

//print the type and time of an event
ostream& operator<<(ostream &os, const EventClass& event)
{
  int type = event.getEventType();
  os << type << " at time" << event.getEventTime() << endl;
  return os;
}

EventClass::~EventClass()
{
}
