#include <iostream>
#include <cstdio>
using namespace std;

template <class T>
struct Tree
{
	T data;
	Tree *leftTree,*rightTree;
};

template <class T>
class BinaryTree
{
	private :

	Tree<T> *TreeTop;
	unsigned int numberOfElements;

// Some Private Functions That Serve As Helper Functions To Public Function
// Too Dangerous To Be Declared Public As They Return Pointer To The Data Which The User May Manipulate And Program Goes Wrong...!!

/* Returns The Parent Node Of A Given Element Exept TreeTop */

	Tree<T>* findParentNodeOf (T data1,Tree<T>* tree)
	{
			if (data1==tree->leftTree->data || data1==tree->rightTree->data)
				return tree;
			else if (data1 < tree->data)
				findParentNodeOf (data1,tree->leftTree);
			else
				findParentNodeOf (data1,tree->rightTree);
	}

/* Searches The Tree For A Particular Data Element And Returns The Pointer To It -- >Used in findElement Function And deleteElement Function */


	Tree<T>* search (T data1,Tree<T> *tree)
	{
		if (tree!=NULL)
		{
			if (tree->data==data1)
				return tree;
			else if (data1 < tree->data)
				search (data1,tree->leftTree);
			else 
				search (data1,tree->rightTree);
		}
		else
		{
			cout<<"\n\n Element Not Found \n  ";
			return NULL;
		}
	}

/* Deletes The Entire Tree On Program Completion --> Called By The Destructor Of BST class */

	void deleteTree (Tree<T> *tree)
	{
		int flag=0;		
		Tree<T> *temp=tree;		
		if (tree->rightTree!=NULL)
		{
			deleteTree(tree->rightTree);
			//delete temp;
		}
		if (tree->leftTree!=NULL)
			deleteTree(tree->leftTree);

		if (tree->leftTree==NULL && tree->rightTree==NULL)
		{
			delete tree;flag=1;
		}
		
	if (!flag)
		delete tree;
			
	}	


/* Makes Each Node Of The BST, Initiliasing With Given Data --> Used By insertElement Function */

		
	Tree<T>* makeTree (T data1)
	{
		Tree<T> *temp=new Tree<T>;
		temp->data=data1;
		temp->leftTree=NULL;	
		temp->rightTree=NULL;
		return temp;
	}
	
	public :

// Constructor	

	BinaryTree ()
	{
		TreeTop=NULL;
		numberOfElements=0;
	}

// Destructor

	~BinaryTree ()
	{
		deleteTree (TreeTop);
	}		
	
	
// Inserts A Given Element In The BST
	
	void insertElement (T data1,Tree<T> *tree,int flag=1)
	{
		if (TreeTop==NULL)
		{
			Tree<T> *temp=makeTree (data1);
			numberOfElements++;
			
			TreeTop=temp;	
		}
			
		else if (flag==0)
		{
			Tree<T> *temp=makeTree (data1);
			numberOfElements++;
			if (data1 < tree->data)
				tree->leftTree=temp;
			else
				tree->rightTree=temp;
		}

		else
		{
			if ( data1 < tree->data )
			{
				if (tree->leftTree!=NULL)
					insertElement (data1,tree->leftTree,1);
				else 
					insertElement (data1,tree,0);
			}
			else
			{
				if (tree->rightTree!=NULL)
					insertElement (data1,tree->rightTree,1);
				else	
					insertElement (data1,tree,0);
			}			
					
		}	
	}

// Overload Of The insertElement Function To Have Abstraction
	
	void insertElement (T data1)
	{
		insertElement (data1,TreeTop,1);
	}
	
// Deletes A Given Element

	void deleteElement (T data1)
	{
		Tree<T> *parent=findParentNodeOf (data1,TreeTop);
		Tree<T> *delNode=search (data1,TreeTop);

		if (delNode->rightTree==NULL && delNode->leftTree==NULL)
		{
			parent->leftTree=NULL;
			parent->rightTree=NULL;
			delete delNode;
			numberOfElements--;
		}
		
		else if (delNode->leftTree==NULL && delNode->rightTree!=NULL)
		{
			if (delNode->data < parent->data)
				parent->leftTree=delNode->rightTree;
			else
				parent->rightTree=delNode->rightTree;
			
			delete delNode;
			numberOfElements--;
		}
			
		else if (delNode->leftTree!=NULL && delNode->rightTree==NULL)
		{	
			if (delNode->data < parent->data)
				parent->leftTree=delNode->leftTree;
			else
				parent->rightTree=delNode->leftTree;
			
			delete delNode;
			numberOfElements--;
		}
		
		else
		{
			if (delNode->data < parent->data)
			{
				parent->leftTree=delNode->rightTree;
				delNode->rightTree->leftTree=delNode->leftTree;
			}
			else
			{
				parent->rightTree=delNode->rightTree;
				delNode->rightTree->leftTree=delNode->leftTree;
			}

			delete delNode;
			numberOfElements--;
		}
}
				
// Searches A Given Element Using The search Function Declared Earlier--> Abstraction Of Search Function
		
	T findElement (T data1)
	{
		Tree<T> *tree=search (data1,TreeTop);
		if (tree==NULL)	
		{
			cout<<"\n Element Not FOund \n ";
			
		}
			
		else 
			return tree->data;
	}			

// Prints The Tree		
		
	void printTree (Tree<T> *tree)
	{
		cout<<"\n Data In Branch Is "<<tree->data;
		
		if (tree->leftTree!=NULL)
			printTree (tree->leftTree);
		if (tree->rightTree!=NULL)
			printTree (tree->rightTree);
		
	}
	
// Overloaded Function For Abstraction

	void printTree ()
	{
		printTree (TreeTop);
	}

};


int main ()
{
	BinaryTree<int> bt;
	for (int i=0;i<7;i++)
	{
		int temp;
		scanf ("%d",&temp);
		//cout<<"\n Data Got "<<temp<<"\n";
		bt.insertElement (temp);
	}

	
	bt.printTree ();
	cout<<"\n\n\n "<<bt.findElement (7);

	bt.deleteElement (2);
	bt.printTree ();	

	cout<<"\n";
return 0;
}

		
