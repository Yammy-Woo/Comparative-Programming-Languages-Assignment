#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int noNumbers = 100;    // Number of numbers
int noDigits = 50;      // Number of digits in each number

int arrayToInt(int* sumArray)
{
    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += sumArray[i] * pow(10, i);
    }
    return sum;
}

int largeSum(int* numbers)
{
    int length = noDigits;
    int sumArray = malloc(sizeof(int) * length);
    if (sumArray == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }
    int carry;

    memset(sumArray, 0, (noDigits + 1) * sizeof(int));

    for (int i = 0; i < noNumbers; i++)
    {
        carry = 0;
        for (int j = 0; j < noDigits; j++)
        {
            sumArray[j] += numbers[noDigits - j + 1];
            sumArray[j] += carry;

            if (sumArray[j] >= 10) 
            {
                carry = sumArray[j] % 10;
                sumArray[j] /= 10;
            }
            else
            {
                carry = 0;
            }
            printf("%d", sumArray[j]);
        }

        if (carry > 0)
        {
            sumArray = realloc(sumArray, sizeof(int) * (length + 1));
            sumArray[length] = carry;
            length++;
        }
        printf("\n");
    }

    return arrayToInt(sumArray);
}

int main(int argc, char **argv)
{
    int numbers[noNumbers][noDigits];

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

    int i = 0, j = 0;

    char input = fgetc(fp);
    while (input != EOF)
    {
        if (input == '\n')
        {
            i++;
            j = 0;
        }
        else
        {
            numbers[i][j] = input - '0';    // Convert char to int
            j++;
        }

        input = fgetc(fp);
    }
    fclose(fp);

    printf("%d\n", largeSum(*numbers));

    return 0;
}