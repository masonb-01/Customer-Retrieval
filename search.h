#ifndef SEARCH_H
#define SEARCH_H

#include "customer.h"
#include "hash_tables.h"
#include "trie.h"
#include <vector>

// Function declarations for searching customers

// Search by exact Customer ID using the hash table
Customer* searchByCustomerIDExact(const std::string& customerID);

// Search by partial Customer ID using the Trie
std::vector<Customer*> searchByCustomerIDPartial(const std::string& customerIDPrefix, Trie& customerIDTrie);

// Search by exact Phone Number using the hash table
Customer* searchByPhoneNumberExact(const std::string& phoneNumber);

// Search by partial Phone Number using the Trie
std::vector<Customer*> searchByPhoneNumberPartial(const std::string& phonePrefix, Trie& phoneTrie);

// Search by Name prefix using the Trie
std::vector<Customer*> searchByName(const std::string& namePrefix, Trie& nameTrie);

// Search by exact Name using the Trie
std::vector<Customer*> searchByNameExact(const std::string& name, Trie& nameTrie);

#endif // SEARCH_H