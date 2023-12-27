//Assignment # 5
//Student Name : Varadharaja Perumal
//Student Id   : 1008475675
//Due : Tuesday, March 15, 2016

#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <cstdlib>
#include<ctime>
#include<string>
#include <sstream>
#include <vector>

using namespace std;

struct aEventRec
{	
	int fltNo;
	char arrDepCode;
	int arrDepTime;
	int gateNo;
	string orig;
	string dest;
	string remark;
	bool operator < (const aEventRec other) const
	{
		return (arrDepTime < other.arrDepTime);
	}
};

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename aEventRec>
class BinaryHeap
{
public:
	//Default constructor - with an optional capacity (that defaults to 100)
	explicit BinaryHeap(int capacity = 100)
		: array(capacity + 1), currentSize(0)
	{
	}
	//Parameter constructor - vector<Comparable> & items passed as parameter
	explicit BinaryHeap(const vector<aEventRec> & items)
		: array(items.size() + 10), currentSize(items.size())
	{
		for (int i = 0; i < items.size(); i++)
		{
			array[i + 1] = items[i]; // vector items copied into array
		}
		buildHeap(); //array elements are ordered in a heap structure
	}

	bool isEmpty() const
	{
		return currentSize == 0;
	}

	int getSize() const
	{
		return currentSize;
	}

	/**
	* Find the smallest item in the priority queue.
	* Return the smallest item, or throw Underflow if empty.
	*/
	const aEventRec & findMin() const
	{
		if (isEmpty())
		{
			throw UnderflowException();
		}
		return array[1];
	}

	/**
	* Insert item x, allowing duplicates.
	*/
	// Percolate up - hole /= 2 moves the hole up to its parent
	void insert(const aEventRec & x)
	{
		if (currentSize == array.size() - 1)
		{
			array.resize(array.size() * 2);
		}
		// Percolate up - hole /= 2 moves the hole up to its parent
		int hole = ++currentSize;
		for (; hole > 1 && x < array[hole / 2]; hole /= 2) // hole /= 2 means next iteration hole has moved up
		{                                                // i.e. hole percolates up wards
			array[hole] = array[hole / 2]; // element at hole/2 moved down
										   // to the hole posn if x < array[ hole / 2 ]
		}
		array[hole] = x; // when x value NOT < than hole/2 then x placed at hole posn
	}
	/**
	* Remove the minimum item.
	* Throws UnderflowException if empty.
	*/
	void deleteMin()
	{
		if (isEmpty())
		{
			throw UnderflowException();
		}
		array[1] = array[currentSize--];// last item placed at root and percolated down
		percolateDown(1);//to its appropriate place starting from root posn
	}

	/**
	* Remove the minimum item and place it in minItem variable.
	* Throws UnderflowException if empty.
	*/
	void deleteMin(aEventRec & minItem)
	{
		if (isEmpty())
		{
			throw UnderflowException();
		}

		minItem = array[1];// minimum item(root) stored in minItem variable
		array[1] = array[currentSize--];// last item placed at root and percolated down
		percolateDown(1); //to its appropriate place starting from root posn
	}

	void makeEmpty()
	{
		currentSize = 0;
	}

private:
	int   currentSize;  // Number of elements in heap
	vector<aEventRec> array;  // The heap array

							  /**
							  * Establish heap order property from an arbitrary
							  * arrangement of items. Runs in linear time.
							  */
	void buildHeap()
	{
		for (int i = currentSize / 2; i > 0; i--)
		{
			percolateDown(i); //percolated down to its appropriate place
							  // starting from posn(i) = currentSize / 2 = hole
		}
	}

