#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate gcd
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find modular inverse of e modulo phi(n)
long long modInverse(long long e, long long phi) {
    for (long long d = 2; d < phi; ++d) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

// Function to encrypt a message using RSA
long long encrypt(long long message, long long e, long long n) {
    long long result = 1;
    message = message % n;
    while (e > 0) {
        if (e % 2 == 1) {
            result = (result * message) % n;
        }
        e = e / 2;
        message = (message * message) % n;
    }
    return result;
}

// Function to decrypt a message using RSA
long long decrypt(long long ciphertext, long long d, long long n) {
    long long result = 1;
    ciphertext = ciphertext % n;
    while (d > 0) {
        if (d % 2 == 1) {
            result = (result * ciphertext) % n;
        }
        d = d / 2;
        ciphertext = (ciphertext * ciphertext) % n;
    }
    return result;
}

int main() {
    long long p = 3;  // First prime number
    long long q = 11; // Second prime number

    // Compute n = p * q
    long long n = p * q;

    // Compute Euler's Totient function: phi(n) = (p-1)*(q-1)
    long long phi = (p - 1) * (q - 1);

    // Choose e (public key exponent)
    long long e = 7;

    // Ensure that gcd(e, phi(n)) = 1
    if (gcd(e, phi) != 1) {
        cout << "e and phi(n) are not coprime, choose a different e." << endl;
        return -1;
    }

    // Compute d (private key exponent) such that (e * d) % phi(n) = 1
    long long d = modInverse(e, phi);
    if (d == -1) {
        cout << "Could not find modular inverse." << endl;
        return -1;
    }

    // Message to be encrypted
    long long message = 4;

    // Encrypt the message
    long long ciphertext = encrypt(message, e, n);
    cout << "Ciphertext: " << ciphertext << endl;

    // Decrypt the ciphertext
    long long decryptedMessage = decrypt(ciphertext, d, n);
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}

