#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void generate_dsa_signature(unsigned long long p, unsigned long long q, unsigned long long g, unsigned long long x, unsigned long long k, unsigned long long m, unsigned long long *r, unsigned long long *s) {
    *r = modExp(g, k, p) % q;
    unsigned long long k_inv = 1;
    *s = (k_inv * (m + x * (*r))) % q;
}

void generate_rsa_signature(unsigned long long n, unsigned long long d, unsigned long long m, unsigned long long *signature) {
    *signature = modExp(m, d, n);
}

int main() {
    unsigned long long p = 23, q = 11, g = 4, x = 3, m = 9, k;
    unsigned long long r, s, rsa_signature;
    srand(time(0));

    k = rand() % q;

    printf("DSA Signature for first message:\n");
    generate_dsa_signature(p, q, g, x, k, m, &r, &s);
    printf("r: %llu\ns: %llu\n", r, s);

    k = rand() % q;

    printf("\nDSA Signature for same message (with new k):\n");
    generate_dsa_signature(p, q, g, x, k, m, &r, &s);
    printf("r: %llu\ns: %llu\n", r, s);

    unsigned long long n = 187, d = 103;

    printf("\nRSA Signature for the message:\n");
    generate_rsa_signature(n, d, m, &rsa_signature);
    printf("RSA Signature: %llu\n", rsa_signature);

    return 0;
}
