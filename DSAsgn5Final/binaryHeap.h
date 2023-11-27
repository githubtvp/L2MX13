#include <iostream>
#include <cstdlib>
#include <string>
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
	bool operator<(const aEventRec other) const
	{
		return (arrDepTime < other.arrDepTime);
	}
};

class UnderflowException
{
};
class IllegalArgumentException
{
};
class ArrayIndexOutOfBoundsException
{
};
class IteratorOutOfBoundsException
{
};
class IteratorMismatchException
{
};
class IteratorUninitializedException
{
};

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

//Prototype declaration
template <class aEventRec>
class BinaryHeap
{
public:
//The explicit function specifier controls unwanted implicit type conversions. 
	~BinaryHeap();
	explicit BinaryHeap(int capacity = 100); // : theHeapArray(capacity + 1), currentSize(0){};
	explicit BinaryHeap(const vector<aEventRec> &items); //: theHeapArray(items.size() + 10), currentSize(items.size()) {};
	bool isEmpty() const;
	int getSize() const;
	const aEventRec &findMin() const;
	void insert(const aEventRec &x);
	void deleteMin();
	void deleteMin(aEventRec &minItem);
	void makeEmpty();
private:
	int currentSize;		 // Number of elements in heap
	vector<aEventRec> theHeapArray; // The Heap Array
	void buildHeap();
	void percolateDown(int hole);
};

//Definition of Class BinaryHeap
//Destructor
template<class aEventRec>
BinaryHeap<aEventRec>::~BinaryHeap()	
{
}
// Default constructor - with an optional capacity (that defaults to 100)
template<class aEventRec>
BinaryHeap<aEventRec>::BinaryHeap(int capacity)
	: theHeapArray(capacity + 1), currentSize(0)
{
}

// Parameter constructor - vector<aEventRec> & eventsList passed as parameter
template<class aEventRec>
BinaryHeap<aEventRec>::BinaryHeap(const vector<aEventRec> &eventsList)
	: theHeapArray(eventsList.size() + 10), currentSize(eventsList.size())
{
	for (int i = 0; i < eventsList.size(); i++)
	{
		theHeapArray[i + 1] = eventsList[i]; // vector eventsList copied into theHeapArray
	}
	buildHeap(); // theHeapArray elements are ordered in a heap structure
}
template<class aEventRec>
bool BinaryHeap<aEventRec>::isEmpty() const
{
	return currentSize == 0;
}
template<class aEventRec>
int BinaryHeap<aEventRec>::getSize() const
{
	return currentSize;
}

/**
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw Underflow if empty.
 */
template<class aEventRec>
const aEventRec& BinaryHeap<aEventRec>:: findMin() const
{
	if (isEmpty())
	{
		throw UnderflowException();
	}
	return theHeapArray[1];
}


/**
 * Insert item x, allowing duplicates.
 */
// Percolate up - hole /= 2 moves the hole up to its parent
template<class aEventRec>
void BinaryHeap<aEventRec>::insert(const aEventRec &eventArrDeptime)
{
	if (currentSize == theHeapArray.size() - 1)
	{
		theHeapArray.resize(theHeapArray.size() * 2);
	}
	// Percolate up - hole /= 2 moves the hole up to its parent
	int hole = ++currentSize;
	for (; hole > 1 && eventArrDeptime < theHeapArray[hole / 2]; hole /= 2) // hole /= 2 means next iteration hole has moved up
	{												   // i.e. hole percolates up wards
		theHeapArray[hole] = theHeapArray[hole / 2];				   // element at hole/2 moved down
													   // to the hole posn if eventArrDeptime < theHeapArray[ hole / 2 ]
	}
	theHeapArray[hole] = eventArrDeptime; // when eventArrDeptime value NOT < than hole/2 then eventArrDeptime placed at hole posn
}
/**
 * Remove the minimum item.
 * Throws UnderflowException if empty.
 */
template<class aEventRec>
void BinaryHeap<aEventRec>::deleteMin()
{
	if (isEmpty())
	{
		throw UnderflowException();
	}
	theHeapArray[1] = theHeapArray[currentSize--]; // last item placed at root(deleting the minimum) and percolated down
	percolateDown(1);				 // to its appropriate place starting from root posn
}

/**
 * Remove the minimum item and place it in minItem variable.
 * Throws UnderflowException if empty.
 */
template<class aEventRec>
void BinaryHeap<aEventRec>::deleteMin(aEventRec &minItem)
{
	if (isEmpty())
	{
		throw UnderflowException();
	}

	minItem = theHeapArray[1];				 // minimum item(root) stored in minItem variable
	theHeapArray[1] = theHeapArray[currentSize--]; // last item placed at root(deleting the minimum) and percolated down
	percolateDown(1);				 // to its appropriate place starting from root posn
}

template<class aEventRec>
void BinaryHeap<aEventRec>::makeEmpty()
{
	currentSize = 0;
}

/**
 * Establish heap order property from an arbitrary
 * arrangement of items. Runs in linear time.
 */
template<class aEventRec>
void BinaryHeap<aEventRec>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; i--)
	{
		percolateDown(i); // percolated down to its appropriate place
						  //  starting from posn(i) = currentSize / 2 = hole
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
template<class aEventRec>
void BinaryHeap<aEventRec>::percolateDown(int hole) // hole = parent, & (hole*2) = child(first)
{
	int child;									  // holds the index of child level
	aEventRec tmp = theHeapArray[hole];				  // parent = hole = posn(i) = (currentSize / 2)
												  // hole = parent, (hole*2) = child(first)
	for (; hole * 2 <= currentSize; hole = child) // hole = child means child loc becomes the
												  // next hole(parent) loc for next iteration - i.e. hole percolates down
	{
		child = hole * 2; // hole = parent, (hole*2) = child(first)
		if (child != currentSize && theHeapArray[child + 1] < theHeapArray[child])
		{
			child++; // choose the index of the lower of the two child
		}

		if (theHeapArray[child] < tmp) // if child element is less than the tmp value that came in
		{
			theHeapArray[hole] = theHeapArray[child]; // child element is moved up
										// to its parent loc
		}
		else
		{
			break; // case when both child are greater than parent
		}
	}
	theHeapArray[hole] = tmp; // then tmp value is stored at the new hole loc
}
