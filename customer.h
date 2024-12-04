#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

// Class representing a customer
class Customer {
public:
    std::string customerID;
    std::string name;
    std::string birthdate;
    int age;
    std::string gender;
    std::string phoneNumber;
    std::string purchaseHistory;
    std::string primaryStore;

    Customer() : age(0) {} // Default constructor initializes age to 0
    Customer(const std::vector<std::string>& data); // Constructor to initialize from data vector
};

#endif // CUSTOMER_H