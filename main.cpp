#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <stdexcept>
#include "loader.h"
#include "search.h"

// Color codes for console text using ANSI escape codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// Function to clear the console screen
void clearScreen() {
    // ANSI escape code to clear the screen and move the cursor to the top-left corner
    std::cout << "\033[2J\033[1;1H";
}

// Function to pause execution until the user presses Enter
void pause() {
    std::cout << "\nPress Enter to continue...";
    // Ignore any remaining input and wait for Enter key
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to display a single customer's information in a formatted style
void displayCustomerFormatted(Customer* customer) {
    if (customer) {
        // Display customer details with formatting and color
        std::cout << BLUE << "----------------------------------------" << RESET << std::endl;
        std::cout << std::left << std::setw(18) << "CustomerID:" << customer->customerID << std::endl;
        std::cout << std::left << std::setw(18) << "Name:" << customer->name << std::endl;
        std::cout << std::left << std::setw(18) << "Birthdate:" << customer->birthdate << std::endl;
        std::cout << std::left << std::setw(18) << "Age:" << customer->age << std::endl;
        std::cout << std::left << std::setw(18) << "Gender:" << customer->gender << std::endl;
        std::cout << std::left << std::setw(18) << "PhoneNumber:" << customer->phoneNumber << std::endl;
        std::cout << std::left << std::setw(18) << "PrimaryStore:" << customer->primaryStore << std::endl;
        std::cout << std::left << std::setw(18) << "PurchaseHistory:" << customer->purchaseHistory << std::endl;
        std::cout << BLUE << "----------------------------------------" << RESET << std::endl;
    }
    else {
        // Display message if customer is not found
        std::cout << RED << "Customer not found." << RESET << std::endl;
    }
}

// Function to compare customers by name (used for sorting in ascending order)
bool compareByName(Customer* a, Customer* b) {
    return a->name < b->name;
}

// Function to compare customers by age (used for sorting in ascending order)
bool compareByAge(Customer* a, Customer* b) {
    return a->age < b->age;
}

// Function to display a list of customers with pagination and optional sorting options
void displayCustomerList(std::vector<Customer*>& customers, bool showSortingOptions = true) {
    if (customers.empty()) {
        std::cout << RED << "No customers to display." << RESET << std::endl;
        pause();
        return;
    }

    if (showSortingOptions) {
        // Provide sorting options to the user
        int sortChoice;
        std::cout << CYAN << "\nSort results by:" << RESET << std::endl;
        std::cout << "1. Name (Ascending)" << std::endl;
        std::cout << "2. Name (Descending)" << std::endl;
        std::cout << "3. Age (Ascending)" << std::endl;
        std::cout << "4. Age (Descending)" << std::endl;
        std::cout << "Enter choice (default 1): ";
        std::string sortInput;
        std::getline(std::cin, sortInput);
        sortChoice = sortInput.empty() ? 1 : std::stoi(sortInput);

        // Perform sorting based on user's choice
        switch (sortChoice) {
        case 1:
            std::sort(customers.begin(), customers.end(), compareByName);
            break;
        case 2:
            std::sort(customers.begin(), customers.end(), [](Customer* a, Customer* b) {
                return a->name > b->name;
                });
            break;
        case 3:
            std::sort(customers.begin(), customers.end(), compareByAge);
            break;
        case 4:
            std::sort(customers.begin(), customers.end(), [](Customer* a, Customer* b) {
                return a->age > b->age;
                });
            break;
        default:
            std::sort(customers.begin(), customers.end(), compareByName);
            break;
        }
    }

    size_t total = customers.size();
    size_t perPage = 5; // Number of customers to display per page
    size_t pages = (total + perPage - 1) / perPage;

    // Display customers page by page
    for (size_t page = 0; page < pages; ++page) {
        clearScreen();
        std::cout << YELLOW << "Displaying customers " << (page * perPage + 1)
            << " to " << std::min((page + 1) * perPage, total)
            << " of " << total << RESET << std::endl << std::endl;

        size_t start = page * perPage;
        size_t end = std::min(start + perPage, total);
        for (size_t i = start; i < end; ++i) {
            displayCustomerFormatted(customers[i]);
        }

        if (page < pages - 1) {
            // Prompt user to proceed to the next page
            std::cout << "\nPress Enter to view next page...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            pause();
        }
    }
}

// Function to display the help menu
void displayHelp() {
    clearScreen();
    std::cout << CYAN << "--- Help Menu ---" << RESET << std::endl;
    std::cout << "This application allows you to search for customers by Customer ID, "
        << "Phone Number, or Name. You can also view default search values.\n"
        << std::endl;
    std::cout << "Menu Options:" << std::endl;
    std::cout << "1. Search by Customer ID - Enter a full or partial Customer ID to search." << std::endl;
    std::cout << "2. Search by Phone Number - Enter a full or partial Phone Number to search." << std::endl;
    std::cout << "3. Search by Name - Enter a full or partial Name to search." << std::endl;
    std::cout << "4. Default Search Values - View the top 50 customers sorted alphabetically." << std::endl;
    std::cout << "5. View Search History - View your past search queries." << std::endl;
    std::cout << "6. Help - View instructions on how to use the application." << std::endl;
    std::cout << "0. Exit - Exit the application." << std::endl;
    pause();
}

int main() {
    // Initialize Tries for different search criteria
    Trie nameTrie;
    Trie customerIDTrie;
    Trie phoneTrie;
    std::vector<Customer*> allCustomers;

    // Define the expected length of Customer IDs and Phone Numbers
    const size_t customerIDLength = 8;    // Adjust if your Customer IDs have a different length
    const size_t customerPhoneNumberLength = 15; // Adjust based on your data

    // Search history vectors to keep track of user queries
    std::vector<std::string> searchHistoryID;
    std::vector<std::string> searchHistoryPhone;
    std::vector<std::string> searchHistoryName;

    // Load data from CSV file and populate data structures
    std::cout << "Loading data..." << std::endl;
    loadData("customer_dataset_final.csv", nameTrie, customerIDTrie, phoneTrie, allCustomers);
    std::cout << GREEN << "Data loaded successfully." << RESET << std::endl;
    pause();

    bool isSorted = false; // Flag to check if 'allCustomers' is already sorted

    int choice = -1; // Initialize choice to avoid uninitialized variable warning

    // Main program loop
    do {
        clearScreen();
        // Display the main menu
        std::cout << YELLOW << "--- Customer Search Menu ---" << RESET << std::endl;
        std::cout << GREEN << "1. Search by Customer ID" << RESET << std::endl;
        std::cout << GREEN << "2. Search by Phone Number" << RESET << std::endl;
        std::cout << GREEN << "3. Search by Name" << RESET << std::endl;
        std::cout << GREEN << "4. Default Search Values" << RESET << std::endl;
        std::cout << GREEN << "5. View Search History" << RESET << std::endl;
        std::cout << GREEN << "6. Help" << RESET << std::endl;
        std::cout << GREEN << "0. Exit" << RESET << std::endl;
        std::cout << "Enter choice: ";
        std::string inputChoice;
        std::getline(std::cin, inputChoice);

        // Validate menu choice input
        try {
            choice = std::stoi(inputChoice);
        }
        catch (std::exception& e) {
            std::cout << RED << "Invalid choice. Please enter a number between 0 and 6." << RESET << std::endl;
            pause();
            continue;
        }

        if (choice < 0 || choice > 6) {
            std::cout << RED << "Invalid choice. Please enter a number between 0 and 6." << RESET << std::endl;
            pause();
            continue;
        }

        std::string input;
        std::vector<Customer*> customers;

        switch (choice) {
        case 1: {
            // Search by Customer ID
            clearScreen();
            std::cout << YELLOW << "--- Search by Customer ID ---" << RESET << std::endl;
            std::cout << "Enter Customer ID: ";
            std::getline(std::cin, input);

            // Input validation
            if (input.empty()) {
                std::cout << RED << "Customer ID cannot be empty." << RESET << std::endl;
                pause();
                break;
            }

            searchHistoryID.push_back(input);

            // Ask user for exact or partial match
            std::cout << "Do you want to perform an exact match? (Y/N): ";
            std::string matchChoice;
            std::getline(std::cin, matchChoice);

            if (matchChoice == "Y" || matchChoice == "y") {
                // Perform exact match using hash table
                Customer* customer = searchByCustomerIDExact(input);
                if (customer) {
                    displayCustomerFormatted(customer);
                    pause();
                }
                else {
                    std::cout << RED << "No exact match found for Customer ID: " << input << RESET << std::endl;
                    pause();
                }
            }
            else {
                // Perform partial match using Trie
                customers = searchByCustomerIDPartial(input, customerIDTrie);
                if (!customers.empty()) {
                    std::cout << YELLOW << "\nDisplaying closest matches:\n" << RESET << std::endl;
                    displayCustomerList(customers); // showSortingOptions defaults to true
                }
                else {
                    std::cout << RED << "No customers found with that Customer ID prefix." << RESET << std::endl;
                    pause();
                }
            }
            break;
        }
        case 2: {
            // Search by Phone Number
            clearScreen();
            std::cout << YELLOW << "--- Search by Phone Number ---" << RESET << std::endl;
            std::cout << "Enter Phone Number: ";
            std::getline(std::cin, input);

            // Input validation
            if (input.empty()) {
                std::cout << RED << "Phone Number cannot be empty." << RESET << std::endl;
                pause();
                break;
            }

            searchHistoryPhone.push_back(input);

            // Ask user for exact or partial match
            std::cout << "Do you want to perform an exact match? (Y/N): ";
            std::string matchChoice;
            std::getline(std::cin, matchChoice);

            if (matchChoice == "Y" || matchChoice == "y") {
                // Perform exact match using hash table
                Customer* customer = searchByPhoneNumberExact(input);
                if (customer) {
                    displayCustomerFormatted(customer);
                    pause();
                }
                else {
                    std::cout << RED << "No exact match found for Phone Number: " << input << RESET << std::endl;
                    pause();
                }
            }
            else {
                // Perform partial match using Trie
                customers = searchByPhoneNumberPartial(input, phoneTrie);
                if (!customers.empty()) {
                    std::cout << YELLOW << "\nDisplaying closest matches:\n" << RESET << std::endl;
                    displayCustomerList(customers); // showSortingOptions defaults to true
                }
                else {
                    std::cout << RED << "No customers found with that Phone Number prefix." << RESET << std::endl;
                    pause();
                }
            }
            break;
        }
        case 3: {
            // Search by Name
            clearScreen();
            std::cout << YELLOW << "--- Search by Name ---" << RESET << std::endl;
            std::cout << "Enter Name: ";
            std::getline(std::cin, input);

            // Input validation
            if (input.empty()) {
                std::cout << RED << "Name cannot be empty." << RESET << std::endl;
                pause();
                break;
            }

            searchHistoryName.push_back(input);

            // Ask user for exact or partial match
            std::cout << "Do you want to perform an exact match? (Y/N): ";
            std::string matchChoice;
            std::getline(std::cin, matchChoice);

            if (matchChoice == "Y" || matchChoice == "y") {
                // Perform exact match using Trie
                customers.clear(); // Prepare to collect exact matches
                customers = searchByNameExact(input, nameTrie);
                if (!customers.empty()) {
                    displayCustomerList(customers, false); // Do not show sorting options
                }
                else {
                    std::cout << RED << "No exact match found for Name: " << input << RESET << std::endl;
                    pause();
                }
            }
            else {
                // Perform partial match using Trie
                customers = searchByName(input, nameTrie);
                if (!customers.empty()) {
                    std::cout << YELLOW << "\nDisplaying closest matches:\n" << RESET << std::endl;
                    displayCustomerList(customers); // showSortingOptions defaults to true
                }
                else {
                    std::cout << RED << "No customers found with that name prefix." << RESET << std::endl;
                    pause();
                }
            }
            break;
        }
        case 4:
            // Display default search values (top 50 customers)
            clearScreen();
            std::cout << YELLOW << "--- Default Search Values ---" << RESET << std::endl;
            if (!isSorted) {
                std::sort(allCustomers.begin(), allCustomers.end(), compareByName);
                isSorted = true;
            }
            customers.assign(allCustomers.begin(), allCustomers.begin() + std::min((size_t)50, allCustomers.size()));
            displayCustomerList(customers); // showSortingOptions defaults to true
            break;

        case 5:
            // View search history
            clearScreen();
            std::cout << YELLOW << "--- Search History ---" << RESET << std::endl;
            std::cout << CYAN << "\nCustomer ID Searches:" << RESET << std::endl;
            if (searchHistoryID.empty()) {
                std::cout << "No Customer ID searches made." << std::endl;
            }
            else {
                for (const auto& id : searchHistoryID) {
                    std::cout << "- " << id << std::endl;
                }
            }
            std::cout << CYAN << "\nPhone Number Searches:" << RESET << std::endl;
            if (searchHistoryPhone.empty()) {
                std::cout << "No Phone Number searches made." << std::endl;
            }
            else {
                for (const auto& phone : searchHistoryPhone) {
                    std::cout << "- " << phone << std::endl;
                }
            }
            std::cout << CYAN << "\nName Searches:" << RESET << std::endl;
            if (searchHistoryName.empty()) {
                std::cout << "No Name searches made." << std::endl;
            }
            else {
                for (const auto& name : searchHistoryName) {
                    std::cout << "- " << name << std::endl;
                }
            }
            pause();
            break;

        case 6:
            // Display help menu
            displayHelp();
            break;

        case 0:
            // Exit the application
            std::cout << GREEN << "Exiting program. Goodbye!" << RESET << std::endl;
            break;

        default:
            // Handle invalid choices (should not reach here due to earlier validation)
            std::cout << RED << "Invalid choice. Please select again." << RESET << std::endl;
            pause();
            break;
        }
    } while (choice != 0);

    // Clean up allocated memory for customers
    for (Customer* customer : allCustomers) {
        delete customer;
    }

    return 0;
}