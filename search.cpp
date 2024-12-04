#include "search.h"
#include <algorithm>
#include <cctype>

// Search for a customer by exact Customer ID using the hash table
Customer* searchByCustomerIDExact(const std::string& customerID) {
    auto it = customerIDMap.find(customerID);
    if (it != customerIDMap.end())
        return it->second;
    return nullptr;
}

// Search for customers by partial Customer ID using the Trie
std::vector<Customer*> searchByCustomerIDPartial(const std::string& customerIDPrefix, Trie& customerIDTrie) {
    return customerIDTrie.search(customerIDPrefix, 25); // Limit to 25 results
}

// Search for a customer by exact Phone Number using the hash table
Customer* searchByPhoneNumberExact(const std::string& phoneNumber) {
    auto it = phoneMap.find(phoneNumber);
    if (it != phoneMap.end())
        return it->second;
    return nullptr;
}

// Search for customers by partial Phone Number using the Trie
std::vector<Customer*> searchByPhoneNumberPartial(const std::string& phonePrefix, Trie& phoneTrie) {
    return phoneTrie.search(phonePrefix, 25); // Limit to 25 results
}

// Search for customers by Name prefix using the Trie
std::vector<Customer*> searchByName(const std::string& namePrefix, Trie& nameTrie) {
    return nameTrie.search(namePrefix, 25); // Limit to 25 results
}

// Search for customers by exact Name using the Trie
std::vector<Customer*> searchByNameExact(const std::string& name, Trie& nameTrie) {
    TrieNode* node = nameTrie.root;
    std::string cleanedName = name;
    // Normalize the name
    std::transform(cleanedName.begin(), cleanedName.end(), cleanedName.begin(), ::tolower);
    // Remove leading whitespace
    cleanedName.erase(0, cleanedName.find_first_not_of(" \t\n\r\f\v"));
    // Remove non-printable characters
    cleanedName.erase(std::remove_if(cleanedName.begin(), cleanedName.end(), [](char c) {
        return !std::isprint(static_cast<unsigned char>(c));
        }), cleanedName.end());

    // Traverse the Trie based on the cleaned name
    for (char c : cleanedName) {
        if (!node->children[c])
            return {}; // No match found
        node = node->children[c];
    }
    // Check if this node represents the end of a word (exact match)
    if (node->isEndOfWord && !node->customers.empty()) {
        return node->customers;
    }
    else {
        return {};
    }
}