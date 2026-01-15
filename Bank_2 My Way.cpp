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
void ShowTransactionsMenu();

enum enMainMenuOptions
{
	eClientsList = 1,
	eAddClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransactions = 6,
	eExit = 7
};

enum enTransactionsMenuOptions
{
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalances = 3,
	eMainMenu = 4
};

struct sClients
{
	std::string AccountNumber;
	std::string PINCode;
	std::string Name;
	std::string Phone;

	double AccountBalance = 0;

	bool MarkForDelete = false;
};

// ----------------------------------> Data_Base <----------------------------------

std::vector <std::string> SplitString(std::string StrToSplit, std::string delim)
{
	std::vector <std::string> vSplitedString;
	std::string Word;
	short pos = 0;

	while ((pos = StrToSplit.find(delim)) != std::string::npos)
	{
		Word = StrToSplit.substr(0, pos);

		if (Word != "")
			vSplitedString.push_back(Word);

		StrToSplit.erase(0, pos + delim.length());
	}
	if (StrToSplit != "")
		vSplitedString.push_back(StrToSplit);

	return vSplitedString;
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

bool ClientExistsByAccountNumber(std::string FileName, std::string AccountNumber)
{
	std::fstream MyFile;
	MyFile.open(FileName, std::ios::in);

	if (MyFile.is_open())
	{
		std::string Line;
		sClients Client;

		while (std::getline(MyFile, Line))
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

void SaveClientsDataToFile(std::string FileName, std::vector <sClients>& vAllClients)
{
	std::fstream MyFile;
	MyFile.open(FileName, std::ios::out);

	if (MyFile.is_open())
	{
		std::string Line;
		for (sClients& Client : vAllClients)
		{
			if (!Client.MarkForDelete)
			{
				Line = ConvertRecordToLien(Client);
				MyFile << Line << std::endl;
			}
		}
		MyFile.close();
	}
}

// ----------------------------------> Input <----------------------------------

short ReadMainMenuOption()
{
	short InputValue = 0;
	std::cout << "Choose what do you want to do [1 to 6]? ";
	std::cin >> InputValue;

	return InputValue;
}

short ReadTransactionsMenuOption()
{
	short InputValue = 0;
	std::cout << "Choose what do you want to do [1 to 4]? ";
	std::cin >> InputValue;

	return InputValue;
}

double ReadDepositAmount()
{
	double InputValue = 0;
	std::cout << "\nPlease enter deposit amount? ";
	std::cin >> InputValue;

	return InputValue;
}

double ReadWithdrawAmount()
{
	double InputValue = 0;
	std::cout << "\nPlease enter withdraw amount? ";
	std::cin >> InputValue;

	return InputValue;
}

sClients ReadNewClient()
{
	sClients Client;

	std::cout << "Enter Account Number? ";
	std::getline(std::cin >> std::ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(ClientsFileName, Client.AccountNumber))
	{
		std::cout << "\nClient with account number [" << Client.AccountNumber << "] is already exists! Enter Account Number? ";
		std::getline(std::cin, Client.AccountNumber);
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
	std::cout << "Enter Account Number? ";
	std::getline(std::cin >> std::ws, InputValue);

	return InputValue;
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

// ----------------------------------> Processing <----------------------------------

void BackToMainMenu()
{
	std::cout << "\n\nPress any key to back to Main Menu...";
	system("pause>0");
	system("cls");
	ShowMainMenu();
}

void BackToTransactionsMenu()
{
	std::cout << "\n\nPress any key to back to Transactions Menu...";
	system("pause>0");
	system("cls");
	ShowTransactionsMenu();
}

void AddNewClient()
{
	sClients Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLien(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';

	do
	{
		std::cout << "Adding New Client\n\n";

		AddNewClient();

		std::cout << "\n\nClient Added Susccessfully. Do you want to add more clients (y/n)? ";
		std::cin >> AddMore;

		std::cout << std::endl << std::endl;

	} while (toupper(AddMore) == 'Y');
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

void MarkClientForDeleteByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	for (sClients& Client : vAllClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.MarkForDelete = true;
			break;
		}
	}
}

void DeleteClientByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	sClients Client;
	char Answer = 'Y';

	if (FindClientByAccountNumber(AccountNumber, Client, vAllClients))
	{
		PrintClientCard(Client);

		std::cout << "\n\nAre you sure you want to delete this client (y/n)? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vAllClients);
			SaveClientsDataToFile(ClientsFileName, vAllClients);

			std::cout << "\n\nClient Deleted Successfully!";
		}
	}
	else
		std::cout << "\n\nClient with account number [" << AccountNumber << "] is NOT found!";
}

void UpdateClientByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	sClients Client;
	char Answer = 'Y';

	if (FindClientByAccountNumber(AccountNumber, Client, vAllClients))
	{
		PrintClientCard(Client);

		std::cout << "\n\nAre you sure you want to update this client (y/n)? ";
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

			SaveClientsDataToFile(ClientsFileName, vAllClients);

			std::cout << "\n\nClient Updated Successfully!";
		}
	}
	else
		std::cout << "\n\nClient with account number [" << AccountNumber << "] is NOT found!";
}

double AddDepositToClientBalance(std::string AccountNumber, double DepositAmount, std::vector <sClients>& vAllClients)
{
	double NewBalance = 0;
	for (sClients& C : vAllClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.AccountBalance += DepositAmount;
			NewBalance = C.AccountBalance;
			break;
		}
	}
	SaveClientsDataToFile(ClientsFileName, vAllClients);

	return NewBalance;
}

void AddDepositByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	sClients Client;
	char Answer = 'y';
	double DepositAmount = 0;

	while (!FindClientByAccountNumber(AccountNumber, Client, vAllClients))
	{
		std::cout << "\nClient with account number [" << AccountNumber << "] does not exist!\n\n";
		AccountNumber = ReadAccountNumber();
	}

	PrintClientCard(Client);

	DepositAmount = ReadDepositAmount();

	std::cout << "\n\nAre you sure you want to perform this transaction (y/n)? ";
	std::cin >> Answer;

	if (toupper(Answer) == 'Y')
		std::cout << "\n\nOperation Done Successfully. New Balance is: " << AddDepositToClientBalance(AccountNumber, DepositAmount, vAllClients);
}

double WithdrawFromClientBalance(std::string AccountNumber, double WithdrawAmount, std::vector <sClients>& vAllClients)
{
	double NewBalance = 0;
	for (sClients& C : vAllClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.AccountBalance -= WithdrawAmount;
			NewBalance = C.AccountBalance;
			break;
		}
	}
	SaveClientsDataToFile(ClientsFileName, vAllClients);

	return NewBalance;
}

void WithdrawByAccountNumber(std::string AccountNumber, std::vector <sClients>& vAllClients)
{
	sClients Client;
	char Answer = 'y';
	double WithdrawAmount = 0;

	while (!FindClientByAccountNumber(AccountNumber, Client, vAllClients))
	{
		std::cout << "\nClient with account number [" << AccountNumber << "] does not exist!\n\n";
		AccountNumber = ReadAccountNumber();
	}

	PrintClientCard(Client);

	WithdrawAmount = ReadWithdrawAmount();

	while (WithdrawAmount > Client.AccountBalance)
	{
		std::cout << "\n\nAmount exceeds the balance, you can withdraw up to " << Client.AccountBalance << std::endl;
		WithdrawAmount = ReadWithdrawAmount();
	}
	

	std::cout << "\n\nAre you sure you want to perform this transaction (y/n)? ";
	std::cin >> Answer;

	if (toupper(Answer) == 'Y')
		std::cout << "\n\nOperation Done Successfully. New Balance is: " << WithdrawFromClientBalance(AccountNumber, WithdrawAmount, vAllClients);

}

double TotalBalances(std::vector <sClients>& vAllCients)
{
	double TotalBalances = 0;

	for (sClients& Client : vAllCients)
	{
		TotalBalances += Client.AccountBalance;
	}

	return TotalBalances;
}

// ----------------------------------> Output <----------------------------------

void ShowClientsListScreen()
{
	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);

	int NumberOfClients = vAllClients.size();
	
	std::cout << "\n\t\t\t\t\tClients List (" << NumberOfClients << ") Client(s)\n";

	std::cout << "-------------------------------------------------------------------------------------------------------------\n";
	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(10) << "PIN Code";
	std::cout << "| " << std::left << std::setw(40) << "Client Name";
	std::cout << "| " << std::left << std::setw(15) << "Phone Number";
	std::cout << "| " << std::left << std::setw(18) << "Account Balance" << std::left << std::setw(1) << "|";
	std::cout << "\n-------------------------------------------------------------------------------------------------------------\n";

	if (NumberOfClients == 0)
		std::cout << "|\t\t\t\t\tNo Clients To Show In The System" << std::right << std::setw(37) << "|" << std::endl;

	else
		for (sClients& Client : vAllClients)
		{
			std::cout << "| " << std::left << std::setw(15) << Client.AccountNumber;
			std::cout << "| " << std::left << std::setw(10) << Client.PINCode;
			std::cout << "| " << std::left << std::setw(40) << Client.Name;
			std::cout << "| " << std::left << std::setw(15) << Client.Phone;
			std::cout << "| " << std::left << std::setw(18) << Client.AccountBalance << std::left << std::setw(1) << "|" << std::endl;
		}

	std::cout << "-------------------------------------------------------------------------------------------------------------\n";
}

void ShowAddClientsScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Add New Clients Screen";
	std::cout << "\n------------------------------------------------------------\n";

	AddNewClients();
}

void ShowDeleteClientScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Delete Clients Screen";
	std::cout << "\n------------------------------------------------------------\n";

	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	std::string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vAllClients);
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

void ShowFindClientScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Find Client Screen";
	std::cout << "\n------------------------------------------------------------\n";

	sClients Client;
	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	std::string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client, vAllClients))
		PrintClientCard(Client);
	else
		std::cout << "\n\nClient with account number [" << AccountNumber << "] is NOT found!";
}

void ShowEndScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Program Ends";
	std::cout << "\n------------------------------------------------------------\n";
}

void ShowDepositScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Deposit Screen";
	std::cout << "\n------------------------------------------------------------\n";

	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	std::string AccountNumber = ReadAccountNumber();

	AddDepositByAccountNumber(AccountNumber, vAllClients);
}

void ShowWithdrawScreen()
{
	std::cout << "\n------------------------------------------------------------\n";
	std::cout << "                    Withdraw Screen";
	std::cout << "\n------------------------------------------------------------\n";

	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	std::string AccountNumber = ReadAccountNumber();

	WithdrawByAccountNumber(AccountNumber, vAllClients);
}

void ShowTotalBalancesScreen()
{
	std::vector <sClients> vAllClients = LoadClientsDataFromFile(ClientsFileName);
	int NumberOfClients = vAllClients.size();

	std::cout << "\n\t\t\t\t\tBalances List (" << NumberOfClients << ") Client(s)\n";

	std::cout << "-------------------------------------------------------------------------------------------------------------\n";
	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(58) << "Client Name";
	std::cout << "| " << std::left << std::setw(29) << "Account Balance" << std::left << std::setw(1) << "|";
	std::cout << "\n-------------------------------------------------------------------------------------------------------------\n";

	for (sClients& Client : vAllClients)
	{
		std::cout << "| " << std::left << std::setw(15) << Client.AccountNumber;
		std::cout << "| " << std::left << std::setw(58) << Client.Name;
		std::cout << "| " << std::left << std::setw(29) << Client.AccountBalance << std::left << std::setw(1) << "|" << std::endl;
	}

	std::cout << "-------------------------------------------------------------------------------------------------------------\n";
	std::cout << "\n\t\t\t\t\t\t\t\tTotal Balances = " << TotalBalances(vAllClients);
}

void PerformTransactionsMenuOptions(enTransactionsMenuOptions TransactionsMenuOption)
{
	switch (TransactionsMenuOption)
	{
	case enTransactionsMenuOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		BackToTransactionsMenu();
		break;

	case enTransactionsMenuOptions::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		BackToTransactionsMenu();
		break;

	case enTransactionsMenuOptions::eTotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		BackToTransactionsMenu();
		break;

	case enTransactionsMenuOptions::eMainMenu:
		system("cls");
		ShowMainMenu();
		break;
	}
}

void ShowTransactionsMenu()
{
	std::cout << "============================================================\n";
	std::cout << "                    Transactions Menu Screen\n";
	std::cout << "============================================================\n";
	std::cout << "\t[1] Deposit.\n";
	std::cout << "\t[2] Withdraw.\n";
	std::cout << "\t[3] Total Balances.\n";
	std::cout << "\t[4] Main Menu.\n";
	std::cout << "============================================================\n";
	PerformTransactionsMenuOptions((enTransactionsMenuOptions)ReadTransactionsMenuOption());

}

void PerformMainMenuOptions(enMainMenuOptions MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMainMenuOptions::eClientsList:
		system("cls");
		ShowClientsListScreen();
		BackToMainMenu();
		break;

	case enMainMenuOptions::eAddClient:
		system("cls");
		ShowAddClientsScreen();
		BackToMainMenu();
		break;

	case enMainMenuOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		BackToMainMenu();
		break;

	case enMainMenuOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		BackToMainMenu();
		break;

	case enMainMenuOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		BackToMainMenu();
		break;

	case enMainMenuOptions::eTransactions:
		system("cls");
		ShowTransactionsMenu();
		break;

	case enMainMenuOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

void ShowMainMenu()
{
	std::cout << "============================================================\n";
	std::cout << "                    Main Menu Screen\n";
	std::cout << "============================================================\n";
	std::cout << "\t[1] Show Clients List.\n";
	std::cout << "\t[2] Add New Client.\n";
	std::cout << "\t[3] Delete Client.\n";
	std::cout << "\t[4] Update Client Info.\n";
	std::cout << "\t[5] Find Client.\n";
	std::cout << "\t[6] Transactions.\n";
	std::cout << "\t[7] Exit.\n";
	std::cout << "============================================================\n";
	PerformMainMenuOptions((enMainMenuOptions)ReadMainMenuOption());
}

int main()
{
	ShowMainMenu();
	return 0;
}