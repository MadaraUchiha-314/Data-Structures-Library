/*
 * This will provide the major algos related to graph
 * i am plannig to implement the following
 * 1. DFS
 * 2. BFS
 * 3. Topological Sort
 * 4. Minimum spanning trees
 * 5. shortest path 
 * 6. euler and hamiltonian path (NP complete :p :D)
 * 7. planarity
 * 8. isomorphism
 *
 * These will take years to impelement by lets give it a start already
 */

 /*
 * The GraphAlgoritm's object will have to be made to use the algorithms.
 */

#include "Graph.h"

using namespace std;

template <class T>
class GraphAlgorithm
{
	bool* visited;
	
	public :

	GraphAlgorithm (unsigned int numNodes)
	{
		visited = new bool[numNodes];
		for (int i=0;i<numNodes;i++)
			visited[i] = false;
	}
	~GraphAlgorithm ()
	{
		delete[] visited;
		visited = NULL;
	}
	
	bool dfs (Graph<T>* g,unsigned int node_number,T data)
	{
		
		visited[node_number] = true;
		
		Node<T>* tempNode;
		tempNode = g->getDataListPointer ();
		// cout<<"In node number "<<node_number<<"\t Data he is "<<tempNode[node_number].getData ()<<"\n";
		
		if (tempNode[node_number].getData() == data)
			 //cout<<"Match....!!\n";
		if (tempNode[node_number].getData() == data)
			return true;

		std::list<Edge>* tempList = g->getConnectionListPointer ();
		for (std::list<Edge> :: iterator it = tempList[node_number].begin ();it!=tempList[node_number].end ();it++)
		{	
			// cout<<"candidate for false "<<it->to<<"\n";
			if (visited[it->to] == false)
			{
				if (dfs (g,it->to,data)==false)
					continue;
				else
					return true;

			}
		}



	}
	
	bool dfs (Graph<T>* g,T data)
	{
		unsigned int numNodes = g->getNoOfNodes ();
		
		for (int i=0;i<numNodes;i++)
			visited[i] = false;
		dfs (g,0,data);
		
	}
};


int main ()
{
	Graph<int> g(7,true);
	
	g.addConnection (0,1);
	g.addConnection (0,2);
	g.addConnection (1,3);
	g.addConnection (2,3);
	g.addConnection (2,5);
	g.addConnection (3,4);
	g.addConnection (3,5);
	g.addConnection (4,6);
	g.addConnection (5,6);

	g.printGraph ();
	
	for (int i=0;i<7;i++)
		g.addData (i,10*i);

	GraphAlgorithm<int> ga(7);

	if (ga.dfs (&g,10) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";
	if (ga.dfs (&g,7) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";
	if (ga.dfs (&g,30) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";	

	if (ga.dfs (&g,20) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";	
	return 0;
}
	
