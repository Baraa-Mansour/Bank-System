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
    FindClient = 5,
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
    vector<stClient> vClients = GetAllClients(FilePath);

    PrintTableHeader(vClients.size());
    for (const stClient& Client : vClients)
        PrintClientsTableRecord(Client);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// Exit Screen
void EndProgramScreen()
{
    cout << "========================================" << endl;
    cout << "\t\tProgram End" << endl;
    cout << "========================================" << endl;
}

// Main Menue Screen
void MainMenueScreen()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "\t\tMain Menue" << endl;
    cout << "========================================" << endl;
    cout << "\t[1] Show Clients List" << endl;
    cout << "\t[2] Add New Client" << endl;
    cout << "\t[3] Delete Client" << endl;
    cout << "\t[4] Update Client" << endl;
    cout << "\t[5] Find Client" << endl;
    cout << "\t[6] Exit" << endl << endl;
}
void GetUserOption()
{
    enProgramOptions Option = (enProgramOptions)Validation::ReadNumberInRange("Chose Operation: ", 1, 6);

    switch (Option)
    {
    case ShowClintsList:
        ShowClientsScreen();
        break;
    case AddNewClient:
        break;
    case DeleteClient:
        break;
    case UpdateClient:
        break;
    case FindClient:
        break;
    case Exit:
        EndProgramScreen();
        break;
    default:
        break;
    }
}

int main()
{
    MainMenueScreen();
    GetUserOption();
}
