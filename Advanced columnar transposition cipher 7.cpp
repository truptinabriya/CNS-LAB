#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Function to reorder columns based on a key
vector<int> getColumnOrder(const string& key) {
    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < key.length(); ++i) {
        keyOrder.emplace_back(key[i], i);
    }
    sort(keyOrder.begin(), keyOrder.end());

    vector<int> columnOrder;
    for (const auto& [ch, index] : keyOrder) {
        columnOrder.push_back(index);
    }
    return columnOrder;
}

// Function to encrypt using Advanced Columnar Transposition Cipher
string advancedColumnarEncrypt(const string& plaintext, const string& key1, const string& key2) {
    int numCols1 = key1.length();
    int numRows1 = (plaintext.length() + numCols1 - 1) / numCols1; // Calculate required rows
    vector<vector<char>> grid1(numRows1, vector<char>(numCols1, 'X')); // Initialize grid with 'X'

    // Fill the grid row-wise with plaintext
    size_t index = 0;
    for (int i = 0; i < numRows1 && index < plaintext.length(); ++i) {
        for (int j = 0; j < numCols1 && index < plaintext.length(); ++j) {
            grid1[i][j] = plaintext[index++];
        }
    }

    // First transposition based on key1
    vector<int> order1 = getColumnOrder(key1);
    string intermediateCipher;
    for (int col : order1) {
        for (int row = 0; row < numRows1; ++row) {
            intermediateCipher += grid1[row][col];
        }
    }

    // Second transposition based on key2
    int numCols2 = key2.length();
    int numRows2 = (intermediateCipher.length() + numCols2 - 1) / numCols2;
    vector<vector<char>> grid2(numRows2, vector<char>(numCols2, 'X')); // Initialize grid with 'X'

    index = 0;
    for (int i = 0; i < numRows2 && index < intermediateCipher.length(); ++i) {
        for (int j = 0; j < numCols2 && index < intermediateCipher.length(); ++j) {
            grid2[i][j] = intermediateCipher[index++];
        }
    }

    vector<int> order2 = getColumnOrder(key2);
    string finalCipher;
    for (int col : order2) {
        for (int row = 0; row < numRows2; ++row) {
            finalCipher += grid2[row][col];
        }
    }

    return finalCipher;
}

// Function to decrypt using Advanced Columnar Transposition Cipher
string advancedColumnarDecrypt(const string& cipherText, const string& key1, const string& key2) {
    int numCols2 = key2.length();
    int numRows2 = (cipher

