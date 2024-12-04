#include "trie.h"
#include <queue>
#include <cctype>
#include <algorithm>

// Constructor to initialize the Trie
Trie::Trie() {
    root = new TrieNode();
}

// Function to insert a key (e.g., name) and associate it with a customer
void Trie::insert(const std::string& key, Customer* customer) {
    TrieNode* node = root;
    std::string cleanedKey = key;
    // Convert to lowercase
    std::transform(cleanedKey.begin(), cleanedKey.end(), cleanedKey.begin(), ::tolower);
    // Remove leading whitespace
    cleanedKey.erase(0, cleanedKey.find_first_not_of(" \t\n\r\f\v"));
    // Remove non-printable characters
    cleanedKey.erase(std::remove_if(cleanedKey.begin(), cleanedKey.end(), [](char c) {
        return !std::isprint(static_cast<unsigned char>(c));
        }), cleanedKey.end());
    // Traverse or build the Trie
    for (char c : cleanedKey) {
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
    }
    // Mark the end of a word and store the customer
    node->isEndOfWord = true;
    node->customers.push_back(customer);
}

// Function to search for customers based on a prefix
std::vector<Customer*> Trie::search(const std::string& prefix, size_t maxResults) {
    TrieNode* node = root;
    std::string cleanedPrefix = prefix;
    // Convert to lowercase
    std::transform(cleanedPrefix.begin(), cleanedPrefix.end(), cleanedPrefix.begin(), ::tolower);
    // Remove leading whitespace
    cleanedPrefix.erase(0, cleanedPrefix.find_first_not_of(" \t\n\r\f\v"));
    // Remove non-printable characters
    cleanedPrefix.erase(std::remove_if(cleanedPrefix.begin(), cleanedPrefix.end(), [](char c) {
        return !std::isprint(static_cast<unsigned char>(c));
        }), cleanedPrefix.end());
    // Traverse the Trie based on the prefix
    for (char c : cleanedPrefix) {
        if (!node->children[c])
            return {}; // No matches found
        node = node->children[c];
    }
    // Perform BFS to collect customers under this prefix
    std::vector<Customer*> results;
    std::queue<TrieNode*> queue;
    queue.push(node);

    while (!queue.empty() && results.size() < maxResults) {
        TrieNode* current = queue.front();
        queue.pop();
        if (current->isEndOfWord) {
            // Add customers associated with this node
            results.insert(results.end(), current->customers.begin(), current->customers.end());
        }
        // Enqueue child nodes
        for (auto& child : current->children) {
            queue.push(child.second);
        }
    }
    return results;
}