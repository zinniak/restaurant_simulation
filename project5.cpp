//Programmer: Zinnia Khan
//Date: December 4, 2019
//Purpose: Project 5 - Creating a Restaurant simulation

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "RestaurantClass.h"


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
  cout << "This is a restuarant simulation program. Please input a file with " \
       "one parameter value on each line in the following order: " << endl;
  cout << "Percentage of people that do not want to wait in a long line." \
       << endl;
  cout << "The number of people in a line for the line to be considered long." \
       << endl;
  cout << "The mean server wait time." << endl;
  cout << "The standard deviation of the server wait time." << endl;
  cout << "The restaurant close time" << endl;
  cout << "The maximum time between customer arrivals." << endl;
  cout << "The minimum time between customer arrivals." << endl;
  cout << "The seed value." << endl;
  cout << "Insert file name: " << endl;
  //testing if paramteer input file is valid
  string fileName;
  cin >> fileName;
  ifstream inFileName;
  inFileName.open(fileName.c_str());
  //if fails to open parameter file, print out information
  if (inFileName.fail())
  {
    cout << "Error: Invalid input parameter file!" << endl;
    cout << "Exiting the program." << endl;
  }
  else
  {
    //read parameters into restaurant class
    cout << "Setting Restaurant simulation parameters..." << endl;
    cout << "\n" << endl;
    //initialize our restaurant
    RestaurantClass myRest;
    myRest.setRestaurantInfo(inFileName);
    myRest.printRestaurantInfo();
    cout << "**** BEGINNING RESTAURANT SIMULATION ****" << endl;
    do
    {
      myRest.setNextEvent();
    } while (myRest.getEventListNum() != 0);
    myRest.printRestaurantStats();
    cout << "**** END OF SIMULATION ****" << endl;
  }
};

#endif
