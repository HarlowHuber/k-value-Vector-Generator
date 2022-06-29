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

	int hamming_norm = 0;

	for (int a : max_vector)
	{
		hamming_norm += a;
	}

	std::vector<std::multimap<int, std::vector<int>, std::greater<int>>> mapped_vectors(static_cast<__int64>(hamming_norm) + 1);

	mapped_vectors[hamming_norm].insert(std::pair(calc_mb_value(max_vector), max_vector));

	// calculate all vectors
	calculate_all_vectors(max_vector, hamming_norm, num_attributes - 1, mapped_vectors);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "\n Program took " << duration.count() << " microseconds to generate vectors." << std::endl;

	if (print) print_sorted_vectors(mapped_vectors);
}

// destructor
vector_generate::~vector_generate()
{
	delete[] kv_attributes;
}

/*
 *	calculate all vectors below the given max_vector
 
	ALGORITHM:
	This algorithm calculates all possible vectors for a given MAXIMUM input vector. Therefore, if the input vectors
	have k-values of k = (3, 5, 2), the maximum input vector will be (2, 4, 1).
	The number of vectors that are generated will be the product of all k-values multiplied against each other.
	Therefore, using the last example, the number of vectors will be: 3 * 5 * 2 = 30.
*/
void vector_generate::calculate_all_vectors(std::vector<int> max_vector, int max_hamming_norm, int max_vector_index, std::vector<std::multimap<int, std::vector<int>, std::greater<int>>>& sorted_vectors)
{
	//int last_index = (int)max_vector.size() - 1;

	// iterate over every index starting from the given index
	for (int i = max_vector_index; i >= 0; i--)
	{
		int value = max_vector[i];
		int decrement = 1;

		// decrement the value at the specific index until it is 0
		// add the copied vector to the list of all vectors
		// then, recurse on the copied vector if the value is not the last value, 
		// and if the value at the last index is greater than 0
		while (value > 0)
		{
			std::vector<int> copy_vector(max_vector);
			copy_vector[i] -= decrement;
			int hamming_norm = max_hamming_norm - decrement;
			value = copy_vector[i];
			decrement++;

			// insert copy vector into sorted_vectors by looping over possible vectors with the same mixed-base value
			// then, insert based on what vector has higher order elements or greater higher order elements
			int key = calc_mb_value(copy_vector);
			auto it1 = sorted_vectors[hamming_norm].equal_range(key); // pair of two iterators; first points at before the range of the key; second points to after
			bool higher_order = false;

			// iterate over every vector with the same key
			for (auto it2 = it1.first; it2 != it1.second && !higher_order; it2++)
			{
				// iterate over elements of the copy_vector and a vector with the same key
				// if copy_vector has greater elements, it is placed before the other vector
				for (int i = 0; i < num_attributes; i++)
				{
					if (it2->second[i] < copy_vector[i])
					{
						higher_order = true;
						sorted_vectors[hamming_norm].emplace_hint(it2, std::pair<int, std::vector<int>>(key, copy_vector)); // inserts before the vector that it2 points to
						break;
					}
					else if (it2->second[i] > copy_vector[i]) break;
				}
			}
			
			// insert at the end of the vectors with the same key (mixed-base value) if it is smaller
			if (!higher_order) sorted_vectors[hamming_norm].emplace_hint(it1.second, key, copy_vector);

			if (i > 0)
			{
				calculate_all_vectors(copy_vector, hamming_norm, i - 1, sorted_vectors); // 
			}
		}
	}
}

// calculate mixed base value
int vector_generate::calc_mb_value(std::vector<int> vector)
{
	int vector_value = 0;

	for (int i = 0; i < num_attributes; i++)
	{
		vector_value += vector[i] * std::pow(kv_attributes[i], num_attributes - i - 1);
	}

	return vector_value;
}

// print all sorted vectors
void vector_generate::print_sorted_vectors(std::vector<std::multimap<int, std::vector<int>, std::greater<int>>> sorted_vectors)
{
	for (int i = (int)sorted_vectors.size() - 1; i >= 0; i--)
	{
		std::cout << "\n Hamming norm: " << i << std::endl;
		print_vectors(sorted_vectors[i]);
	}
}

// print a list of vectors
void vector_generate::print_vectors(std::multimap<int, std::vector<int>, std::greater<int>>& all_vectors)
{
	for (auto [key, vector] : all_vectors)
	{
		std::cout << "\tVector: ";

		for (int i : vector)
		{
			std::cout << i << ",";
		}

		std::cout << "\tValue: " << key << std::endl;
	}
}
