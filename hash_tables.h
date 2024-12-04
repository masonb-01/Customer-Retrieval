#ifndef HASH_TABLES_H
#define HASH_TABLES_H

#include "customer.h"
#include <unordered_map>

// Global hash tables to store mappings from CustomerID and PhoneNumber to Customer objects
extern std::unordered_map<std::string, Customer*> customerIDMap;
extern std::unordered_map<std::string, Customer*> phoneMap;

// Function to insert a customer into the hash tables
void insertIntoHashTables(Customer* customer);

#endif // HASH_TABLES_H