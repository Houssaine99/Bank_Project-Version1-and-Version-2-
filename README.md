# Bank Management System 🏦

A console-based banking application developed in C++ that provides comprehensive client account management and transaction operations.

## 📋 Project Overview

This repository contains two complete implementations of a banking management system:
- **Dr. Mohammed Abu-Hadhoud's Way**: Following the instructor's approach and methodology
- **My Way**: Personal implementation with custom optimizations and structure

Both implementations solve the same problem but demonstrate different coding styles, function organization, and implementation strategies.

## ✨ Features

### Bank System Version 1
- **Client Management**
  - View all clients list
  - Add new clients
  - Delete existing clients
  - Update client information
  - Find specific client by account number

### Bank System Version 2 (Extended)
All features from Version 1, plus:
- **Transaction Operations**
  - Deposit money to client accounts
  - Withdraw money from client accounts
  - View total balances across all accounts
  - Transaction validation and confirmation

## 🗂️ Project Structure

```
.
├── Bank_1 Dr Way.cpp          # Version 1 - Instructor's implementation
├── Bank_1 My Way.cpp          # Version 1 - Personal implementation
├── Bank_2 Dr Way.cpp          # Version 2 - Instructor's implementation
├── Bank_2 My Way.cpp          # Version 2 - Personal implementation
└── ClientsDataBase.txt        # Data storage file (auto-generated)
```

## 🔧 Technical Details

### Data Structure
```cpp
struct sClients {
    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete;
};
```

### File Storage Format
Client data is stored in a text file using the delimiter `#//#`:
```
AccountNumber#//#PINCode#//#ClientName#//#Phone#//#Balance
```

### Key Components

**Input Validation**
- Account number uniqueness checking
- Balance validation for withdrawals
- User confirmation for critical operations

**File Operations**
- Load client data from file
- Save/update client records
- Append new client records
- Delete records with mark-for-delete pattern

**Menu System**
- Main menu navigation
- Transaction submenu
- Clear screen transitions
- User-friendly prompts

## 🚀 How to Run

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- C++11 or higher

### Compilation

```bash
# For Dr. Way implementation
g++ "Bank_1 Dr Way.cpp" -o bank1_dr
g++ "Bank_2 Dr Way.cpp" -o bank2_dr

# For My Way implementation
g++ "Bank_1 My Way.cpp" -o bank1_my
g++ "Bank_2 My Way.cpp" -o bank2_my
```

### Execution

```bash
# Run any compiled version
./bank1_dr
./bank1_my
./bank2_dr
./bank2_my
```

## 🎯 Key Differences Between Implementations

### Dr. Mohammed Abu-Hadhoud's Approach
- Structured function organization
- Clear separation of concerns
- Standard procedural flow
- Traditional menu handling with recursion

### My Approach
- Enhanced input validation with `InputFail()` function
- More modular input functions
- Loop-based menu system (avoiding recursion)
- Additional helper functions for code reusability
- Improved error handling
- Cleaner separation between data processing and display

## 📖 Usage Example

### Adding a New Client
1. Select option `[2] Add New Client` from main menu
2. Enter account number (must be unique)
3. Enter PIN code
4. Enter client name
5. Enter phone number
6. Enter initial account balance
7. Choose to add more clients or return to menu

### Making a Transaction (Version 2)
1. Select option `[6] Transactions` from main menu
2. Choose transaction type (Deposit/Withdraw)
3. Enter account number
4. Verify client details
5. Enter transaction amount
6. Confirm transaction
7. View updated balance

## ⚠️ Important Notes

- The program uses `system("cls")` for Windows. For Linux/Mac, replace with `system("clear")`
- `system("pause>0")` is Windows-specific
- Client data persists in `ClientsDataBase.txt`
- Always backup the database file before testing delete operations
- Account numbers must be unique across the system

## 🎓 Learning Outcomes

This project demonstrates:
- File I/O operations in C++
- Data structure implementation
- Menu-driven console applications
- CRUD operations (Create, Read, Update, Delete)
- Input validation techniques
- Vector manipulation
- String parsing and manipulation
- Function organization and modular programming

## 👨‍💻 Author

**El Houssaine Ambarki**
- Project Start Date: 15:30, 09/08/2025
- Instructor: Dr. Mohammed Abu-Hadhoud

## 📝 License

This project is created for educational purposes as part of programming coursework.

---

**Note**: Both implementations are fully functional and can be used independently. Choose the version that best fits your learning style or coding preferences.
