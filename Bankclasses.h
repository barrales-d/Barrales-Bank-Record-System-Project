#pragma once
#ifndef __BANK_CLASSES__
#define __BANK_CLASSES__

#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

const string SP = ", "; // Separater
/*	Struct to hold a Date: mm/dd/yr	*/
struct Date {
	Date() = default;
	Date(int m, int d, int y) {
		month = m; 
		day = d; 
		year = y;
	}
	//	"mm/dd/yr"
	Date(string& date) {	
		string digits = "";
		for (int i = 0; i < date.size(); i++) {//[ 1,0,/,9,/,2,0,0,2 ]
			if (date[i] == '/') {
				int temp = stoi(digits);
				if (i < 3)
					month = temp;
				else if (i >= 3 && i < 6)
					day = temp; 
				digits = "";
			}else 
				digits += date[i];
		}
		year = stoi(digits);
	}

	int day;
	int month;
	int year;
	void show() { cout << month << "/" << day << "/" << year << endl; }
	string to_string() {
		const string m = std::to_string(month);
		const string d = std::to_string(day);
		const string y = std::to_string(year);
		return m + "/" + d + "/" + y;
	}
};

/*	
 *	Virtual class to hold data about a table(class)
 *	Entity() = title of table
 *	Attributes() = tites of column headers 
 *	createTuple() = string of the attribute values of a tuple seperated by a comma
 *	-> return "A1, A2, A3, ..., An";
 *	
 *	Every class marked with public Data must implement these functions to be able to 
 *	work with the Database Class in "Banksystem.h"
 */
class Data {
public:
	string virtual Entity() = 0;
	string virtual Attributes() = 0;
	string virtual createTuple() = 0;
};

/*	
 *	Person class: technical virtual class in which there should never be a declaration of Person anywhere
 *	i.e Person x = Person(); should never be declared
 */
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
		DoB.show();
	}
	string virtual createTuple() {
		return Ssn + SP + Fname + SP + Lname + SP + DoB.to_string();
	};
	string Ssn;
	string Fname;
	string Lname;
	Date DoB;
};

/*
 * Customer class: table of all customers who have accounts in the system 
 * Entity() = "Customers", Attributes() = "Ssn, Fname, Lname, DoB, Number of Accounts"
 * Primary key(Ssn)
 */
class Customer : public Person {
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
	// Data implementation
	string Entity() { return "Customers"; }
	string Attributes() { return "Ssn, Fname, Lname, DoB, Number of Accounts"; }
	string createTuple() { return Person::createTuple() + SP + to_string(numberOfAccounts); }
private:
	int numberOfAccounts;
};

/*
 *	Employee Table: table of all employees in the system
 *	Entity() = "Employees", Attributes() = "Ssn, Fname, Lname, DoB, Salary, Mssn"
 *	Primary Key(Ssn), Foreign key(Mssn) references Employee(Ssn)
 */
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
	//	Data implementation
	string Entity() { return "Employees"; }
	string Attributes() { return "Ssn, Fname, Lname, DoB, Salary, Mssn"; }
	string createTuple() {
		string manager;
		if (Mssn)
			manager = *Mssn;
		else
			manager = "null";
		return Person::createTuple() + SP + to_string(Salary) + SP + manager;
	}
	float Salary;
	string* Mssn;
private:
};

/*
 *	Account Table: table of all accounts the bank has opened
 *	Entity() = "Accounts", Attributes() = "Type, Amount, AccNumber, Cssn"
 *	Primary key(AccNumber), Foreign Key(Cssn) references Customer(Ssn)
 */
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

	//Data implementation
	string Entity() { return "Accounts"; }
	string Attributes() { return "Type, Amount, Account Number, Cssn"; }
	string createTuple() { return Type + SP + to_string(Amount) + AccNumber + *Cssn; }
private:
	string Type;
	float Amount;
	string AccNumber;
	string* Cssn;
};

/*
 *	CreateAccount Table: Table of all accounts created, with the employee who made it and the date the account was created
 *	Entity() = "Created Accounts", Attributes() = "Essn, AccNumber, Date"; 
 *	Foreign key(Essn) references Employee(Ssn) 
 *	Foreign key(AccNumber) references Account(AccNumber)
 */
class CreateAccount : public Data {
public:
	CreateAccount() = default;
	CreateAccount(string* e, string* a, Date d) {
		Essn = e;
		Acc = a;
		date = d;
	}

	//	Data implementation
	string Entity() { return "Created Accounts"; }
	string Attributes() { return "Essm, Account Number, Date"; }
	//	Should never have a null value
	string createTuple() { return *Essn + SP + *Acc + SP + date.to_string(); }
private:
	string* Essn;
	string* Acc;
	Date date;
};




#endif