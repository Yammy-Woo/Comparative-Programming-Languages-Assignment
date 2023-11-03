import java.util.ArrayList;
import java.lang.Math;

/* Reused Prime class from problem 60 */
class Prime {
    final static int firstPrime = 2;
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    private static int lastPrime = 0;           // Last element in primes, which is also the largest prime in primes

    public static boolean isPrime(long n) {        
        if (!isPrimeByList(n)) { return false; }
        if (lastPrime <= Math.sqrt(n)) {
            for (long i = lastPrime + 2; i <= Math.sqrt(n); i++) {
                if (n % i == 0) { return false; }
            }
        }
        return true;    // True if the given number is a prime number
    }

    private static boolean isPrimeByList(long n) {
        for (int prime : primes) {   
            if (n % prime == 0) { return false; }   // False if the given number is not a prime number
            if (prime > Math.sqrt(n)) { return true; }
        }
        return true;    // True if the given number is a prime number
    }

    public static void generatePrimes(int limit) {
        while (lastPrime <= limit) {
            generateNext();
        }
    }

    public static void generateNext() {
        int n;
        if (lastPrime == firstPrime) { 
            n = lastPrime + 1;
        }
        else {
            n = lastPrime + 2;
            while (!isPrimeByList(n)) {
                n += 2;
            }
        }
        lastPrime = n;
        primes.add(lastPrime);
    }

    static class PrimePairConnection {
        public static long sumPairs() {
            /* According to the problem, n is a multiple of p2 and has its last digits formed by p1 
               Let n = m * 10^d + p1, where d = number of digits of p1,
               such that the last d digits of m are 0s.
               n mod p2 = (m * 10^d + p1) mod p2 = 0
               => m * 10^d mod p2 = -p1 mod p2
               => m = (-p1 * (10^d)^-1) mod p2
               (10^d)^-1, the multiplicative inverse of 10^d,
               can be found using Extended Euclid Algorithm.
            */
            long sum = 0, zeros, m;
            int p1 = 5, p2;
            for (int prime : primes) {
                if (prime <= 5) { continue; }
                p2 = prime;
                zeros = (int) Math.pow(10, (int) Math.log10(p1) + 1);
                /* (A % B + B) % B can handle negative A */
                m = (-p1 * ModularInverse.modularInverse(zeros, p2) % p2 + p2) % p2;
                sum += m * zeros + p1;
                p1 = prime;
            }
            return sum;
        }
    }
}

/* Find modular inverse using Extended Euclid Algorithm.
   References: 
    https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/modular-inverses
    https://brilliant.org/wiki/extended-euclidean-algorithm/#:~:text=It%20is%20a%20method%20of,complicated%20algorithms%20in%20number%20theory
    https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
*/ 
class ModularInverse {
    public static long x;
    public static long y;
    
    public static long egcd(long m, long n) {
        if (m == 0) {
            x = 0;
            y = 1;
            return n;
        }

        long gcd = egcd(n % m, m);

        long temp = x;
        x = y - n / m * x;
        y = temp;

        return gcd;
    }

    public static long modularInverse(long n1, long n2) {
        egcd(n1, n2);
        return x % n2;
    }
}

public class euler_134_prime_pair_connection {
    static int limit = 1000000;    // Number of primes in the set
    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            limit = Integer.parseInt(args[0]);
        }

        Prime.generatePrimes(limit);

        System.out.println(Prime.PrimePairConnection.sumPairs());
        //System.out.println(ModularInverse.modularInverse(1000, 13));
    }
}
