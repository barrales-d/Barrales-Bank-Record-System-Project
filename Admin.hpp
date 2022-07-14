#ifndef __ADMIN_HPP__
#define __ADMIN_HPP__

#include <string>
#include <map>
#include "Users.hpp"

const int ZERO_CHAR_ASCII = 48;

class Admin : protected Users {
private:
	// map username to number of accounts that person has
	std::map<std::string, int> m_userDatabase;
public:
	//	Sign in constructor uses the ADMIN.txt to fill the m_userDatabase;
	Admin(const std::string& username, const std::string& password) : Users(username, password, true) {
		m_FileManager.open(m_fileName, std::fstream::in);
		std::string data;
		//read file until you find the tag ACCOUNTS
		while (std::getline(m_FileManager, data) && data != ACCOUNT_TAG) {}

		//	get information from file about all the users 
		while (std::getline(m_FileManager, data)) {

			//	gets the last char from the string data, then subtracts 48 from it to get the real number
			int number_of_accounts = data.at(data.length() - 1) - ZERO_CHAR_ASCII;
			//	resizes the string dat to only have the username, without the "space + number"
			//	i.e. username 3 = username
			data.resize(data.length() - 2);
			//	puts data into the database;
			m_userDatabase[data] = number_of_accounts;
		}
		//closes file
		m_FileManager.close();
	}
	~Admin();
	//const std::map<std::string, int>& database() { return m_userDatabase; } - unsure if I need it outside of this class

	//	Admins have the power to create accounts for a user, delete account, show all accounts, modify account? 

	//	Create Account for this username
	int createAccount(const std::string& username, const std::string& password, const std::string& accountType, int startingAmount);
	//	Delete Account for this username
	//	Delete Account(const std::string& username, int accountNumber);


};
#endif //	!__Admin_HPP__ 