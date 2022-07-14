
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
	}
	catch (const std::logic_error& args) {
		//	if they do not throw that passwords do not match and exit
		throw std::logic_error(args.what());
	}
	m_userDatabase[username] = accountNumber;
	return accountNumber;
}
//	!end of Create Account