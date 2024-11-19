#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate (base^exponent) % mod
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

int main() {
    // Example of public parameters
    long long prime = 23;  // A small prime number
    long long base = 5;    // A primitive root modulo prime

    // Alice's private key
    long long a = 6;

    // Bob's private key
    long long b = 15;

    // Alice's public key (A = base^a % prime)
    long long A = power(base, a, prime);

    // Bob's public key (B = base^b % prime)
    long long B = power(base, b, prime);

    // Now, Alice and Bob exchange their public keys.
    cout << "Alice's public key: " << A << endl;
    cout << "Bob's public key: " << B << endl;

    // Alice computes the shared secret using Bob's public key (S_A = B^a % prime)
    long long shared_secret_Alice = power(B, a, prime);
    // Bob computes the shared secret using Alice's public key (S_B = A^b % prime)
    long long shared_secret_Bob = power(A, b, prime);

    // Both should have the same shared secret
    cout << "Shared secret (computed by Alice): " << shared_secret_Alice << endl;
    cout << "Shared secret (computed by Bob): " << shared_secret_Bob << endl;

    return 0;
}

