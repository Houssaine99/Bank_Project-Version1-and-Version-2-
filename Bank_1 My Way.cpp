/*
								------------------------------------------
							   |-> Bank 1 Project: By El Houssaine Ambarki|
							   |Started at 15:30 09/08/2025               |
	                            ------------------------------------------
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>

std::string ClientsFileName = "ClientsDataBase.txt";

enum enMenu { ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Exit = 6, Non = 7 };

struct stClientsData
{
	std::string AccountNumber;
	std::string PINCode;
	std::string ClientName;
	std::string Phone;

	double AccountBalance = 0;
	bool MarkForDelete = false;
};

// --------------Inputs--------------

bool InputFail()
{
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return true;
	}
	else
		return false;
}

short ReadShortNumberInRange(std::string Message, short From, short To)
{
	short InputValue = 0;
	bool isInputFail = false;


	do
	{
		std::cout << Message;
		std::cin >> InputValue;
		isInputFail = InputFail();

	} while (InputValue < From || InputValue > To || isInputFail);

	return InputValue;
}

double GetDoubleNumber(std::string Message)
{
	double InputValue = 0;
	bool isInputFail = false;

	do
	{
		std::cout << Message;
		std::cin >> InputValue;
		isInputFail = InputFail();

	} while (isInputFail);

	return InputValue;
}

char GetCharacter(std::string Message)
{
	char InputValue;
	std::cout << Message;
	std::cin >> InputValue;
	std::cin.ignore(1000, '\n');

	return toupper(InputValue);
}

std::string GetString(std::string Message, bool IgnoreWS = false)
{
	std::string InputValue;
	std::cout << Message;
	if (IgnoreWS)
		std::getline(std::cin >> std::ws, InputValue);
	else
		std::getline(std::cin, InputValue);

	return InputValue;
}

enMenu GetUserChoice()
{
	short UserChoice = ReadShortNumberInRange("Choose what do you want to do? [1 to 6]? ", 1, 6);
	return enMenu(UserChoice);
}

stClientsData ReadClientData(std::string AccountNumber)
{
	stClientsData Client;

	Client.AccountNumber = AccountNumber;

	Client.PINCode = GetString("Enter PIN Code? ");
	Client.ClientName = GetString("Enter Client Name? ");
	Client.Phone = GetString("Enter Phone Number? ");
	Client.AccountBalance = GetDoubleNumber("Enter Account Balance? ");

	return Client;
}

//--------------DataFiles--------------

std::vector <std::string> SplitString(std::string StrToSplit, std::string delim)
{
	std::vector <std::string> vSplitedString;
	std::string SingleWord;
	short pos = 0;

	while ((pos = StrToSplit.find(delim)) != std::string::npos)
	{
		SingleWord = StrToSplit.substr(0, pos);

		if (SingleWord != "")
			vSplitedString.push_back(SingleWord);

		StrToSplit.erase(0, pos + delim.length());
	}
	if (StrToSplit != "")
		vSplitedString.push_back(StrToSplit);

	return vSplitedString;
}

std::string ConvertRecordToLine(stClientsData& ClientRecord, std::string Seperator = "#//#")
{
	std::string Line;

	Line += ClientRecord.AccountNumber + Seperator;
	Line += ClientRecord.PINCode + Seperator;
	Line += ClientRecord.ClientName + Seperator;
	Line += ClientRecord.Phone + Seperator;
	Line += std::to_string(ClientRecord.AccountBalance);

	return Line;
}

stClientsData ConvertLineToRecord(std::string Line, std::string Seperator = "#//#")
{
	stClientsData Client;
	std::vector <std::string> vSplitedString = SplitString(Line, Seperator);

	Client.AccountNumber = vSplitedString[0];
	Client.PINCode = vSplitedString[1];
	Client.ClientName = vSplitedString[2];
	Client.Phone = vSplitedString[3];
	Client.AccountBalance = std::stod(vSplitedString[4]);

	return Client;
}

std::vector <stClientsData> LoadDataFromFile(std::string FileName)
{
	std::vector <stClientsData> vAllClients;

	std::fstream DataFile;
	DataFile.open(FileName, std::ios::in);

	if (DataFile.is_open())
	{
		std::string DataLine;
		stClientsData Client;

		while (std::getline(DataFile, DataLine))
		{
			Client = ConvertLineToRecord(DataLine);
			vAllClients.push_back(Client);
		}
		
		DataFile.close();
	}

	return vAllClients;
}

void SaveDataToFile(std::string FileName, std::vector <stClientsData>& vAllClientsData)
{
	std::fstream DataFile;
	DataFile.open(FileName, std::ios::out);

	if (DataFile.is_open())
	{
		std::string DataLine;
		for (stClientsData& Client : vAllClientsData)
		{
			DataLine = ConvertRecordToLine(Client);
			DataFile << DataLine << std::endl;
		}

		DataFile.close();
	}
}

void SaveClientToFile(std::string FileName, stClientsData Client)
{
	std::fstream DataFile;
	DataFile.open(FileName, std::ios::out | std::ios::app);

	if (DataFile.is_open())
	{
		DataFile << ConvertRecordToLine(Client) << std::endl;
		DataFile.close();
	}
}

void DeleteClientFromFile(std::string FileName, std::vector<stClientsData>& vAllClients)
{
	std::fstream DataFile;
	DataFile.open(FileName, std::ios::out);

	if (DataFile.is_open())
	{
		std::string DataLine;
		for (stClientsData& Client : vAllClients)
		{
			if (!Client.MarkForDelete)
			{
				DataLine = ConvertRecordToLine(Client);
				DataFile << DataLine << std::endl;
			}
		}

		DataFile.close();
	}
}

//--------------Proccessing--------------

bool FindClientByAccountNumber(std::string AccountNumber, std::vector <stClientsData>& vAllClients, stClientsData& Client)
{
	for (stClientsData& C : vAllClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void MarkClientForDelete(std::string AccountNumber, std::vector <stClientsData>& vAllClients)
{
	for (stClientsData& Client : vAllClients)
	{
		if (Client.AccountNumber == AccountNumber)
			Client.MarkForDelete = true;
	}
}

// --------------Outputs--------------

void GetKeyPress()
{
	std::cout << "\n\nPress any key to back to Main Menu...";
	system("pause>0");
}

void ShowScreenTitle(std::string Title)
{
	std::cout << "=================================================\n";
	std::cout << "\t\t" << Title << std::endl;
	std::cout << "=================================================\n";
}

void PrintClientCard(stClientsData& Client)
{
	std::cout << "\nThe following are the client details:\n";
	std::cout << "---------------------------------------\n";
	std::cout << "Account Number : " << Client.AccountNumber << std::endl;
	std::cout << "PIN Code       : " << Client.PINCode << std::endl;
	std::cout << "Client Name    : " << Client.ClientName << std::endl;
	std::cout << "Phone Number   : " << Client.Phone << std::endl;
	std::cout << "Account Balance: " << Client.AccountBalance << std::endl;
	std::cout << "---------------------------------------\n";
}

void ShowMainMenuScreen()
{
	ShowScreenTitle("Main Menu Screen");
	std::cout << "[1] Show Clients List.\n";
	std::cout << "[2] Add New Client.\n";
	std::cout << "[3] Delete Client.\n";
	std::cout << "[4] Update Client Info.\n";
	std::cout << "[5] Find Client.\n";
	std::cout << "[6] Exit.\n";
	std::cout << "=================================================\n";
}

void ShowClientsList(std::vector <stClientsData>& vAllClientsDataList)
{
	
	system("cls");

	std::cout << "\n\t\t\t\t\tClients List (" << vAllClientsDataList.size() << ") Client(s)\n";

	std::cout << "----------------------------------------------------------------------------------------------------------\n";
	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(10) << "PIN Code";
	std::cout << "| " << std::left << std::setw(40) << "Client Name";
	std::cout << "| " << std::left << std::setw(15) << "Phone Number";
	std::cout << "| " << std::left << std::setw(18) << "Account Balance";
	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	for (stClientsData& Client : vAllClientsDataList)
	{
		std::cout << "| " << std::left << std::setw(15) << Client.AccountNumber;
		std::cout << "| " << std::left << std::setw(10) << Client.PINCode;
		std::cout << "| " << std::left << std::setw(40) << Client.ClientName;
		std::cout << "| " << std::left << std::setw(15) << Client.Phone;
		std::cout << "| " << std::left << std::setw(18) << Client.AccountBalance << std::endl;
	}
	std::cout << "----------------------------------------------------------------------------------------------------------\n";
	
	GetKeyPress();
}

void AddNewClientData(std::vector <stClientsData>& vAllClients)
{
	stClientsData Client;
	short AddMore = 'n';
	
	do
	{
		system("cls");

		std::cout << std::endl;
		ShowScreenTitle("Add New Client Screen");

		std::cout << "Adding New Client:\n\n";

		Client.AccountNumber = GetString("Enter Account Number? ", true);

		while (FindClientByAccountNumber(Client.AccountNumber, vAllClients, Client))
		{
			std::cout << "Client with account number [" << Client.AccountNumber << "] already exist, ";
			Client.AccountNumber = GetString("Enter another account number? ");
		}

		Client = ReadClientData(Client.AccountNumber);

		SaveClientToFile(ClientsFileName, Client);

		vAllClients = LoadDataFromFile(ClientsFileName);
		
		AddMore = GetCharacter("\n\nClient added successfully. Do you want to add more clients (y/n) ");

	} while (AddMore == 'y' || AddMore == 'Y');

	GetKeyPress();
}

void DeleteClientData(std::vector <stClientsData>& vAllClients)
{
	stClientsData Client;
	std::string AccountNumber;
	short Answer = 'n';

	system("cls");
	
	ShowScreenTitle("Delete Client Screen");

	AccountNumber = GetString("\nEnter Account Number? ", true);

	if (FindClientByAccountNumber(AccountNumber, vAllClients, Client))
	{
		PrintClientCard(Client);

		Answer = GetCharacter("\n\nAre you sure you want to delete this client (y/n)? ");

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDelete(AccountNumber, vAllClients);
			DeleteClientFromFile(ClientsFileName, vAllClients);

			std::cout << "\n\nClient deleted successfully.\n";
		}
	}
	else
		std::cout << "\n\nClient With Account Number (" << AccountNumber << ") does NOT exist";

	GetKeyPress();
}

void UpdateClientInfo(std::vector <stClientsData>& vAllClients)
{
	stClientsData Client;
	std::string AccountNumber;
	char Answer = 'n';

	system("cls");

	ShowScreenTitle("Update Client Info Screen");

	AccountNumber = GetString("\nEnter Account Number? ", true);

	if (FindClientByAccountNumber(AccountNumber, vAllClients, Client))
	{
		PrintClientCard(Client);
		
		Answer = GetCharacter("\n\nAre you sure you want to update this client (y/n)? ");

		std::cout << std::endl << std::endl;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClientsData& C : vAllClients)
			{
				if (C.AccountNumber == AccountNumber)
					C = ReadClientData(AccountNumber);
			}
			
			SaveDataToFile(ClientsFileName, vAllClients);

			std::cout << "\n\nClient updated successfully.\n";
		}
	}
	else
		std::cout << "\n\nClient With Account Number (" << AccountNumber << ") does NOT exist";

	GetKeyPress();

}

void FindClientInfo(std::vector <stClientsData>& vAllClients)
{
	std::string AccountNumber;
	stClientsData Client;

	system("cls");
	ShowScreenTitle("Find Client Screen");

	AccountNumber = GetString("Enter Account Number? ", true);

	if (FindClientByAccountNumber(AccountNumber, vAllClients, Client))
		PrintClientCard(Client);
	else
		std::cout << "\n\nClient With Account Number (" << AccountNumber << ") does NOT exist";
	
	GetKeyPress();
}

void Bank_1()
{
	std::vector <stClientsData> vAllClients;
	enMenu UserChoice = enMenu::Non;

	while (UserChoice != 6)
	{
		system("cls");

		vAllClients = LoadDataFromFile(ClientsFileName);

		ShowMainMenuScreen();
		UserChoice = GetUserChoice();

		switch (UserChoice)
		{
		case enMenu::ShowClients:
			ShowClientsList(vAllClients);
			break;

		case enMenu::AddClient:
			AddNewClientData(vAllClients);
			break;

		case enMenu::DeleteClient:
			DeleteClientData(vAllClients);
			break;

		case enMenu::UpdateClient:
			UpdateClientInfo(vAllClients);
			break;

		case enMenu::FindClient:
			FindClientInfo(vAllClients);
			break;

		case enMenu::Exit:
			break;

		default:
			std::cout << "\n\nSomething Went Wrong!\n";
			break;
		}
	}
}

int main()
{
	Bank_1();
	return 0;
}