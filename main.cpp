#include <iostream>


#include "Users.hpp"
#include "Admin.hpp"


using namespace std;

void SignIn();
void Register();
void LogIn_Admin();
void CreateAccount_Admin(Admin& admin);
void WithdrawOrDeposit(Users& user);
void Withdraw(Users& user);
void Deposit(Users& user);
void ViewAccount(Users& user);

// ______________________MAIN______________________
int main() {
	int choice = 0;
	//	step 1: sign in or register
	cout << "Hello, welcome to Barrales Banking System!\n" << endl;
	do {
		cout << "	1---> Sign In" << endl;
		cout << "	2---> Register" << endl;
		cout << "	3---> Admin\n" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Invalid Option!" << endl;
		}
	} while (choice != 1 && choice != 2 && choice != 3);

	if (choice == 1) {//	Sign In to existing account, try to find a file with the log in info
		SignIn();
	}
	else if (choice == 2) {//	 Register an account, try to create a file with log in info
		Register();
	}
	else if (choice == 3) {//	Admin: log into admin account
		LogIn_Admin();
	}
	return 0;
}
// _____________________!_END_MAIN_________________________


//	Users power :: signing into their account
void SignIn() {
	std::string userName;
	std::string password;
	bool success = false;
	do {
		//	step 1: get username/password 
		cout << "Enter Log In information: " << endl;
		cout << "	Username: ";
		cin >> userName;
		cout << "	Password: ";
		cin >> password;

		// step 2: try to create an instance of a user with username and password
		try {
			Users user(userName, password);
			success = true;
			WithdrawOrDeposit(user);
		}
		catch (const std::invalid_argument& args) {
			cout << args.what() << endl;
			success = false;
		}
		catch (const std::logic_error& args) {
			cout << args.what() << endl;
			success = false;
		}
	} while (!success);
}
//	!END User sign in

// Users power :: register a new account
void Register() {
	std::string userName, name, email;
	std::string password;
	//	step 1: get username/password 
	cout << "Enter Basic Information: " << endl;
	cout << "	Name: ";
	cin.get();
	std::getline(cin, name);
	cout << "	Email: ";
	cin >> email;

	cout << "Enter Information: " << endl;
	cout << "	Username: ";
	cin >> userName;
	cout << "	Password: ";
	cin >> password;

	//	step 2: try to create instance with all information given
	try {
		Users user(userName, password, name, email);
	}
	catch (const std::invalid_argument& args) {
		cout << args.what() << endl;
	}
	SignIn();
}
//	!END Register

//	Admin power :: logging into admin account
void LogIn_Admin() {
	std::string userName, password;
	cout << "Enter Log In Information: " << endl;
	cout << "	Username: ";
	cin >> userName;
	cout << "	Password: ";
	cin >> password;
	try {
		Admin admin(userName, password);
		int choice;
		cout << "Welcome Admin! What would you like to do today?" << endl;
		cout << "	1---> Create Account" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice == 1) {
			CreateAccount_Admin(admin);
		}
		else {
			cout << "Invalid Option!" << endl;
		}
	}
	catch (const std::invalid_argument& args) {
		cout << args.what() << endl;
	}
	catch (const std::logic_error& args) {
		cout << args.what() << endl;
	}
}
//	!END logging into Admin account

//	Admin power :: Create Account
void CreateAccount_Admin(Admin& admin) {
	bool success = false;

	std::string username, password, accountType;
	int amount;

	cout << "What type of account would to like to open?(Checkings or Savings) ";
	cin >> accountType;
	cout << "How much would you like to deposit as a starting amount? ";
	cin >> amount;
	do {
		cout << "Who would you like to make an account for?" << endl;
		cout << "	Username: ";
		cin >> username;
		cout << "	Password: ";
		cin >> password;

		try {
			int accountNumber = admin.createAccount(username, password, accountType, amount);

			cout << "Ok, your account has been made. You will be able to deposite and withdrawal money from it!" << endl;
			cout << "Please remember your account Number is: " << accountNumber << endl;
			//	Once the program gets here we know everything worked you can exit the loop
			success = true;
		}
		catch (const std::logic_error& args) {
			cout << args.what() << endl;
			//	Error occur try to sign in again
			success = false;
		}
	} while (!success);
}
//	!END Create Account

//	Users power :: withdraw / deposit Amount 
void WithdrawOrDeposit(Users& user) {
	int choice;
	cout << "Welcome to your account " << user.getName() << '!' << endl;
	do {
		cout << "Please selected which action to take: " << endl;
		cout << "	1---> Withdrawal" << endl;
		cout << "	2---> Deposit" << endl;
		cout << "	3---> View Account\n" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice == 1) {
			Withdraw(user);
		}
		else if (choice == 2) {
			Deposit(user);
		}
		else if (choice == 3) {
			ViewAccount(user);
		}
		else {
			cout << "Invalid option!" << endl;
		}
	} while (choice != 1 && choice != 2);
}
//	!END withdraw or Deposit

void Withdraw(Users& user) {
	//	call user funciton withdraw(account, amount)
	return;
}
void Deposit(Users& user) {
	return;
}
void ViewAccount(Users& user) {
	int accountNumber;
	cout << "Enter the account Number you wish to view: ";
	cin >> accountNumber;
	try {
		Account account = user.getAccount(accountNumber);
		cout << "\nAccount Number: " << account.number << endl;
		cout << "Account Type: " << account.type << endl;
		cout << "Amount : $" << account.amount << endl << endl;
	}
	catch (...) {
		cout << "Account with that account number could not be found. " << endl;
	}
}
