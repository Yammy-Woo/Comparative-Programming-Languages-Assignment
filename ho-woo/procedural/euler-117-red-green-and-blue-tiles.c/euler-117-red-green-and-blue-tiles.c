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
    char* difference = malloc(sizeof(char) * (length + 1));
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
    if (strlen(difference) == 0) {
        difference = "0";
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
    //printf("n1: %s n2: %s\n", n1, n2);

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
        //printf("%s\n", product);
        //printf("np+c: %s\n", newProduct);
        /* Add the product to the totak product string */
        strcat(newProduct, tens);       // Add 0 at the end
        //printf("pro: %s newPro: %s\n", product, newProduct);
        product = add(product, newProduct);
        //printf("%s\n", product);
        strcat(tens, "0");
    }
    
    return product;
}

int compare(char* n1, char* n2) {
    if (strlen(n1) < strlen(n2)) { return -1; }
    if (strlen(n1) > strlen(n2)) { return 1; }
    return strcmp(n1, n2);
}

/* Return the quotient of two large numbers represented as strings. */
char* divide(char* n1, char* n2) {
    char* dividend = malloc(sizeof(char) * strlen(n1));
    char* quotient = malloc(sizeof(char) * strlen(n1));
    char* product = malloc(sizeof(char) * (strlen(n2) + 1));
    if (dividend == NULL || quotient == NULL || product == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("n1: %s n2: %s\n", n1, n2);

    // Continue iteration until dividend is not smaller than divisor
    int index = 0;
    while (index < strlen(n1) && compare(dividend, n2) < 0) {
        strncat(dividend, &n1[index], 1);
        index++;
    }

    for (int i = index - 1; i < strlen(n1); i++) {
        printf("dividend: %s divisor: %s\n", dividend, n2);

        int times = (dividend[0] - '0') / (n2[0] - '0');
        printf("times: %d\n", times);

        char tempQuot[10];
        sprintf(tempQuot, "%d", times);

        product = multiply(n2, tempQuot);

        printf("dividend: %s product: %s\n", dividend, product);
        while (compare(dividend, product) < 0) {
            times--;
            sprintf(tempQuot, "%d", times);
            product = multiply(n2, tempQuot);
        }

        while (times < 10 && compare(subtract(dividend, product), n2) >= 0) {
            times++;
            sprintf(tempQuot, "%d", times);
            product = multiply(n2, tempQuot);
            printf("times: %d product: %s\n", times, product);
        }
        printf("product: %s\n", product);
        dividend = subtract(dividend, product);

        printf("quot: %s remainder: %s\n", tempQuot, dividend);

        strcat(quotient, tempQuot);

        strncat(dividend, &n1[i + 1], 1);
        printf("%s\n", dividend);
    }

    if (strlen(quotient) == 0) {
        return "0";
    }

    printf("quotient: %s\n", quotient);

    return quotient;
}

char* factorialWithStart(char* r, char* n) {
    //printf("r: %s n: %s\n", r, n);
    if (compare(n, r) == 0) {
        return "1";
    }
    //printf("sub: %s temp: %s\n", subtract(n, "1"), temp);
    //printf("%s * %s: %s\n", n, temp, multiply(n, temp));
    return multiply(n, factorialWithStart(r, subtract(n, "1")));
}

char* factorial(char* n) {
    return factorialWithStart("1", n);
}

char* combination(int n, int r) {
    char* strN = malloc(sizeof(char) * 2);
    char* strR = malloc(sizeof(char) * 2);
    char* strNR = malloc(sizeof(char) * 2);;
    sprintf(strN, "%d", n);
    sprintf(strR, "%d", r);
    sprintf(strNR, "%d", n - r);

    if (r == 1) { return strN; }
    if (n == r) { return "1"; }

    //printf("n: %s\n", factorial(strN));
    //printf("r: %s\n", factorial(strR));
    printf("n: %d r: %d\n", n, r);
    printf("n / r: %s\n", factorialWithStart(strR, strN));
    printf("n - r: %s\n", factorial(strNR));
    //printf("mul: %s\n", multiply(factorial(strR), factorial(strNR)));
    //return divide(factorial(strN), multiply(factorial(strR), factorial(strNR)));
    return divide(factorialWithStart(strR, strN), factorial(strNR));
}

char* countWays(int red, int green, int blue, int totalUnits) {
    char* count = malloc(sizeof(char) * MAX_LENGTH);
    char* ways = malloc(sizeof(char) * MAX_LENGTH);
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
                //printf("tiles: %d\n", tiles);
                ways = multiply(combination(tiles, i), multiply(combination(tiles - i, j), combination(tiles - i - j, k)));
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

    char* n1 = malloc(sizeof(char) * 100);
    char* n2 = malloc(sizeof(char) * 100);
    
    strcpy(n1, "0");
    strcpy(n2, "0");
    
    //printf("Result: %s\n", subtract("1", "1"));
    //printf("Result: %s\n", factorialWithStart("5", "20"));
    //printf("%s\n", factorial("20"));
    // printf("Result: %s\n", divide("10055", "8"));
    //printf("%s\n", combination(39, 1));
    //printf("%s\n", combination(20, 5));
    //printf("Result: %s\n", multiply("523022617466601111760007224100074291200000000", "9"));
    // char *string, *endptr;
    // unsigned long long int dividend;
    // string = "15511210043330985984000000";
    // strtoull(string, &endptr, dividend);
    // printf("%llu\n", dividend);
    // char *str1 = "5600";
    // char *str2 = "8";
    // printf("%s\n",  strcmp(str1, str2) < 0 ? "True" : "False");
    
    char* count = countWays(red, green, blue, totalUnits);    // Call countWays() to get the result
    printf("Count: %s\n", count);
    return 0;
}