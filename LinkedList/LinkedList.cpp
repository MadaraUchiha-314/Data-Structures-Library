#include <iostream>
#include <iterator>

using namespace std;

template <class T>
struct node
{
	T data;
	node *next;
};

template <class T>
class LinkedList
{
	private :
	node<T> *start;
	unsigned int numElements;

	// Creates A New Node. Puts The Data Into The Node. Returns The Pointer Of The Node Created

	node<T>* createNewNode (T data1)
	{
		node<T> *temp;	
		temp = new node<T>;
		temp->data=data1;
		temp->next=NULL;
	return temp;
	}
	
	public :
	// Constructor	
	LinkedList ()
	{
		start=NULL;
		numElements=0;
	}
	// Destructor	
	~LinkedList ()
	{
		node<T> *temp;	
		temp=start;
		while (temp!=NULL)
		{	
			delete temp;
			temp=temp->next;
		}
	}

	// getDataAtIndex Function
	/*
	   Returns Data At Given Index As Argument.
	   If Index Is Invalid The Returns The Data Of 1st Element 
	*/	

	T getDataAtIndex (unsigned int index)
	{
		node<T> *temp=start;		
		if (index < numElements)
		{		
			for (int i=0;i<index;i++)
				temp=temp->next;
		}
	return temp->data;
	
	}

	// Acessor Function Of Class LinkedList	- Returns The Start Pointer Of The Linked List

	node<T>* begin ()
	{
		return start;
	}

	node<T>* end ()
	{
		return NULL;
	}
	// Acessor Function Of Class LinkedList - Returns The Number Of Elements In The List	

	unsigned int size ()
	{
		return numElements;
	}


	// Inserts A Given Node At Begenning Of List
	/* 
	Returns 0 If No Memory Along With Error Message
	Returns 1 If Sucessfully Inserted
	*/ 	

	int push_front (T data1)
	{
		node<T> *temp;
		temp=createNewNode (data1);
		
		if (temp==NULL)
		{
			cerr<<"\n No Memory In Heap \n";
			return 0;
		}
		
		else 
		{
			if (start!=NULL)		
			{
				temp->next=start;
				start=temp;
				numElements++;
			}
			else
			{
				start=temp;
				numElements++;
			}
		}
return 1;
	}
// Inserts A Given Node At End Of List
/* 
Returns 0 If No Memory Along With Error Message
Returns 1 If Sucessfully Inserted
*/ 
	int push_back (T data1)
	{
		node<T> *temp;
		node<T> *ptr=start;
		temp=createNewNode (data1);

		if (temp==NULL)
		{
			cerr<<"\n No Memory In Heap \n";
			return 0;
		}
		
		else 
		{
		
			if (start==NULL)
			{	
				start=temp;
				numElements++;
			}
			else 
			{
				while (ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
				numElements++;
			}
		}
return 1;
		
	}

// Inserts A Given Node At Given Index
/* 
Returns 0 If No Memory Along With Error Message
Returns 1 If Sucessfully Inserted
*/ 

	int insert(unsigned int index,T data1)
	{
		node<T> *ptr;
		ptr=start;	
		
		if (index==0)
			this->push_front (data1);
		else if (index==(numElements-1))
			this->push_back (data1);
		else
		{
			node<T> *temp=createNewNode (data1);
			if (temp==NULL)
			{
				cerr<<"\n No Memory In Heap \n";
				return 0;
			}
			else 
			{
				for (int i=0;i<index-1;i++)
					ptr=ptr->next;
				temp->next=ptr->next;
				ptr->next=temp;
				numElements++;
			
			}
			
		return 1;
		}
	}

	// Deletes Node From Begenning Of List
	/*
	Returns 0 If Empty List
	Returns 1 If Sucessfully Deleted
	*/

	int pop_front ()
	{
		if (numElements==0)
		{
			cerr<<"\n Nothing To Delete \n";
			return 0;
		}
		else 
		{		
			node<T> *temp;	
			temp=start;
			start=start->next;
			delete temp;
			numElements--;
		return 1;
		}
	}

	// Deletes Node From End Of List
	/*
	Returns 0 If Empty List
	Returns 1 If Sucessfully Deleted
	*/


	int pop_back ()
	{
		if (numElements==0)
		{
			cerr<<"\n Nothing To Delete \n";
			return 0;
		}
		else 
		{		
			node<T> *temp;	
			temp=start;
		
			while (temp->next->next!=NULL)		
				temp=temp->next;
			
			delete (temp->next);
			numElements--;
			temp->next=NULL;

		return 1;
		}
	}
			
	int remove (unsigned int index)
	{
		if (numElements==0)
		{
			cerr<<"\n Nothing To Delete \n";
			return 0;
		}
		else 
		{			
			node<T> *temp;
			node<T> *ptr=start;		
			if (index==0)
				this->pop_front ();
			else if (index== (numElements-1) )	
				this->pop_back ();
			else
			{
				for (int i=0;i<index-1;i++)
					ptr=ptr->next;
				temp=ptr->next->next;
				delete ptr->next;
				ptr->next=temp;
				numElements--;
			}
		return 1;
		}
	}
	
	unsigned int search (T data1)
	{
		unsigned int index=0;		
		node<T> *temp=start;
		
		while (temp!=NULL)
		{	
			if (temp->data == data1)	
				return index;
			index++;
			temp=temp->next;
		}
		
	return -1;
	}
	
	void merge (node<T> *ptr,unsigned int numberOfElements)
	{
		node<T> *temp=start;
		// Make temp point to the starting of the first list
 
		while (temp->next!=NULL)
		{
			temp=temp->next;
		}
		// Traverse Through The List
		
		temp->next=ptr;
		numElements=numElements + numberOfElements;
	}

			
	void printList ()
	{
		cout<<"\n";		
		node<T> *temp=start;
		while (temp!=NULL)
		{
			cout<<temp->data<<"\t";
			temp=temp->next;
		}	
		cout<<"\n";
	}


	class iterator : public std::iterator<std::forward_iterator_tag,node<T>*>
	{
		node<T>* itr;

		public :

		iterator (node<T>* temp) : itr(temp) {}
		iterator (const iterator& myitr) : itr(myitr.itr) {}
		iterator& operator++ ()
		{
			itr = itr->next;
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
			return itr->data;
		}
		T *operator->() 
		{
  			return &itr->data;
		}

	};


};

int main ()
{
	LinkedList<int> L;
	LinkedList<int> L2;

	for (int i=1;i<6;i++)
		L.push_front (i);
	for (int i=7;i<=10;i++)
		L2.push_front (i);	

	L.printList ();

	L2.printList ();
	
	L.push_front (6);
	
	L.printList ();

	L.push_back (0);
	
	L.printList ();
		
	L.insert (3,7);
	
	L.printList ();
		
	L.pop_front();
	
	L.printList ();

	L.pop_back ();
		
	L.printList ();
	
	L.remove (2);
	
	L.printList ();
	
	L.merge (L2.begin (),L2.size ());	

	L.printList ();
	
		
	cout<<"\n Index Of 4 Is  "<<L.search (4)<<"\n";

	cout<<"\n Data At Index "<<L.search (4) <<" Is "<<L.getDataAtIndex (L.search (4))<<"\n";

	for (LinkedList<int>::iterator it=L.begin ();it!=L.end ();it++)
	{
		cout<<*it<<"\t";
	}
	cout<<"\n";
		

return 0;
}	

