#include <iostream>
#include <cstring>

/*
* Segment Tree
* An Abstract Function Will Be Defined Which Can Be Modified Later
*/

template <class T>
class SegmentTree
{
	T *tree;
	T *lazy;
	int size;

	public :

	/*
	* Best To Allocate The Memory While Making The Object Itself
	*/

	SegmentTree (int N)
	{
		/*
		* N Is The Number Of Elements In The Array
		* Maximum Size Of A Segment Tree Of Size N = 4*N
		*/

		tree = new T[4*N];
		lazy = new T[4*N];

		memset(lazy, 0, sizeof lazy);

		size = N;

	}

	~SegmentTree ()
	{
		delete[] tree;
		delete[] lazy;
	}

	private :

	/*
	* This Function Builds A Segment Tree From A Generic Array
	* T *array is the Pointer To The Actual Data Array
	* tree_index is the Position In The Tree Array Where The Node/Info. Abt The Nodes Will Be Placed
	*/
	template <typename Func>
	void build_tree (int tree_index,int L,int R,T* array,Func f)
	{
		/*
		* Case Where It Is Out Of Range
		*/
		if (L > R)
			return;

		/*
		* We Are Inserting A Leaf Node
		*/
		if (L == R)
		{
			tree[tree_index] = array[L];

			return;
		}

		/*
		* Recursively Build The Left Half And The Right Half
		*/
		build_tree (tree_index*2,L,(L+R)/2,array,f);
		build_tree ((tree_index*2)+1,((L+R)/2)+1,R,array,f);
		
		/*
		* After Completing Building The Left And Right Subtree Build The Current Node
		*/

		tree[tree_index] = f(tree[tree_index*2],tree[(tree_index*2)+1]);

		
	}

	/*
	* This Is The Update Where We Assign A Value To L and R
	* Same Function Can Be Modified To Add,Multiply etc. 
	*/
	template <typename Func>
	void update_tree (int tree_index,int curr_L,int curr_R,int L,int R,T value,Func f)
	{

		if (lazy[tree_index] != 0)
		{
			tree[tree_index] += lazy[tree_index];

			if (curr_L != curr_R)
			{
				lazy[tree_index*2] += lazy[tree_index];
				lazy[(tree_index*2)+1] += lazy[tree_index];
			}

			lazy[tree_index] = 0;
		}

		/*
		* Out Of Bounds Condition
		*/

		if ((curr_L > curr_R) || (curr_L > R) || (curr_R < L))
			return;

		/*
		* Fully Within Range
		*/

		if ((curr_L >= L) && (curr_R <= R))
		{
			tree[tree_index] += value;

			/*
			* Case When Its Not A Leaf Node
			*/

			if (curr_L != curr_R)
			{
				lazy[tree_index*2] += value;
				lazy[(tree_index*2)+1] += value;
			}

			return;


		}

		/*
		* Recursively Update The Left Half And The Right Half
		*/

		update_tree (tree_index*2,curr_L,(curr_L+curr_R)/2,L,R,value,f);
		update_tree ((tree_index*2)+1,((curr_L+curr_R)/2)+1,curr_R,L,R,value,f);

		/*
		* After Completing Updating The Left And Right Subtree Update The Current Node
		*/

		tree[tree_index] = f(tree[tree_index*2],tree[(tree_index*2)+1]);

	}

	template <typename Func>
	T query_tree (int tree_index,int curr_L,int curr_R,int L,int R,Func f)
	{
		/*
		* Out Of Range Condition
		*/

		if ((curr_L > curr_R) || (curr_L > R) || (curr_R < L))
			return -1;


		if (lazy[tree_index] != 0)
		{
			tree[tree_index] += lazy[tree_index];

			if (curr_L != curr_R)
			{
				lazy[tree_index*2] += lazy[tree_index];
				lazy[(tree_index*2)+1] += lazy[tree_index];
			}


			lazy[tree_index] = 0;
		}



		if ((curr_L >= L) && (curr_R <= R))
		{
			return tree[tree_index];
		}

		T query_left = query_tree (tree_index*2,curr_L,(curr_L+curr_R)/2,L,R,f);

		T query_right = query_tree((tree_index*2)+1,((curr_L+curr_R)/2)+1,curr_R,L,R,f);

		T result = f(query_left,query_right);

		return result;

	}

	public :

	template <typename Func>
	T query_tree (int L,int R,Func f)
	{
		return query_tree(1,0,size-1,L,R,f);
	}

	template <typename Func>
	void update_tree (int L,int R,T value,Func f)
	{
		update_tree (1,0,size-1,L,R,value,f);
	}

	template <typename Func>
	void build_tree (T* array,Func f)
	{
		build_tree (1,0,size-1,array,f);
	}

};

int max (int a,int b)
{
	if (a>b)
		return a;
	else
		return b;
}

int main ()
{

	int array[20];
	SegmentTree<int> s(20);

	for (int i=0;i<20;i++)
		array[i] = 1;

	s.build_tree (array,max);

	s.update_tree (0,6,5,max);
	s.update_tree (7,10,12,max);
	s.update_tree (10,19,100,max);

	std::cout<<s.query_tree(0,19,max)<<"\n";

return 0;
}
