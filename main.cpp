#include <iostream>
#include "Validation.h"
#include <vector>
#include<iomanip>
#include <fstream>
#include <string>

using namespace std;

// Consts
static const string Delimiter = "#//#";
static const string FilePath = "Clients.txt";


// Enums
enum enMainMenueOption
{
    ShowClintsList = 1,
    AddNewClient = 2,
    DeleteClientOption = 3,
    UpdateClientOption = 4,
    FindClientOption = 5,
    Exit = 6,
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


// Files Functions
vector<stClient> GetAllClients(string FilePath)
{
    vector<stClient> vClients;
    fstream File;
    File.open(FilePath, ios::in);

    if (File.is_open())
    {
        string Record = "";
        stClient Client;

        while (getline(File, Record))
        {
            Client = RecordToClient(Record);
            vClients.push_back(Client);
        }

        File.close();
    }

    return vClients;
}
bool FindClient(string AccountNumber, stClient& Client)
{
    vector<stClient> vClients = GetAllClients(FilePath);

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
    File.open(FilePath, ios::out | ios::app);

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
    File.open(FilePath, ios::out); //overwrite

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
    vector<stClient> vClients = GetAllClients(FilePath);

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
    vector<stClient> vClients = GetAllClients(FilePath);

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
string ReadUniqueAccountNumber()
{
    stClient Client;
    string AccountNumber = ReadAccountNumber();

    while (FindClient(AccountNumber, Client))
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
    vector<stClient> vClients = GetAllClients(FilePath);

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


// Find Screen
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


// Exit
void EndProgramScreen()
{
    PrintScreenHeader("Program End");
}


// Main Menue
enMainMenueOption GetMainMenuOption()
{
    enMainMenueOption Option = (enMainMenueOption)Validation::ReadNumberInRange("Chose Operation: ", 1, 6);

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
    case Exit:
        EndProgramScreen();
        break;
    default:
        EndProgramScreen();
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
    cout << "\t[6] Exit" << endl << endl;
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

    } while (Option != enMainMenueOption::Exit);
}
