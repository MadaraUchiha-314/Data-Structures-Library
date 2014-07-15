#include <iostream>

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
			node<T> *temp=start;		
			for (int i=0;i<index;i++)
				temp=start->next;
		}
	return temp->data;
	
	}
// Acessor Function Of Class LinkedList	- Returns The Start Pointer Of The Linked List

	node<T>* getStartPointer ()
	{
		return start;
	}
// Acessor Function Of Class LinkedList - Returns The Number Of Elements In The List	

	unsigned int getNumberOfElements ()
	{
		return numElements;
	}
// Creates A New Node. Puts The Data Into The Node. Returns The Pointer Of The Node Created

	node<T>* createNewNode (T data1)
	{
		node<T> *temp;	
		temp = new node<T>;
		temp->data=data1;
		temp->next=NULL;
	return temp;
	}

// Inserts A Given Node At Begenning Of List
/* 
Returns 0 If No Memory Along With Error Message
Returns 1 If Sucessfully Inserted
*/ 	

	int insertAtBeg (T data1)
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
	int insertAtEnd (T data1)
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

	int  insertAtIndex (T data1,unsigned int index)
	{
		node<T> *ptr;
		ptr=start;	
		
		if (index==0)
			this->insertAtBeg (data1);
		else if (index==(numElements-1))
			this->insertAtEnd (data1);
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

	int deleteFromBeg ()
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


	int deleteFromEnd ()
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
			
	int deleteIndex (unsigned int index)
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
				this->deleteFromBeg ();
			else if (index== (numElements-1) )	
				this->deleteFromEnd ();
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
	
	unsigned int getIndexOf (T data1)
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
	
	void mergeList (node<T> *ptr,unsigned int numberOfElements)
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
	

};

int main ()
{
	LinkedList<int> L;
	LinkedList<int> L2;

	for (int i=1;i<6;i++)
		L.insertAtBeg (i);
	for (int i=7;i<=10;i++)
		L2.insertAtBeg (i);	

	L.printList ();

	L2.printList ();
	
	L.insertAtBeg (6);
	
	L.printList ();

	L.insertAtEnd (0);
	
	L.printList ();
		
	L.insertAtIndex (7,3);
	
	L.printList ();
		
	L.deleteFromBeg ();
	
	L.printList ();

	L.deleteFromEnd ();
		
	L.printList ();
	
	L.deleteIndex (2);
	
	L.printList ();
	
	L.mergeList (L2.getStartPointer (),L2.getNumberOfElements ());	

	L.printList ();
	
		
cout<<"\n Index Of 4 Is  "<<L.getIndexOf (4)<<"\n";

cout<<"\n Data At Index "<<L.getIndexOf (4) <<" Is "<<L.getDataAtIndex (L.getIndexOf (4))<<"\n";
	

return 0;
}	

