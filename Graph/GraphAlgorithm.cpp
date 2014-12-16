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
 * These will take years to impelement, but lets give it a start already
 */

 /*
 * The GraphAlgoritm's object will have to be made to use the algorithms.
 */

#include "Graph.h"
#include <queue>

using namespace std;

template <class T>
class GraphAlgorithm
{
	bool* visited;

	bool dfsHelper (Graph<T>* g,unsigned int node_number,T data)
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
				if (dfsHelper (g,it->to,data)==false)
					continue;
				else
					return true;

			}
		}


	}
	
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
	
	bool dfs(Graph<T>* g,unsigned int node_number,T data)
	{

		unsigned int numNodes = g->getNoOfNodes ();
		
		for (int i=0;i<numNodes;i++)
			visited[i] = false;
		return dfsHelper (g,node_number,data);
	}
	bool dfs (Graph<T>* g,T data)
	{
		
		unsigned int numNodes = g->getNoOfNodes ();
		
		for (int i=0;i<numNodes;i++)
			visited[i] = false;
		return dfsHelper (g,0,data);
	}
	bool existsPath (Graph<T>* g, unsigned int from,unsigned int to)
	{
		Node<T>* tempNode = g->getDataListPointer ();
		return dfs (g,from,tempNode[to].getData ());
	}
	
	bool bfs (Graph<T>* g,unsigned int node_number,T data)
	{
		unsigned int numNodes = g->getNoOfNodes ();
		Node<T> *tempNode = g->getDataListPointer ();
		std::list<Edge>* tempList = g->getConnectionListPointer ();


		for (int i=0;i<numNodes;i++)
			visited[i] = false;
		std::queue<unsigned int> q;
		q.push (node_number);

		while (q.size () > 0)
		{
			unsigned int temp = q.front ();
			q.pop ();
			if (tempNode[temp].getData () == data)
				return true;
			else
			{
				for (std::list<Edge>::iterator it = tempList[temp].begin ();it!=tempList[temp].end ();it++)
				{
					if (visited[it->to] == false)
						q.push (it->to);
				}
			}
		}

		return false;
	}

	bool bfs (Graph<T>* g,T data)
	{
		return bfs (g,0,data);
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

	/*
	* Testingwhether graph has been made properly
	*/ 
	g.printGraph ();
	
	/* 
	* Adding Some Data To The Graph
	*/
	for (int i=0;i<7;i++)
		g.addData (i,10*i);

	/* 
	* Making an algorithm object
	*/
	GraphAlgorithm<int> ga(7);

	/* 
	* Testing DFS
	*/

	/*
	* Test Case -1
	*/
	if (ga.dfs (&g,10) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";

	/*
	* Test Case -2
	*/

	if (ga.dfs (&g,7) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";

	/*
	* Test Case -3
	*/

	if (ga.dfs (&g,30) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";	

	/*
	* Test Case -4
	*/

	if (ga.dfs (&g,20) == true)
		std::cout<<"Got it by dfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"DFS OVER \n";


	/*
	* Testing existsPath ()
	*/
	cout<<ga.existsPath (&g,2,6)<<"\n";
	cout<<ga.existsPath (&g,6,2)<<"\n";
	cout<<ga.existsPath (&g,4,3)<<"\n";



	/*
	*  Testing BFS
	*/
	
	/*
	* Test Case -1
	*/

	if (ga.bfs (&g,10) == true)
		std::cout<<"Got it by bfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"BFS OVER \n";

	/*
	* Test Case -2
	*/

	if (ga.bfs (&g,7) == true)
		std::cout<<"Got it by bfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"BFS OVER \n";

	/*
	* Test Case -3
	*/
	
	if (ga.bfs (&g,30) == true)
		std::cout<<"Got it by bfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"BFS OVER \n";
	
	/*
	* Test Case -4
	*/

	if (ga.bfs (&g,20) == true)
		std::cout<<"Got it by bfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"BFS OVER \n";

	/*
	* Test Case -5
	*/

	if (ga.bfs (&g,60) == true)
		std::cout<<"Got it by bfs ..!! \n";
	else
		cout<<"Dint Get :( \n";
	cout<<"BFS OVER \n";


	
	return 0;
}
	
