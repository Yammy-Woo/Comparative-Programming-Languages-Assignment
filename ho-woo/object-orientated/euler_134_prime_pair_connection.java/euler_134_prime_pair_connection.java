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
        public static int lastDigits(int num, int n) {
            return num % ((int) Math.pow(10, (int) Math.log10(n) + 1));
        }

        
        public static int sumPairs() {
            /* According to the problem, n is a multiple of p2 and has its last digits formed by p1 
               Let n = m + p1
               n mod p2 = (m + p1) mod p2 = m mod p2 + p1 mod p2 = 0
               => m mod p2 = -p1 mod p2
            */
            int sum = 0;
            int p1 = 5;
            for (int prime : primes) {
                if (prime <= 5) { continue; }
                int p2 = prime;
                int n = p2;
                while (lastDigits(n , p1) != p1) {
                    n += p2;
                }
                System.out.println(n);
                sum += n;
                p1 = prime;
            }
            return sum;
        }
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
        Prime.generateNext();

        System.out.println(Prime.PrimePairConnection.sumPairs());
    }
}