	/**
	* Internal method to percolate down in the heap.
	* hole is the index at which the percolate begins.
	* posn(i) = (currentSize / 2) = hole
	*/
	// is called either by buildHeap() or deleteMin() Note : insert(item) does not call this function
	// buildHeap starts from parent = hole = posn(i) = (currentSize / 2)
	// deleteMin() starts from parent = hole = 1
	void percolateDown(int hole)   // hole = parent, & (hole*2) = child(first)
	{
		int child; // holds the index of child level
		aEventRec tmp = array[hole]; // parent = hole = posn(i) = (currentSize / 2)
									 // hole = parent, (hole*2) = child(first)
		for (; hole * 2 <= currentSize; hole = child) // hole = child means child loc becomes the
													  //next hole(parent) loc for next iteration - i.e. hole percolates down
		{
			child = hole * 2; //hole = parent, (hole*2) = child(first)
			if (child != currentSize && array[child + 1] < array[child])
			{
				child++; // choose the index of the lower of the two child
			}

			if (array[child] < tmp) // if child element is less than the tmp value that came in
			{
				array[hole] = array[child];// child element is moved up
										   // to its parent loc
			}
			else
			{
				break; //case when both child are greater than parent
			}
		}
		array[hole] = tmp; // then tmp value is stored at the new hole loc
	}
};

template <class Type>
class StackType
{
public:
	~StackType();// Destructor
	StackType(int maxSize);	// Parameter constructor
							// 1. Copy constructor
	StackType(const StackType<Type>& otherStack); // copy constructor
												  // 2. Assignment Operator overload
	const StackType<Type>& operator = (const StackType<Type>& otherStack);

	//const StackType<Type>& StackType<Type>::operator = (const StackType<Type>& otherStack)
	void initializeStack();
	void invertStack();
	bool isEmptyStack() const;
	bool isFullStack() const;
	Type stackTop() const;  // peek into stack to know the Top content of stack
	void push(Type anItem);
	Type pop();
private:
	int stackMaxSize;
	int curSize;
	bool isFull, isEmpty;
	Type *list;
	//CopyStack Function that facilitates 1. Copy constructor
	// and the 2. Assignment Operator overload
	void copyStack(const StackType<Type>& otherStack);
};

template<class Type>
StackType<Type>::~StackType()
{
	delete[] list;
	//cout << "Destructor activated .." << endl;
}

template<class Type>
StackType<Type>::StackType(int maxSize = 100)
{
	if (maxSize <= 0)
	{
		stackMaxSize = 100;
	}
	else
	{
		stackMaxSize = maxSize;
	}
	curSize = 0;
	list = new Type[stackMaxSize];
	//cout << "Parameter constructor used .." << endl;
}

// 1. Copy constructor that will use the void copyStack Function
template<class Type>
StackType<Type>::StackType(const StackType<Type>& otherStack)
{
	list = NULL; // to facilitate delete
	copyStack(otherStack);
}

// 2. Assignment Operator Overload that will use the void copyStack Function
template<class Type>
const StackType<Type>& StackType<Type>::operator = (const StackType<Type>& otherStack)
{
	if (this != &otherStack) // ie. pointers are not pointing to same Object
		copyStack(otherStack);// avoid self copy
	return *this;// return contents at where the pointer points to
}

//CopyStack Function that facilitates 1. Copy constructor
// and the 2. Assignment Operator overload
template<class Type>
void StackType<Type>::copyStack(const StackType<Type>& otherStack)
{
	delete[] list;
	stackMaxSize = otherStack.stackMaxSize;
	curSize = otherStack.curSize;
	list = new Type[stackMaxSize];
	for (int i = 0; i < curSize; i++)
	{
		list[i] = otherStack.list[i];
	}
}

template<class Type>
void StackType<Type>::initializeStack()
{
	curSize = 0;
}

template<class Type>
void StackType<Type>::invertStack()
{
	StackType<Type> tmpStack(stackMaxSize);
	if (!isEmptyStack())
	{
		tmpStack.curSize = curSize;
		tmpStack.list = new Type[stackMaxSize];
		for (int i = 0; i < curSize; i++)
		{
			tmpStack.list[i] = list[i];
		}

		for (int i = (curSize - 1); i >= 0; i--)
		{
			list[i] = tmpStack.list[i];
		}
	}
	else
	{
		//cout << "Stack is Empty !!" << endl;
	}
}


