#ifndef LOGIN_PAGE_H
#define LOGIN_PAGE_H

#include <iostream>
#include <fstream>
#include "cJSON.h"

using namespace std;

// Function to check if an account exists in the JSON file
bool isAccountExists(const std::string& account);

// Function to create a new account in the JSON file
void createAccount(const std::string& account, const std::string& password);

// Function to handle the login page
string login_page();

// Function to validate the entered password against the stored password in JSON
bool validatePassword(const std::string& account, const std::string& enteredPassword);

#endif // LOGIN_PAGE_H
