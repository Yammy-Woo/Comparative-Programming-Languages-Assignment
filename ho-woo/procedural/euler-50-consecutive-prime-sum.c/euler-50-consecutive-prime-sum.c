#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int firstPrime = 2;

typedef struct Prime
{
    int value;
    struct Prime* prev;
    struct Prime* next;
}Prime;


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

void printSum(Prime *head, Prime *tail, int sum)
{
    Prime *current = head;
    while (current != tail)
    {
        printf("%d + ", current->value);
        current = current->next;
    }
    printf("%d = %d\n", current->value, sum);
    printf("Longest sum of consecutive primes: %d\n", sum);
}

int main(int argc, char **argv)
{
    int limit = 1000000;    // Set default limit to 1 million as required in the original question

    if (argc > 1)           // Take input from command line if a upper limit is given
    {
        limit = atoi(argv[1]);
        if (limit <= 2) 
        {
            printf("The input limit cannot be 2 or lower, since 2 is the first prime number.\n");
            return 0;
        }
    }

    int i = firstPrime;

    /* Initialize head of the linked list */
    Prime *head = malloc(sizeof(Prime));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head->value = i;
    head->prev = NULL;
    head->next = NULL;

    Prime *current = head;

    int sum = i;                // sum of consecutive primes
    int length_sum = 1;         // length of sum

    while (sum < limit)
    {
        i++;

        if (isPrime(i)) {
            current->next = malloc(sizeof(Prime));
            if (current->next == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
            }

            current->next->value = i;
            current->next->prev = current;
            current->next->next = NULL;
            current = current->next;

            sum += i;
            length_sum++;
        }
    }

    Prime *tail = current;
    Prime *currentHead = head;
    Prime *currentTail = tail;
    int currentSum = sum;

    while (currentHead != currentTail)
    {
        // Shift right
        while (currentSum < limit && !isPrime(currentSum) && currentTail->next != NULL)
        {
            currentSum -= currentHead->value;
            currentHead = currentHead->next;

            currentTail = currentTail->next;
            currentSum += currentTail->value;
        }
        if (currentSum < limit && isPrime(currentSum)) { break; }

        sum -= tail->value;
        tail = tail->prev;
        
        currentHead = head;
        currentTail = tail;
        currentSum = sum;
    }

    printSum(currentHead, currentTail, currentSum);

    return 0;
}