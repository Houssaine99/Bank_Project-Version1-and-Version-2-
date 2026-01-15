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
void ShowMainMenu();

struct sClients
{
	std::string AccountNumber;
	std::string PINCode;
	std::string Name;
	std::string Phone;

	double AccountBalance = 0;

	bool MarkForDelete = false;
};

enum enMainMenuOptions
{
	eShowClientsList = 1,
	eAddClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eExit = 6
};

std::vector <std::string> SplitString(std::string StrToSplit, std::string delim)
{
	std::vector <std::string> vSplitedStr;
	std::string SingleWord;
	short pos = 0;

	while ((pos = StrToSplit.find(delim)) != std::string::npos)
	{
		SingleWord = StrToSplit.substr(0, pos);
		
		if (SingleWord != "")
			vSplitedStr.push_back(SingleWord);

		StrToSplit.erase(0, pos + delim.length());
	}
	if (StrToSplit != "")
		vSplitedStr.push_back(StrToSplit);

	return vSplitedStr;
}

sClients ConvertLineToRecord(std::string Line, std::string Seperator = "#//#")
{
	std::vector <std::string> vSplitedLine = SplitString(Line, Seperator);
	sClients Client;

	Client.AccountNumber = vSplitedLine[0];
	Client.PINCode = vSplitedLine[1];
	Client.Name = vSplitedLine[2];
	Client.Phone = vSplitedLine[3];
	Client.AccountBalance = std::stod(vSplitedLine[4]);

	return Client;
}

std::string ConvertRecordToLien(sClients Record, std::string Seperator = "#//#")
{
	std::string Line;

	Line += Record.AccountNumber + Seperator;
	Line += Record.PINCode + Seperator;
	Line += Record.Name + Seperator;
	Line += Record.Phone + Seperator;
	Line += std::to_string(Record.AccountBalance);

	return Line;

}

std::vector <sClients> LoadClientsDataFromFile(std::string FileName)
{
	std::vector <sClients> vAllClients;

	std::fstream MyFile;
	MyFile.open(FileName, std::ios::in);

	if (MyFile.is_open())
	{
		std::string Line;
		sClients Client;

		while (std::getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vAllClients.push_back(Client);
		}

		MyFile.close();
	}

	return vAllClients;
}

void AddDataLineToFile(std::string FileName, std::string Line)
{
	std::fstream MyFile;
	MyFile.open(FileName, std::ios::out | std::ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << std::endl;
		MyFile.close();
	}
}

void SaveClientDataToFile(std::string FileName, std::vector <sClients>& vAllClients)
{
	std::fstream MyFile;
	MyFile.open(FileName, std::ios::out);

	if (MyFile.is_open())
	{
		for (sClients& Client : vAllClients)
		{
			std::string Line;

			if (!Client.MarkForDelete)
			{
				Line = ConvertRecordToLien(Client);
				MyFile << Line << std::endl;
			}
		}

		MyFile.close();
	}
}

bool ClientExistsByAccountNumber(std::string FileName, std::string AccountNumber)
{
	std::fstream MyFile;
	MyFile.open(FileName, std::ios::in);

	if (MyFile.is_open())
	{
		sClients Client;
		std::string Line;

		while(std::getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

sClients ReadNewClient()
{
	sClients Client;

	std::cout << "Enter Account Number? ";
	std::getline(std::cin >> std::ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(ClientsFileName, Client.AccountNumber))
	{
		std::cout << "\nClient with account number [" << Client.AccountNumber << "] is already exists. Enter another account number? ";
		std::getline(std::cin >> std::ws, Client.AccountNumber);
	}

	std::cout << "Enter PIN Code? ";
	std::getline(std::cin, Client.PINCode);

	std::cout << "Enter Client Name? ";
	std::getline(std::cin, Client.Name);

	std::cout << "Enter Phone Number? ";
	std::getline(std::cin, Client.Phone);

	std::cout << "Enter Account Balance? ";
	std::cin >> Client.AccountBalance;

	return Client;
}

std::string ReadAccountNumber()
{
	std::string InputValue;
	std::cout << "\nEnter Account Number? ";
	std::getline(std::cin >> std::ws, InputValue);

	return InputValue;
}

void PrintClientCard(sClients& Client)
{
	std::cout << "\nThe following are the client details:\n";
	std::cout << "---------------------------------------\n";
	std::cout << "Account Number : " << Client.AccountNumber << std::endl;
	std::cout << "PIN Code       : " << Client.PINCode << std::endl;
	std::cout << "Client Name    : " << Client.Name << std::endl;
	std::cout << "Phone Number   : " << Client.Phone << std::endl;
	std::cout << "Account Balance: " << Client.AccountBalance << std::endl;
	std::cout << "---------------------------------------\n";
}

sClients ChangeClientRecord(std::string AccountNumber)
{
	sClients Client;

	Client.AccountNumber = AccountNumber;

	std::cout << "\n\nEnter PIN Code? ";
	std::getline(std::cin >> std::ws, Client.PINCode);

	std::cout << "Enter Name? ";
	std::getline(std::cin, Client.Name);

	std::cout << "Enter Phone? ";
	std::getline(std::cin, Client.Phone);

	std::cout << "Enter Account Balance? ";
	std::cin >> Client.AccountBalance;

	return Client;
}

bool FindClientByAccountNumber(std::string AccountNumber, sClients& Client, std::vector <sClients>& vAllClients)
{
	for (sClients& C : vAllClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void MarkClientForDeleteByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	for (sClients& Client : vAllClients)
	{
		if (Client.AccountNumber == AccountNumber)
			Client.MarkForDelete = true;
	}
}

void DeleteClientByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	sClients Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vAllClients))
	{
		PrintClientCard(Client);

		std::cout << "\n\nAre you sure you want to delete this client (y/n)? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vAllClients);
			SaveClientDataToFile(ClientsFileName, vAllClients);
			vAllClients = LoadClientsDataFromFile(ClientsFileName);

			std::cout << "\n\nClient Deleted Successfully.";
		}
	}
	else
		std::cout << "\n\nClient with account number [" << AccountNumber << "] is NOT found!";
}

void UpdateClientByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	sClients Client;
	char Answer = 'y';

	if (FindClientByAccountNumber(AccountNumber, Client, vAllClients))
	{
		PrintClientCard(Client);

		std::cout << "\n\nAre you sure you want to update this client (y/n)?  ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (sClients& C : vAllClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientDataToFile(ClientsFileName, vAllClients);

			std::cout << "\n\nClient Updated Successfully";
		}
	}
	else
		std::cout << "\n\nClient with account number [" << AccountNumber << "] is NOT found!";

}

void ShowEndScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Program Ends";
	std::cout << "\n------------------------------------------------------------\n";
}

void ShowFindClientScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Find Client Screen";
	std::cout << "\n------------------------------------------------------------\n";

	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	sClients Client;

	std::string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client, vAllClients))
		PrintClientCard(Client);
	else
		std::cout << "\n\nClient with account number [" << AccountNumber << "] is NOT found!";

}

void ShowUpdateClientScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Update Client Screen";
	std::cout << "\n------------------------------------------------------------\n";

	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	std::string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vAllClients);
}

void ShowDeleteClientScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Delete Client Screen";
	std::cout << "\n------------------------------------------------------------\n";

	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	std::string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vAllClients);
}

void AddNewClient()
{
	sClients Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLien(Client));
}

void AddNewClients()
{
	char AddMore = 'n';
	do
	{
		std::cout << "Adding New Client:\n\n";

		AddNewClient();

		std::cout << "\nClient Added Successfully. Do you want to add more (y/n)? ";
		std::cin >> AddMore;

		std::cout << std::endl << std::endl;

	} while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientsScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Add New Clients Screen";
	std::cout << "\n------------------------------------------------------------\n";

	AddNewClients();
}

void ShowAllClientsScreen()
{
	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);

	std::cout << "\n\t\t\t\t\tClients List (" << vAllClients.size() << ") Client(s)\n";

	std::cout << "----------------------------------------------------------------------------------------------------------\n";
	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(10) << "PIN Code";
	std::cout << "| " << std::left << std::setw(40) << "Client Name";
	std::cout << "| " << std::left << std::setw(15) << "Phone Number";
	std::cout << "| " << std::left << std::setw(18) << "Account Balance";
	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	if (vAllClients.size() == 0)
		std::cout << "\t\t\t\t\tNo Clients To Show In The System!\n";
	else
		for (sClients& Client : vAllClients)
		{
			std::cout << "| " << std::left << std::setw(15) << Client.AccountNumber;
			std::cout << "| " << std::left << std::setw(10) << Client.PINCode;
			std::cout << "| " << std::left << std::setw(40) << Client.Name;
			std::cout << "| " << std::left << std::setw(15) << Client.Phone;
			std::cout << "| " << std::left << std::setw(18) << Client.AccountBalance << std::endl;
		}

	std::cout << "----------------------------------------------------------------------------------------------------------\n";
}

void GoBackToMainMenu()
{
	std::cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	ShowMainMenu();
}

short ReadMainMenuOption()
{
	short InputValue = 0;
	std::cout << "Choose what do you want to do [1 to 6]?  ";
	std::cin >> InputValue;

	return InputValue;
}

void PerformMainMenuOptions(enMainMenuOptions MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMainMenuOptions::eShowClientsList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
		
	case enMainMenuOptions::eAddClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

void ShowMainMenu()
{
	system("cls");
	std::cout << "============================================================\n";
	std::cout << "                    Main Menu Screen\n";
	std::cout << "============================================================\n";
	std::cout << "\t[1] Show Clients List.\n";
	std::cout << "\t[2] Add New Client.\n";
	std::cout << "\t[3] Delete Client.\n";
	std::cout << "\t[4] Update Client Info.\n";
	std::cout << "\t[5] Find Client.\n";
	std::cout << "\t[6] Exit.\n";
	std::cout << "============================================================\n";
	PerformMainMenuOptions((enMainMenuOptions)ReadMainMenuOption());
}

int main()
{
	ShowMainMenu();
	return 0;
}