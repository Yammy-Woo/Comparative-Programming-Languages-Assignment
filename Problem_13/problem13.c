#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long arrayToInt(int length, int* sumArray)
{
    long sum = 0;
    long n = 1;
    for (int i = 0; i < 10; i++)
    {
        sum += sumArray[i] * n;
        n *= 10;
    }

    return sum;
}

long largeSum(int noNumber, int* lengths, int** numbers)
{
    int* sumArray = numbers[0];
    int j;
    int carry;

    for (int i = 0; i < noNumber; i++) {
        carry = 0;
        for (j = lengths[i] - 1; j >= 0; j--) {
            sumArray[j] += numbers[i][j];
            if (sumArray[j] >= 10) {
                carry = sumArray[j] % 10;
                sumArray[j] /= 10;
            }
        }
        
        if (carry > 0) {
            j++;
            sumArray = realloc(sumArray, sizeof(int) * j);
            if (sumArray == NULL) {
                printf("Memory allocation failed.");
                return 1;
            }
            sumArray[j] = carry;
        }
    }

    return arrayToInt(j, sumArray);
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