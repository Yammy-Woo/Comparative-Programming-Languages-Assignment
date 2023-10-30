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
bool coprime(long int m, long int n) {
    if (m == 1 || n == 1) { return true; }  // Return true if numbers have only 1 as their common factor.
    if (m == n) { return false; }   // Return False if m == n != 1, meaning that they have m as their common factor.

    if (m > n) { m = m % n; }
    else { n = n % m; }
    if (m == 0 || n == 0) { return false; }     // Return False if either m or n is divisible by the other.
    return coprime(m, n);
}

/* Check whether the sides form an almost equilateral triangle,
    i.e. one side (differSide) differs from the other two equal sides (equalSides) by no more than 1.
*/
bool isAlmostEquilateral(long int equalSides, long int differSide) {
    if (labs(equalSides * 2 - differSide) == 1) { return true; }
    return false;
}

long int sumPerimeters(long int maxPerimeter) {
    long int sum = 0;
    /* Find all integer sided right-angled triangles (Pythagorean triples) within the range by Euclid's formula.
        The sum of the triple, which is the perimeter, is
        (m^2 - n^2) + 2mn + (m^2 + n^2).
        The perimeter of two right-angled triangles combined is either
        (m^2 - n^2) * 2 + (m^2 + n^2) = 3(m^2) - n^2
        or 2mn * 2 + (m^2 + n^2) = m^2 + 4mn + n^2
        Given the smallest n = 1, the smallest perimeter will be m^2 + 4m + 1.
        Therefore, if m^2 + 4m + 1 > maxPerimeter, the resulting perimeter must exceed maxPerimeter. 
    */
    for (long int m = 2; m * m + 4 * m + 1 <= maxPerimeter; m++) {
        for (long int n = 1; n < m; n++) {
            if ((m + n) % 2 == 0) { continue; } // Skip n when m and n are both even or odd
            if (!coprime(m, n)) { continue; }   // Skip n when m and n are not coprime

            long int a = m * m - n * n;
            long int b = 2 * m * n;
            long int c = m * m + n * n;
            
            long int perimeter;

            /* Check whether the right-angled triangle can form an almost equilateral triangle */
            /* There are two ways to combine two right-angled triangles into an isosceles triangle. */
            if (isAlmostEquilateral(a, c)) {    // Join by side b
                perimeter = a * 2 + c * 2;
                if (perimeter > maxPerimeter) { break; }
                sum += perimeter;
            }

            if (isAlmostEquilateral(b, c)) {   // Join by side a
                perimeter = b * 2 + c * 2;
                if (perimeter > maxPerimeter) { break; }
                sum += perimeter;
            }
        }
    }
    return sum;     // Return the sum
}

int main(int argc, char **argv) {
    long int maxPerimeter = 1000000000;  // Set maximum perimeter to 1 billion by default as required in the original question

    if (argc > 1) { // Take input from command line if a upper limit is given
        maxPerimeter = atoi(argv[1]);
    }

    printf("%d\n", sumPerimeters(maxPerimeter));
}