template<class Type>
bool StackType<Type>::isEmptyStack() const
{
	return(curSize == 0);
}

template<class Type>
bool StackType<Type>::isFullStack() const
{
	return (curSize == stackMaxSize);
}

template<class Type>
Type StackType<Type>::stackTop() const  // peek into stack to know the Top content of stack
{
	if (!isEmptyStack())
	{
		return list[curSize - 1];
	}
	else
	{
		//cout << "Stack is Empty !!" << endl;
		//return NULL;
	}
};

template<class Type>
void StackType<Type>::push(Type anItem)
{
	if (!isFullStack())
	{
		list[curSize] = anItem;
		curSize++;
	}
	else
	{
		cout << "Stack is Full, item cannot be pushed !!" << endl;
	}
}

template<class Type>
Type StackType<Type>::pop()
{
	Type tmp;
	tmp = stackTop();
	if (!isEmptyStack())
	{
		curSize--;
	}
	else
	{
		cout << "Stack is Empty, nothing to pop !!" << endl;
	}
	return tmp;
};


//*** BEGIN - Main Constants and global declarations ******

const string ASNO = " Assignment # 5 ";
const string STNAME = " Student Name : Varadharaja Perumal ";
const string STID = " Student Id   : 1008475675 ";
const string DUEDT = " Due : Tuesday, March 15, 2016\n ";

const int MAX_HOURS = 24;
const int FLT_NUMBER_START = 1000;
const int NO_OF_FLIGHTS = 14;
const int IN_FLTS_HOURLY_SCHEDULE[] = { 2, 3, 4, 9, 11, 14, 17, 19, 28, 33, 37, 44, 49, 55 };
const	string ORIG[] = { "LAX", "SMF", "IAH", "ABQ", "SJC", "PHX", "SFO", "SLC", "TUL", "DCA", "BNA",
		"MAF", "HOS", "ELP" };
const	string DESTN[] = { "JFK", "RDU", "MSP", "ATL", "BOS", "MIA", "ORD", "AUS", "ONT", "LAS", "SEA",
		"AMA", "DEN", "MEM" };
const string DATA_FILE_NAME1 = "servicedFlightsList.txt";  // the data text file name containing the data
const string DATA_FILE_NAME2 = "divertedFlightsList.txt";  // the data text file name containing the data

//*** END - Main Constants and global declarations ******

int getDepartureTime(int timeIn);
void createGateNosStack(StackType<int> &aGateList, int noOfGates);
void printServicedFlightSchedules(vector<aEventRec>  aSerFlightsSched, ostream &outStream);
void printDivertedFlightSchedules(vector<aEventRec>  aDiverFlightsSched, ostream &outStream);
void printGateUsage(vector<int> gateNoDepsCount, ostream &outStream);
void printAsgHeader(ostream &outStream);
void printAsgFooter(ostream &outStream);

