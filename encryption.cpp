#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
//=======================================================//
using namespace std;

// Function to encrypt a single character using Caesar cipher
char encryptChar(char c, int shift)
{
    if (isalpha(c))
    {
        char base = islower(c) ? 'a' : 'A';
        return ((c - base + shift) % 26 + 26) % 26 + base;
    }
    return c;
}
//=======================================================//
// Function to encrypt a string using Caesar cipher
string encrypt(const string &text, int shift)
{
    string result;
    for (char c : text)
    {
        result += encryptChar(c, shift);
    }
    return result;
}
//=======================================================//
// Function to decrypt a string (reverse of encryption)
string decrypt(const string &text, int shift)
{
    return encrypt(text, -shift);
}
//=======================================================//
// Function to encrypt a file
void encryptFile(const string &inputFile, const string &outputFile, int shift)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open())
    {
        throw runtime_error("Unable to open input file: " + inputFile);
    }
    if (!outFile.is_open())
    {
        throw runtime_error("Unable to open output file: " + outputFile);
    }

    string line;
    while (getline(inFile, line))
    {
        outFile << encrypt(line, shift) << endl;
    }

    cout << "File encrypted successfully!" << endl;
}
//=======================================================//
// Function to decrypt a file
void decryptFile(const string &inputFile, const string &outputFile, int shift)
{
    encryptFile(inputFile, outputFile, -shift); // Decryption is just encryption with negative shift
    cout << "File decrypted successfully!" << endl;
}
//=======================================================//
// Function to get a valid integer input from the user
int getValidIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid integer." << endl;
    }
}
//=======================================================//
// Function to get a valid file name from the user
string getValidFileName(const string &prompt)
{
    string fileName;
    while (true)
    {
        cout << prompt;
        getline(cin, fileName);
        if (!fileName.empty())
        {
            return fileName;
        }
        cout << "File name cannot be empty. Please try again." << endl;
    }
}
//=======================================================//
int main()
{
    try
    {
        string inputFile = getValidFileName("Enter input file name: ");
        string outputFile = getValidFileName("Enter output file name: ");
        int shift = getValidIntInput("Enter shift value (1-25): ");

        // Ensure shift is within valid range
        shift = ((shift % 26) + 26) % 26;

        char choice;
        while (true)
        {
            cout << "Encrypt (E) or Decrypt (D)?: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (toupper(choice) == 'E' || toupper(choice) == 'D')
            {
                break;
            }
            cout << "Invalid choice. Please enter 'E' or 'D'." << endl;
        }

        if (toupper(choice) == 'E')
        {
            encryptFile(inputFile, outputFile, shift);
        }
        else
        {
            decryptFile(inputFile, outputFile, shift);
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}