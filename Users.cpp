
#include "Users.hpp"

//	Logging In to an existing account
Users::Users(const std::string& username, const std::string& password) {

	m_userName = username;
	m_fileName = FILE_PATH + m_userName + ".txt";

	m_FileManager.open(m_fileName, std::fstream::in);
	if (!m_FileManager.is_open()) {
		//	file doesn't exist
		throw std::invalid_argument("Unable to open file with username");
	}
	else {
		std::getline(m_FileManager, m_Password);

		if (password != m_Password) {
			//	password found within the file does not match the password passed in 
			throw std::logic_error("passwords do not match!");
		}
		else {
			//	file found / opened, and passwords match!
			std::getline(m_FileManager, m_Name);
			std::getline(m_FileManager, m_Email);
			m_FileManager.close();
		}

	}
}
//	!end of log in


//	Registering a new account 
Users::Users(const std::string& username, const std::string& password, const std::string& name, const std::string& email) {

	//	Create a filename base on the username
	m_userName = username;
	m_fileName = FILE_PATH + m_userName + ".txt";

	//	Check to see if filename exists already
	m_FileManager.open(m_fileName, std::fstream::in);
	if (m_FileManager.is_open()) {
		//	file does exist
		throw std::invalid_argument("File already exist with that username, please log in.");
	}
	//	Close read in file before opening a write file
	m_FileManager.close();

	//	Open file to write to 
	m_FileManager.open(m_fileName, std::fstream::out);

	//	Write basic information to file 
	m_Password = password;
	m_FileManager << m_Password << std::endl;

	m_Name = name;
	m_FileManager << m_Name << std::endl;

	m_Email = email;
	m_FileManager << m_Email << std::endl;
	//	Close file
	m_FileManager.close();

	//	Admin things: Add user to ADMIN.txt and default account number to 0 because it is a new account 
	std::string adminFile = ExtendFileName("ADMIN");
	m_FileManager.open(adminFile, std::ios_base::app);
	m_FileManager << m_userName + " 0\n";
	m_FileManager.close();

}
//	!end of register 

//	Withdrawing from account 
int Users::withdrawal(int accountNumber, int amount) {
	return 0;
}
//	!end of withdrawal

//	Depositing into account 
int Users::deposit(int accountNumber, int amount) {
	return 0;
}
//!end of deposit