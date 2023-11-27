#include <iostream>

using namespace std;


template <class Type>
class StackType
{
public:
	~StackType();// Destructor
	StackType(); //Default constructor
	StackType(int maxSize = 100);	// Parameter constructor
							// 1. Copy constructor
	StackType(const StackType<Type>& otherStack); // copy constructor
												  // 2. Assignment Operator overload
	const StackType<Type>& operator = (const StackType<Type>& otherStack);
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
StackType<Type>::StackType()
{
    stackMaxSize = 100;
	curSize = 0;
	list = new Type[stackMaxSize];
	//cout << "Default constructor used .." << endl;
}

template<class Type>
StackType<Type>::StackType(int maxSize)
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
	//else
	//{
		//cout << "Stack is Empty !!" << endl;
	//}
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
		return 0;
	}
}

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
