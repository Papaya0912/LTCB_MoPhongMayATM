# 🏧 ATM & Bank Management Simulation System

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20(Console)-lightgrey.svg)

## 📌 Overview
A comprehensive console-based ATM and Bank Management System written in C. This project simulates real-world banking operations, including user authentication, transaction processing (deposits, withdrawals, transfers), and administrative controls. It utilizes local File I/O for persistent data storage, ensuring that account balances and transaction histories are saved across sessions.

## ✨ Key Features

### 👤 User Panel
* **Secure Login**: Password-protected access with a strict security policy (accounts lock automatically after 3 failed login attempts).
* **Fund Management**: Deposit and withdraw money with real-time balance validation.
* **Money Transfers**: Transfer funds seamlessly to other registered account IDs.
* **Transaction History**: View a detailed log of all past transactions (deposits, withdrawals, transfers) complete with precise timestamps (Epoch time conversion).

### 🛡️ Administrator Panel
* **Account Provisioning**: Register new bank accounts or delete existing ones.
* **Security Control**: Manually lock suspicious accounts or unlock accounts penalized by the 3-fail rule.
* **Administrative Override**: Direct fund deposits into user accounts for system rewards or issue resolutions.

## 🛠️ Technical Implementation
* **Data Structures**: Extensively uses `struct` to model Bank Accounts and arrays/pointers for memory manipulation.
* **File Handling (I/O)**: Uses `fopen`, `fprintf`, and `fscanf` to persistently store user credentials, balances, and history in `Danhsachtaikhoan.txt`.
* **System Utilities**: Integrates `<time.h>` for timestamping operations and `<conio.h>` for interactive console prompts (`getch()`).

## 🚀 Getting Started

### Prerequisites
* A C Compiler (e.g., GCC, MinGW)
* Windows OS (due to the usage of `<conio.h>` and `system("cls")`)

### Compilation & Execution
1. Clone the repository:
2. Navigate to the source code directory and compile the program:
3. Run the application:
