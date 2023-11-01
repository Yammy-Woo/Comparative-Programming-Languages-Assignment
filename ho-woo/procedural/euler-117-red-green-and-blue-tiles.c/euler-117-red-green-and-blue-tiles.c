#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX_LENGTH 100  // Maximum length of large number

// Insert 0 at the head of string to increase its length to the required length
char* addLength(int length, char* n) {
    if (strlen(n) >= length) {
        return n;
    }
    char* newN = malloc(sizeof(char) * length);
    if (newN == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    
    while (strlen(newN) + strlen(n) < length) {
        strcat(newN, "0");
    }
    strcat(newN, n);

    return newN;
}

/* Return the sum of two large numbers represented as strings. */
char* add(char* n1, char* n2) {
    int carry = 0;
    int length = strlen(n1) > strlen(n2) ? strlen(n1) : strlen(n2);
    char* sum = malloc(sizeof(char) * (length + 1));
    if (sum == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    n1 = addLength(length, n1);
    n2 = addLength(length, n2);

    for (int i = length - 1; i >= 0; i--) {
        int tempSum = (n1[i] - '0') + (n2[i] - '0') + carry;
        if (tempSum >= 10) {
            carry = tempSum / 10;
            tempSum %= 10;
        }
        else {
            carry = 0;
        }
        char newSum[length];
        sprintf(newSum, "%d", tempSum);
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

/* Return the difference of two large numbers represented as strings.
   The difference is always positive. */
char* subtract(char* n1, char* n2) {
    int borrow = 0;
    int length = strlen(n1) > strlen(n2) ? strlen(n1) : strlen(n2);
    char* difference = malloc(sizeof(char) * length);
    if (difference == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    n1 = addLength(length, n1);
    n2 = addLength(length, n2);

    for (int i = length - 1; i >= 0; i--) {
        int tempDiff = (n1[i] - '0') - (n2[i] - '0') - borrow;
        if (tempDiff < 0) {
            borrow = 1;
            tempDiff += 10;
        }
        else {
            borrow = 0;
        }

        if (i == 0 && tempDiff == 0) { break; }     // Avoid inserting 0 at the head of the final difference 
        char newDifference[length];
        sprintf(newDifference, "%d", tempDiff);
        strcat(newDifference, difference);     // Insert new digit before difference
        strcpy(difference, newDifference);
    }
    return difference;
}

/* Return the product of two large numbers represented as strings. */
char* multiply(char* n1, char* n2) {
    int carry = 0;
    int maxLength = strlen(n1) + strlen(n2);
    char* tens = malloc(sizeof(char) * maxLength);
    char* product = malloc(sizeof(char) * maxLength);
    if (tens == NULL || product == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    product = "0";

    for (int i = strlen(n1) - 1; i >= 0; i--) {
        char* newProduct = malloc(sizeof(char) * maxLength);
        if (newProduct == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        for (int j = strlen(n2) - 1; j >= 0; j--) {
            //printf("n1: %c n2: %c\n", n1[i], n2[j]);
            int tempProduct = (n1[i] - '0') * (n2[j] - '0') + carry;
            if (tempProduct >= 10) {
                carry = tempProduct / 10;
                tempProduct %= 10;
            }
            else {
                carry = 0;
            }
            //printf("tp: %d\n", tempProduct);
            /* Insert new digit to the head of the product string */
            char temp[maxLength];
            sprintf(temp, "%d", tempProduct);
            strcat(temp, newProduct);
            strcpy(newProduct, temp);
        }
        //printf("np: %s\n", newProduct);
        /* Insert carry to the head of the product string */
        if (carry > 0) {
            char temp[maxLength];
            sprintf(temp, "%d", carry);
            strcat(temp, newProduct);
            strcpy(newProduct, temp);
            carry = 0;
        }
        //printf("np+c: %s\n", newProduct);
        /* Add the product to the totak product string */
        strcat(newProduct, tens);       // Add 0 at the end
        //printf("pro: %s\n", newProduct);
        product = add(product, newProduct);
        strcat(tens, "0");
    }
    return product;
}

/* Return the quotient of two large numbers represented as strings. */
char* divide(char* n1, char* n2) {
    if (strlen(n2) >= 15) {     // Nearly exceed maximum value of long long int
        return divide(divide(n1, divide(n2, "10000")), "10000");
    }

    char* tempDividend = malloc(sizeof(char) * strlen(n1));
    char* quotient = malloc(sizeof(char) * strlen(n1));
    if (tempDividend == NULL || quotient == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    //printf("n1: %s n2: %s\n", n1, n2);

    // Continue iteration until dividend is not smaller than divisor
    int index = 0;
    while (index < strlen(n1) && atoll(tempDividend) < atoll(n2)) {
        strncat(tempDividend, &n1[index], 1);
        index++;
    }

    for (int i = index - 1; i < strlen(n1); i++) {
        if (atoll(tempDividend) == LLONG_MAX || atoll(n2) == LLONG_MAX) {
            printf("dividend: %lld divisor: %lld\n", atoll(tempDividend), atoll(n2));
        }
        
        long long int tempQuot = atoll(tempDividend) / atoll(n2);    
        sprintf(tempDividend, "%lld", atoll(tempDividend) % atoll(n2));
        //printf("quot: %lld remainder: %s\n", tempQuot, tempDividend);

        char temp[strlen(n1)];
        sprintf(temp, "%lld", tempQuot);
        strcat(quotient, temp);

        strncat(tempDividend, &n1[i + 1], 1);
        //printf("%s\n", tempDividend);
    }

    if (strlen(quotient) == 0) {
        return "0";
    }

    //printf("%s\n", quotient);

    return quotient;
}

char* factorialWithStart(char* r, char* n) {
    // printf("r: %s n: %s\n", r, n);
    if (strcmp(n, r) <= 0) {
        return "1";
    }
    char* temp = factorialWithStart(r, subtract(n, "1"));
    //printf("sub: %s temp: %s\n", subtract(n, "1"), temp);
    //printf("%s*temp: %s\n", n, multiply("5", "24"));
    return multiply(n, temp);
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

    // printf("n: %s\n", factorial(strN));
    // printf("r: %s\n", factorial(strR));
    // printf("n - r: %s\n", factorial(strNR));
    // printf("mul: %s\n", multiply(factorial(strR), factorial(strNR)));
    return divide(factorial(strN), multiply(factorial(strR), factorial(strNR)));
}

char* countWays(int red, int green, int blue, int totalUnits) {
    char* count = malloc(sizeof(char) * MAX_LENGTH);
    if (count == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    count = "0";
    // Start from 1 and increment the number of red/green/blue tiles
    for (int i = 0; i * red <= totalUnits; i++) { 
        for (int j = 0; i * red + j * green <= totalUnits; j++) {
            for (int k = 0; i * red + j * green + k * blue <= totalUnits; k++) {
                int tiles = i + j + k + (totalUnits - red * i - green * j - blue * k);   // Find the number of tiles in the row
                char* ways = multiply(combination(tiles, i), multiply(combination(tiles - i, j), combination(tiles - i - j, k)));
                printf("Tiles: %d\tRed: %d\tGreen: %d\tBlue: %d\tGrey: %d\tWays: %s\n", tiles, i, j, k, tiles - i - j - k, ways);
                printf("%s\n %s\n %s\n", combination(tiles, i), combination(tiles - i, j), combination(tiles - i - j, k));
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

    char* n1 = malloc(sizeof(char) * 100);
    char* n2 = malloc(sizeof(char) * 100);
    
    strcpy(n1, "0");
    strcpy(n2, "0");
    
    //printf("Result: %s\n", subtract("10", "1"));
    //printf("Result: %s\n", factorialWithStart("7", "10"));
    // printf("%s\n", factorial("29"));
    // printf("%s\n", divide("4292145000", "1000"));
    printf("%s\n", combination(50, 25));
    //printf("%s\n", combination(7, 5));
    //printf("Result: %s\n", multiply("24", "5"));

    
    // char* count = countWays(red, green, blue, totalUnits);    // Call countWays() to get the result
    // printf("Count: %s\n", count);
    return 0;
}