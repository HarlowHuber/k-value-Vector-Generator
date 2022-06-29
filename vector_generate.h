#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

class vector_generate
{
private:
	// array of k-values for each attribute
	int* kv_attributes;

	// number of attributes
	int num_attributes;

	// calculate all vectors grouped by Hamming norm and sorted
	void calculate_all_vectors(std::vector<int> max_vector, int max_hamming_norm, int max_vector_index, std::vector<std::multimap<int, std::vector<int>, std::greater<int>>>& sorted_vectors);

	// calculate mixed base value of vector
	int calc_mb_value(std::vector<int> vector);

	// print a list of vectors grouped by Hamming norm
	void print_sorted_vectors(std::vector<std::multimap<int, std::vector<int>, std::greater<int>>> sorted_vectors);

	// print a list of vectors
	void print_vectors(std::multimap<int, std::vector<int>, std::greater<int>>& all_vectors);

public:
	// constructor
	vector_generate(int* _kv_attributes, int _num_attributes, bool print);

	// destructor
	~vector_generate();
};
