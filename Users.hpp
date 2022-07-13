#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <fstream>
#include <stdexcept>


const std::string FILE_PATH = "C:\\Users\\CSUFTitan\\Documents\\Visual Studio 2022\\source\\repos\\Barrales Bank Record System Project\\Users\\";

static std::string ExtendFileName(const std::string& username) { return FILE_PATH + username + ".txt"; }


struct Account
{
	int number;
	std::string type;
	int amount;
};

class Users {
private:
	std::string m_userName;
	std::string m_Name;
	std::string m_Email;
protected:
	std::string m_Password;
	std::fstream  m_FileManager;
	std::string m_fileName;
	Account m_ActiveAccount;
public:
	//	Sign In constructor
	Users(const std::string& username, const std::string& password);
	//	Register constructor
	Users(const std::string& username, const std::string& password, const std::string& name, const std::string& email);

	// basic getters
	const std::string& getName() { return m_Name; }
	const std::string& getUserName() { return m_userName; }
	const std::string& getEmail() { return m_Email; }

	//	Takes amount from the accountNumber found in file, Returns the remaining amount in account 
	int withdrawal(int accountNumber, int amount);
	//	Adds amount to the accountNumber found in file, returns the new total in account;
	int deposit(int accountNumber, int amount);
};

#endif // !__USER_HPP__