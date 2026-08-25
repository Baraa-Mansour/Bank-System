#include <iostream>
#include "Validation.h"
#include <vector>
#include<iomanip>
#include <fstream>
#include <string>

using namespace std;

// Consts
static const string Delimiter = "#//#";
static const string ClientsFilePath = "Clients.txt";
static const string UsersFilePath = "Users.txt";



// Enums
enum enMainMenueOption
{
    ShowClintsList = 1,
    AddNewClient = 2,
    DeleteClientOption = 3,
    UpdateClientOption = 4,
    FindClientOption = 5,
    TransactionOption = 6,
    UserManagment = 7,
    Logout = 8,
};
enum enTransactionOption
{
    DepositOption = 1,
    WithdrawOption = 2,
    TotalBalancesOption = 3,
    TrToMainmenu = 4
};
enum enUserManagmentOption
{
    ShowUsersList = 1,
    AddNewUsers = 2,
    DeleteUserOption = 3,
    UpdateUserOption = 4,
    FindUserOption = 5,
    UmToMainmenu = 6,
};


// Structs
struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0.0;
};
struct stUser
{
    string Username = "Unknown";
    string Password = "1234";
    int Permissions = 0;
};


// String
vector<string> SplitString(string Line, string Delimiter = " ")
{
    vector<string> vWords;
    string Word = "";
    short Pos = 0;

    while ((Pos = Line.find(Delimiter)) != std::string::npos)
    {
        Word = Line.substr(0, Pos);

        if (!Validation::IsEmpty(Word))
            vWords.push_back(Word);

        Line.erase(0, Pos + Delimiter.length());
    }

    // Print last word cause find method wont find it if Line dont end with white space
    if (!Validation::IsEmpty(Line))
        vWords.push_back(Line);

    return vWords;
}


// Convert
string ClientToRecord(stClient Client)
{
    string Record = "";

    Record += Client.AccountNumber + Delimiter;
    Record += Client.PinCode + Delimiter;
    Record += Client.Name + Delimiter;
    Record += Client.Phone + Delimiter;
    Record += to_string(Client.AccountBalance);

    return Record;
}
stClient RecordToClient(string Record)
{
    vector<string> vRecord = SplitString(Record, Delimiter);
    stClient Client;

    Client.AccountNumber = vRecord.at(0);
    Client.PinCode = vRecord.at(1);
    Client.Name = vRecord.at(2);
    Client.Phone = vRecord.at(3);
    Client.AccountBalance = stod(vRecord.at(4));

    return Client;
}

string UserToRecord(stUser User)
{
    string Record = "";

    Record += User.Username + Delimiter;
    Record += User.Password + Delimiter;
    Record += to_string(User.Permissions);

    return Record;
}
stUser RecordToUser(string Record)
{
    vector<string> vRecord = SplitString(Record, Delimiter);
    stUser User;

    User.Username = vRecord.at(0);
    User.Password = vRecord.at(1);
    User.Permissions = stod(vRecord.at(2));

    return User;
}

// Files Functions
vector<string> GetAllRecord(string FilePath)
{
    vector<string> vRecords;
    fstream File;
    File.open(FilePath, ios::in);

    if (File.is_open())
    {
        string Record = "";
        while (getline(File, Record))
        {
            vRecords.push_back(Record);
        }

        File.close();
    }

    return vRecords;
}

vector<stUser> GetAllUsers()
{
    vector<string> vRecords = GetAllRecord(UsersFilePath);
    vector<stUser> vUsers;

    for (const string& Record : vRecords)
    {
        stUser User = RecordToUser(Record);
        vUsers.push_back(User);
    }

    return vUsers;
}

vector<stClient> GetAllClients()
{
    vector<string> vRecords = GetAllRecord(ClientsFilePath);
    vector<stClient> vClients;
    
    for (const string& Record : vRecords)
    {
        stClient client = RecordToClient(Record);
        vClients.push_back(client);
    }

    return vClients;
}
bool FindClient(string AccountNumber, stClient& Client)
{
    vector<stClient> vClients = GetAllClients();

    for (const stClient& VectorClient : vClients)
    {
        if (VectorClient.AccountNumber == AccountNumber)
        {
            Client = VectorClient;
            return true;
        }
    }

    return false;
}
bool SaveClient(stClient Client)
{
    fstream File;
    File.open(ClientsFilePath, ios::out | ios::app);

    if (File.is_open())
    {
        string Record = ClientToRecord(Client);
        File << Record << endl;

        File.close();

        return true;
    }


    return false;
}
void SaveClientsVector(vector<stClient> vClients) // Overwrite File!!!
{
    fstream File;
    File.open(ClientsFilePath, ios::out); //overwrite

    if (File.is_open())
    {
        for (const stClient& Client : vClients)
        {
            File << ClientToRecord(Client) << endl;
        }
        File.close();
    }
}
bool DeleteClient(string AccountNumber)
{
    bool IsFound = false;
    vector<stClient> vClients = GetAllClients();

    for (int i = 0; i < vClients.size(); i++)
    {
        if (vClients.at(i).AccountNumber == AccountNumber)
        {
            IsFound = true;
            vClients.erase(vClients.begin() + i);
            break;
        }
    }

    if (IsFound)
        SaveClientsVector(vClients);

    return IsFound;
}
bool UpdateClient(string AccountNumber, stClient NewClient)
{
    bool IsFound = false;
    vector<stClient> vClients = GetAllClients();

    for (int i = 0; i < vClients.size(); i++)
    {
        if (vClients.at(i).AccountNumber == AccountNumber)
        {
            IsFound = true;
            vClients.at(i) = NewClient;
            break;
        }
    }

    if (IsFound)
        SaveClientsVector(vClients);

    return IsFound;
}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = RecordToClient(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}


