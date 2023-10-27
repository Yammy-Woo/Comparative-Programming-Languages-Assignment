#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int firstPrime = 2;
int* primes;
int* sizedPrimes;
int size;

/* Function to check whether a given number is a prime number */
bool isPrime(int n)
{
    for (int i = firstPrime; i <= n / 2; i++)
    {
        if (n % i == 0) 
        {
            return false;   // False if the given number is not a prime number
        }
    }
    return true;    // True if the given number is a prime number
}

/* Function to check whether a given number is a prime number by the list of prime numbers */
bool isPrimeByList(int n)
{
    for (int i = 0; primes[i] <= n / 2; i++)
    {
        if (n % primes[i] == 0) 
        {
            return false;   // False if the given number is not a prime number
        }
    }
    return true;    // True if the given number is a prime number
}

void generatePrimes(int limit)
{
    sizedPrimes = malloc(sizeof(int));
    size = 1;
    sizedPrimes[0] = 2;
    for (int i = 3; i < limit; i += 2) {
        if (isPrimeByList(i)) {
            size++;
            sizedPrimes = realloc(sizedPrimes, sizeof(int) * size);
            sizedPrimes[size - 1] = i;
        }
    }
    primes = sizedPrimes;
}

int main(int argc, char **argv)
{
    int setSize = 5;        // Set default set size to 5 as required in the original question

    if (argc > 1)           // Take input from command line if a upper limit is given
    {
        setSize = atoi(argv[1]);
        if (setSize <= 2) 
        {
            printf("The set size should not be lower than 2.\n");
            return 0;
        }
    }

    generatePrimes(10000);
    for (int i = 0; i < size; i++) {
        printf("%d\n", primes[i]);
    }
}