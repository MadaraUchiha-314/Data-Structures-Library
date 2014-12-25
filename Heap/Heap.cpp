/*
 * Heap Library
 * No container is associated with this library
 * The user has to provide a container with a random-access iterator for the algorithms to work
 * The implemented algorithms are :
 * 1. make_heap
 * 2. push_heap
 * 3. pop_heap
 * 4. sort_heap
 */

#include <iostream>
#include <utility>
#include <functional>

template <class RandomAccessIterator>
void swap (RandomAccessIterator first,int index1,int index2)
{
	RandomAccessIterator a = first + index1;
	RandomAccessIterator b = first + index2;

    auto temp(std::move(*a));
    *a = std::move(*b);
    *b = std::move(temp);
	

}

template <class RandomAccessIterator>
void make_heap (RandomAccessIterator first,RandomAccessIterator last)
{

	int num_ele = (last - first) + 1;
	for (int i=num_ele-1;i>=1;i--)
	{
		if (first[i] < first[(i-1)/2])
		{
			/*
			* Swap Function becomes a little complicated here.
			*/
			swap (first,i,(i-1)/2);

			int k = i;

			while ( ( (first[k] >= first[2*k + 1]) && ((2*k+1)<num_ele) ) || ( (first[k] >= first[2*k + 2]) && ((2*k+2)<num_ele) ) )
			{
				if ((first[k] >= first[2*k + 1]))
				{
					swap (first,k,(2*k + 1));
					k = 2*k + 1;
				}
				else 
				{
					swap (first,k,(2*k + 2));
					k = 2*k + 2;
				}
			}

		}
	}
	
	
}


template <class RandomAccessIterator,typename Compare>
void make_heap (RandomAccessIterator first,RandomAccessIterator last,Compare comp)
{

	int num_ele = (last - first) + 1;
	for (int i=num_ele-1;i>=1;i--)
	{
		if (comp (first[i],first[(i-1)/2]))
		{
			/*
			* Swap Function becomes a little complicated here.
			*/
			swap (first,i,(i-1)/2);

			int k = i;

			while ( ( (!comp (first[k],first[2*k+1]) && ((2*k+1)<num_ele) ) ) || ( (!comp (first[k],first[2*k+2]) && ((2*k+2)<num_ele) ) ) )
			{
				if (!(comp (first[k],first[2*k+1])))
				{
					swap (first,k,(2*k + 1));
					k = 2*k + 1;
				}
				else 
				{
					swap (first,k,(2*k + 2));
					k = 2*k + 2;
				}
			}

		}
	}
	
	
}


template <class RandomAccessIterator>
void push_heap (RandomAccessIterator first,RandomAccessIterator last)
{
	make_heap (first,last);
}

template <class RandomAccessIterator,typename Compare>
void push_heap (RandomAccessIterator first,RandomAccessIterator last,Compare comp)
{
	make_heap (first,last,comp);
}


int main ()
{
	int a[8] = {1,5,3,4,7,8,2,6};

	make_heap (&a[0],&a[6]);

	for (int i=0;i<7;i++)
		std::cout<<a[i]<<"\t";
	
	std::cout<<"\n";

	push_heap (&a[0],&a[7]);

	for (int i=0;i<8;i++)
		std::cout<<a[i]<<"\t";
	
	std::cout<<"\n";




	int b[7] = {7,6,5,4,3,2,1};

	make_heap (&b[0],&b[6],std::less<int> ());

	for (int i=0;i<7;i++)
		std::cout<<b[i]<<"\t";
	
	std::cout<<"\n";



	return 0;
}

