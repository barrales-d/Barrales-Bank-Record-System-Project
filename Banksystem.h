#pragma once
#ifndef __BANK_NAMESPACE__
#define __BANK_NAMESPACE__

#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

const string SP = ", "; // Separater
struct Date {
	int day;
	int month; 
	int year; 
	string to_string() {
		const string m = std::to_string(month);
		const string d = std::to_string(day);
		const string y = std::to_string(year);
		return m + "/" + d + "/" + y;
	}
};

void showDate(const Date& d) {
	cout << d.month << "/" << d.day << "/" << d.year << endl;
}
class Data {
public: 
	string virtual Entity() = 0;
	string virtual Attributes() = 0;
};
class Person : public Data {
public:
	Person() = default;
	Person(
		const string& s,
		const string& fn, 
		const string& ln, 
		const Date& dob
	) : Ssn(s), Fname(fn), Lname(ln), DoB(dob) {};

	void display() {
		cout << Fname << ' ' << Lname << ", born on ";
		showDate(DoB);
	}
	string virtual createTuple() {
		return Ssn + SP + Fname + SP + Lname + SP + DoB.to_string();
	};
protected:
	string Ssn;
	string Fname; 
	string Lname; 
	Date DoB;
};
class Customer : public Person{
public: 
	Customer() = default;
	Customer(
		const string& s,
		const string& fn,
		const string& ln,
		const Date& dob,
		int noa = 0
	) : Person(s, fn, ln, dob), numberOfAccounts(noa) {};

	void display() {
		Person::display();
		cout << "Number of accounts: " << numberOfAccounts << endl;
	}
	string createTuple() {
		return Person::createTuple() + SP + to_string(numberOfAccounts);
	}
	string Entity() { return "Customers"; }
	string Attributes() { return "Ssn, Fname, Lname, DoB, Number of Accounts"; }
private: 
	int numberOfAccounts; 
	//Primary key(Ssn)
};

class Employee : public Person {
public:
	Employee() = default;
	Employee(
		const string& s,
		const string& fn,
		const string& ln,
		const Date& dob,
		float sal,
		string* manager = NULL
	) : Person(s, fn, ln, dob), Salary(sal) {
		Mssn = manager;
	};
	void display() {
		Person::display();
		cout << "Is making: $" << Salary << endl;
		if (Mssn)
			cout << "Managed by: " << *Mssn;
		else
			cout << "does not have a manager yet";

		cout << endl;
	}
	string& SSN() { return Ssn; }
	void setSSN(const string& ssn) { Ssn = ssn; }
	void setFname(const string& fn) { Fname = fn; }
	void setLname(const string& ln) { Lname = ln; }
	void setdob(const Date& dob) { DoB = dob; }
	void setSalary(float sal) { Salary = sal; }
	void setMssn(string* manager) { Mssn = manager; }

	string  createTuple() {
		string manager;
		if (Mssn)
			manager = *Mssn;
		else
			manager = "null";
		return Person::createTuple() + SP + to_string(Salary) + SP + manager;
	}

	string Entity() { return "Employees"; }
	string Attributes() { return "Ssn, Fname, Lname, DoB, Salary, Mssn"; }

private:
	float Salary;
	string* Mssn;
};


class Account : public Data {
public:
	Account() = default;
	Account(
		const string& t,
		float a,
		const string& an,
		string* customer
	) : Type(t), Amount(a), AccNumber(an) {
		Cssn = customer;
	};
	string createTuple() {
		return Type + SP + to_string(Amount) + AccNumber + *Cssn;
	}
	string Entity() { return "Accounts"; }
	string Attributes() { return "Type, Amount, Account Number, Cssn"; }
private:
	string Type;
	float Amount;
	string AccNumber;
	string* Cssn;
};

class CreateAccount : public Data {
public:
	CreateAccount() = default;
	CreateAccount(string* e, string* a, string* c) {
		Essn = e;
		Acc = a;
		Cssn = c;
	}
	string createTuple() {
		return *Essn + SP + *Acc + SP + *Cssn;
	}
	string Entity() { return "Created Accounts"; }
	string Attributes() { return "Essm, Account Number, Cssn"; }
private:
	string* Essn;
	string* Acc;
	string* Cssn;
};



// Only use with class datatypes above never with basic types
class Database {
public:
	Database() = default;
	static enum Tables {
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
	T loadTuple(const Tables& arg) {
		filename = filePath + T().Entity() + ".csv";
		fileManager.open(filename, std::ios::in);
		T container; 
		string data;
		getline(fileManager, data);// grab headers throw away
		switch (arg) {
		case Tables::Customers: 
			break; 
		case Tables::Employees:
			fileManager >> data;
			data.erase(data.end() - 1);
			container.setSSN(data);
			cout << container.SSN() <<endl;
			fileManager.close();
			break; 
		case Tables::Accounts:
			break;
		case Tables::CreateAccounts:
			break;
		}

		return container;
	}
private:
	std::fstream fileManager;
	const string filePath = ".\\Database\\";
	string filename;
};
#endif // !__BANK_NAMESPACE__
