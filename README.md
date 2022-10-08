# Barrales Bank Record System Project with C++ 

## Bank Record System: 
 A Bank record system is a system in which you are able to record a user's bank account information. This program is able to create, delete, and view bank account information. As well as withdraw and deposit from those accounts. This all is able to happened because the program reads/writes to a text file.

## Things I learned: 
1. how to handle files
2. data management and organization
3. Account security and authenticity
4. String manipulation

### Users class: 
A User is a person with an user account, which is created with a username and pasword. This is then used to open a text file with that person's username, ***username.txt***.

This text file contains all information about that user and all their account information.
- A user is able to __Withdraw__ or __Deposit__ from any of their accounts. 
- They also are able to __View__ their account based on the account number.

_Any changes made to their account will be updated accordingly._

### Admin class:
An Admin is a person with data about all users in the system, thus is a child of the Users class to record information recorded about all users into a special text file, ***ADMIN.txt***.

This file contains information on all users currently in the system, specifically the number of account that user holds. 
- Admins are able to __Create__, __Delete__ account for a specific user. 
- They are also able to __View__ all of the accounts a user holds. 

_Since it is a child class of Users, ADMIN.txt will also be updated accordingly._
