//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Project 5 - Class member function definitions of RestaurantClass

using namespace std;

#include "RestaurantClass.h"


RestaurantClass::RestaurantClass()
{
  serverBusy = false;
  impatientCust = PROB_IMPATIENT_CUST;
  longLine = LONG_LINE;
  mean = DISTR_MEAN;
  sd = DISTR_STD;
  closeTime = CLOSE_TIME;
  maxInterval = MAX_INTERV;
  minInterval = MIN_INTERV;
  seed = SEED;
  //statistics
  numCust = 0;
  serverBusyTime = 0;
  custWaitNum = 0;
  custLeft = 0;
  longestLine = 0;
  custArrvGapTime = 0;
  longestArrvTime = 0;
  totalCustArrvEvents = 0;
  lastCustTime = 0;
}


void RestaurantClass::setRestaurantInfo(ifstream &inFile)
{
  inFile >> impatientCust;
  inFile >> longLine;
  inFile >> mean;
  inFile >> sd;
  inFile >> closeTime;
  inFile >> maxInterval;
  inFile >> minInterval;
  inFile >> seed;
  setSeed(seed);
}


void RestaurantClass::printRestaurantInfo()
{
  cout << "PRINITNG RESTAURANT INFORMATION" << endl;
  cout << "Restaurant Closing Time: " << closeTime << endl;
  cout << "Percentage of Impatient Customers: " << impatientCust << endl;
  cout << "Customers in Long Line: " << longLine << endl;
  cout << "Seed Value: " << seed << endl;
  cout << "Mean Server Wait Time: " << mean << endl;
  cout << "Standard Deviation of Server Wait Time: " << sd << endl;
  cout << "Max Time Between Customer Arrivals: " << maxInterval << endl;
  cout << "Min Time Between Customer Arrivals: " << minInterval << endl;
  cout << "\n" << endl;
}


void RestaurantClass::setNextEvent()
{
  //setting first event as customer arrival at time 0
  if (getEventListNum() == 0)
  {
    EventClass event(CUST_ARRV, START_TIME);
    eventList.insertValue(event);
    totalCustArrvEvents = totalCustArrvEvents + 1;
  }
  else
  {
    EventClass event;
    eventList.removeFront(event);
    if (event.getEventType() == CUST_ARRV)
    {
      totalCustArrvEvents = totalCustArrvEvents + 1;
      cout << "Event: A customer has arrived at the restaurant!" << endl;
      if (event.getEventTime() > closeTime)
      {
        cout << "    The restaurant has closed. Cannot serve this customer." \
        << endl;
      }
      else
      {
        //schedule next customer arrival event
        int nextArrvTime = getUniform(minInterval, maxInterval);
        EventClass nextEvent(CUST_ARRV, event.getEventTime() + nextArrvTime);
        eventList.insertValue(nextEvent);
        custArrvGapTime = custArrvGapTime + (nextArrvTime);
        if (nextArrvTime > longestArrvTime)
        {
          longestArrvTime = nextArrvTime;
        }
      }

      //if server is not busy, serve next customer
      if (serverBusy == false)
      {
        EventClass nextEvent(START_SERV, event.getEventTime());
        eventList.insertValue(nextEvent);
      }
      //if server is busy, customer stands in line if not closing time
      else
      {
        if (event.getEventTime() < closeTime)
        {
          cout << "    The server is occupied with another customer." << endl;
          //determining if the next customer is an impatient customer
          if (getUniform(0, 100) < impatientCust)
          {
            cout << "    This customer is an impatient customer." << endl;
            // impatient customer gets in line if line is not "long"
            if (custLine.getNumElems() <= longLine)
            {
              EventClass nextEvent(CUST_ENQUEUE, event.getEventTime());
              eventList.insertValue(nextEvent);
            }
            //impatient customer leaves if line is "long"
            else
            {
              cout << "    The customer left due to a long line!" << endl;
              custLeft = custLeft + 1;
            }
          }
          //patient customer gets in line
          else
          {
            EventClass nextEvent(CUST_ENQUEUE, event.getEventTime());
            eventList.insertValue(nextEvent);
          }
        }
      }
    }

    if (event.getEventType() == START_SERV)
    {
      serverBusy = true;
      cout << "Event: The server is serving the next customer." << endl;
      int serveTime = getNormal(mean, sd);
      //determining how long it will take to serve the customer
      EventClass nextEvent(FIN_SERV, event.getEventTime() + serveTime);
      eventList.insertValue(nextEvent);
      serverBusyTime = serverBusyTime + serveTime;
    }

    if (event.getEventType() == FIN_SERV)
    {
      cout << "Event: The server has finished serving a customer." << endl;
      //server starts serving next customer if there is a line
      if (custLine.getNumElems() != 0)
      {
        EventClass nextEvent;
        custLine.dequeue(nextEvent);
        EventClass nextNextEvent(START_SERV, event.getEventTime());
        eventList.insertValue(nextNextEvent);
      }
      else
      {
        serverBusy = false;
      }
    }

    if (event.getEventType() == CUST_ENQUEUE)
    {
      custLine.enqueue(event);
      cout << "Event: The customer has gotten in line." << endl;
      custWaitNum = custWaitNum + 1;
    }

    // keeping track of the longest line
    if (custLine.getNumElems() > longestLine)
    {
      longestLine = custLine.getNumElems();
    }

    //printing info
    cout << "Current Time: " << event.getEventTime() << endl;
    cout << "Number of people currently waiting in line: " \
    << custLine.getNumElems() << endl;
    cout << "Number of events scheduled: " << getEventListNum() << endl;
    cout << "*********************************************************" << endl;
    lastCustTime = event.getEventTime();
  }
}


int RestaurantClass::getEventListNum()
{
  return eventList.getNumElems();
}


void RestaurantClass::printRestaurantStats()
{
  numCust = totalCustArrvEvents - custLeft; //no. of customers served
  double percTimeServerBusy = double(serverBusyTime) / double(closeTime) * 100;
  double percCustWait = double(custWaitNum) / double(numCust) * 100;
  double meanCustArrvGapTime = double(custArrvGapTime) \
                              / double(totalCustArrvEvents);
  cout << "PRINING RESTAURANT STATISTICS" << endl;
  cout << "Total number of customers that showed up: " << totalCustArrvEvents \
       << endl;
  cout << "Percentage of time the server was busy helping customers: " \
       << percTimeServerBusy << endl;
  cout << "Percentage of customers that had to wait in line: " << percCustWait \
       << endl;
  cout << "The number of customers that arrived, but left due to excessive" << \
       " line length: " << custLeft << endl;
  cout << "The longest the line was throughout the simulation: " \
       << longestLine << endl;
  cout << "The total number of customers that were served: " << numCust << endl;
  cout << "Average time between customer arrivals: " << meanCustArrvGapTime \
       << endl;
  cout << "The longest time interval between customer arrivals: " \
       << longestArrvTime << endl;
}
