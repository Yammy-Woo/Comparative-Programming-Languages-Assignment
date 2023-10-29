import java.util.HashMap;
import java.util.HashSet;
import java.lang.Math;

class IntegerRightTriangle {
    static HashMap<Integer, Integer> perimeters;
    static HashSet<Integer> singulars;

    /* According to Euclid's Formula for Pythagorean Triples, 
       (a, b, c) are a Pythagorean triple iff 
       a = k * (m^2 - n^2)
       b = k * 2mn
       c = k * (m^2 + n^2)
       where k >= 1, m > n > 0 > 0, either m or n is even and m, n are coprime.
       Reference: https://en.wikipedia.org/wiki/Pythagorean_triple
    */
    /* Check whether the given two numbers are coprime, i.e. they have their highest common factor as 1. */
    public static boolean coprime(int m, int n) {
        if (m == 1 || n == 1) { return true; }  // Return true if numbers have only 1 as their common factor.
        if (m == n) { return false; }   // Return False if m == n != 1, meaning that they have m as their common factor.

        if (m > n) { m = m % n; }
        else { n = n % m; }
        if (m == 0 || n == 0) { return false; }     // Return False if either m or n is divisible by the other.
        return coprime(m, n);
    }

    public static void findSides(int maxPerimeter) {
        perimeters = new HashMap<Integer, Integer>();
        for (int a = 3; a * 3 < maxPerimeter; a++) {
            for (int b = a; a + b * 2 < maxPerimeter; b++) {
                double temp = pythagoras(a, b);
                if (temp % 1 == 0 && a + b + temp <= maxPerimeter) {
                    int c = (int) temp;
                    int perimeter = a + b + c;
                    System.out.println(perimeter);
                    if (!perimeters.containsKey(perimeter)) {
                        perimeters.put(perimeter, 1);
                    }
                    else {
                        perimeters.put(perimeter, perimeters.get(perimeter) + 1);
                    }
                }
            }
        }
    }

    public static int countSingular() {
        singulars = new HashSet<Integer>(perimeters.keySet());
        for (int perimeter:perimeters.keySet()) {
            if (perimeters.get(perimeter) > 1)
            {
                singulars.remove(perimeter);
            }
        }
        return singulars.size();
    }
}

public class euler_75_singular_integer_right_triangles {
    static int length = 1500000;    // Number of primes in the set
    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            length = Integer.parseInt(args[0]);
        }

        IntegerRightTriangle.findSides(length);
        System.out.println(IntegerRightTriangle.countSingular());
    }
}
