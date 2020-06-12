//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Project 5 - Class definition of RestaurantClass

#include <iostream>
#include <fstream>
using namespace std;

#ifndef _RESTAURANTCLASS_H_
#define _RESTAURANTCLASS_H_
#include "constants.h"
#include "EventClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "random.h"

//the class RestaurantClass creates an object representing a restaurant
//simulation for a single day
class RestaurantClass
{
  private:
    //list to store events
    SortedListClass<EventClass> eventList;
    //list to represents customer queue
    FIFOQueueClass<EventClass> custLine;
    //probability that the customer is an impatient customer
    int impatientCust;
    //the number of people in a line for the line to be considered a "long line"
    int longLine;
    //the mean of the normal distribution
    double mean;
    //the standard deviation of the normal distribution
    double sd;
    //the time the restaurant closes
    int closeTime;
    //the max time to generate the next event
    int maxInterval;
    //the min time to generate the next event
    int minInterval;
    //the seed to generate a random number
    int seed;
    //no. of customers that leave due to long line
    int custLeft;
    //no. of customers served
    int numCust;
    //to determine if server is busy, returns true if server is busy
    bool serverBusy;
    //the total time the server was busy serving customers
    int serverBusyTime;
    //the number of customers that wait in lin
    int custWaitNum;
    //the longest the line was able to get
    int longestLine;
    //the total amount of time between customer arrivals
    int custArrvGapTime;
    //the longest time interval between customer arrivals
    int longestArrvTime;
    //total number of customer arrival events
    int totalCustArrvEvents;
    //the time the last customer arrived at
    int lastCustTime;

  public:
    RestaurantClass();
    //read restaurant parameters from inFile
    void setRestaurantInfo(ifstream& inFile);
    //print restaurant parameters information
    void printRestaurantInfo();
    //set the events in events list
    void setNextEvent();
    //get the number of events
    int getEventListNum();
    //print restaurant statistics for the day
    void printRestaurantStats();
};


#endif