// General
void Pause()
{
    cout << "Press any key to back to Mainmenue . . .";
    system("pause>0");
}
void PrintScreenHeader(string ScreenName)
{
    cout << "========================================" << endl;
    cout << ScreenName << endl;
    cout << "========================================" << endl;
}
void PrintClientRecord(stClient Client)
{
    cout << "\nThe following is the extracted client record:\n";
    cout << "_________________________________________________" << endl;
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n_________________________________________________" << endl;
}

string ReadAccountNumber()
{
    string AccountNumber = "";

    cout << "Enter Account Number: ";
    getline(cin >> ws, AccountNumber);

    return AccountNumber;
}
string ReadExisteningAccoutNumber()
{
    string AccountNumber = ReadAccountNumber();

    while (!ClientExistsByAccountNumber(AccountNumber, ClientsFilePath))
    {
        cout << "NotFound!, Try Again: " << endl;
        AccountNumber = ReadAccountNumber();
    }

    return AccountNumber;
}
string ReadUniqueAccountNumber()
{
    string AccountNumber = ReadAccountNumber();

    while (ClientExistsByAccountNumber(AccountNumber, ClientsFilePath))
    {
        cout << "Account Number [" << AccountNumber << "] Already Existing, Enter Different one: ";
        getline(cin >> ws, AccountNumber);
    }

    return AccountNumber;
}

stClient ReadNewClient()
{
    stClient Client;

    Client.AccountNumber = ReadUniqueAccountNumber();

    cout << "Pin Code: ";
    getline(cin, Client.PinCode);

    cout << "Name: ";
    getline(cin, Client.Name);

    cout << "Phone: ";
    getline(cin, Client.Phone);

    Client.AccountBalance = Validation::ReadPositiveDoubleNumber("Enter Balance: ");

    return Client;
}
stClient ReadUpdateClient(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Pin Code: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Name: ";
    getline(cin, Client.Name);

    cout << "Phone: ";
    getline(cin, Client.Phone);

    Client.AccountBalance = Validation::ReadPositiveDoubleNumber("Enter Balance: ");

    return Client;
}

void PrintOptionList(vector<string> ListItems)
{
    for (int i = 0; i < ListItems.size(); i++)
    {
        cout << "\t[" << i+1 << "] " << ListItems[i] << endl;
    }
}


