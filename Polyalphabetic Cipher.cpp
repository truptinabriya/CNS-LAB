#include <iostream>
#include <string>
using namespace std;

// Function to extend the keyword to match the length of the text
string extendKey(const string& text, const string& key) {
    string extendedKey = key;
    while (extendedKey.length() < text.length()) {
        extendedKey += key;
    }
    return extendedKey.substr(0, text.length());
}

// Function to encrypt or decrypt using the Polyalphabetic Cipher
string polyalphabeticCipher(const string& text, const string& key, bool encrypt) {
    string result = "";
    string extendedKey = extendKey(text, key);

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        char k = extendedKey[i];

        if (isalpha(c)) {
            // Determine base ('A' for uppercase, 'a' for lowercase)
            char base = isupper(c) ? 'A' : 'a';
            char keyBase = isupper(k) ? 'A' : 'a';

            // Calculate shift value
            int shift = (encrypt ? 1 : -1) * (k - keyBase);
            result += char((c - base + shift + 26) % 26 + base);
        } else {
            // Non-alphabetic characters remain unchanged
            result += c;
        }
    }

    return result;
}

int main() {
    string text, key, mode;

    // Input the text, key, and mode
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the keyword: ";
    cin >> key;
    cout << "Mode (encrypt/decrypt): ";
    cin >> mode;

    // Convert text and key to uppercase for

