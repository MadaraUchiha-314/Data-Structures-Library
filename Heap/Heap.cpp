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

int main ()
{
	int a[7] = {1,5,3,4,7,8,2};

	make_heap (&a[0],&a[6]);

	for (int i=0;i<7;i++)
		std::cout<<a[i]<<"\t";
	
	std::cout<<"\n";

	return 0;
}

