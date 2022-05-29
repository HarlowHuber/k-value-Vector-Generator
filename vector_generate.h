#include <stdio.h>
#include <vector>
#include <iostream>

class vector_generate
{
private:
	// array of k-values for each attribute
	int* kv_attributes;

	// number of attributes
	int num_attributes;

	// caluclate all vectors below the given max_vector
	void calculate_all_vectors(std::vector<int> max_vector, int max_vector_index, std::vector<std::vector<int>>& all_vectors);

	// group vectors by hamming norm
	void group_by_hamming_norm(std::vector<std::vector<std::vector<int>>>& sorted_vectors, std::vector<std::vector<int>> unsorted_vectors);

	// heap sort performed for each Hamming norm
	void sort_vectors_in_hamming_norm(std::vector<std::vector<std::vector<int>>>& unsorted_vectors);

	// heap sort 
	void heapSort(std::vector<std::vector<int>>& unsorted_vectors, int heap_size);

	// heapify
	void heapify(std::vector<std::vector<int>>& unsorted_vectors, int num_vectors, int index);

	// swap two vectors
	void swap(std::vector<std::vector<int>>& unsorted_vectors, int min_child_index, int root_index);

	// overloaded operator for vector comparison
	bool compare(std::vector<int> left_vector, std::vector<int> rhs);

	// print a list of vectors grouped by Hamming norm
	void print_sorted_vectors(std::vector<std::vector<std::vector<int>>> sorted_vectors);

	// print a list of vectors
	void print_vectors(std::vector<std::vector<int>>& all_vectors);

public:
	// constructor
	vector_generate(int* _kv_attributes, int num_attributes, bool print);

	// destructor
	~vector_generate();
};
