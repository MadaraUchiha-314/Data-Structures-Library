#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

template <class T>
class Vector
{
	private :
	T *ptr;
	unsigned int numEle;
	unsigned int memAvail;

	public :

// Constructor
	Vector ()
	{
		numEle=0;
		ptr=NULL;
		memAvail=0;
	}

// Another Constructor
	
	Vector (unsigned int initialSize)
	{
		ptr = (T*)calloc (initialSize,sizeof (T));
		numEle=0;
		memAvail=initialSize;
		
	}

// Destructor

	~Vector ()
	{	
		free (ptr);
	}

// Function To Add Elements	

	void addElement (T data)
	{
		if (memAvail==0)
		{		
			T *temp=(T*)calloc ((numEle+1),sizeof(T));
			for (int i=0;i<numEle;i++)
				temp[i]=ptr[i];

			temp[numEle]=data;
			numEle++;

			free (ptr);
			ptr = temp;
		}
		
		else
		{
			ptr[numEle]=data;
			numEle++;
			memAvail--;
		}
	}

// Reserves Memory Of Total Size Elements...Includes The Current Elements  + Memory Available

	void reserveMem (unsigned int size)
	{
			if (size > (numEle+memAvail) )
			{
				T *temp=(T*)calloc ((size),sizeof(T));
				for (int i=0;i<numEle;i++)
					temp[i]=ptr[i];
	

				free (ptr);
				ptr = temp;
				memAvail=size-numEle;
			}
	}

// Tells The Total Number OF Elements The Vector Can Hold
		
	unsigned int tellCapacity ()
	{
		return numEle+memAvail;
	}

// Makes The Vector Back To The Original Required Size
	
	void shrinkToFit ()
	{
		ptr=(T*)realloc (ptr,numEle*sizeof (T));
		memAvail=0;
	}

// Tells The Current Size Of The Vector

	unsigned int tellSize ()
	{
		return numEle;
	}

// Function To Print Whole Vector	

	void printVector ()
	{
		for (int i=0;i<numEle;i++)
			cout<<ptr[i]<<"\t";
	}

// Function To Replace Element

	int  replaceElement (T data,unsigned int index)
	{
		if (index < numEle )
		{	
			ptr[index]=data;
			return 1;
		}


		else 
		{	
			cerr<<"\nLess Number Of Elements \n";
			return 0;
		}	
	}

// Function To Delete A Given Index

	int deleteElement (unsigned int index)
	{	
			int i;
			T *temp;
					
		if (index < numEle)
		{
			
			for (i=index;i<this->numEle-1;i++)
			{
			
				ptr[i]=ptr[i+1];
				temp++;
			}
			numEle--;
			return 1;
		}
		else 
		{
			return 0;
		}
			temp++;
			free (temp);
	
	}


// Function To Get The Pointer To The First Element

	T* getPointerToFirstElement ()
	{	
		return ptr;	
	}

// Overloaded The Operators
	
	T& operator[] (unsigned int index)
	{
		if (index >= numEle)
			return ptr[0];
		else
			return ptr[index];
	}
	
	const T& operator[] (unsigned int index) const
	{

		if (index >= numEle)
			return ptr[0];
		else
			return ptr[index];
	}
		
	
};


int main ()
{
	Vector<int> v(15);
	
	for (int i=0;i<6;i++)
		v.addElement (i);
	
	cout<<"\n";
	v.printVector ();
	
	cout<<"\n";
	v.addElement (17);
	
	v.printVector ();
	cout<<"\n";
	
	v[3]=7;
	
	v.printVector ();

	cout<<"\n";
	v.replaceElement (9,4);
		
	v.printVector ();
	
	cout<<"\n";
	v.deleteElement (2);

	v.printVector ();

	cout<<"\n";
	 
	v.reserveMem (100);
	cout<<"\n";
	cout<<v.tellCapacity ();
	
	cout<<"\n";
	v.printVector ();

	v.shrinkToFit ();
	
	cout<<"\n";
	v.printVector ();
	cout<<"\n";
	cout<<v.tellCapacity ();
	cout<<"\n";

return 0;
}	
