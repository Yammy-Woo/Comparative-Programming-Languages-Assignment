#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int firstPrime = 2;

int main(int argc, char **argv)
{
    long n = 600851475143;    // Set default limit to 600851475143 as required in the original question

    if (argc > 1)           // Take input from command line if given
    {
        n = atol(argv[1]);
    }

    long maxPrimeFactor = -1;
    long i = firstPrime;

    while (n >= firstPrime)
    {
        /* If n is divisible by i, divide n by i until the new n is not divisible by i. 
           Since n is not divisible by i, it is not divisible by any number which has i as a n.
           As a result, non-prime numbers are filtered out. */
        while (n % i == 0)
        {
            n /= i;
            maxPrimeFactor = i;
        }   

        i++; // Increment i
        
        /* After the above while loop, the n variable is not divisible by any value smaller than i. 
           For any number j smaller than i, i * j is not divisible by n. 
           Therefore, if i * i > n, it is guaranteed that n is not divisible by any number equal to or larger than i. 
           This proves that n is a prime number. */
        if (i * i > n) 
        {
            if (n > maxPrimeFactor)
            {
                maxPrimeFactor = n;
            }
            break;
        }
    }

    if (maxPrimeFactor < 0)
    {
        printf("No prime factor found.\n");
    }
    else
    {
        printf("Largest prime factor: %ld\n", maxPrimeFactor);
    }

    return 0;
}