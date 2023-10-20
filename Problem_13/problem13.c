#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long arrayToInt(int length, int* number)
{
    long sum = 0;
    long n = 1;

    if (length > 10) {
        length = 10;
    }

    for (int i = length - 1; i >= 0; i--)
    {
        sum += number[i] * n;
        n *= 10;
    }

    return sum;
}

// For testing
void arrayToString(int length, int* number) {
    for (int i = 0; i < length; i++)
    {
        printf("%d", number[i]);
    }   
    printf("\n");
}

void reverseArray(int length, int* number)
{
    for (int i = 0; i < length / 2; i++) {
        int temp = number[i];
        number[i] = number[length - i - 1];
        number[length - i - 1] = temp;
    }
}

void addLength(int currentLength, int targetLength, int* number) {
    reverseArray(currentLength, number);    // Reverse array before reallocation such that new 0s are added at the head of the array
    number = realloc(number, sizeof(int) * targetLength);
    if (number == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }
    reverseArray(targetLength, number);
}

long largeSum(int noNumber, int* lengths, int** numbers)
{
    int* sumArray = numbers[0];
    int sumLength = lengths[0];
    int j;
    int carry = 0;

    for (int i = 1; i < noNumber; i++) {
        if (sumLength < lengths[i]) {
            addLength(sumLength, lengths[i], sumArray);
            sumLength = lengths[i];
        }
        else if (lengths[i] < sumLength) {
            addLength(lengths[i], sumLength, numbers[i]);
            lengths[i] = sumLength;
        }

        for (j = lengths[i] - 1; j >= 0; j--) {
            sumArray[j] += numbers[i][j] + carry;
            if (sumArray[j] >= 10) {
                carry = sumArray[j] / 10;
                sumArray[j] %= 10;
            }
            else {
                carry = 0;
            }
        }
        
        if (carry > 0) {
            reverseArray(sumLength, sumArray);
            sumLength++;
            sumArray = realloc(sumArray, sizeof(int) * sumLength);
            if (sumArray == NULL) {
                printf("Memory allocation failed.");
                exit(1);
            }
            reverseArray(sumLength, sumArray);
            sumArray[0] = carry;
        }
    }

    return arrayToInt(sumLength, sumArray);
}

int main(int argc, char **argv)
{
    char* file = "numbers.txt";

    if (argc > 1)   // Take file name from command line
    {
        file = argv[1];
    }

    FILE *fp;
    fp = fopen(file, "r");
    if (file == NULL) {
        printf("Fail to open file.\n");
        return 1;
    }

    int noNumbers = 1;    // Number of numbers
    int noDigits = 0;     // Number of digits in each number

    int** numbers = malloc(sizeof(int*));
    int* lengths = malloc(sizeof(int));
    if (numbers == NULL || lengths == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    numbers[0] = malloc(sizeof(int));
    if (numbers[0] == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    char input = fgetc(fp);
    while (input != EOF)
    {
        if (input == '\n')
        {
            lengths[noNumbers - 1] = noDigits;

            noNumbers++;
            numbers = realloc(numbers, sizeof(int*) * noNumbers);
            lengths = realloc(lengths, sizeof(int*) * noNumbers);
            if (numbers == NULL) {
                printf("Memory allocation failed.");
                return 1;
            }

            noDigits = 0;
        }
        else
        {
            noDigits++;
            numbers[noNumbers - 1] = realloc(numbers[noNumbers - 1], sizeof(int) * noDigits);
            if (numbers[noNumbers - 1] == NULL) {
                printf("Memory allocation failed.");
                return 1;
            }
            numbers[noNumbers - 1][noDigits - 1] = input - '0';    // Convert char to int
        }

        input = fgetc(fp);
    }
    fclose(fp);
    lengths[noNumbers - 1] = noDigits;

    printf("%ld\n", largeSum(noNumbers, lengths, numbers));

    return 0;
}