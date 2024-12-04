#include "customer.h"
#include <cstdlib> // For std::atoi

// Constructor to initialize a Customer object from a vector of strings
Customer::Customer(const std::vector<std::string>& data) {
    name = data[0];                   // Name
    customerID = data[1];             // CustomerID
    phoneNumber = data[2];            // PhoneNumber
    age = std::atoi(data[3].c_str()); // Age (converted from string to integer)
    birthdate = data[4];              // Birthdate
    gender = data[5];                 // Gender
    primaryStore = data[6];           // PrimaryStore
    purchaseHistory = data[7];        // PurchaseHistory
}