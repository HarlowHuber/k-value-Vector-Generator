#include "vector_generate.h"
#include <chrono>

// constructor
vector_generate::vector_generate(int* _kv_attributes, int _num_attributes, bool print)
{
	auto start = std::chrono::high_resolution_clock::now();
	kv_attributes = _kv_attributes;
	num_attributes = _num_attributes;
	std::vector<int> max_vector(num_attributes);
	
	// construct maximum vector
	for (int i = 0; i < num_attributes; i++)
	{
		max_vector[i] = kv_attributes[i] - 1;
	}

	// list of all vectors
	std::vector<std::vector<int>> all_vectors;
	all_vectors.push_back(max_vector);

	// calculate all vectors
	calculate_all_vectors(max_vector, 0, all_vectors);

	std::cout << "\n Created " << all_vectors.size() << " vectors." << std::endl;

	// calculate the maximum Hamming norm
	int max_hamming_norm = 0;

	for (int i = 0; i < num_attributes; i++)
	{
		max_hamming_norm += kv_attributes[i] - 1;
	}

	// sort vectors
	std::vector<std::vector<std::vector<int>>> sorted_vectors(static_cast<__int64>(max_hamming_norm) + 1);

	group_by_hamming_norm(sorted_vectors, all_vectors);
	sort_vectors_in_hamming_norm(sorted_vectors);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "\n Program took " << duration.count() << " microseconds to run." << std::endl;

	if (print) print_sorted_vectors(sorted_vectors);
}

// destructor
vector_generate::~vector_generate()
{
	delete[] kv_attributes;
}

// calculate all vectors below the given max_vector
void vector_generate::calculate_all_vectors(std::vector<int> max_vector, int max_vector_index, std::vector<std::vector<int>>& all_vectors)
{
	int last_index = (int)max_vector.size() - 1;

	for (int i = max_vector_index; i <= last_index; i++)
	{
		int value = max_vector[i];
		int decrement = 1;

		while (value > 0)
		{
			std::vector<int> copy_vector(max_vector);
			copy_vector[i] -= decrement;
			value = copy_vector[i];
			decrement++;
			all_vectors.push_back(copy_vector);

			if (i < last_index && copy_vector[last_index] > 0)
			{
				calculate_all_vectors(copy_vector, i + 1, all_vectors);
			}
		}
	}
}

// group vectors by hamming norm
void vector_generate::group_by_hamming_norm(std::vector<std::vector<std::vector<int>>>& sorted_vectors, std::vector<std::vector<int>> unsorted_vectors)
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

// heap sort performed for each Hamming norm
void vector_generate::sort_vectors_in_hamming_norm(std::vector<std::vector<std::vector<int>>>& unsorted_vectors)
{
	for (auto& hamming_norm : unsorted_vectors)
	{
		heapSort(hamming_norm, (int)hamming_norm.size());
	}
}

// heap sort with minimum heap
void vector_generate::heapSort(std::vector<std::vector<int>>& unsorted_vectors, int heap_size)
{
	// build heap
	for (int root = heap_size / 2 - 1; root >= 0; root--)
	{
		heapify(unsorted_vectors, heap_size, root);
	}

	// extract elements from heap
	for (int i = heap_size - 1; i >= 0; i--)
	{
		swap(unsorted_vectors, 0, i);		// move current root to end
		heapify(unsorted_vectors, i, 0);	// heapify the reduced heap
	}
}

// heapify
void vector_generate::heapify(std::vector<std::vector<int>>& unsorted_vectors, int heap_size, int root_index)
{
	int min_child_index = root_index;	
	int left_child_index = 2 * root_index + 1;
	int right_child_index = 2 * root_index + 2;

	// if left child is smaller than minimum
	if (left_child_index < heap_size && compare(unsorted_vectors[left_child_index], unsorted_vectors[min_child_index]))
	{
		min_child_index = left_child_index;
	}

	// if right child is smaller than minimum
	if (right_child_index < heap_size && compare(unsorted_vectors[right_child_index], unsorted_vectors[min_child_index]))
	{
		min_child_index = right_child_index;
	}

	//	if smallest is not root
	//		swap min child and root
	//		heapify new subtree
	if (min_child_index != root_index)
	{
		swap(unsorted_vectors, min_child_index, root_index);
		heapify(unsorted_vectors, heap_size, min_child_index); 
	}
}

// swap two vectors
void vector_generate::swap(std::vector<std::vector<int>>& unsorted_vectors, int min_child_index, int root_index)
{
	std::vector<int> temp = unsorted_vectors[min_child_index];
	unsorted_vectors[min_child_index] = unsorted_vectors[root_index];
	unsorted_vectors[root_index] = temp;
}

// overloaded operator for vector comparison within the same Hamming norm
// return true if left vector is smaller than right vector
bool vector_generate::compare(std::vector<int> left_vector, std::vector<int> right_vector)
{
	int left_vector_value = 0;
	int right_vector_value = 0;

	// calculate decimal value
	for (int i = 0; i < num_attributes; i++)
	{
		int base = std::pow(kv_attributes[i], num_attributes - i - 1);
		left_vector_value += left_vector[i] * base;
		right_vector_value += right_vector[i] * base;
	}

	if (left_vector_value < right_vector_value) return true;
	else return false;
}

// print a list of vectors grouped by Hamming norm
void vector_generate::print_sorted_vectors(std::vector<std::vector<std::vector<int>>> sorted_vectors)
{
	for (int i = (int)sorted_vectors.size() - 1; i >= 0; i--)
	{
		std::cout << "\n Hamming norm: " << i << std::endl;
		print_vectors(sorted_vectors[i]);
	}
}

// print a list of vectors
void vector_generate::print_vectors(std::vector<std::vector<int>>& all_vectors)
{
	for (std::vector vector : all_vectors)
	{
		std::cout << " ";

		for (int i : vector)
		{
			std::cout << i;
		}

		std::cout << std::endl;
	}
}
