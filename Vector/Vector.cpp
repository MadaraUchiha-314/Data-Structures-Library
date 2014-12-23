#include <iostream>
#include <cstdio>
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

	void push_back (T data)
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

	void reserve (unsigned int size)
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
		
	unsigned int capacity ()
	{
		return numEle+memAvail;
	}

// Makes The Vector Back To The Original Required Size
	
	void shrink_to_fit ()
	{
		ptr=(T*)realloc (ptr,numEle*sizeof (T));
		memAvail=0;
	}

// Tells The Current Size Of The Vector

	unsigned int size ()
	{
		return numEle;
	}

// Function To Replace Element

	int insert (unsigned int index,T data)
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

	int erase (unsigned int index)
	{	
			int i;
			
					
		if (index < numEle)
		{
			for (i=index;i<this->numEle-1;i++)
			{
			
				ptr[i]=ptr[i+1];
				
			}
			numEle--;
			return 1;
		}
		else 
		{
			return 0;
		}
			
	}


// Function To Get The Pointer To The First Element

	T* begin ()
	{	
		return ptr;	
	}

// Function To Get The Pointer To The Last Element

	T* end ()
	{	
		return ptr+numEle;	
	}
	
// Tells whether the Vector is empty

	bool empty ()
	{
		if (numEle==0)
			return true;
		else
			return false;
	}

// Returns the value of the front most element

	T front ()
	{
		return *ptr;
	}

// Returns the value of the last element of the vector

	T back ()
	{
		return ptr[numEle-1];
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

	class iterator : public std::iterator<std::forward_iterator_tag,T*>
	{
		T* itr;

		public :

		iterator (T* temp) : itr(temp) {}
		iterator (const iterator& myitr) : itr(myitr.itr) {}
		iterator& operator++ ()
		{
			itr = ++itr;;
			return *this;

		}
		iterator operator++ (int) 
		{
  			iterator result(*this);
 			++*this;
  			return result;
		}

		bool operator== (const iterator& rhs) 
		{
			return itr == rhs.itr;

		}
		bool operator!= (const iterator& rhs) 
		{
			return itr != rhs.itr;

		}
		T& operator*()
		{
			return *itr;
		}
	
	};




// Function To Print Whole Vector	

	void printVector ()
	{
		for (int i=0;i<numEle;i++)
			cout<<ptr[i]<<"\t";
	}
		
	
};


int main ()
{
	Vector<int> v(15);
	
	for (int i=0;i<6;i++)
		v.push_back (i);
	
	cout<<"\n";
	v.printVector ();
	
	cout<<"\n";
	v.push_back (17);
	
	v.printVector ();
	cout<<"\n";
	
	v[3]=7;
	
	v.printVector ();

	cout<<"\n";
	v.insert (4,9);
		
	v.printVector ();
	
	cout<<"\n";
	v.erase (2);

	v.printVector ();

	cout<<"\n";
	 
	v.reserve (100);
	cout<<"\n";
	cout<<v.capacity ();
	
	cout<<"\n";
	v.printVector ();

	v.shrink_to_fit ();
	
	cout<<"\n";
	v.printVector ();

	cout<<"\n";
	cout<<v.capacity ();

	cout<<"\n";

	for (Vector<int>::iterator it=v.begin ();it!=v.end();it++)
		cout<<*it<<"\t";
	cout<<"\n";

return 0;
}	
