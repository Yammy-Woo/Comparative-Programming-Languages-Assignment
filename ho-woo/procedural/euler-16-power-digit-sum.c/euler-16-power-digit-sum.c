#include <stdio.h>
#include <stdlib.h>

/* Global variables */
const int base = 2;
int exponent;

/* Use a linked list of Digits to represent the large number (2 power exponent) */
/* struct Digit containing a digit and keep a record of the previous node and next node in the list */
typedef struct Digit
{
    int value;
    struct Digit* prev;
    struct Digit* next;
}Digit;

/* Calculate the sum of the digits of the number and print the sum */
void printSum(Digit* tail) {
    Digit *current = tail;  // Start from tail
    int sum = 0;
    /* Iterate through the digits and sum them */
    do
    {
        sum += current->value;  
        current = current->prev;
    } while (current != NULL);

    printf("%d\n", sum);
}

/* Calculate the number 2 powers the input exponent using a linked list of Digits.
   Return the tail pointer of the linked list of Digits representing the resulting number. */
Digit* powerToDigits(Digit* head, Digit* tail) {
    int carry;
    /* Allocate meomory for current and temp */
    Digit* current = malloc(sizeof(Digit));
    Digit* temp = malloc(sizeof(Digit));

    if (current == NULL || temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    /* Multiply the number in each loop. The number of iteration is the input exponent. */
    for (int i = 0; i < exponent; i++)
    {
        current = head;
        carry = 0;

        /* Multiply the number in each loop */
        while (current != NULL)
        {
            current->value = current->value * base + carry;   // Calculate the value in each digit

            /* Carrying */
            if (current->value >= 10) 
            {
                carry = current->value / 10;
                current->value %= 10;
            }
            else
            {
                carry = 0;
            }
            current = current->next;
        }

        /* Add carry to the tail if carry > 0 */
        if (carry > 0)
        {
            tail->next = malloc(sizeof(Digit));
            if (tail->next == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }

            tail->next->value = carry;
            tail->next->prev = tail;
            tail = tail->next;
        }
    }
    return tail;
}

int main(int argc, char **argv)
{
    exponent = 1000;    // Set default exponent to 1000 as required in the original question

    if (argc > 1)           // Take input from command line if a upper limit is given
    {
        exponent = atoi(argv[1]);
    }

    /* Initialize head pointer of the linked list */
    Digit *head = malloc(sizeof(Digit));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head->value = 1;
    head->prev = NULL;
    head->next = NULL;

    Digit *tail = head;     // Initialize tail pointer
    tail = powerToDigits(head, tail);   // Call powerToDigits() and receive the tail of the resulting number
    printSum(tail); // Call printSum() to calculate and display the sum of the digits in the number

    return 0;
}