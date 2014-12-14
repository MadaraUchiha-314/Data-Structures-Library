/*
 * This is a generic library on Graph Theory
 * Implementing some of it algorithms
 * I have mostly kept the data structure apart from the algorithms that run on it.
 */

/*
 * This is the data structure part
 * where we implement how the graph is stored in the memory
 * 1. Adjecency lists
 * 2. Adjecency Matrices
 * I am implementing both here
 */

/*
 * Adjecency list will be implemented as an array of list
 * list data strucutre is taken from the c++ stl itself
 */
/*
 * This library does not really take note on the data that the graph will store 
 * but will rather look at the connections and theier weights
 * but at some point of time it may be required to manipulate the data so providing an optional class to store data
 */

#include <list>
#include <cstdlib>
#include <iostream>
#include <exception>
/*
 * Node stores the data of the graph 
 * array of node will be made depending on the user's choice
 * a constructor overload while instantiating the graph will do the job 
 */

template <class T>
class Node
{
	T data;
};

template <class T>
class Graph
{
	unsigned int numNodes;
	std::list<unsigned int>* nodeConnections;
	Node<T>* node;

	public :
	Graph ()
	{
		numNodes = 0;
		nodeConnections = NULL;
		node = NULL;
	}
	Graph (unsigned int numNodes)
	{
		nodeConnections = new std::list<unsigned int>[numNodes];
		node = NULL;

		/*
		 * Fail check for any errors here
		 * i dont want to put any output to stderr
		 */
		if (nodeConnections!=NULL)
			this->numNodes = numNodes;
		else
			this->numNodes = 0;
	}
	Graph (unsigned int numNodes,bool requireData)
	{
		this->numNodes = numNodes;
		nodeConnections = new std::list<unsigned int>[numNodes];
		
		if (requireData==true)
			node = new Node<T>[numNodes];

		/*
		 * Fail check for any errors here
		 * i dont want to put any output to stderr
		 */
		if (nodeConnections!=NULL && node!=NULL)
			this->numNodes = numNodes;
		else
			this->numNodes = 0;
	}
	~Graph ()
	{
		if (nodeConnections!=NULL)
			delete[] nodeConnections;
		if (node!=NULL)
			delete[] node;
	}

	void addConnection (unsigned int from,unsigned int to) 
	{
		try
		{
			nodeConnections[from].push_back (to);
		}
		catch (std::exception& e)
		{
			std::cout<<e.what ()<<"\n";	
		}
	}

	void printGraph ()
	{
		for (int i=0;i<numNodes;i++)
		{
			std::cout<<i<<" is connected with -> ";
			for (std::list<unsigned int>::iterator it=nodeConnections[i].begin ();it!=nodeConnections[i].end();it++)
				std::cout<<*it<<" -> ";	
			std::cout<<"\n";
		}
	}


};
int main ()
{
	Graph<int> g(10);
	g.addConnection (0,1);
	g.addConnection (0,2);
	g.addConnection (1,5);
	g.printGraph ();
	return 0;
}

