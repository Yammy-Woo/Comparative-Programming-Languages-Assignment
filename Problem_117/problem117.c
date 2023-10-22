#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long int factorialWithStart(int r, unsigned long long int n) {
    if (n <= r) {
        return 1;
    }

    unsigned long long int accumulator = factorialWithStart(r, n - 1);
    if (accumulator <= 0) {
        return 0;
    }
    if (ULLONG_MAX / accumulator < n) {
        printf("Too Large! Max: %llu\n", ULLONG_MAX);
        n = 0;
    }
    return n * accumulator;
}

unsigned long long int factorial(int n) {
    return factorialWithStart(1, n);
}

unsigned long long int combination(int n, int r) {
    //printf("Combination: %llu\t%llu\n", factorialWithStart(r, n), factorial(n - r));
    unsigned long long int result;
    if (n - r > r) {
        result = factorialWithStart(n - r, n) / factorial(r);
    }
    else {
        result = factorialWithStart(r, n) / factorial(n - r);
    }
    
    if (result <= 0) {
        printf("%d %d %d %d %d\n", n - r, n / 2, r, n / 2, n);
        return factorialWithStart(n - r, n / 2) / factorial(r) * factorialWithStart(n / 2, n);
    }
    return result;
}

unsigned long long int countWays(int red, int green, int blue, int totalUnits) {
    unsigned long long count = 0;
    for (int i = 0; i * red <= totalUnits; i++) { // Start from 1 and increment the number of red/green/blue tiles
        for (int j = 0; i * red + j * green <= totalUnits; j++) {
            for (int k = 0; i * red + j * green + k * blue <= totalUnits; k++) {
                int tiles = i + j + k + (totalUnits - red * i - green * j - blue * k);   // Find the number of tiles in the row
                unsigned long long int ways = combination(tiles, i) * combination(tiles - i, j) * combination(tiles - i - j, k);
                if (tiles > 30 && i > 10) {
                    printf("Tiles: %d\tRed: %d\tGreen: %d\tBlue: %d\tGrey: %d\tWays: %llu\n", tiles, i, j, k, tiles - i - j - k, ways);
                }
                count += ways;
            }
        }      
    }
    
    return count;
}

/* This function counts the number of ways a row can be tiled with the given types of tiles.
    size: Number of tile types, colors: Units of each tile, totalUnits: Number of empty units to be filled */
unsigned long long countWaysR(int size, int* colors, int totalUnits, int noTile, unsigned long long count) {
    if (size == 0) {
        return 1;
    }
    if (noTile * colors[size - 1] <= totalUnits) {
        int tiles = noTile + (totalUnits - colors[size - 1] * noTile);
        count += combination(tiles, noTile) * countWaysR(size - 1, colors, totalUnits - colors[size - 1] * noTile, noTile + 1, count);
        printf("Color: %d\tNoTiles: %d\tTiles: %d\tCount: %lld\tReturn: %lld\n", colors[size - 1], noTile, tiles, count, combination(tiles, noTile));
        return combination(tiles, noTile);
    }
    return countWaysR(size - 1, colors, totalUnits, 0, count);
}

unsigned long long countWaysBase(int size, int* colors, int totalUnits) {
    return countWaysR(size, colors, totalUnits, 0, 0);
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

    unsigned long long  count = countWays(red, green, blue, totalUnits);    // Call countWays() to get the result
    printf("Count: %llu\n", count);
    printf("F: %llu\n", factorial(14));
    printf("C: %llu\n", combination(31, 14));

    // int count = countWaysBase(size, colors, totalUnits);
    // printf("%d\n", count);

    return 0;
}