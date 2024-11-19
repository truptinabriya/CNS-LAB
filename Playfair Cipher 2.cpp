#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to generate the Playfair matrix
vector<vector<char>> generateMatrix(const string& key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    string processedKey;
    vector<bool> used(26, false);

    // Remove duplicates from the key and replace 'J' with 'I'
    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) {
            processedKey += c;
            used[c - 'A'] = true;
        }
    }

    // Add the rest of the alphabet (excluding 'J')
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            processedKey += c;
            used[c - 'A'] = true;
        }
    }

    // Fill the matrix with the processed key
    for (int i = 0, k = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = processedKey[k++];
        }
    }

    return matrix;
}

// Function to find the position of a character in the matrix
pair<int, int> findPosition(const vector<vector<char>>& matrix, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Character not found (should not happen)
}

// Function to process the text into digraphs
string processText(const string& text) {
    string processedText;
    for (char c : text) {
        if (isalpha(c)) {
            processedText += toupper(c == 'J' ? 'I' : c);
        }
    }

    // Add filler 'X' for duplicate letters in a digraph or odd length
    for (size_t i = 0; i < processedText.length(); i += 2) {
        if (i + 1 < processedText.length() && processedText[i] == processedText[i + 1]) {
            processedText.insert(i + 1, "X");
        }
    }
    if (processedText.length() % 2 != 0) {
        processedText += 'X';
    }

    return processedText;
}

// Playfair Cipher encryption or decryption
string playfairCipher(const string& text, const vector<vector<char>>& matrix, bool encrypt) {
    string result;
    string processedText = processText(text);

    for (size_t i = 0; i < processedText.length(); i += 2) {
        char a = processedText[i];
        char b = processedText[i + 1];
        auto [row1, col1] = findPosition(matrix, a);
        auto [row2, col2] = findPosition(matrix, b);

        if (row1 == row2) {
            // Same row: shift columns
            result += matrix[row1][(col1 + (encrypt ? 1 : 4)) % 5];
            result += matrix[row2][(col2 + (encrypt ? 1 : 4)) % 5];
        } else if (col1 == col2) {
            // Same column: shift rows
            result += matrix[(row1 + (encrypt ? 1 : 4)) % 5][col1];
            result += matrix[(row2 + (encrypt ? 1 : 4)) % 5][col2];
        } else {
            // Rectangle swap
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }

    return result;
}

int main() {
    string key, text, mode;

    // Input the key and the text
    cout << "Enter the key: ";
    getline(cin, key);
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Mode (encrypt/decrypt): ";
    cin >> mode;

    // Convert mode to lowercase
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    // Generate the Playfair matrix
    vector<vector<char>> matrix = generateMatrix(key);

    // Encrypt or decrypt based on the mode
    bool encrypt = (mode == "encrypt");
    string result = playfairCipher(text, matrix, encrypt);

    // Display the result
    cout << "Output: " << result << endl;

    return 0;
}

