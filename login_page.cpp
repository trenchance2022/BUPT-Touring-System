#include <iostream>
#include <fstream>
#include "cJSON.h"
#include "login_page.h"

using namespace std;

#define JSON_FILE_PATH "./user_accounts.json"

// Function to check if an account exists in the JSON file
bool isAccountExists(const string& account) {
    cJSON* root = nullptr;
    cJSON* accounts = nullptr;

    // Read the JSON file
    ifstream file(JSON_FILE_PATH);
    if (!file) {
        return false; // File does not exist, account does not exist
    }

    // Read the content of the file into a string
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Parse the JSON data
    root = cJSON_Parse(data.c_str());

    // Check for JSON parsing errors
    if (root == nullptr) {
        return false; // JSON parsing error, account does not exist
    }

    // Get the 'accounts' array from the JSON
    accounts = cJSON_GetObjectItem(root, "accounts");
    if (accounts == nullptr) {
        cJSON_Delete(root);
        return false; // No 'accounts' array found in JSON, account does not exist
    }

    // Check if the account exists in the 'accounts' array
    bool exists = cJSON_GetObjectItem(accounts, account.c_str()) != nullptr;

    // Clean up and return the result
    cJSON_Delete(root);
    return exists;
}

// Function to create a new account in the JSON file
void createAccount(const string& account, const string& password) {
    cJSON* root = nullptr;
    cJSON* accounts = nullptr;

    // Read the existing JSON file or create a new one
    ifstream file(JSON_FILE_PATH);
    if (file) {
        // Read the content of the file into a string
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        // Parse the existing JSON data
        root = cJSON_Parse(data.c_str());
    }

    // If JSON parsing failed or the file doesn't exist, create a new JSON structure
    if (root == nullptr) {
        root = cJSON_CreateObject();
        cJSON_AddItemToObject(root, "accounts", cJSON_CreateObject());
    }

    // Get the 'accounts' array from the JSON
    accounts = cJSON_GetObjectItem(root, "accounts");

    // Create the new account in the 'accounts' array
    cJSON_AddItemToObject(accounts, account.c_str(), cJSON_CreateString(password.c_str()));

    // Write the updated JSON back to the file
    ofstream outFile(JSON_FILE_PATH);
    if (outFile) {
        // Convert the JSON structure to a string
        char* jsonStr = cJSON_Print(root);

        // Write the JSON string to the file
        outFile << jsonStr;
        outFile.close();

        // Clean up memory
        free(jsonStr);
    }

    // Clean up memory
    cJSON_Delete(root);
}

// Function to validate the entered password against the stored password in JSON
bool validatePassword(const string& account, const string& enteredPassword) {
    cJSON* root = nullptr;
    cJSON* accounts = nullptr;

    // Read the existing JSON file
    ifstream file(JSON_FILE_PATH);
    if (!file) {
        return false; // File does not exist, login fails
    }

    // Read the content of the file into a string
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Parse the existing JSON data
    root = cJSON_Parse(data.c_str());

    // Check for JSON parsing errors
    if (root == nullptr) {
        return false; // JSON parsing error, login fails
    }

    // Get the 'accounts' array from the JSON
    accounts = cJSON_GetObjectItem(root, "accounts");
    if (accounts == nullptr) {
        cJSON_Delete(root);
        return false; // No 'accounts' array found in JSON, login fails
    }

    // Get the stored password from the 'accounts' array
    cJSON* accountObj = cJSON_GetObjectItem(accounts, account.c_str());
    if (accountObj == nullptr || !cJSON_IsString(accountObj)) {
        cJSON_Delete(root);
        return false; // Account not found or invalid password format, login fails
    }

    // Compare the entered password with the stored password
    const char* storedPassword = cJSON_GetStringValue(accountObj);
    bool passwordMatch = (storedPassword != nullptr) && (enteredPassword == storedPassword);

    // Clean up memory
    cJSON_Delete(root);

    // Return whether the passwords match
    return passwordMatch;
}
