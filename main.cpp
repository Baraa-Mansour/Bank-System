#include <iostream>
#include "Validation.h"
#include <vector>
#include<iomanip>
#include <fstream>
#include <string>

using namespace std;

static const string Delimiter = "#//#";
static const string FilePath = "Clients.txt";

enum enProgramOptions
{
    ShowClintsList = 1,
    AddNewClient = 2,
    DeleteClientOption = 3,
    UpdateClientOption = 4,
    FindClientOption = 5,
    Exit = 6,
};

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
string to_string(stClient Client)
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
        string Record = to_string(Client);
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
            File << to_string(Client) << endl;
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

// General
void BackToMainScreen()
{
    system("pause");
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

// Show Clients Screen
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
void ShowClientsScreen()
{
    system("cls");
    vector<stClient> vClients = GetAllClients(FilePath);

    PrintTableHeader(vClients.size());
    for (const stClient& Client : vClients)
        PrintClientsTableRecord(Client);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    BackToMainScreen();
}

// Add New Client
string ReadUniqueAccountNumber()
{
    stClient Client;
    string AccountNumber = "";
    cout << "Enter Account Number: ";
    getline(cin >> ws, AccountNumber);

    while (FindClient(AccountNumber, Client))
    {
        cout << "Account Number [" << AccountNumber << "] Already Existing, Enter Different one: ";
        getline(cin >> ws, AccountNumber);
    }

    return AccountNumber;
}
stClient ReadClient()
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
void AddNewClientScreen()
{
    system("cls");
    PrintScreenHeader("Add New Clients Screen");
    
    do
    {
        stClient Client = ReadClient();

        if (SaveClient(Client))
            cout << "Added Successfully" << endl;
        else
            cout << "Something Went Wrong, Try Later!" << endl;

    } while (Validation::ReadYorN("Add More Clients? [Y OR N]"));

    BackToMainScreen();
}

// Delete Client 
void DeleteClientScreen()
{
    system("cls");
    PrintScreenHeader("Delete Client Screen");
    
    stClient Client;

    cout << "Enter AccountNumber: ";
    cin >> Client.AccountNumber;

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
    BackToMainScreen();
}

// Exit Screen
void EndProgramScreen()
{
    system("cls");
    PrintScreenHeader("Program End");
}

// Main Menue Screen
void MainMenueScreen()
{
    system("cls");
    PrintScreenHeader("Main Menue Screen");
    cout << "\t[1] Show Clients List" << endl;
    cout << "\t[2] Add New Client" << endl;
    cout << "\t[3] Delete Client" << endl;
    cout << "\t[4] Update Client" << endl;
    cout << "\t[5] Find Client" << endl;
    cout << "\t[6] Exit" << endl << endl;
}
enProgramOptions GetUserOption()
{
    enProgramOptions Option = (enProgramOptions)Validation::ReadNumberInRange("Chose Operation: ", 1, 6);

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
        break;
    case FindClientOption:
        break;
    case Exit:
        EndProgramScreen();
        break;
    default:
        EndProgramScreen();
        break;
    }

    return Option;
}

int main()
{
    enProgramOptions Option;
    do
    {
        MainMenueScreen();
        Option = GetUserOption();

    } while (Option != Exit);
}
