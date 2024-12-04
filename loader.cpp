#include "loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <algorithm>

// Function to parse a line from the CSV file and extract data fields
void parseCSVLine(const std::string& line, std::vector<std::string>& data) {
    // Regular expression to handle CSV parsing with quoted fields
    std::regex csvRegex(R"((\"[^\"]*(\"{2})*[^\"]*\")|[^,]+)");
    std::sregex_iterator it(line.begin(), line.end(), csvRegex);
    std::sregex_iterator end;
    while (it != end) {
        std::string match = (*it).str();
        // Remove leading comma if present
        if (!match.empty() && match[0] == ',') {
            match = match.substr(1);
        }
        // Remove enclosing quotes, if any
        if (!match.empty() && match[0] == '"' && match.back() == '"') {
            match = match.substr(1, match.size() - 2);
            // Replace double quotes with single quotes
            size_t pos = 0;
            while ((pos = match.find("\"\"", pos)) != std::string::npos) {
                match.replace(pos, 2, "\"");
                pos += 1;
            }
        }
        // Trim whitespace
        match.erase(0, match.find_first_not_of(" \t\n\r\f\v"));
        match.erase(match.find_last_not_of(" \t\n\r\f\v") + 1);
        // Remove non-printable characters
        match.erase(std::remove_if(match.begin(), match.end(), [](char c) {
            return !std::isprint(static_cast<unsigned char>(c));
            }), match.end());
        data.push_back(match);
        ++it;
    }
}

// Function to load data from the CSV file and populate data structures
void loadData(const std::string& filename, Trie& nameTrie, Trie& customerIDTrie, Trie& phoneTrie, std::vector<Customer*>& allCustomers) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    getline(file, line); // Skip header line
    int lineNumber = 1;
    int loadedCustomers = 0;

    while (getline(file, line)) {
        lineNumber++;
        std::vector<std::string> data;
        parseCSVLine(line, data);
        if (data.size() < 8) {
            // Handle incomplete data
            std::cerr << "Warning: Incomplete data at line " << lineNumber << std::endl;
            continue;
        }
        // Create a new Customer object
        Customer* customer = new Customer(data);
        allCustomers.push_back(customer);
        // Insert into hash tables
        insertIntoHashTables(customer);
        // Insert into Tries
        nameTrie.insert(customer->name, customer);
        customerIDTrie.insert(customer->customerID, customer);
        phoneTrie.insert(customer->phoneNumber, customer);
        loadedCustomers++;
    }
    file.close();
    std::cout << "Total customers loaded: " << loadedCustomers << std::endl;
}