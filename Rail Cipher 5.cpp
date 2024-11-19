#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to encrypt using Rail Fence Cipher
string railFenceEncrypt(const string& text, int key) {
    // Create a 2D vector to represent the rail pattern
    vector<vector<char>> rail(key, vector<char>(text.length(), '\n'));

    // Fill the rail matrix in a zigzag pattern
    int row = 0;
    bool directionDown = false;
    for (size_t i = 0; i < text.length(); ++i) {
        rail[row][i] = text[i];

        if (row == 0 || row == key - 1) {
            directionDown = !directionDown;
        }
        row += directionDown ? 1 : -1;
    }

    // Read the characters row by row to get the ciphertext
    string cipherText;
    for (const auto& r : rail) {
        for (char c : r) {
            if (c != '\n') {
                cipherText += c;
            }
        }
    }
    return cipherText;
}

// Function to decrypt using Rail Fence Cipher
string railFenceDecrypt(const string& cipherText, int key) {
    // Create a 2D vector to represent the rail pattern
    vector<vector<char>> rail(key, vector<char>(cipherText.length(), '\n'));

    // Mark the zigzag pattern in the rail matrix
    int row = 0;
    bool directionDown = false;
    for (size_t i = 0; i < cipherText.length(); ++i) {
        rail[row][i] = '*';

        if (row == 0 || row == key - 1) {
            directionDown = !directionDown;
        }
        row += directionDown ? 1 : -1;
    }

    // Fill the rail matrix with the ciphertext characters
    size_t index = 0;
    for (auto& r : rail) {
        for (char& c : r) {
            if (c == '*' && index < cipherText.length()) {
                c = cipherText[index++];
            }
        }
    }

    // Read the plaintext by following the zigzag pattern
    string plainText;
    row = 0;
    directionDown = false;
    for (size_t i = 0; i < cipherText.length(); ++i) {
        plainText += rail[row][i];

        if (row == 0 || row == key - 1) {
            directionDown = !directionDown;
        }
        row += directionDown ? 1 : -1;
    }
    return plainText;
}

int main() {
    string text, mode;
    int key;

    // Input text, mode, and key
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the key (number of rails): ";
    cin >> key;
    cout << "Mode (encrypt/decrypt): ";
    cin >> mode;

    if (mode == "encrypt") {
        string cipherText = railFenceEncrypt(text, key);
        cout << "Encrypted Text: " << cipherText << endl;
    } else if (mode == "decrypt") {
        string plainText = railFenceDecrypt(text, key);
        cout << "Decrypted Text: " << plainText << endl;
    } else {
        cout << "Invalid mode! Please choose 'encrypt' or 'decrypt'." << endl;
    }

    return 0;
}

