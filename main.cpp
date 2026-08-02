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
    DeleteClient = 3,
    UpdateClient = 4,
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

// General
void BackToMainScreen()
{
    system("pause");
}
string ReadUniqueAccountNumber()
{
    stClient Client;
    string AccountNumber = "";
    cout << "Enter Account Number: ";
    getline(cin >> ws, AccountNumber);

    while (FindClient(AccountNumber, Client))
    {
        cout << "Account Number [" << AccountNumber <<"] Already Existing, Enter Different one: ";
        getline(cin >> ws, AccountNumber);
    }

    return AccountNumber;
}
void PrintScreenHeader(string ScreenName)
{
    cout << "========================================" << endl;
    cout << ScreenName << endl;
    cout << "========================================" << endl;
}

// Show Client Screen
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
    case DeleteClient:
        break;
    case UpdateClient:
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
