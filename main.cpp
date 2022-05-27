#include "vector_sort.h"

int main()
{
	// get vector length
	int num_attributes = 0;

	std::cout << "\n Enter the number of attributes per vector: ";

	if (!(std::cin >> num_attributes))
	{
		std::cout << "\n Enter a number next time." << std::endl;

		return 0;
	}

	// get max attributes and create maximum vector
	std::vector<int> max_vector;
	int* kv_attributes = new int[num_attributes];
	int num_vectors = 1;

	for (int i = 0; i < num_attributes; i++)
	{
		std::cout << "\n Enter the k-value for attribute " << i;

		if (!(std::cin >> kv_attributes[i]))
		{
			std::cout << "\n Enter a number next time." << std::endl;

			return 0;
		}

		max_vector.push_back(kv_attributes[i] - 1);
		num_vectors *= kv_attributes[i];
	}

	// list of all vectors
	std::vector<std::vector<int>> all_vectors(num_vectors);
	all_vectors.push_back(max_vector);

	// calculate all vectors
	calculate_all_vectors(max_vector, max_vector.size() - 1, all_vectors);

	std::cout << "\n Created " << all_vectors.size() << " vectors." << std::endl;

	int max_hamming_norm = 0;

	for (int i = 0; i < num_attributes; i++)
	{
		max_hamming_norm += kv_attributes[i] - 1;
	}

	// sort vectors
	std::vector<std::vector<std::vector<int>>> sorted_vectors(max_hamming_norm);
	group_by_hamming_norm(sorted_vectors, all_vectors);
	sort_vectors_in_hamming_norm(sorted_vectors);
	print_sorted_vectors(sorted_vectors);

	return 0;
}