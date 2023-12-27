/*
 * BinaryHeap.h
 *
 *  Created on: Mar 4, 2016
 *      Author: myaccount
 */
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "dsexceptions.h"
#include <vector>
using namespace std;

struct aEventRec
{
	int fltNo;
	char arrCode;
	int arrTime;
	char depCode;
	int depTime;
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



// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable getMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename aEventRec>
class BinaryHeap
{
  public:
	//Default constructor - with an optional capacity (that defaults to 100)
    explicit BinaryHeap( int capacity = 100 )
      : array( capacity + 1 ), currentSize( 0 )
    {
    }
    //Parameter constructor - vector<Comparable> & items passed as parameter
    explicit BinaryHeap( const vector<aEventRec> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
        for( int i = 0; i < items.size( ); i++ )
        {
        	array[ i + 1 ] = items[ i ]; // vector items copied into array
        }
        buildHeap( ); //array elements are ordered in a heap structure
    }

    bool isEmpty( ) const
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
    const aEventRec & getMin( ) const
    {
        if( isEmpty( ) )
        {
        	throw UnderflowException( );
        }
        return array[ 1 ];
    }

    /**
     * Insert item x, allowing duplicates.
     */
    // Percolate up - hole /= 2 moves the hole up to its parent
    void insert( const aEventRec & x )
    {
        if( currentSize == array.size( ) - 1 )
        {
        	array.resize( array.size( ) * 2 );
        }
        // Percolate up - hole /= 2 moves the hole up to its parent
        int hole = ++currentSize;
        for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 ) // hole /= 2 means next iteration hole has moved up
        {                                                // i.e. hole percolates up wards
        	array[ hole ] = array[ hole / 2 ]; // element at hole/2 moved down
        	                                  // to the hole posn if x < array[ hole / 2 ]
        }
        array[ hole ] = x; // when x value NOT < than hole/2 then x placed at hole posn
    }
    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) )
        {
        	throw UnderflowException( );
        }
        array[ 1 ] = array[ currentSize-- ];// last item placed at root and percolated down
        percolateDown( 1 );//to its appropriate place starting from root posn
    }

    /**
     * Remove the minimum item and place it in minItem variable.
     * Throws UnderflowException if empty.
     */
    void deleteMin(aEventRec & minItem )
    {
        if( isEmpty( ) )
        {
        	throw UnderflowException( );
        }

        minItem = array[ 1 ];// minimum item(root) stored in minItem variable
        array[ 1 ] = array[ currentSize-- ];// last item placed at root and percolated down
        percolateDown( 1 ); //to its appropriate place starting from root posn
    }

    void makeEmpty( )
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
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
        {
        	percolateDown( i ); //percolated down to its appropriate place
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
    void percolateDown( int hole )   // hole = parent, & (hole*2) = child(first)
    {
        int child; // holds the index of child level
		aEventRec tmp = array[ hole ]; // parent = hole = posn(i) = (currentSize / 2)
                                      // hole = parent, (hole*2) = child(first)
        for( ; hole * 2 <= currentSize; hole = child ) // hole = child means child loc becomes the
        	                               //next hole(parent) loc for next iteration - i.e. hole percolates down
        {
            child = hole * 2; //hole = parent, (hole*2) = child(first)
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
            {
            	child++; // choose the index of the lower of the two child
            }

            if( array[ child ] < tmp ) // if child element is less than the tmp value that came in
            {
            	array[ hole ] = array[ child ];// child element is moved up
            	                        // to its parent loc
            }
            else
            {
            	break; //case when both child are greater than parent
            }
        }
        array[ hole ] = tmp; // then tmp value is stored at the new hole loc
    }
};

#endif






