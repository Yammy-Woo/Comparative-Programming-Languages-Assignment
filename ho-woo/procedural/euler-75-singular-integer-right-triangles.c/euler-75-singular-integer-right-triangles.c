#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* According to Euclid's Formula for Pythagorean Triples, 
    (a, b, c) are a Pythagorean triple iff 
    a = k * (m^2 - n^2)
    b = k * 2mn
    c = k * (m^2 + n^2)
    where k >= 1, m > n > 0, either m or n is even and m, n are coprime.
    Reference: https://en.wikipedia.org/wiki/Pythagorean_triple
*/
/* Check whether the given two numbers are coprime, i.e. they have their highest common factor as 1. */
bool coprime(int m, int n) {
    if (m == 1 || n == 1) { return true; }  // Return true if numbers have only 1 as their common factor.
    if (m == n) { return false; }   // Return False if m == n != 1, meaning that they have m as their common factor.

    if (m > n) { m = m % n; }
    else { n = n % m; }
    if (m == 0 || n == 0) { return false; }     // Return False if either m or n is divisible by the other.
    return coprime(m, n);
}

int* findSides(int* size, int* perimeters, int maxPerimeter) {
    /* The sum of the triple, which is the perimeter, is
        (m^2 - n^2) + 2mn + (m^2 + n^2) = 2(m^2) + 2mn.
        Given the smallest n = 1, the smallest perimeter will be 2(m^2) + 2m.
        Therefore, if 2(m^2) + 2m > maxPerimeter, the resulting perimeter must exceed maxPerimeter. 
    */
    for (int m = 2; 2 * m * m + 2 * m <= maxPerimeter; m++) {
        for (int n = 1; n < m; n++) {
            if ((m + n) % 2 == 0) { continue; } // Skip n when m and n are both even or odd
            if (!coprime(m, n)) { continue; }   // Skip n when m and n are not coprime

            int a = m * m - n * n;
            int b = 2 * m * n;
            int c = m * m + n * n;
            int tripleSum = a + b + c;
            for (int k = 1; k * tripleSum <= maxPerimeter; k++) {
                int perimeter = k * tripleSum;
                *size += 1;
                perimeters = realloc(perimeters, sizeof(int) * (*size));
                if (perimeters == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                perimeters[*size - 1] = perimeter;
            }
        }
    }
    return perimeters;
}

void printArray(int size, int* array) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Quick Sort Reference: https://www.geeksforgeeks.org/quick-sort/?ref=lbp
void swap(int* array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int pos = low - 1;
    for (int i = low; i < high; i++) {
        if (array[i] < pivot) { 
            pos++;
            swap(array, i, pos);
        }
    }
    pos++;
    swap(array, pos, high);
    return pos;
}

void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}

int countSingular(int size, int* perimeters) {
    int count = 0;
    quickSort(perimeters, 0, size - 1);

    for (int i = 0; i < size; i++) {
        if (i < size - 1 && perimeters[i] == perimeters[i + 1]) { continue; }
        if (i > 0 && perimeters[i] == perimeters[i - 1]) { continue; }
        count++;
    }
    return count;
}

int main(int argc, char **argv) {
    int length = 1500000; // Set default set size to 5 as required in the original question

    if (argc > 1) { // Take input from command line if a upper limit is given
        length = atoi(argv[1]);
    }
    
    int* perimeters = malloc(sizeof(int));
    if (perimeters == NULL) { 
        printf("Memory allocation failed.\n");
        exit(1);
    }
    int size = 0;

    perimeters = findSides(&size, perimeters, length);
    printf("%d\n", countSingular(size, perimeters));
}