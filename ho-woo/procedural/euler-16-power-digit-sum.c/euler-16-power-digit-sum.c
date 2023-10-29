#include <stdio.h>
#include <stdlib.h>

const int base = 2; 
int exponent;

typedef struct Digit
{
    int value;
    struct Digit* prev;
    struct Digit* next;
}Digit;

void printSum(Digit* tail) {
    Digit *current = tail;
    int sum = 0;

    do
    {
        sum += current->value;
        current = current->prev;
    } while (current != NULL);

    printf("%d\n", sum);
}

Digit* powerToDigits(Digit* head, Digit* tail) {
    int carry;
    Digit* current = malloc(sizeof(Digit));
    Digit* temp = malloc(sizeof(Digit));

    if (current == NULL || temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < exponent; i++)
    {
        current = head;
        carry = 0;

        while (current != NULL)
        {
            current->value = current->value * base + carry;

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
    exponent = 1000;    // Set default to 1000 as required in the original question

    if (argc > 1)           // Take input from command line if a upper limit is given
    {
        exponent = atoi(argv[1]);
    }

    /* Initialize head of the linked list */
    Digit *head = malloc(sizeof(Digit));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head->value = 1;
    head->prev = NULL;
    head->next = NULL;

    Digit *tail = head;
    tail = powerToDigits(head, tail);
    printSum(tail);

    return 0;
}