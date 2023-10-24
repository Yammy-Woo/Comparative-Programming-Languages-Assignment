#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 100

void addLength(int length, char* n) {
    n = realloc(n, sizeof(char) * length);
    char* newN = malloc(sizeof(char) * length);
    
    while (strlen(n) < length) {
        strcpy(newN, "0");
        strcat(newN, n);
        strcpy(n, newN);
    }
    free(newN);
}

char* add(char* n1, char* n2) {
    int carry = 0;
    int length = strlen(n1) > strlen(n2) ? strlen(n1) : strlen(n2);
    char* sum = malloc(sizeof(char) * (length + 1));
    addLength(length, n1);
    addLength(length, n2);

    for (int i = length - 1; i >= 0; i--) {
        int tempProduct = (n1[i] - '0') + (n2[i] - '0') + carry;
        if (tempProduct >= 10) {
            carry = tempProduct / 10;
            tempProduct %= 10;
        }
        else {
            carry = 0;
        }
        char newSum[length];
        sprintf(newSum, "%d", tempProduct);
        strcat(newSum, sum);     // Insert new digit before sum
        strcpy(sum, newSum);
    }
    if (carry > 0) {
        char newSum[length + 1];
        sprintf(newSum, "%d", carry);
        strcat(newSum, sum);
        strcpy(sum, newSum);
    }
    return sum;
}

char* multiply(char* n1, char* n2) {
    int carry = 0;
    int maxLength = strlen(n1) + strlen(n2);
    char* tens = malloc(sizeof(char) * maxLength);
    char* product = malloc(sizeof(char) * maxLength);

    for (int i = strlen(n2) - 1; i >= 0; i--) {
        char* newProduct = malloc(sizeof(char) * maxLength);
        for (int j = strlen(n1) - 1; j >= 0; j--) {
            int tempProduct = (n2[i] - '0') * (n1[j] - '0') + carry;
            printf("%d\n", tempProduct);
            if (tempProduct >= 10) {
                carry = tempProduct / 10;
                tempProduct %= 10;
            }
            else {
                carry = 0;
            }
            /* Insert new digit to the head of the product string */
            char temp[maxLength];
            sprintf(temp, "%d", tempProduct);
            strcat(temp, newProduct);
            strcpy(newProduct, temp);
        }
        /* Insert carry to the head of the product string */
        if (carry > 0) {
            char temp[maxLength];
            sprintf(temp, "%d", carry);
            strcat(temp, newProduct);
            strcpy(newProduct, temp);
        }
        /* Add the product to the totak product string */
        strcat(newProduct, tens);       // Add 0 at the end
        product = add(product, newProduct);
        strcat(tens, "0");
    }
    return product;
}

char* divide(char* n1, char* n2) {

    return "";
}

char* factorialWithStart(char* r, char* n) {
    if (n <= r) {
        return "1";
    }

    return multiply(n, factorialWithStart(r, n - 1));
}

char* factorial(char* n) {
    return factorialWithStart("1", n);
}

char* combination(int n, int r) {
    char strN[MAX_LENGTH];
    char strR[MAX_LENGTH];
    char strNR[MAX_LENGTH];
    sprintf(strN, "%d", n);
    sprintf(strR, "%d", r);
    sprintf(strNR, "%d", n - r);
    return divide(factorialWithStart(strNR, strN), factorial(strR));
}

char* countWays(int red, int green, int blue, int totalUnits) {
    char* count = malloc(sizeof(char) * MAX_LENGTH);
    count = "0";
    for (int i = 0; i * red <= totalUnits; i++) { // Start from 1 and increment the number of red/green/blue tiles
        for (int j = 0; i * red + j * green <= totalUnits; j++) {
            for (int k = 0; i * red + j * green + k * blue <= totalUnits; k++) {
                int tiles = i + j + k + (totalUnits - red * i - green * j - blue * k);   // Find the number of tiles in the row
                char* ways = multiply(combination(tiles, i), multiply(combination(tiles - i, j), combination(tiles - i - j, k)));
                if (tiles > 30 && i > 10) {
                    printf("Tiles: %d\tRed: %d\tGreen: %d\tBlue: %d\tGrey: %d\tWays: %s\n", tiles, i, j, k, tiles - i - j - k, ways);
                }
                count = add(count, ways);
            }
        }      
    }
    
    return count;
}

int main(int argc, char **argv)
{
    const int red = 2, green = 3, blue = 4;
    int totalUnits = 50;
    if (argc > 1)           // Take input from command line if given
    {
        totalUnits = atoi(argv[1]);
    }

    int colors[] = {red, green, blue};            // Tile types
    int size = sizeof(colors) / sizeof(int);    // Number of tile types
    //int count = countWays(size, colors, totalUnits);    // Call countWays() to get the result

    char* count = countWays(red, green, blue, totalUnits);    // Call countWays() to get the result
    printf("Count: %s\n", count);

    char* n1 = malloc(sizeof(char) * 100);
    char* n2 = malloc(sizeof(char) * 100);
    strcpy(n1, "31");
    strcpy(n2, "");
    printf("%s\n", combination(31, 11));

    // int count = countWaysBase(size, colors, totalUnits);
    // printf("%d\n", count);

    return 0;
}