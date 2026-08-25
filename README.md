# Bank Management System

This project is a simple console-based bank management system built to practice C++ programming fundamentals, file handling, data validation, and modular program design.

> Note: This program uses Windows-specific console commands such as `cls` and `pause`, so it is intended to run on Windows. To make it work on another operating system, replace those commands with the equivalent command for your environment.

## About

The program manages bank clients and system users through a text-based menu. Client data is stored in `Clients.txt`, and user data is stored in `Users.txt`. The application supports viewing, adding, deleting, updating, and finding client information, as well as performing deposits, withdrawals, and balance checks. It also includes user management with permission-based access.

## Features

- View the full list of bank clients.
- Add new clients with account number, PIN, name, phone, and balance.
- Delete existing client records.
- Update client information.
- Find a client by account number.
- Perform deposit transactions.
- Perform withdrawal transactions.
- View the total balances of all clients.
- Manage users and assign permissions.
- Show, add, update, delete, and find user records.
- Save and load client and user data from text files.
- Simple console UI with menu navigation and validation prompts.

## Required data files

Before running the program, make sure the project folder contains these files in the same directory as the executable or source file:

- `Clients.txt` - stores client records.
- `Users.txt` - stores user records and permissions.

You can create both files as empty text files before the first run. The program reads and writes them automatically.

> Important: `Users.txt` must contain at least one record for the default admin user, because the program checks for the username `admin` when working with user management.

Example admin user record in `Users.txt`:

`admin#//#1234#//#-1`

This format is:

`Username#//#Password#//#Permissions`

The `Permissions` value is stored as an integer bitmask, and `-1` means full permissions.

## How to use

1. Create `Clients.txt` and `Users.txt` in the project folder.
2. Add an admin user record to `Users.txt`.
3. Run the program.
4. Choose an option from the main menu.
5. For client management, enter the required account information.
6. For transactions, enter the account number and transaction amount.
7. Follow the on-screen prompts to confirm actions.
8. Use the menu to continue working with clients or exit the program.

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
- Permission-based user management
- Basic menu-driven console application design

## Code organization

The project is organized around a few main components:

- `main.cpp`: contains the main menu, client management screens, transactions, user management, and file operations.
- `Validation.h`: provides reusable validation functions for reading numbers, checking ranges, validating positive values, and handling yes/no input.

## Data storage

Client data is stored in a text file named `Clients.txt` using a simple delimited record format. Each record contains:

- Account number
- PIN code
- Name
- Phone
- Account balance

User data is stored in `Users.txt` using a delimited format:

- Username
- Password
- Permissions
