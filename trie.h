#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include "customer.h"

// Class representing a node in the Trie
class TrieNode {
public:
    bool isEndOfWord; // Indicates if the node represents the end of a word
    std::unordered_map<char, TrieNode*> children; // Map of child nodes
    std::vector<Customer*> customers; // Customers associated with this node

    TrieNode() : isEndOfWord(false) {}
};

// Class representing the Trie data structure
class Trie {
public:
    TrieNode* root; // Root node of the Trie

    Trie();
    // Function to insert a key and associate it with a customer
    void insert(const std::string& key, Customer* customer);
    // Function to search for customers based on a prefix
    std::vector<Customer*> search(const std::string& prefix, size_t maxResults = 25);
};

#endif // TRIE_H