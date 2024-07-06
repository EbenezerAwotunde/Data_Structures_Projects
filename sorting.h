#pragma once

#include <functional> // std::less
#include <iterator> // std::iterator_traits

namespace sort {

	// This is C++ magic which will allows our function
	// to default to using a < b if the comparator arg
	// is unspecified. It uses defines std::less<T>
	// for the iterator's value_type.
	//
	// For example: if you have a vector<float>, the 
	// iterator's value type will be float. std::less 
	// will select the < for sorting floats as the 
	// default comparator.
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept 
	{ 
		/* TODO */ 
		std::swap(a,b);
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// You may delete the types you don't use to remove the compiler warnings
		using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
		using value_type      = typename _it::value_type;
		using reference       = typename _it::reference;
		using pointer         = typename _it::pointer;

		// TODO
		/*for (int k = 1; k < n; k++) 
		{
			bool cont = false;
			for (int j = 0; j < n - k; j++)
				if (A[j+1] < A[j]) {
			int tmp = A[j]; // swap A[j] and A[j+1]
			A[j] = A[j+1];
			A[j+1] = tmp;
			cont = true;
			}
			if (!cont) break; // stop sorting
		}*/

		RandomIter index;
		RandomIter indexPlusOne;

		for(int i = 1; i < end - begin; i++)
		{
			bool cont = false; 
			for(int j = 0; j < end - begin - i; j++)
			{
				index = begin + j;
				indexPlusOne = index + 1; 
				if(comp(*indexPlusOne, *index)) //comp does a < b
				{
					swap(*index, *indexPlusOne);
					cont = true;
				}
			}
			if (!cont) break;
		}
		
		
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) 
	{ 
		/* TODO */ 
		/*for (int k = 1; k < n; k++ )	
		{
			int tmp = A[k];
			for(int j = k; j > 0 && tmp < A[j-1]; j--)
				A[j] = A[j-1];
			A[j] = tmp;
		}*/
		

		int size = end - begin;
		// Iterate through each element of the array starting from the second element
		for (int i = 1; i < size; ++i)
		{
			// Store the current element
			auto current = std::move(*(begin + i));
			
			// Find the correct position for the current element in the sorted subarray
			int j = i - 1;
			for (; j >= 0 && comp(current, *(begin + j)); --j)
			{
				// Shift elements to the right to make space for the current element
				*(begin + j + 1) = std::move(*(begin + j));
			}
			// Insert the current element into its correct position
			*(begin + j + 1) = std::move(current);
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) 
	{ 
		/* TODO */

		int size = end - begin;

		for(int k = 0; k < size - 1; k++)
		{
			RandomIter minIndex = begin + k;
			for(int i = k + 1; i < size; i++)
			{
				if(comp(*(begin + i), *minIndex))
					minIndex = begin + i;
			}
			std::swap(*minIndex, *(begin + k));
		}
	}
}