//****** BEGIN MAIN PROGRAM ****************
int main()
{
	string outFileName1;// declare string variables to hold file names
	string outFileName2;// declare string variables to hold file names
	string curOutputFile;
	ofstream outFileStream1; //an ifstream object to read input stream from files
	ofstream outFileStream2; //an ifstream object to read input stream from files
	outFileName1 = DATA_FILE_NAME1;
	outFileName2 = DATA_FILE_NAME2;
	outFileStream1.open(outFileName1.c_str());//associates a file stream with the file to open
	outFileStream2.open(outFileName2.c_str());
	char ch;
	srand(time(0));
	int numberOfGates;// for holding the number of gates entered by user
	int countDelayedFlights = 0; // to count the number of flights delayed
	vector<aEventRec>  servicedFlights;// a vector that has all arrivals and departures records
	vector<aEventRec> divertedFlights; // an vector that has all diverted flights records
	int availGateNo; // to hold the available gate no popped from gateNosStack
	int hour = 0;
	int noOfFltsPerHr = NO_OF_FLIGHTS;  //IN_FLTS_HOURLY_SCHEDULE.size();// holds the number of flights per hour initially declared
	BinaryHeap<aEventRec> depFlightsHeap;// a heap of all flights that includes arrivals and departures plan record
	int flitNo = FLT_NUMBER_START;// holds the flight numbers allotted to each successive flight arrivals
	int countAirportFull = 0; // to count the number of times air port full situation occurred 

	printAsgHeader(cout);
	cout << "\nEnter the number of gates in Airport to be tested for :  ";
	cin >> numberOfGates;

	vector<int> gateNoDepsCount(numberOfGates + 1);// a vector that has all arrivals and departures records
	StackType<int> gateNosStack(numberOfGates);// declare a stack object for gateNos
	createGateNosStack(gateNosStack, numberOfGates);// create the gateNos stack

	//build the gateNos array
	for (int i = 0; i < (gateNoDepsCount.size()); i++)
	{
		gateNoDepsCount[i] = 0;
	}

	//build the arrival flight plan array for MAX_HOURS of the day  
	for (hour = 0; hour < MAX_HOURS; hour++)
	{
     for (int i = 0; i < noOfFltsPerHr; i++)
		//for (int i = 0; i < IN_FLTS_HOURLY_SCHEDULE.size(); i++)
		{
			int currArrTime = IN_FLTS_HOURLY_SCHEDULE[i] + (hour * 60);
			aEventRec aNewFltRec;
			aNewFltRec.arrDepTime = currArrTime; // assign current time as arrival time for the flght plan record
			aNewFltRec.arrDepCode = 'A'; // assign arrival code for the time
			aNewFltRec.orig = ORIG[i]; // assign originate location from the ORIG array 
			aNewFltRec.dest = DESTN[i];// assign destination location from the DESTN array 
			aNewFltRec.fltNo = flitNo; // assign a Flight number
			servicedFlights.push_back(aNewFltRec); // push the flight plan arrival record
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
		flightsHeap1.deleteMin();// delete the root record from heap
		if (aFltRec.arrDepCode == 'D')  // if it is a departure flight
		{
			gateNosStack.push(aFltRec.gateNo);	//get the gate no of root record that is to be deleted and replenish the gateStack				
			gateNosStack.invertStack(); // invert stack to prevent last in first out
			servicedFlights.push_back(aFltRec); // push the flight plan departure record with gateNo
		}
		else if (!gateNosStack.isEmptyStack()) // else it is a arrival flight that needs to be allotted a gateNo
		{
			currArrTime = aFltRec.arrDepTime;
			availGateNo = gateNosStack.pop(); //pop a gateNo from gateNostack 
			aFltRec.gateNo = availGateNo; // allot a gateNo to a flight plan
			(gateNoDepsCount[availGateNo])++; // increase allottment count for that paticular gateNo
			servicedFlights.push_back(aFltRec); // push the flight plan arrival record with gateNo

			aFltRec.arrDepTime = getDepartureTime(aFltRec.arrDepTime);// allocate a departure time when arrival allowed and a gate No alloted 
			aFltRec.arrDepCode = 'D';// assign departure code for the time
			int delayTime = (aFltRec.arrDepTime - currArrTime - 60);// calculate flight delay time
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
			flightsHeap1.insert(aFltRec);//insert the flight departure plan into depFlightsHeap
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
	}

	if (countAirportFull > 0)
	{
		printDivertedFlightSchedules(divertedFlights, outFileStream2);
		printDivertedFlightSchedules(divertedFlights, cout);

		outFileStream2 << "\nNumber of Gates in the Airport : " << numberOfGates << endl;
		outFileStream2 << "Number of times Airport was full and consequently total number of flights that got diverted : " << countAirportFull << endl;
		outFileStream2 << "\n       " << numberOfGates << " gates not adequate for the number of Aircrafts arriving into the airprort !" << endl;
		outFileStream2 << "\nPROGRAM EXECUTION ABORTED !!  "<< endl;

		cout << "\nNumber of Gates in the Airport : " << numberOfGates << endl;
		cout << "Number of times Airport was full and consequently total number of flights that got diverted : " << countAirportFull << endl;
		cout << "\n       " << numberOfGates << " gates not adequate for the number of Aircrafts arriving into the airprort !" << endl;
		cout << "\nPROGRAM EXECUTION ABORTED !!  " << endl;
		curOutputFile = outFileName2;
		printAsgFooter(outFileStream2);
	}
	else
	{
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
		printAsgFooter(outFileStream1);
	}
	outFileStream1.close();
	outFileStream2.close();	
	cout << "\nThe above information can also be found saved in file : " << curOutputFile << endl;
	printAsgFooter(cout);
	//cin >> ch;
	return 0;
}
//****** END MAIN PROGRAM ****************

//An arrival time is passed to the function that returns a delayed departure time 
int getDepartureTime(int timeIn)
{
	int numbRange = 100;
	int n2 = 20, numbRange3 = 20;
	int departureTime = 60 + timeIn;
	int delayTime = 0;
	int i;
	i = (1 + rand() % numbRange);
	if (i <= 40)
	{
		delayTime = (n2 + rand() % numbRange3);
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

void printServicedFlightSchedules(vector<aEventRec>  aSerFlightsSched, ostream &outStream)
{
	BinaryHeap<aEventRec> allDayHeap(aSerFlightsSched);
	printAsgHeader(outStream);
	while (allDayHeap.getSize() > 0)
	{
		aEventRec aFltRec;
		aFltRec = allDayHeap.findMin();
		string arrDepStr = " has arrived at gate number ";
		if (aFltRec.arrDepCode == 'D')  // if it is a departure flight
		{
			arrDepStr = "  has departed from gate number ";
		}
		outStream << "\n Flight Number: " << aFltRec.fltNo
			<< " From : " << aFltRec.orig << endl
			<< "                      " << " To : " << aFltRec.dest
			<< arrDepStr << aFltRec.gateNo
			<< " at time: " << aFltRec.arrDepTime << " minute of the day " <<  endl
			<< "                               " << aFltRec.remark << endl;
		allDayHeap.deleteMin();
	}
}

void printDivertedFlightSchedules(vector<aEventRec>  aDiverFlightsSched, ostream &outStream)
{
	printAsgHeader(outStream);
	for (int i = 0; i < aDiverFlightsSched.size(); i++)
	{
		aEventRec aFltRec;
		aFltRec = aDiverFlightsSched[i];

		outStream << "\n Airport full at time : " << aFltRec.arrDepTime << endl;
		outStream << " Flight Number : " << aFltRec.fltNo
			<< " From : " << aFltRec.orig << endl
			<< "                       " << " To : " << aFltRec.dest
			<< " that was to arrive at : " << aFltRec.arrDepTime << " minute of the day " << endl
			<< "                               " << " was diverted to another airport ! " << endl;
	}
}

void printGateUsage(vector<int> gateNoDepsCount, ostream &outStream)
{
	for (int i = 1; i < (gateNoDepsCount.size()); i++)
	{
		outStream << "Gate No : " << i << "  " << gateNoDepsCount[i] << endl;
	}
}

void printAsgHeader(ostream &outStream)
{
	system("clear");
	outStream << endl << "***** Begining of Assignment *****" << endl << endl;
	outStream << endl;
	outStream << ASNO << endl;
	outStream << STNAME << endl;
	outStream << STID << endl;
	outStream << DUEDT << endl;
}

void printAsgFooter(ostream &outStream)
{
	outStream << endl << endl << "***** End of Assignment *****" << endl << endl;
}

//for (hour = 0; hour < MAX_HOURS; hour++)
//{
//	for (int i = 0; i < IN_FLTS_HOURLY_SCHEDULE.size(); i++)
//	{
//		int currArrTime = IN_FLTS_HOURLY_SCHEDULE[i] + (hour * 60);
//		aEventRec aNewFltRec;
//		aNewFltRec.arrDepTime = currArrTime; // assign current time as arrival time for the flght plan record
//		aNewFltRec.arrDepCode = 'A'; // assign arrival code for the time
//		aNewFltRec.orig = ORIG[i]; // assign originate location from the ORIG array 
//		aNewFltRec.dest = DESTN[i];// assign destination location from the DESTN array 
//		aNewFltRec.fltNo = flitNo; // assign a Flight number

//		/*To do only after first round of gate allocation is done
//		  The departures before cuurent time is deleted from heap
//		  and the gate that becomes available is pushed into stack
//		*/
//		if ((flitNo - FLT_NUMBER_START + 1) >  NUMBER_OF_GATES) // after the first round then check for departures and delete from heap
//		{
//			aEventRec aFltRec;
//			aFltRec = depFlightsHeap.findMin(); // to get time of the root record(next for dep) 
//			while (currArrTime > aFltRec.arrDepTime)
//			{
//				gateNosStack.push(aFltRec.gateNo);	//get the gate no of root record that is to be deleted and replenish the gateStack				
//				depFlightsHeap.deleteMin(); // delete the root record as would have departed at curr time
//				aFltRec = depFlightsHeap.findMin();// get the next new root record(next for dep) for next iteration					
//			}
//			gateNosStack.invertStack(); // invert stack to prevent last in first out
//		}

//		//cin >> ch;
//		/* If-else checks for gateNos available in stack
//		   and if available allots gate Nos and a departure time,
//		   and pushes the record into the servicedFlights vector list
//		   and the depFlightsHeap
//		*/
//		if (!gateNosStack.isEmptyStack()) // if gateNos stack not empty - gates available to be allotted 
//		{
//			availGateNo = gateNosStack.pop(); //pop a gateNo from gateNostack 
//			aNewFltRec.gateNo = availGateNo; // allot a gateNo to a flight plan
//			(gateNoDepsCount[availGateNo])++; // increase allottment count for that paticular gateNo
//			servicedFlights.push_back(aNewFltRec); // push the flight plan arrival record

//			aNewFltRec.arrDepTime = getDepartureTime(aNewFltRec.arrDepTime);// allocate a departure time when arrival allowed and a gate No alloted 
//			aNewFltRec.arrDepCode = 'D';// assign departure code for the time

//			int delayTime = (aNewFltRec.arrDepTime - currArrTime - 60);// calculate flight delay time
//			if (delayTime > 0)
//			{
//				countDelayedFlights++;
//				stringstream convert;
//				convert << delayTime;
//				aNewFltRec.remark = "  Flight departure delayed by " + convert.str() + " minutes";
//			}
//			else
//			{
//				aNewFltRec.remark = "  Filght departure on time.";
//			}
//			servicedFlights.push_back(aNewFltRec); //push the flight plan departure record				
//			depFlightsHeap.insert(aNewFltRec);//insert the flight departure plan into depFlightsHeap
//			//cin >> ch;
//		}
//		else
//		{ // no gates available => Airport Full!!
//			aNewFltRec.gateNo = 0; 
//			aNewFltRec.remark = "  Airport Full ! - Filght Diverted to another Airport.";
//			///cin >> ch;
//			divertedFlights.push_back(aNewFltRec); // push the flight plan of a diverted flight
//			countAirportFull++;
//		}
//		flitNo++;
//	}// end : for (int i = 0; i < IN_FLTS_HOURLY_SCHEDULE.size(); i++)

//} // End - for (hour = 0; hour < MAX_HOURS; hour++)
//cin >> ch;