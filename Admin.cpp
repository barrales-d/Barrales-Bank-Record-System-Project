
#include "Admin.hpp"
#include <iostream>

//	Destructor :: right before you destroy the Admin instance, update the .txt file to match the changes made
Admin::~Admin() {
	m_FileManager.open(m_fileName, std::fstream::out);
	//	have to rewrite everything because you can not edit a file easily 
	//	basic info
	m_FileManager << m_Password << std::endl;
	m_FileManager << getName() << std::endl;
	m_FileManager << getEmail() << std::endl;
	//	account database updates
	m_FileManager << ACCOUNT_TAG << std::endl;
	for (const auto& data : m_userDatabase) {
		m_FileManager << data.first << " " << data.second << std::endl;
	}

	m_FileManager.close();
}


//	Create Account 
int Admin::createAccount(const std::string& username, const std::string& password, const std::string& accountType, int startingAmount) {
	int number_of_accounts = 0;
	int accountNumber;	
	
	//	tries to find username within database
	try {
		number_of_accounts = m_userDatabase.at(username);
	}
	catch (...) {
		//	if not throw and exit
		throw std::logic_error("Username is not in the database, Cannot create bank account with no user account.");
	}
	//	tries to log into the users account to ensure security by checking the passwords match
	try {
		Users user(username, password);
		//	user has a file so create a new account for them with information provided
		accountNumber = number_of_accounts + 1;
		Account newAccount = { accountNumber, accountType, startingAmount };
		//	Update the vector in this users account so that the destructor takes care of updating the file with the new account
		user.getAccountList().push_back(newAccount);
		m_userDatabase[username] = user.getAccountList().size();
	}
	catch (const std::logic_error& args) {
		//	if they do not throw that passwords do not match and exit
		throw std::logic_error(args.what());
	}
	return accountNumber;
}
//	!end of Create Account

//	Delete Account
void Admin::deleteAccount(const std::string& username, int accountNumber) {
	int number_of_accounts = 0;
	try {
		number_of_accounts = m_userDatabase.at(username);
	}
	catch (...) {
		throw std::logic_error("Username is not in the database, Cannot delete bank account with no user account.");
	}
	if (number_of_accounts == 0) {
		throw std::logic_error("You have zero bank accounts, please contact employee to help you create one.");
	}

	//	user exist in the database, and has more than 1 account they can delete

	//	open the user file to get their password
	std::string password;
	m_FileManager.open(ExtendFileName(username), std::fstream::in);
	m_FileManager >> password; 
	m_FileManager.close();
	
	//	create user instance to delete the account;
	try {
		Users user(username, password);
		//int index = accountNumber - 1;
		////	finds the account through an iterator since the vector should be in order of account number
		//user.getAccountList().erase(user.getAccountList().begin() + index);
		std::vector<Account>::iterator It = user.getAccountList().begin();
		while (It != user.getAccountList().end()) {
			if (It->number == accountNumber) {
				user.getAccountList().erase(It);
				//update the database information
				m_userDatabase[username] = number_of_accounts - 1;
				break;
			}
			else {
				It++;
			}
		}
	}
	catch (const std::logic_error& args) {
		throw std::logic_error(args.what());
	}
}
//	!end of Delete Account

//	View All Accounts
void Admin::viewAll(const std::string& username) {
	int number_of_accounts = 0;
	try {
		number_of_accounts = m_userDatabase.at(username);
	}
	catch (...) {
		throw std::logic_error("Username is not in the database, Cannot view bank accounts with no user account.");
	}
	if (number_of_accounts == 0) {
		throw std::logic_error("You have zero bank accounts, please contact employee to help you create one.");
	}

	//	open the user file to get their password
	std::string password;
	m_FileManager.open(ExtendFileName(username), std::fstream::in);
	m_FileManager >> password;
	m_FileManager.close();

	try {
		Users user(username, password);
		std::vector<Account> accounts = user.getAccountList();

		std::cout << "\nNumber of Accounts: " << accounts.size() << std::endl;
		for (const auto& acc : accounts) {
			std::cout << "\n	Account Number:		" << acc.number << std::endl;
			std::cout << "	Account Type:		" << acc.type << std::endl;
			std::cout << "	Account Amount:		" << acc.amount << std::endl;
		}
		std::cout << std::endl;
	}
	catch (const std::logic_error& args) {
		throw std::logic_error(args.what());
	}
}
//	!end of view all