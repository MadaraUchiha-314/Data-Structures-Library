/*
 * Graph Algorithm File
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
#include <limits>

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
		
		if (tempNode[node_number].getData() == data)
			return true;

		std::list<Edge>* tempList = g->getConnectionListPointer ();
		for (std::list<Edge> :: iterator it = tempList[node_number].begin ();it!=tempList[node_number].end ();it++)
		{	
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

	GraphAlgorithm ()
	{
		visited=NULL;
	}
	~GraphAlgorithm ()
	{
		if (visited!=NULL)
			delete[] visited;
	}
	
	bool dfs(Graph<T>* g,unsigned int node_number,T data)
	{
	
		unsigned int numNodes = g->getNoOfNodes ();
		visited = new bool[numNodes];	
		
		for (int i=0;i<numNodes;i++)
			visited[i] = false;

		bool result;

		result = dfsHelper (g,node_number,data);

		delete[] visited;
		visited=NULL;

		return result;
	}
	bool dfs (Graph<T>* g,T data)
	{
		
		unsigned int numNodes = g->getNoOfNodes ();
		visited = new bool[numNodes];
		bool result;
		
		for (int i=0;i<numNodes;i++)
			visited[i] = false;

		result = dfsHelper (g,0,data);

		delete[] visited;
		visited=NULL;

		return result;
	}
	bool existsPath (Graph<T>* g, unsigned int from,unsigned int to)
	{
		Node<T>* tempNode = g->getDataListPointer ();
		return dfs (g,from,tempNode[to].getData ());
	}
	
	bool bfs (Graph<T>* g,unsigned int node_number,T data)
	{
		unsigned int numNodes = g->getNoOfNodes ();
		Node<T>* tempNode = g->getDataListPointer ();
		std::list<Edge>* tempList = g->getConnectionListPointer ();
		
		visited = new bool[g->getNoOfNodes()];	

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

		delete[] visited;
		visited=NULL;
		return false;
	}

	bool bfs (Graph<T>* g,T data)
	{
		return bfs (g,0,data);
	}

	void findInDegreeOfNodes (Graph<T>* g,unsigned int *inDegree)
	{
		std::list<Edge>* tempList = g->getConnectionListPointer ();
		unsigned int numNodes =  g->getNoOfNodes ();

		for (unsigned int i=0;i<numNodes;i++)
			inDegree[i]=0;

		for (unsigned int i=0;i<numNodes;i++)
		{
			for (std::list<Edge>::iterator it=tempList[i].begin ();it!=tempList[i].end ();it++)
				inDegree[it->to]++;
		}
	}

	std::list<unsigned int>* topologicalSort (Graph<T>* g)
	{
		unsigned int numNodes = g->getNoOfNodes ();
		std::list<Edge>* tempList = g->getConnectionListPointer ();
		
		unsigned int* inDegree = new unsigned int[numNodes];
		std::list<unsigned int>* resultList = new std::list<unsigned int>;
		
		visited = new bool[numNodes];	
		queue<unsigned int> q;

		for (unsigned int i=0;i<numNodes;i++)
			visited[i]=false;

		findInDegreeOfNodes (g,inDegree);

		for (unsigned int i=0;i<numNodes;i++)
		{
			if (inDegree[i] == 0)
				q.push (i);
		}

		while (q.size () > 0)
		{ 
			unsigned int temp = q.front ();
			visited[temp]=true;
			
			resultList->push_back (temp);
			q.pop ();

			for (std::list<Edge>::iterator it = tempList[temp].begin();it!=tempList[temp].end();it++)
			{
				unsigned int temp2 = it->to;
				inDegree[temp2]--;
			}
			
			for (unsigned int i=0;i<numNodes;i++)
			{
				if (inDegree[i] == 0 && visited[i]==false)
				{
					q.push (i);
					visited[i]=true;
				}
			}
		}
		delete[] visited;
		visited=NULL;
		return resultList;
	}

	unsigned int shortestPath (Graph<T>* g,unsigned int from,unsigned int to)
	{
		unsigned int numNodes = g->getNoOfNodes ();
		std::list<Edge>* tempList = g->getConnectionListPointer ();
		
		unsigned int result;

		unsigned int  *shortestPath = new unsigned int[numNodes];
		visited = new bool[numNodes];
		
		for (unsigned int i=0;i<numNodes;i++)
		{
			shortestPath[i] = std::numeric_limits<unsigned int>::max();
			visited[i] = false;
		}

		visited[from] = true;
		shortestPath[from] = 0;
	
		bool loop_invariant = true;
		unsigned int current_node = from;
		
		while (loop_invariant)
		{
			loop_invariant = false;

			for (std::list<Edge>::iterator it=tempList[current_node].begin ();it!=tempList[current_node].end();it++)
			{
				if (shortestPath[it->to] > (shortestPath[current_node] + it->weight))
					shortestPath[it->to] = shortestPath[current_node] + it->weight;
			}

			visited[current_node] = true;
			unsigned int temp_min = std::numeric_limits<unsigned int>::max ();

			for (unsigned int i=0;i<numNodes;i++)
			{
				if ((shortestPath[i] < temp_min) && visited[i] == false)
				{
					current_node = i;
					temp_min = shortestPath[i];
					loop_invariant = true;
				}
			}
		}
		
		result = shortestPath[to];
	
		delete[] visited;
		delete[]shortestPath;
		visited = NULL;
		
		return result;
	
	}




};


int main ()
{
	Graph<int> g(7,true);
	Graph<int> g2(6);
	Graph<int> g3(4);
	Graph<int> g4(6);
	
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
	GraphAlgorithm<int> ga;

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
		std::list<unsigned int>* resultList = new std::list<unsigned int>;
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
	
	/*
	 * Testing Topological Sort 
	 */

	/*
	 * Test Case -1
	 */

	ga.topologicalSort (&g);

	/*
	 * Graph For test case -2
	 */
	g2.addConnection (0,1);
	g2.addConnection (0,2);
	g2.addConnection (1,3);
	g2.addConnection (2,1);
	g2.addConnection (2,3);
	g2.addConnection (2,4);
	g2.addConnection (3,4);
	g2.addConnection (3,5);
	g2.addConnection (4,5);
	
	/*
	 * Test Case -2
	 */

	std::list<unsigned int>* result;
	result = ga.topologicalSort (&g2);
	for (std::list<unsigned int>::iterator it=result->begin ();it!=result->end();it++)
		cout<<*it<<"-> ";
	cout<<"\n";


	/*
	 * Testing shortest path
	 */

	/*
	 * Graph For Test Case 1
	 */

	g3.addConnection (0,1,1);
	g3.addConnection (0,2,4);
	g3.addConnection (1,2,2);
	g3.addConnection (1,3,6);
	g3.addConnection (2,3,3);

	/*
	 * Test Case -1
	 */
	ga.shortestPath (&g3,0,3);
	ga.shortestPath (&g3,0,2);
	ga.shortestPath (&g3,1,3);

	/*
	 * Graph For Test Case 2
	 */
	
	g4.addConnection (0,1,4);
	g4.addConnection (0,2,1);
	g4.addConnection (0,3,1);
	g4.addConnection (1,2,2);
	g4.addConnection (1,5,1);
	g4.addConnection (2,1,2);
	g4.addConnection (2,5,4);
	g4.addConnection (2,4,3);
	g4.addConnection (3,2,4);
	g4.addConnection (3,4,2);
	g4.addConnection (4,5,1);

	cout<<"Shortest Path From 0 to 5 is "<<ga.shortestPath (&g4,0,5) <<"\n";

	return 0;
}
	
