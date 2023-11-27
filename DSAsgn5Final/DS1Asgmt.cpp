#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include "binaryHeap.h"
#include "stacktype.h"
#include "constants.h"
#include "AsgnHeaderFooter.h"

using namespace std;ṇ

int getDepartureTime(int timeIn);
void createGateNosStack(StackType<int> &aGateList, int noOfGates);
void printServicedFlightSchedules(vector<aEventRec> aSerFlightsSched, ostream &outStream);
void printDivertedFlightSchedules(vector<aEventRec> aDiverFlightsSched, ostream &outStream);
void printGateUsage(vector<int> gateNoDepsCount, ostream &outStream);
void printReportHeader(ostream &outStream);
void printReportFooter(ostream &outStream);

//****** BEGIN MAIN PROGRAM ****************
int main()
{
	string outFileName1; // declare string variables to hold file names
	string outFileName2; // declare string variables to hold file names
	string curOutputFile;
	ofstream outFileStream1; // an ifstream object to read input stream from files
	ofstream outFileStream2; // an ifstream object to read input stream from files
	outFileName1 = DATA_FILE_NAME1;
	outFileName2 = DATA_FILE_NAME2;
	outFileStream1.open(outFileName1.c_str()); // associates a file stream with the file to open
	outFileStream2.open(outFileName2.c_str());
	char ch;
	srand(time(0));
	int numberOfGates;				   // for holding the number of gates entered by user
	int countDelayedFlights = 0;	   // to count the number of flights delayed
	vector<aEventRec> servicedFlights; // a vector that has all arrivals and departures records
	vector<aEventRec> divertedFlights; // an vector that has all diverted flights records
	int availGateNo;				   // to hold the available gate no popped from gateNosStack
	int hour = 0;
	int noOfFltsPerHr = NO_OF_FLIGHTS;	  // IN_FLTS_HOURLY_SCHEDULE.size();// holds the number of flights per hour initially declared
	BinaryHeap<aEventRec> depFlightsHeap; // a heap of all flights that includes arrivals and departures plan record
	int flitNo = FLT_NUMBER_START;		  // holds the flight numbers allotted to each successive flight arrivals
	int countAirportFull = 0;			  // to count the number of times air port full situation occurred

	printReportHeader(cout);
	cout << "Enter the number of gates in Airport to be tested for :  ";
	cin >> numberOfGates;

	vector<int> gateNoDepsCount(numberOfGates + 1);	 // a vector that has all arrivals and departures records
	StackType<int> gateNosStack(numberOfGates);		 // declare a stack object for gateNos
	createGateNosStack(gateNosStack, numberOfGates); // create the gateNos stack

	// build the gateNos array
	for (int i = 0; i < (gateNoDepsCount.size()); i++)
	{
		gateNoDepsCount[i] = 0;
	}

	// build the arrival flight plan array for MAX_HOURS of the day
	for (hour = 0; hour < MAX_HOURS; hour++)
	{
		for (int i = 0; i < noOfFltsPerHr; i++)
		// for (int i = 0; i < IN_FLTS_HOURLY_SCHEDULE.size(); i++)
		{
			int currArrTime = IN_FLTS_HOURLY_SCHEDULE[i] + (hour * 60);
			aEventRec aNewFltRec;
			aNewFltRec.arrDepTime = currArrTime;   // assign current time as arrival time for the flght plan record
			aNewFltRec.arrDepCode = 'A';		   // assign arrival code for the time
			aNewFltRec.orig = ORIG[i];			   // assign originate location from the ORIG array
			aNewFltRec.dest = DESTN[i];			   // assign destination location from the DESTN array
			aNewFltRec.fltNo = flitNo;			   // assign a Flight number
			servicedFlights.push_back(aNewFltRec); // push the flight plan arrival record into vector
			flitNo++;
		}
	}

	// After the arrival flight plan array has been built, build the heap to work with
	BinaryHeap<aEventRec> flightsHeap1(servicedFlights);
	servicedFlights.clear();
	int currArrTime;
	double totalDelay = 0;
	double avgDelay;
	aEventRec aFltRec;
	while (flightsHeap1.getSize() > 0)
	{
		aFltRec = flightsHeap1.findMin(); // to get time of the root record(next for dep)
		flightsHeap1.deleteMin();		  // delete the root record from heap
		if (aFltRec.arrDepCode == 'D')	  // if it is a departure flight
		{
			gateNosStack.push(aFltRec.gateNo); // get the gate no of root record that is to be deleted and replenish the gateStack
			gateNosStack.invertStack();		   // invert stack to prevent last in first out

			//----
			int delayTime = (aFltRec.arrDepTime - currArrTime - 60); // calculate flight delay time
			if (delayTime > 0)
			{
				totalDelay = totalDelay + delayTime;
				countDelayedFlights++;
				stringstream delayTimeStr;
				delayTimeStr << delayTime;
				aFltRec.remark = "  Flight departure delayed by " + delayTimeStr.str() + " minutes";
			}
			else
			{
				aFltRec.remark = "  Filght departure on time.";
			}
            //-------------
			servicedFlights.push_back(aFltRec); // push the flight plan departure record with gateNo
		}
		else if (!gateNosStack.isEmptyStack()) // else it is a arrival flight that needs to be allotted a gateNo
		{
			currArrTime = aFltRec.arrDepTime;
			availGateNo = gateNosStack.pop(); // pop a gateNo from gateNostack
			aFltRec.gateNo = availGateNo;	  // allot a gateNo to a flight plan
			(gateNoDepsCount[availGateNo])++; // increase allottment count for that paticular gateNo
			// servicedFlights.push_back(aFltRec); // push the flight plan arrival record with gateNo

			aFltRec.arrDepTime = getDepartureTime(aFltRec.arrDepTime); // allocate a departure time when arrival allowed and a gate No alloted
			aFltRec.arrDepCode = 'D';					// assign departure code for the time			
			flightsHeap1.insert(aFltRec); // insert the flight departure plan into depFlightsHeap
		}
		else // it was a arrival flight for which gateNo was not available
		{
			aFltRec.gateNo = 0;
			aFltRec.remark = "  Airport Full ! - Filght was diverted to another Airport.";
			divertedFlights.push_back(aFltRec); // push the flight plan of a diverted flight
			countAirportFull++;
		}
	}

	if (countDelayedFlights != 0)
	{
		avgDelay = totalDelay / countDelayedFlights;
		avgDelay = round(avgDelay * 100) / 100;
	}

	if (countAirportFull > 0)
	{
		printReportHeader(outFileStream2);
		printDivertedFlightSchedules(divertedFlights, outFileStream2);
		printDivertedFlightSchedules(divertedFlights, cout);

		outFileStream2 << "\nNumber of Gates in the Airport : " << numberOfGates << endl;
		outFileStream2 << "Number of times Airport was full and consequently total number of flights that got diverted : " << countAirportFull << endl;
		outFileStream2 << "\n       " << numberOfGates << " gates not adequate for the number of Aircrafts arriving into the airprort !" << endl;
		// outFileStream2 << "\nPROGRAM EXECUTION ABORTED !!  " << endl;

		cout << "\nNumber of Gates in the Airport : " << numberOfGates << endl;
		cout << "Number of times Airport was full and consequently total number of flights that got diverted : " << countAirportFull << endl;
		cout << "\n       " << numberOfGates << " gates not adequate for the number of Aircrafts arriving into the airprort !" << endl;
		// cout << "\nPROGRAM EXECUTION ABORTED !!  " << endl;
		curOutputFile = outFileName2;
		printReportFooter(outFileStream2);
		outFileStream2.close();
	}
	// else
	//{
	printReportHeader(outFileStream1);
	printServicedFlightSchedules(servicedFlights, outFileStream1);
	printServicedFlightSchedules(servicedFlights, cout);

	outFileStream1 << "\nNumber of Gates in the Airport : " << numberOfGates << endl;
	printGateUsage(gateNoDepsCount, outFileStream1);
	outFileStream1 << "\nNumber of flights that had delayed departure : " << countDelayedFlights << endl;
	outFileStream1 << "Average delay time for Departure flights : " << avgDelay << " minutes " << endl;

	cout << "\nNumber of Gates in the Airport : " << numberOfGates << endl;
	printGateUsage(gateNoDepsCount, cout);
	cout << "\nNumber of flights that had delayed departure : " << countDelayedFlights << endl;
	cout << "Average delay time for Departure flights : " << avgDelay << " minutes " << endl;
	curOutputFile = outFileName1;
	printReportFooter(outFileStream1);
	//	}
	outFileStream1.close();
	cout << "\nThe above information can also be found saved in file : '" << curOutputFile << "' " << endl;
	cout << "\nand in file : '" << outFileName2 << "' " << endl;
	printReportFooter(cout);
	// cin >> ch;
	return 0;
}
//****** END MAIN PROGRAM ****************

