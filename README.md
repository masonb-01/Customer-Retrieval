
# Electronic Customer Database & Retrieval system 
# Also know as, “E-CustomerX”

Overview

This application allows users to search for customers by Customer ID, Phone Number, or Name. It supports both exact and partial matches and provides options for sorting and viewing search history. The application utilizes two key data structures:
- Trie: For efficient prefix-based searches.
- Hash Tables: For fast exact lookups.

Features

# Search Options:
- Exact Match: Find customers matching the exact input.
- Partial Match: Find customers matching the input prefix.
# Search Criteria:
- Customer ID
- Phone Number
- Name
# Sorting Options:
- Name: Ascending or Descending.
- Age: Ascending or Descending.
# Search History:
- View past search queries.
# Help Menu:
- Instructions on how to use the application.
# Default Search Values:
- View top 50 customers sorted alphabetically.

Requirements

# C++ Compiler: 
- Ensure you have a compiler that supports C++11 or higher
# Operating System:
- Linux supported
- MacOSm supported
- Windows: ANSI escape codes for console text coloring may require additional configuration for some computers.
# Dataset File: 
- customer_dataset_final.csv should be placed in the same directory as the source code.

File Structure

# Source Files:
- main.cpp: Main application logic and user interface.
- customer.h / customer.cpp: Customer class definition and implementation.
- hash_tables.h / hash_tables.cpp: Hash tables for exact searches.
- trie.h / trie.cpp: Trie data structure for prefix searches.
- loader.h / loader.cpp: Data loading from CSV file.
- search.h / search.cpp: Search functions using tries and hash tables.

Compilation Instructions

# Download the Source Code:
- Ensure all the source files listed above are in the same directory.
# Open a Terminal or IDE:
- Navigate to the directory containing the source files.
# Compile the Code:
- Use the following command to compile the application:
    g++ -std=c++11 main.cpp customer.cpp hash_tables.cpp trie.cpp loader.cpp search.cpp -o customer_search
# Explanation:
-std=c++11: Specifies the use of the C++11 standard.
-o customer_search: Sets the output executable file name to customer_search.

Running the Application

Ensure the Dataset is Present:
- The customer_dataset_final.csv file must be in the same directory as the compiled executable.
# Run the Application:
- Use the following command:
    ./customer_search
    -  On Windows, you may need to run customer_search.exe
# Using the Application:
  Main Menu:
- You will see a menu with options to search by Customer ID, Phone Number, Name, view default values, search history, help, or exit.
# Performing a Search:
- Select an option by entering the corresponding number.
- Enter the search value when prompted.
- Choose whether to perform an exact match (Y) or partial match (N).
# Viewing Results:
- For partial matches, you can sort the results.
- Results are displayed with pagination; press Enter to navigate through pages.
# Search History:
- Option 5 allows you to view your past search queries.
# Help:
- Option 6 displays instructions on how to use the application.
# Exiting the Application:
- Select option 0 from the main menu to exit.

Dataset Format
- File Name: customer_dataset_final.csv
Columns:
- Name
- CustomerID
- PhoneNumber
- Age
- Birthdate
- Gender
- PrimaryStore
- PurchaseHistory