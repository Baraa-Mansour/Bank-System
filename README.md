# Bank Management System

This project is a simple console-based bank management system built to practice C++ programming fundamentals, file handling, data validation, and modular program design.

> Note: This program uses Windows-specific console commands such as `cls` and `pause`, so it is intended to run on Windows. To make it work on another operating system, replace those commands with the equivalent command for your environment.

## About

The program allows a user to manage client records for a bank through a text-based menu. Client data is stored in a file named `Clients.txt`, and the system supports viewing, adding, deleting, updating, and finding client information. It also provides basic transaction operations such as deposits, withdrawals, and total balance viewing.

## Features

- View the full list of bank clients.
- Add new clients with account number, PIN, name, phone, and balance.
- Delete existing client records.
- Update client information.
- Find a client by account number.
- Perform deposit transactions.
- Perform withdrawal transactions.
- View the total balances of all clients.
- Save and load client data from a file.
- Simple console UI with menu navigation and validation prompts.

## How to use

1. Run the program.
2. Choose an option from the main menu.
3. For client management, enter the required account information.
4. For transactions, enter the account number and transaction amount.
5. Follow the on-screen prompts to confirm actions.
6. Use the menu to continue working with clients or exit the program.

## How to run

### Using Visual Studio

1. Open `Bank.sln` in Visual Studio.
2. Build the solution.
3. Run the project.

## Programming topics covered

- C++ input/output (`cin`, `cout`, `getline`)
- Control flow (`if`, `switch`, loops)
- Structures for grouping related client data
- Functions for modular code organization
- File handling with `fstream`
- String parsing and record conversion
- Input validation and range checking
- Basic menu-driven console application design

## Code organization

The project is organized around two main components:

- `main.cpp`: contains the main menu, client management screens, transaction screens, and file operations.
- `Validation.h`: provides reusable validation functions for reading numbers, checking ranges, validating positive values, and handling yes/no input.

## Data storage

Client data is stored in a text file named `Clients.txt` using a simple delimited record format. Each record contains:

- Account number
- PIN code
- Name
- Phone
- Account balance
