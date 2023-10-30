import java.lang.Math;

class AlmostEquilateralTriangle {
    /* An almost equilateral triangle is also an isosceles triangle,
       which can be separated into two equal right-angled triangles.
       In this approach,
       I first generate integer sided right-angled triangles using Euclid's Formula for Pythagorean Triples (See problem 75), 
       then check if each integer sided right-angled triangle is an almost equilateral triangle.
       Since Area = 1/2 * a * b for right-angled triangles,
       the combination of two right-angled triangles has Area = a * b.
       In the case of integer sided right-angled triangles,
       since both a and b are integers, the resulting area must be an integer.

       Note that there is no need to multiply the triple by k to find the multiples, 
       since the difference between the sides' length will be multiplied as well,
       and the resulting triple will not be "almost equilateral".
    */

    /* Check whether the given two numbers are coprime, i.e. they have their highest common factor as 1. */
    public static boolean coprime(long m, long n) {
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
    public static boolean isAlmostEquilateral(long equalSides, long differSide) {
        if (Math.abs(equalSides * 2 - differSide) == 1) { return true; }
        return false;
    }

    /* Find all almost equilateral triangles with perimeters not exceeding the given maximum perimeter. */
    public static long sumPerimeters(long maxPerimeter) {
        long sum = 0;
        /* Find all integer sided right-angled triangles (Pythagorean triples) within the range by Euclid's formula.
           The sum of the triple, which is the perimeter, is
           (m^2 - n^2) + 2mn + (m^2 + n^2) = 2(m^2) + 2mn.
           The perimeter of two right-angled triangles combined is either
           (m^2 - n^2) * 2 + (m^2 + n^2) = 3(m^2) - n^2
           or 2mn * 2 + (m^2 + n^2) = m^2 + 4mn + n^2
           Given the smallest n = 1, the smallest perimeter will be m^2 + 4m + 1.
           Therefore, if m^2 + 4m + 1 > maxPerimeter, the resulting perimeter must exceed maxPerimeter. 
        */
        for (long m = 2; m * m + 4 * m + 1 <= maxPerimeter; m++) {
            for (long n = 1; n < m; n++) {
                if ((m + n) % 2 == 0) { continue; } // Skip n when m and n are both even or odd
                if (!coprime(m, n)) { continue; }   // Skip n when m and n are not coprime

                /* The sides of integer sided right-angled triangle */
                long a = m * m - n * n;
                long b = 2 * m * n;
                long c = m * m + n * n;
                
                long perimeter;
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
}

public class euler_94_almost_equilateral_triangles {
    static long maxPerimeter = 1000000000;    // Maximum perimeter set to 1 billion by default
    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            maxPerimeter = Integer.parseInt(args[0]);
        }

        System.out.println(AlmostEquilateralTriangle.sumPerimeters(maxPerimeter));
    }
}
