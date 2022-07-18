
#include "Users.hpp"

//	Logging In to an existing account
Users::Users(const std::string& username, const std::string& password, bool admin) {

	m_userName = username;
	m_fileName = FILE_PATH + m_userName + ".txt";
	m_Admin = admin;

	
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
			if (!m_Admin) {//	if you are an admin use admin constructor only
				std::string data = "";
				std::getline(m_FileManager, data);
				if (data != ACCOUNT_TAG) {
					//	End of file no account exists yet
					m_FileManager.close();
				}
				else {
					int number_of_accounts = 0;
					m_FileManager >> number_of_accounts;
					for (int i = 0; i < number_of_accounts; i++) {
						//	should put all account data into a vector of accounts
						m_FileManager >> m_ActiveAccount.number;
						
						m_FileManager >> m_ActiveAccount.type;
						
						m_FileManager >> data;
						
						//	erase 1 character off the beginning of string
						data.erase(0, 1);
						
						m_ActiveAccount.amount = std::stoi(data);
						m_Accounts.push_back(m_ActiveAccount);
					}
					m_FileManager.close();
				}
			}
			else {
				//close file properly so that the Admin constructor has no issues
				m_FileManager.close();
			}
		}
	}
}
//	!end of log in


//	Registering a new account 
Users::Users(const std::string& username, const std::string& password, const std::string& name, const std::string& email, bool admin) {

	//	Create a filename base on the username
	m_userName = username;
	m_fileName = FILE_PATH + m_userName + ".txt";
	m_Admin = admin;

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


//	Destructor :: right before you destroy the User instance, update the .txt file to match the changes made to any account
Users::~Users() {
	if (!m_Admin) {	// if you are not an admin don't use this destructor because we dont want to override what the admin destructor did
		m_FileManager.open(m_fileName, std::fstream::out);
		if (m_FileManager.is_open()) {
			//	have to rewrite everything because you can not edit a file easily 
			//	basic info
			m_FileManager << m_Password << std::endl;
			m_FileManager << m_Name << std::endl;
			m_FileManager << m_Email << std::endl;

			if (!m_Accounts.empty()) {//	if not empty, the constructor found accounts in the file put back accounts into file
				m_FileManager << ACCOUNT_TAG << std::endl;
				m_FileManager << m_Accounts.size() << std::endl;
				for (const auto& acc : m_Accounts) {
					m_FileManager << acc.number << std::endl;
					m_FileManager << acc.type << std::endl;
					m_FileManager << '$' << acc.amount << std::endl;
				}
			}
			m_FileManager.close();
		}
	}
}

//	Withdrawing from account 
int Users::withdrawal(int accountNumber, int amount) {
	//	Taking money from account
	//	Step 1: checking accountNumber exists in file
	m_FileManager.open(m_fileName, std::fstream::in);
	std::string data;
	while (std::getline(m_FileManager, data) && data != ACCOUNT_TAG) { }
	if (data != ACCOUNT_TAG) {
		//	You reach the end of the file without find the ACCOUNT_TAG -> no accounts exist for this user
		throw std::logic_error("No accounts found, please contact employee to help you make one.");
	}

	//	You found account_tag begin search through accounts to find account number
	int count = 0;
	//	read in the number of accounts 
	m_FileManager >> count; 
	m_ActiveAccount.number = -1;//	No account can be negative 
	for (int i = 0; i < count && m_ActiveAccount.number != accountNumber; i++) {
		//read in data until you find the account number in file OR get to the end of a file
		m_FileManager >> m_ActiveAccount.number;
		m_FileManager >> m_ActiveAccount.type;
		m_FileManager >> data;
		data.erase(0, 1);
		m_ActiveAccount.amount = std::stoi(data);
	}
	if (m_ActiveAccount.number != accountNumber) {
		//	None of the accounts match the desired number -> does not exists 
		//	i.e looking for account number: 2 when a user only has 1 account
		throw std::logic_error("Unable to find account with the Number: " + std::to_string(accountNumber));
	}

	//	FINALLY DONE GETTING ACCOUNT INFORMATION FROM FILE WITHDRAWAL CLOSE THE FILE!!!!
	m_FileManager.close();

	if (amount > m_ActiveAccount.amount) {	// amount you want is more than you have
		throw std::logic_error("You do not have enough funds in your account to make this transaction. You only have $" + std::to_string(m_ActiveAccount.amount));
	}
	//	You found account in file, you have enough money to withdrawal
	m_ActiveAccount.amount -= amount;

	//	update the account in the vector
	m_Accounts[accountNumber - 1].amount = m_ActiveAccount.amount;

	//	return remaining amount of money in account
	return m_ActiveAccount.amount;
}
//	!end of withdrawal

//	Depositing into account 
int Users::deposit(int accountNumber, int amount) {
	//	check to see if the account exists
	int index = getAccountIndex(accountNumber);
	if (index == -1) { throw std::logic_error("Account could not be found please try a different account number"); }
	
	//	make sure that amount you want to add is positive; No negative numbers
	if (amount <= 0) { throw std::logic_error("Please enter a valid amount to deposit, Thank you!"); }
	m_ActiveAccount = m_Accounts.at(index);
	m_ActiveAccount.amount += amount; 

	m_Accounts[index] = m_ActiveAccount;
	
	return m_ActiveAccount.amount;
}
//!end of deposit

//Get account index

int Users::getAccountIndex(int accountNumber) {
	int size = m_Accounts.size();
	for (int i = 0; i < size; i++) {
		if (accountNumber == m_Accounts[i].number) {
			return i;
		}
	}
	return -1; 
}
//!end of get account index