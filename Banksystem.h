#pragma once
#ifndef __BANK_NAMESPACE__
#define __BANK_NAMESPACE__

#include <iostream> 
#include <string>
#include <fstream>

#include "Bankclasses.h"
using namespace std;
/*	Only use with class datatypes from Bankclasses.h never with basic types
 *	Class Database: is a wrapper class to do the file manipulation, insertion and deletion of the 4 Tables in "Bankclasses.h"
 */
class Database {
public:
	Database() = default;
	enum Tables {
		Customers,
		Employees, 
		Accounts,
		CreateAccounts
	};

	template <typename T>
	void createTable() {
		filename = filePath + T().Entity() + ".csv";
		fileManager.open(filename, std::ios::out);
		if(fileManager.is_open()) {
			fileManager << T().Attributes() << endl;
		}
		fileManager.close();
	}
	template <typename T>
	void createTuple(T arg) {
		filename = filePath + T().Entity() + ".csv";
		fileManager.open(filename, std::ios::app);
		if (fileManager.is_open()) {
			fileManager << arg.createTuple() << endl;
		}
		fileManager.close();
	}
	template<typename T>
	void loadTuple(const Tables& arg, T& container) {
		filename = filePath + T().Entity() + ".csv";
		fileManager.open(filename, std::ios::in); 
		string data;
		getline(fileManager, data);// grab headers throw away
		switch (arg) {
		case Tables::Customers: 
			break; 
		case Tables::Employees:
			fileManager >> container.Ssn;
			container.Ssn.erase(container.Ssn.end() - 1);	
			fileManager >> container.Fname; 
			container.Fname.erase(container.Fname.end() - 1);
			fileManager >> container.Lname; 
			container.Lname.erase(container.Lname.end() - 1);
			fileManager >> data;
			data.erase(data.end() - 1);
			container.DoB = Date(data);
			fileManager >> container.Salary;
			/*fileManager >> data; 
			data.erase(data.end() - 1);
			*(container.Mssn) = data;
			fileManager.close();*/
			break; 
		case Tables::Accounts:
			break;
		case Tables::CreateAccounts:
			break;
		}
	}
private:
	std::fstream fileManager;
	const string filePath = ".\\Database\\";
	string filename;
};
#endif // !__BANK_NAMESPACE__
