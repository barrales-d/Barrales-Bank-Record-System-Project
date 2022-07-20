#include <iostream>


#include "Users.hpp"
#include "Admin.hpp"


using namespace std;

void SignIn();
void Register();
void LogIn_Admin();
void CreateAccount_Admin(Admin& admin);
void DeleteAccount_Admin(Admin& admin);
void ViewAccounts_Admin(Admin& admin);
void WithdrawOrDeposit(Users& user);
void Withdraw(Users& user);
void Deposit(Users& user);
void ViewAccount(Users& user);

// ______________________MAIN______________________
int main() {
	int choice = 0;
	//	step 1: sign in or register
	do {
		cout << "\nHello, welcome to Barrales Banking System!\n" << endl;
		cout << "	1---> Sign In" << endl;
		cout << "	2---> Register" << endl;
		cout << "	3---> Admin" << endl;
		cout << "	4---> Exit Program\n" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice == 1) {//	Sign In to existing account, try to find a file with the log in info
			SignIn();
		}
		else if (choice == 2) {//	 Register an account, try to create a file with log in info
			Register();
		}
		else if (choice == 3) {//	Admin: log into admin account
			LogIn_Admin();
		}
		if (choice > 4 || choice < 1)
		{
			cout << "Invalid Option!" << endl;
		}
	} while (choice != 4);
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
	cout << "\nOk your Account has been created, please sign in\n" << endl;
	SignIn();
}
//	!END Register

//	Admin power :: logging into admin account
void LogIn_Admin() {
	std::string userName, password;
	cout << "Enter Admin Log In Information: " << endl;
	cout << "	Username: ";
	cin >> userName;
	cout << "	Password: ";
	cin >> password;
	try {
		Admin admin(userName, password);
		int choice;
		cout << "\nWelcome Admin! What would you like to do today?" << endl;
		do {
			cout << "	1---> Create Account" << endl;
			cout << "	2---> Delete Account" << endl;
			cout << "	3---> View All Accounts" << endl;
			cout << "	4---> Sign Out" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice == 1) {
				CreateAccount_Admin(admin);
			}
			else if (choice == 2) {
				DeleteAccount_Admin(admin);
			}
			else if (choice == 3) {
				ViewAccounts_Admin(admin);
			}
			else if(choice > 4 || choice < 1) {
				cout << "Invalid Option!" << endl;
			}
		} while (choice != 4);
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

	cout << "\nWhat type of account would to like to open?(Checkings or Savings) ";
	cin >> accountType;
	cout << "How much would you like to deposit as a starting amount? ";
	cin >> amount;
	do {
		cout << "\nWho would you like to make an account for?" << endl;
		cout << "	Username: ";
		cin >> username;
		cout << "	Password: ";
		cin >> password;

		try {
			int accountNumber = admin.createAccount(username, password, accountType, amount);

			cout << "\nOk, your account has been made. You will be able to deposite and withdrawal money from it!" << endl;
			cout << "	Please remember your account Number is: " << accountNumber << endl;
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

//	Admin power :: Delete Account 
void DeleteAccount_Admin(Admin& admin) {
	std::string username; 
	int num; 

	cout << "\nWho would you like to delete an account for?" << endl;
	cout << "	Username: ";
	cin >> username;
	cout << "Which Account would you like to delete today? Enter your Account number: ";
	cin >> num;
	
	try {
		admin.deleteAccount(username, num);
		cout << "\nOk! Your Account has been removed!" << endl;
	}
	catch (const std::logic_error& args) {
		cout << args.what() << endl;
	}
}
//	!END Delete Account
 
//	Admin power :: View Accounts
void ViewAccounts_Admin(Admin& admin) {
	std::string username;

	cout << "\nWho's account would you like to view today?" << endl;
	cout << "	Username: ";
	cin >> username;

	try {
		admin.viewAll(username);
	}
	catch (const std::logic_error& args) {
		cout << args.what() << endl;
	}
}
//	!END View Accounts

//	Users power :: withdraw / deposit Amount 
void WithdrawOrDeposit(Users& user) {
	int choice;
	cout << "\nWelcome to your account " << user.getName() << '!' << endl;
	do {
		cout << "Please selected which action to take: " << endl;
		cout << "	1---> Withdrawal" << endl;
		cout << "	2---> Deposit" << endl;
		cout << "	3---> View Account" << endl;
		cout << "	4---> Sign Out\n" << endl;
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
		else if(choice > 4 || choice < 1) {
			cout << "Invalid option!" << endl;
		}
	} while (choice != 4);
}
//	!END withdraw or Deposit

//	Users powers 
void Withdraw(Users& user) {
	//	call user funciton withdraw(account, amount)
	int num, amount, remainingAmount = 0;
	cout << "Enter the account number you wish to withdraw from: ";
	cin >> num;
	cout << "Enter the amount of money you would like to withdraw: ";
	cin >> amount; 
	try {
		remainingAmount = user.withdrawal(num, amount);
		cout << "\nOk! $" << amount << " was removed from your account, leaving you with $" << remainingAmount << " left in your account!\n" << endl;
	}
	catch (const std::logic_error& args) {
		cout << args.what() << endl;
	}
}
void Deposit(Users& user) {
	int num, amount, new_total = 0;
	cout << "Enter the account number you wish to deposit to: ";
	cin >> num;
	cout << "Enter the amount of money you would like to deposit: ";
	cin >> amount;
	try {
		new_total = user.deposit(num, amount);
		cout << "\nOk $" << amount << " has been deposited into your account. Your Account now holds: $" << new_total << endl;

	}
	catch (const std::logic_error& args) {
		cout << args.what() << endl;
	}
}
void ViewAccount(Users& user) {
	int accountNumber;
	cout << "Enter the account number you wish to view: ";
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
//	!END of users powers