// Client System
// Show Clients
void PrintTableHeader(int NumberOfClients)
{
    cout << "\n\t\t\t\t\tClient List (" << NumberOfClients << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintClientsTableRecord(stClient Client)
{
    cout << endl;
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
    cout << endl;
}
void PerformShowClientsScreen()
{
    vector<stClient> vClients = GetAllClients();

    PrintTableHeader(vClients.size());
    for (const stClient& Client : vClients)
        PrintClientsTableRecord(Client);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void ShowClientsScreen()
{
    PrintScreenHeader("Show Clients Screen");

    PerformShowClientsScreen();

    Pause();
}


// Add New Client
void PerformAddNewClient()
{
    do
    {
        stClient Client = ReadNewClient();

        if (SaveClient(Client))
            cout << "Added Successfully" << endl;
        else
            cout << "Something Went Wrong, Try Later!" << endl;

    } while (Validation::ReadYorN("Add More Clients? [Y OR N]"));
}
void AddNewClientScreen()
{
    PrintScreenHeader("Add New Clients Screen");
    
    PerformAddNewClient();

    Pause();
}


// Delete Client 
void PerformDeleteClient()
{
    stClient Client;

    Client.AccountNumber = ReadAccountNumber();

    if (FindClient(Client.AccountNumber, Client))
    {
        PrintClientRecord(Client);

        if (Validation::ReadYorN("Sure Want To Delete This Record? [Y OR N]"))
            DeleteClient(Client.AccountNumber) ? cout << "Deleted Successfully" << endl : cout << "Something Went Wrong, Try Later!" << endl;
    }
    else
    {
        cout << "Account Number [" << Client.AccountNumber << "] Not Found!" << endl;
    }
}
void DeleteClientScreen()
{
    PrintScreenHeader("Delete Client Screen");
    
    PerformDeleteClient();
    
    Pause();
}


// Update Client 
void PerformUpdateClient()
{
    stClient Client;
    Client.AccountNumber = ReadAccountNumber();

    if (FindClient(Client.AccountNumber, Client))
    {
        PrintClientRecord(Client);

        if (Validation::ReadYorN("Sure Want To Update This Record? [Y OR N]"))
        {
            Client = ReadUpdateClient(Client.AccountNumber);

            if (UpdateClient(Client.AccountNumber, Client))
                cout << "Updated Successfully" << endl;
            else
                cout << "Something Went Wrong!, Try Again Later" << endl;
        }
    }
    else
    {
        cout << "Account Number [" << Client.AccountNumber << "] Not Found!" << endl;
    }
}
void UpdateClientScreen()
{
    PrintScreenHeader("Update Client screen");

    PerformUpdateClient();
    
    Pause();
}


// Find Client
void PerformFindClientScreen()
{
    stClient Client;
    Client.AccountNumber = ReadAccountNumber();

    if (FindClient(Client.AccountNumber, Client))
    {
        PrintClientRecord(Client);
    }
    else
    {
        cout << "Account Number [" << Client.AccountNumber << "] Not Found!" << endl;
    }
}
void FindClientScreen()
{
    PrintScreenHeader("Find Client Screen");
    
    PerformFindClientScreen();

    Pause();
}
// End Client System


// Transaction System
// Deposit 
double ReadDepositAmount()
{
    return Validation::ReadPositiveDoubleNumber("Enter Deposit Amount: ");
}
void PerformDeposit()
{
    stClient Client;

    Client.AccountNumber = ReadExisteningAccoutNumber();

    FindClient(Client.AccountNumber, Client);

    PrintClientRecord(Client);

    double DepositAmount = ReadDepositAmount();
    Client.AccountBalance += DepositAmount;

    if (Validation::ReadYorN("Sure Want To Perform This Transaction? Y/N"))
    {
        if (UpdateClient(Client.AccountNumber, Client))
            cout << "Done Successfully!, New Balance Is: " << Client.AccountBalance << endl;
        else
            cout << "Something Went Wrong, Try AgainLater" << endl;
    }

}
void DepositScreen()
{
    PrintScreenHeader("Deposit Screen");

    PerformDeposit();

    Pause();
}


// Withdraw
double ReadWithdrawAmount(double AccountBalance)
{
    double WithdrawAmount = Validation::ReadPositiveDoubleNumber("Enter Withdraw Amount: ");

    while (WithdrawAmount > AccountBalance)
    {
        cout << "Not Enough Balance, You Can Withdraw Up To: " << AccountBalance << endl;
        WithdrawAmount = Validation::ReadPositiveDoubleNumber("Enter Withdraw Amount: ");
    }

    return WithdrawAmount;
}
void PerformWithdraw()
{
    stClient Client;

    Client.AccountNumber = ReadExisteningAccoutNumber();

    FindClient(Client.AccountNumber, Client);

    PrintClientRecord(Client);

    double DepositAmount = ReadWithdrawAmount(Client.AccountBalance);
    Client.AccountBalance -= DepositAmount;

    if (Validation::ReadYorN("Sure Want To Perform This Transaction? Y/N"))
    {
        if (UpdateClient(Client.AccountNumber, Client))
            cout << "Done Successfully!, New Balance Is: " << Client.AccountBalance << endl;
        else
            cout << "Something Went Wrong, Try AgainLater" << endl;
    }

}
void WithdrawScreen()
{
    PrintScreenHeader("Withdraw Screen");

    PerformWithdraw();

    Pause();
}


// Total Balances
void PrintBalancesTableHeader(int NumberOfClients)
{
    cout << "\n\t\t\t\t\tClient List (" << NumberOfClients << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintBalancesTableRecord(stClient Client)
{
    cout << endl;
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
    cout << endl;
}
void PerformTotalBalances()
{
    vector<stClient> vClients = GetAllClients();
    double TotalBalances = 0;

    PrintBalancesTableHeader(vClients.size());
    for (const stClient& Client : vClients)
    {
        PrintBalancesTableRecord(Client);
        TotalBalances += Client.AccountBalance;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "\t\t\t\t\t\t\tTotal Balances: " << TotalBalances << endl;
}
void TotalBalancesScreen()
{
    PrintScreenHeader("Total Balances Screen");

    PerformTotalBalances();

    Pause();
}


// Transaction Mainmenu
enTransactionOption GetTransactionOption()
{
    enTransactionOption Option = (enTransactionOption)Validation::ReadNumberInRange("Chose Operation: ", 1, 4);

    return Option;
}
void PerformTransactionOption(enTransactionOption Option)
{
    system("cls");
    switch (Option)
    {
    case DepositOption:
        DepositScreen();
        break;
    case WithdrawOption:
        WithdrawScreen();
        break;
    case TotalBalancesOption:
        TotalBalancesScreen();
        break;
    case TrToMainmenu:
        break;
    default:
        break;
    }
}

void TransactionMainmenuScreen()
{
    PrintScreenHeader("Transaction Screen");
    cout << "\t[1] Deposit" << endl;
    cout << "\t[2] Withdraw" << endl;
    cout << "\t[3] Total Balances" << endl;
    cout << "\t[4] Mainmenu" << endl;
}

void RunTransactionSystem()
{
    enTransactionOption Option;

    do
    {
        system("cls");

        TransactionMainmenuScreen();

        Option = GetTransactionOption();

        PerformTransactionOption(Option);

    } while (Option != enTransactionOption::TrToMainmenu);
}
// End Transaction System


// User System
// Show Users
void PrintUsersTableHeader(int NumberOfUsers)
{
    cout << "\n\t\t\t\t\tClient List (" << NumberOfUsers << ")User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(20) << "Username";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << left << setw(12) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintUsersTableRecord(stUser User)
{
    cout << endl;
    cout << "| " << setw(20) << left << User.Username;
    cout << "| " << setw(30) << left << User.Password;
    cout << "| " << setw(12) << left << User.Permissions;
    cout << endl;
}
void PrintUsersTableRecords(vector<stUser> vUsers)
{
    for (const stUser& User : vUsers)
        PrintUsersTableRecord(User);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PerformShowUsers()
{
    vector<stUser> Users = GetAllUsers();

    PrintUsersTableHeader(Users.size());
    PrintUsersTableRecords(Users);
}
void ShowUserScreen()
{
    PrintScreenHeader("Show Users");
    PerformShowUsers();
    Pause();
}

// User Manage Mainmenu
void PrintUserManageOptionList()
{
    vector<string> ListItems =
    {
        "Show Users List",
        "Add New Users",
        "Delete User",
        "Update User",
        "Find User",
        "Mainmenu"
    };
    PrintOptionList(ListItems);
}
enUserManagmentOption GetUserManagOption()
{
    enUserManagmentOption Option = (enUserManagmentOption)Validation::ReadNumberInRange("Chose Operation: ", 1, 6);

    return Option;
}
void PerformUserManagOption(enUserManagmentOption Option)
{
    system("cls");
    switch (Option)
    {
    case ShowUsersList:
        ShowUserScreen();
        break;
    case AddNewUsers:
        break;
    case DeleteUserOption:
        break;
    case UpdateUserOption:
        break;
    case FindUserOption:
        break;
    case UmToMainmenu:
        break;
    default:
        break;
    }
}
void UserManagmentScreen()
{
    enUserManagmentOption Option;
    do
    {
        system("cls");

        PrintScreenHeader("User Managment");
        PrintUserManageOptionList();

        Option = GetUserManagOption();
        PerformUserManagOption(Option);

    } while (Option != enUserManagmentOption::UmToMainmenu);
}
// End User System


// Main Menue
enMainMenueOption GetMainMenuOption()
{
    enMainMenueOption Option = (enMainMenueOption)Validation::ReadNumberInRange("Chose Operation: ", 1, 8);

    return Option;
}
void PerformMainMenuOption(enMainMenueOption Option)
{
    system("cls");
    switch (Option)
    {
    case ShowClintsList:
        ShowClientsScreen();
        break;
    case AddNewClient:
        AddNewClientScreen();
        break;
    case DeleteClientOption:
        DeleteClientScreen();
        break;
    case UpdateClientOption:
        UpdateClientScreen();
        break;
    case FindClientOption:
        FindClientScreen();
        break;
    case TransactionOption:
        RunTransactionSystem();
        break;
    case UserManagment:
        UserManagmentScreen();
        break;
    case Logout:
    default:
        break;
    }
}
void MainMenuScreen()
{
    PrintScreenHeader("Main Menue Screen");
    cout << "\t[1] Show Clients List" << endl;
    cout << "\t[2] Add New Client" << endl;
    cout << "\t[3] Delete Client" << endl;
    cout << "\t[4] Update Client" << endl;
    cout << "\t[5] Find Client" << endl;
    cout << "\t[6] Transaction" << endl;
    cout << "\t[7] User Managment" << endl;
    cout << "\t[8] Logout" << endl << endl;
}


int main()
{
    enMainMenueOption Option;

    do
    {
        system("cls");

        MainMenuScreen();

        Option = GetMainMenuOption();

        PerformMainMenuOption(Option);

    } while (Option != enMainMenueOption::Logout);
}
