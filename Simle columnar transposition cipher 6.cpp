#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Function to encrypt using Columnar Transposition Cipher
string columnarEncrypt(const string& plaintext, const string& key) {
    int numCols = key.length();
    int numRows = (plaintext.length() + numCols - 1) / numCols; // Calculate required rows
    vector<vector<char>> grid(numRows, vector<char>(numCols, 'X')); // Initialize grid with 'X'

    // Fill the grid row-wise with plaintext
    size_t index = 0;
    for (int i = 0; i < numRows && index < plaintext.length(); ++i) {
        for (int j = 0; j < numCols && index < plaintext.length(); ++j) {
            grid[i][j] = plaintext[index++];
        }
    }

    // Create a mapping of column indices based on sorted key
    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < numCols; ++i) {
        keyOrder.emplace_back(key[i], i);
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Read the grid column-wise based on sorted key order
    string cipherText;
    for (const auto& [ch, col] : keyOrder) {
        for (int row = 0; row < numRows; ++row) {
            cipherText += grid[row][col];
        }
    }

    return cipherText;
}

// Function to decrypt using Columnar Transposition Cipher
string columnarDecrypt(const string& cipherText, const string& key) {
    int numCols = key.length();
    int numRows = (cipherText.length() + numCols - 1) / numCols;

    // Create a mapping of column indices based on sorted key
    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < numCols; ++i) {
        keyOrder.emplace_back(key[i], i);
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Fill the grid column-wise based on sorted key order
    vector<vector<char>> grid(numRows, vector<char>(numCols, 'X'));
    size_t index = 0;
    for (const auto& [ch, col] : keyOrder) {
        for (int row = 0; row < numRows; ++row) {
            if (index < cipherText.length()) {
                grid[row][col] = cipherText[index++];
            }
        }
    }

    // Read the grid row-wise to reconstruct plaintext
    string plainText;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] != 'X') { // Skip padding characters
                plainText += grid[i][j];
            }
        }
    }

    return plainText;
}

int main() {
    string text, key, mode;

    // Input plaintext/ciphertext, key, and mode
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the key (unique keyword): ";
    cin >> key;
    cout << "Mode (encrypt/decrypt): ";
    cin >> mode;

    if (mode == "encrypt") {
        string cipherText = columnarEncrypt(text, key);
        cout << "Encrypted Text: " << cipherText << endl;
    } else if (mode == "decrypt") {
        string plainText = columnarDecrypt(text, key);
        cout << "Decrypted Text: " << plainText << endl;
    } else {
        cout << "Invalid mode! Please choose 'encrypt' or 'decrypt'." << endl;
    }

    return 0;
}

