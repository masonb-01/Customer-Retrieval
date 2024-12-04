#include "hash_tables.h"

// Definition of global hash tables
std::unordered_map<std::string, Customer*> customerIDMap;
std::unordered_map<std::string, Customer*> phoneMap;

// Function to insert a customer into the hash tables
void insertIntoHashTables(Customer* customer) {
    customerIDMap[customer->customerID] = customer;
    phoneMap[customer->phoneNumber] = customer;
}