// An arrival time is passed to the function that returns an arbitarily delayed departure time
int getDepartureTime(int timeIn)
{
	int maxNo = MAX_NO;
	int minDelay = MIN_DELAY_INTR, addlDelay = MAX_ADDL_DELAY_INTR;
	int departureTime = 60 + timeIn;
	int delayTime = 0;
	int i;
	i = (1 + rand() % maxNo);
	if (i <= 40)
	{
		delayTime = (minDelay + rand() % addlDelay);
	}
	return (departureTime + delayTime);
}

// Number of gates entyered by user is used to create the stack of gate numbers
void createGateNosStack(StackType<int> &aGateList, int noOfGates)
{
	for (int i = 1; i <= noOfGates; i++)
	{
		aGateList.push(i);
	}
}

void printServicedFlightSchedules(vector<aEventRec> aSerFlightsSched, ostream &outStream)
{
	BinaryHeap<aEventRec> allDayHeap(aSerFlightsSched);
	int count = allDayHeap.getSize();
	while (allDayHeap.getSize() > 0)
	{
		aEventRec aFltRec;
		aFltRec = allDayHeap.findMin();
		string arrDepStr = " arrived at gate number ";
		if (aFltRec.arrDepCode == 'D') // if it is a departure flight
		{
			arrDepStr = "  departed from gate number ";
		}
		outStream << "\n Flight Number: " << aFltRec.fltNo
				  << " From : " << aFltRec.orig << endl
				  << "                      "
				  << " To : " << aFltRec.dest
				  << arrDepStr << aFltRec.gateNo
				  << " at time: " << aFltRec.arrDepTime << " minute of the day " << endl
				  << "                               " << aFltRec.remark << endl;
		allDayHeap.deleteMin();
		count ++;
	}
	outStream << "\nTotal number of Aircrafts serviced at the airport : " << count;
}

void printDivertedFlightSchedules(vector<aEventRec> aDiverFlightsSched, ostream &outStream)
{
	for (int i = 0; i < aDiverFlightsSched.size(); i++)
	{
		aEventRec aFltRec;
		aFltRec = aDiverFlightsSched[i];

		outStream << "\n Airport full at time : " << aFltRec.arrDepTime << endl;
		outStream << " Flight Number : " << aFltRec.fltNo
				  << " From : " << aFltRec.orig << endl
				  << "                       "
				  << " To : " << aFltRec.dest
				  << " that was to arrive at : " << aFltRec.arrDepTime << " minute of the day " << endl
				  << "                               "
				  << " was diverted to another airport ! " << endl;
	}
	cout << "\nTotal number of flights diverted to other airports : " << aDiverFlightsSched.size();
}

void printGateUsage(vector<int> gateNoDepsCount, ostream &outStream)
{
	outStream << "\nGate wise allottment/utilisation details" << endl;

	for (int i = 1; i < (gateNoDepsCount.size()); i++)
	{
		outStream << "Gate No : " << i << " was alloted/utilised : " << gateNoDepsCount[i] << " number of times " << endl;
	}
}
