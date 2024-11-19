#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Function to calculate the determinant of a 2x2 matrix
int calculateDeterminant(const vector<vector<int>>& matrix) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

// Function to find the modular inverse of a number modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; ++x) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to calculate the inverse of a 2x2 matrix modulo 26
vector<vector<int>> calculateMatrixInverse(const vector<vector<int>>& matrix, int mod) {
    int determinant = calculateDeterminant(matrix);
    int detInverse = modInverse(determinant, mod);

    if (detInverse == -1) {
        throw runtime_error("Matrix is not invertible under mod 26.");
    }

    // Create the inverse matrix
    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = (matrix[1][1] * detInverse) % mod;
    inverse[0][1] = (-matrix[0][1] * detInverse) % mod;
    inverse[1][0] = (-matrix[1][0] * detInverse) % mod;
    inverse[1][1] = (matrix[0][0] * detInverse) % mod;

    // Ensure all values are positive mod 26
    for (auto& row : inverse) {
        for (auto& val : row) {
            val = (val + mod) % mod;
        }
    }

    return inverse;
}

// Function to preprocess the plaintext (convert to uppercase and pad if necessary)
string preprocessText(const string& text) {
    string processedText;
    for (char c : text) {
        if (isalpha(c)) {
            processedText += toupper(c);
        }
    }

    // Pad with 'X' if the length is odd
    if (processedText.length() % 2 != 0) {
        processedText += 'X';
    }

    return processedText;
}

// Function to perform matrix multiplication modulo 26
vector<int> multiplyMatrix(const vector<vector<int>>& matrix, const vector<int>& block, int mod) {
    vector<int> result(block.size(), 0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            result[i] = (result[i] + matrix[i][j] * block[j]) % mod;
        }
    }
    return result;
}

// Function to encrypt or decrypt using the Hill Cipher
string hillCipher(const string& text, const vector<vector<int>>& keyMatrix, int mod) {
    string result;
    for (size_t i = 0; i < text.length(); i += 2) {
        vector<int> block = {text[i] - 'A', text[i + 1] - 'A'};
        vector<int> encryptedBlock = multiplyMatrix(keyMatrix, block, mod);
        result += (encryptedBlock[0] + 'A');
        result += (encryptedBlock[1] + 'A');
    }
    return result;
}

int main() {
    // Define a 2x2 key matrix
    vector<vector<int>> keyMatrix = {
        {6, 24},
        {1, 13}
    };
    const int MOD = 26;

    string text, mode;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Mode (encrypt/decrypt): ";
    cin >> mode;

    // Preprocess the input text
    string processedText = preprocessText(text);

    try {
        if (mode == "encrypt") {
            // Encrypt using the key matrix
            string encryptedText = hillCipher(processedText, keyMatrix, MOD);
            cout << "Encrypted Text: " << encryptedText << endl;
        } else if (mode == "decrypt") {
            // Calculate the inverse matrix for decryption
            vector<vector<int>> inverseMatrix = calculateMatrixInverse(keyMatrix, MOD);

            // Decrypt using the inverse matrix
            string decryptedText = hillCipher(processedText, inverseMatrix, MOD);
            cout << "Decrypted Text: " << decryptedText << endl;
        } else {
            cout << "Invalid mode! Please choose 'encrypt' or 'decrypt'." << endl;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

