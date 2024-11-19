#include <iostream>
#include <string>
using namespace std;

string caesarCipher(string text, int shift, string mode) {
    string result = "";

    // Adjust shift for decryption
    if (mode == "decrypt") {
        shift = -shift;
    }

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // Shift character and wrap around within the alphabet
            result += char((c - base + shift + 26) % 26 + base);
        } else {
            // Non-alphabetic characters remain unchanged
            result += c;
        }
    }

    return result;
}

int main() {
    string text, mode;
    int shift;

    // Input the text, shift, and mode
    cout << "Enter the text: ";
    cin.ignore(); // Clear any leftover newline from previous input
    getline(cin, text);
    cout << "Enter the shift value: ";
    cin >> shift;
    cout << "Mode (encrypt/decrypt): ";
    cin >> mode;

    // Convert mode to lowercase for case-insensitive comparison
    for (char &ch : mode) ch = tolower(ch);

    // Validate mode
    if (mode != "encrypt" && mode != "decrypt") {
        cout << "Invalid mode! Please choose 'encrypt' or 'decrypt'." << endl;
        return 1;
    }

    // Process the text with Caesar Cipher
    string output = caesarCipher(text, shift, mode);

    // Display the result
    cout << "Output: " << output << endl;

    return 0;
}

