#include <stdio.h>
#include <vector>
#include <iostream>

// caluclate all vectors below the given max_vector
void calculate_all_vectors(std::vector<int> max_vector, int max_vector_index, std::vector<std::vector<int>>& all_vectors);

// print a list of vectors
void print_vectors(std::vector<std::vector<int>>& all_vectors);

// group vectors by hamming norm
void group_by_hamming_norm(std::vector<std::vector<std::vector<int>>>& sorted_vectors, std::vector<std::vector<int>> unsorted_vectors);

// print a list of vectors grouped by Hamming norm
void print_sorted_vectors(std::vector<std::vector<std::vector<int>>> sorted_vectors);

// heap sort performed for each Hamming norm
void sort_vectors_in_hamming_norm(std::vector<std::vector<std::vector<int>>>& unsorted_vectors);

// heapify
void heapify(std::vector<std::vector<int>>& unsorted_vectors, int num_vectors, int index);

// overloaded operator for vector comparison
bool operator < (std::vector<int> lhs, std::vector<int> rhs);

// swap two vectors
void swap();
