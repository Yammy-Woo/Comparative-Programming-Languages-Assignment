#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Since the maximum limit of prime number is 10000, the maximum number of digits in a prime number is 5.
#define MAXLIMIT 10000
#define MAXDIGIT 5    

const int firstPrime = 2;
int* primes;
int primeSize;
int setSize;

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

void generatePrimes() {
    primes = malloc(sizeof(int));
    primeSize = 1;
    primes[0] = 2;
    for (int i = 3; i < MAXLIMIT; i += 2) {
        if (isPrimeByList(i)) {
            primeSize++;
            primes = realloc(primes, sizeof(int) * primeSize);
            primes[primeSize - 1] = i;
        }
    }
}

bool checkPrimeConcat(int n1, int n2) {
    char* str1 = malloc(sizeof(char) * MAXDIGIT);
    char* str2 = malloc(sizeof(char) * MAXDIGIT);
    sprintf(str1, "%d", n1);
    sprintf(str2, "%d", n2);

    char* concat = malloc(sizeof(char) * (strlen(str1) + strlen(str2)));
    strcpy(concat, str1);
    long int concat12 = atol(strcat(concat, str2));
    
    strcpy(concat, str2);
    long int concat21 = atol(strcat(concat, str1));
    
    if (!isPrime(concat12) || !isPrime(concat21)) { return false; }
    return true;
}

bool checkSet(int prime, int *set) {
    for (int i = 0; set[i] != 0; i++) {
        if (!checkPrimeConcat(set[i], prime)) { return false; }
    }
    return true;
}

int* primePairSetRecur(int noPrime, int* set, int lastPrime) {
    if (noPrime < 1) { return set; }  // Return the set if the number of primes required to be found is 0 
    for (int i = 0; i < primeSize; i++) {
        if (primes[i] <= lastPrime) { continue; }   // Skip the already checked primes
        /* Skip 2 and 5 since they always result in non primes when they are
           concatenated to other numbers e.g. 12, 22, 15, 25 */ 
        if (primes[i] == 2 || primes[i] == 5) { continue; }

        /* Call checkSet() to check if the prime concatenating to any prime in
           the set always results in a prime */ 
        if (checkSet(primes[i], set)) {
            /* Initialise newSet and add the prime to the set, 
               then recursively call primePairSet() to find next prime */ 
            int* newSet = malloc(sizeof(int) * setSize);
            memcpy(newSet, set, sizeof(int) * setSize);
            newSet[setSize - noPrime] = primes[i];

            newSet = primePairSetRecur(noPrime - 1, newSet, primes[i]);

            /* Check if the new set's size matches the number of primes required to be found */ 
            if (noPrime == 1 || newSet[setSize - (noPrime - 1)] != 0) {
                return newSet;  // Return the new set
            }
        }
    }
    return set; // Return the original set if no matching prime is found.
}

int* primePairSet(int noPrime) {
    int* set = malloc(sizeof(int) * noPrime);
    return primePairSetRecur(noPrime, set, 0);
}

int sumOfPrimePairSet() {
    int sum = 0;

    int* set = primePairSet(setSize);
    if (set[setSize - 1] == 0) {
        printf("Set not found within prime numbers up to %d.\n", MAXLIMIT);
        exit(1);
    }

    for (int i = 0; i < setSize; i++) {
        sum += set[i];
    }
    return sum;
}

int main(int argc, char **argv) {
    setSize = 5; // Set default set size to 5 as required in the original question

    if (argc > 1) { // Take input from command line if a upper limit is given
        setSize = atoi(argv[1]);
        if (setSize < 2) {
            printf("The set size should not be lower than 2.\n");
            return 0;
        }
    }

    generatePrimes();

    printf("%d\n", sumOfPrimePairSet());
}