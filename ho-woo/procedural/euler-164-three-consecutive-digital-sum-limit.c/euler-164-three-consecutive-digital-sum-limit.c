#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

long int* cache;
int cacheSize;

int nextMaxDigit(int lastDigit, int currentDigit) {
    return 9 - lastDigit - currentDigit;
}

long int countCombinationRecur(int lastDigit, int currentDigit, int noDigit) {
    if (noDigit == 0) { return currentDigit == 0 ? 0 : 1; }     // Leading zero not allowed

    int key = lastDigit + currentDigit * 10 + noDigit * 100;
    if (cache[key] >= 0) {
        return cache[key];
    }

    int maxDigit = nextMaxDigit(lastDigit, currentDigit);
    long int count = 0;

    for (int nextDigit = 0; nextDigit <= maxDigit; nextDigit++) {
        count += countCombinationRecur(currentDigit, nextDigit, noDigit - 1);
    }
    
    cache[key] = count;
    return count;
}

long int countCombination(int noDigit) {
    return countCombinationRecur(0, 0, noDigit);
}

int main(int argc, char **argv) {
    int noDigit = 20;  // Set number of digits to 20 by default as required in the original question

    if (argc > 1) { // Take input from command line if given
        noDigit = atoi(argv[1]);
    }
    
    cacheSize = 100 * pow(10, (int)log10(noDigit) + 1);
    cache = malloc(sizeof(long int) * cacheSize);
    memset(cache, -1, sizeof(long int) * cacheSize);

    printf("%ld\n", countCombination(noDigit));
}