#ifndef LOADER_H
#define LOADER_H

#include "customer.h"
#include "hash_tables.h"
#include "trie.h"
#include <vector>

// Function to load data from a CSV file and populate data structures
void loadData(const std::string& filename, Trie& nameTrie, Trie& customerIDTrie, Trie& phoneTrie, std::vector<Customer*>& allCustomers);

#endif // LOADER_H