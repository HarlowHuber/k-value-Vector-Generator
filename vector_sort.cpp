#include "vector_sort.h"

// caluclate all vectors below the given max_vector
void calculate_all_vectors(std::vector<int> max_vector, int max_vector_index, std::vector<std::vector<int>>& all_vectors)
{
	for (int i = max_vector_index; i >= 0 ; i--)
	{
		int value = max_vector[i];
		int decrement = 1;

		while (value > 0)
		{
			std::vector<int> copy_max_vector(max_vector);
			copy_max_vector[i] -= decrement;
			value = copy_max_vector[i];
			decrement++;
			all_vectors.push_back(copy_max_vector);

			if (i > 0 && copy_max_vector[0] > 1) calculate_all_vectors(copy_max_vector, i - 1, all_vectors);
		}
	}
}

// print a list of vectors
void print_vectors(std::vector<std::vector<int>>& all_vectors)
{
	for (std::vector vector : all_vectors)
	{
		for (int i : vector)
		{
			std::cout << i;
		}

		std::cout << std::endl;
	}
}

// group vectors by hamming norm
void group_by_hamming_norm(std::vector<std::vector<std::vector<int>>>& sorted_vectors, std::vector<std::vector<int>> unsorted_vectors)
{
	for (std::vector vector : unsorted_vectors)
	{
		int hamming_norm = 0;

		for (int i : vector)
		{
			hamming_norm += i;
		}

		sorted_vectors[hamming_norm].push_back(vector);
	}
}

// print a list of vectors grouped by Hamming norm
void print_sorted_vectors(std::vector<std::vector<std::vector<int>>> sorted_vectors)
{
	for (int i = 0; i < sorted_vectors.size(); i++)
	{
		print_vectors(sorted_vectors[i]);
		std::cout << "\tHamming norm: " << i << std::endl << std::endl;
	}
}

// heap sort performed for each Hamming norm
void sort_vectors_in_hamming_norm(std::vector<std::vector<std::vector<int>>>& unsorted_vectors)
{
	for (std::vector hamming_norm : unsorted_vectors)
	{

	}
}

// heapify
void heapify(std::vector<std::vector<int>>& unsorted_vectors, int num_vectors, int index)
{
	int min_vector_index = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	// if left child is smaller than root


	// if right child is smaller than minimum


	// if smallest is not root
	if (min_vector_index != index)
	{
		// swap

		heapify(unsorted_vectors, num_vectors, min_vector_index);
	}
}

// overloaded operator for vector comparison
bool operator < (std::vector<int> lhs, std::vector<int> rhs)
{
	return false;
}

// swap two vectors
void swap()
{

}