#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* MINP1 is the first valid p1 of the prime pairs, which is 5 according to the question. */
#define MINP1 5

const int firstPrime = 2;
int* primes;
int primeSize;

void printArray(int size, int* array) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d, ", array[i]);
    }
    printf("]\n");
}

/* Function to check whether a given number is a prime number by the list of
 * prime numbers */
bool isPrimeByList(long int n) {
    for (int i = 0; i < primeSize; i++) {
        if (n % primes[i] == 0) { return false; } // False if the given number is not a prime number
        if (primes[i] > sqrt(n)) { return true; }
    }
    return true; // True if the given number is a prime number
}

/* Function to check whether a given number is a prime number */
bool isPrime(long int n) {
    if (!isPrimeByList(n)) { return false; }

    if (primes[primeSize - 1] <= sqrt(n)) {
        for (long int i = firstPrime; i <= sqrt(n); i++) {
        if (n % i == 0) { return false; } // False if the given number is not a prime number
        }
    }
    return true; // True if the given number is a prime number
}

void generateNext() {
    int n = primes[primeSize - 1] + 2;
    if (n % 2 == 0) { n--;}
    while (!isPrimeByList(n)) { n += 2; }
    primeSize++;
    primes = realloc(primes, sizeof(int) * primeSize);
    if (primes == NULL) { 
        printf("Memory allocation failed.\n");
        exit(1);
    }
    primes[primeSize - 1] = n;
}

void generatePrimes(int limit) {
    primes = malloc(sizeof(int));
    if (primes == NULL) { 
        printf("Memory allocation failed.\n");
        exit(1);
    }
    primeSize = 1;
    primes[0] = 2;
    while (primes[primeSize - 1] <= limit) {
        generateNext();
    }
}

long int modularInverse(long int n1, long int n2) {
    long int x = 0, y = 1, temp;
    long int a = n1, m = n2;

    while (a > 1) {
        temp = x;
        x = y - a / m * x;
        y = temp;

        temp = a % m;
        a = m;
        m = temp; 
    }

    if (y < 0) {
        y += n2;
    }
  
    return y;
}

unsigned long long int sumPairs() {
    /* According to the problem, n is a multiple of p2 and has its last digits formed by p1 
        Let n = m * 10^d + p1, where d = number of digits of p1,
        such that the last d digits of m are 0s.
        n mod p2 = (m * 10^d + p1) mod p2 = 0
        => m * 10^d mod p2 = -p1 mod p2
        => m = (-p1 * (10^d)^-1) mod p2
        (10^d)^-1, the multiplicative inverse of 10^d,
        can be found using Extended Euclid Algorithm.
    */
    unsigned long long int sum = 0, zeros;
    long long int m;
    int p1 = MINP1, p2;
    for (int i = 0; i < primeSize; i++) {
        if (primes[i] <= 5) { continue; }
        p2 = primes[i];
        zeros = (long int)pow(10, (int)log10(p1) + 1);
        /* (A % B + B) % B can handle negative A */
        m = (-p1 * modularInverse(zeros, p2) % p2 + p2) % p2;
        sum += m * zeros + p1;
        p1 = primes[i];
    }
    return sum;
}

int main(int argc, char **argv) {
    int limit = 1000000;  // Set the maximum limit of p1 to 1000000 by default as required in the original question

    if (argc > 1) {     // Take input from command line if given
        limit = atoi(argv[1]);
    }

    generatePrimes(limit);
    //printArray(primeSize, primes);
    printf("%llu\n", sumPairs());
}