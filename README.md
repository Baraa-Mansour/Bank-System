# Bank Management System

This project is a simple console-based bank management system built to practice C++ programming fundamentals, Login System, Bitmask-based permission design, file handling, data validation, and modular program design.

> Note: This program uses Windows-specific console commands such as `cls` and `pause`, so it is intended to run on Windows. To make it work on another operating system, replace those commands with the equivalent command for your environment.

## About

The program manages bank clients and system users through a text-based menu. Client data is stored in `Clients.txt`, and user data is stored in `Users.txt`. The application supports viewing, adding, deleting, updating, and finding client information, as well as performing deposits, withdrawals, and balance checks. It also includes user management with permission-based access.

Users must authenticate with a username and password before using the system; permissions attached to each user control which menu operations are available.

## Features

- Login authentication (username/password) with per-user permission enforcement
- Permission bitmask design allowing granular access control
- Admin account with full permissions (-1) for managing users
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
   - Example admin record: `admin#//#1234#//#-1` (username `admin`, password `1234`, full permissions)
3. Run the program and log in with an existing user from `Users.txt`.
4. After logging in, use the main menu. Options are enabled or disabled based on the logged-in user's permissions.
5. To manage users (create, update, delete), use the `User Managment` menu — only users with `MANAGE_USERS` permission can access it.
6. For client management, enter the required account information.
7. For transactions, enter the account number and transaction amount.
8. Follow the on-screen prompts to confirm actions.
9. Use the menu to continue working with clients or logout.

## How to run

### Using Visual Studio

1. Open `Bank.sln` in Visual Studio.
2. Build the solution.
3. Run the project.

## Programming topics covered

- Authentication (login) and password verification
- Bitmask-based permission design and permission checks
- Simple role-like admin behavior and safe user management constraints
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

The `Permissions` field is an integer bitmask controlling access to features (see the "Login and Permissions" section). The default administrator account should be present in `Users.txt` so an admin can manage users and permissions.

## Login and Permissions

This program requires users to authenticate before using the system. User records are stored in `Users.txt` (see format above). On startup the program shows a login prompt asking for a username and password. After successful login the application enforces permission checks for each main menu option.

Users must exist in `Users.txt` before they can login. The default admin account must be present so an administrator can manage other users. Example admin user record:

admin#//#1234#//#-1

The record fields are: `Username#//#Password#//#Permissions`.

Permissions are stored as an integer bitmask. The program defines these permission flags (values shown):

- READ_CLIENTS (1) — Show clients list
- ADD_CLIENTS (2) — Add new clients
- DELETE_CLIENTS (4) — Delete clients
- UPDATE_CLIENTS (8) — Update clients
- FIND_CLIENTS (16) — Find clients
- MANAGE_TRANSACTIONS (32) — Deposit/Withdraw/Total balances
- MANAGE_USERS (64) — Show/Add/Delete/Update/Find users

You can combine permissions by summing flag values. For example, `1 + 2 + 32 = 35` gives read, add, and transaction permissions.

The special value `-1` means full permissions (administrator). The program prevents deleting or updating the `admin` user from the user management screens.

When creating or updating a user through the program, the UI asks whether to grant full permissions; if not, it interactively asks which permissions to enable and builds the bitmask accordingly.
