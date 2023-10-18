#include <stdio.h>
#include <stdlib.h>

int countDivisors(int n)
{
    int count = 0;
    int i;
    for (i = 1; i * i < n; i++)
    {
        if (n % i == 0) 
        {
            count += 2;
        }
    }

    if (i * i == n) { count++;}

    return count;
}

int main(int argc, char **argv)
{
    int divisors = 500; // Set default required number of divisors to 500 as required in the original question

    if (argc > 1)           // Take input from command line if given
    {
        divisors = atoi(argv[1]);
    }

    int i = 1;
    int n = 1;
    while(countDivisors(n) <= divisors) { 
        i++;
        n += i;
    }

    printf("The value of the first triangle number to have over %d divisors: %d\n", divisors, n);

    return 0;
}