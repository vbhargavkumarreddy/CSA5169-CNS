#include <stdio.h>

// Function to compute the greatest common divisor (GCD) using the Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find the multiplicative inverse of e mod phi_n
int extended_euclidean(int e, int phi_n, int *x, int *y) {
    if (phi_n == 0) {
        *x = 1;
        *y = 0;
        return e;
    }
// p=59. q=61. e=31
    int x1, y1;
    int gcd = extended_euclidean(phi_n, e % phi_n, &x1, &y1);

    *x = y1;
    *y = x1 - (e / phi_n) * y1;

    return gcd;
}

// Function to find the modular inverse
int modular_inverse(int e, int phi_n) {
    int x, y;
    int g = extended_euclidean(e, phi_n, &x, &y);
    if (g != 1) {
        printf("Inverse doesn't exist!\n");
        return -1;
    } else {
        int res = (x % phi_n + phi_n) % phi_n;
        return res;
    }
}

int main() {
    int p, q, n, e, phi_n, d;

    // User input for the public key components (e and n) and prime factors (p and q)
    printf("Enter the prime number p: ");
    scanf("%d", &p);

    printf("Enter the prime number q: ");
    scanf("%d", &q);

    printf("Enter the public exponent e: ");
    scanf("%d", &e);

    // Compute n = p * q
    n = p * q;
    printf("Computed n = p * q = %d\n", n);

    // Compute phi(n) = (p - 1)(q - 1)
    phi_n = (p - 1) * (q - 1);
    printf("Computed phi(n) = (p - 1) * (q - 1) = %d\n", phi_n);

    // Find the private key d, which is the modular inverse of e mod phi(n)
    d = modular_inverse(e, phi_n);
    if (d != -1) {
        printf("Private key d = %d\n", d);
    } else {
        printf("Failed to compute the private key!\n");
    }

    return 0;
}
