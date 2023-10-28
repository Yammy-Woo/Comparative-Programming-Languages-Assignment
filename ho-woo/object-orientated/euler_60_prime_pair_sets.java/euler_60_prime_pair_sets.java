import java.util.ArrayList;
import java.lang.Math;

class Prime {
    final static int firstPrime = 2;
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    private static int lastPrime = 0;           // Last element in primes, which is also the largest prime in primes

    public static boolean isPrime(int n) {
        if (primes.contains(n)) { return true; }
        
        if (!isPrimeByList(n)) { return false; }
        if (lastPrime <= Math.sqrt(n)) {
            for (int i = lastPrime + 2; i <= Math.sqrt(n); i++) {
                if (n % i == 0) {
                    return false;
                }
            }
        }
        
        return true;    // True if the given number is a prime number
    }

    private static boolean isPrimeByList(int n) {
        for (int prime : primes) {   
            if (n % prime == 0) {
                return false;   // False if the given number is not a prime number
            }
            if (prime > Math.sqrt(n)) {
                return true;
            }
        }
        return true;    // True if the given number is a prime number
    }

    public static void addNextPrime() {
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

    public static boolean checkPrimeConcat(int n1, int n2) {
        String str1 = Integer.toString(n1);
        String str2 = Integer.toString(n2);
        int concat12 = Integer.parseInt(str1 + str2);
        int concat21 = Integer.parseInt(str2 + str1);
        
        if (!isPrime(concat12) || !isPrime(concat21)) {
            return false;
        }
        return true;
    }

    public static boolean checkSet(int prime, ArrayList<Integer> set) {
        if (set.isEmpty()) { return true; }
        for (int p : set) {
            if (!checkPrimeConcat(p, prime)) {
                return false;
            }
        }
        return true;
    }

    /* Return the set of primes for which any two primes concatenate to produce another prime.
       noPrime: Number of primes required to be found
       set: The set of primes found
       lastPrime: The last element in the set
     */
    public static ArrayList<Integer> primePairSet(int noPrime, ArrayList<Integer> set, int lastPrime) {
        if (noPrime < 1) { return set; }    // Return the set if the number of primes required to be found is 0

        for (int prime : primes) {
            if (prime <= lastPrime) { continue; }   // Skip the already checked primes
            /* Skip 2 and 5 since they always result in non primes when they are concatenated to other numbers 
               e.g. 12, 22, 15, 25 */
            if (prime == 2 || prime == 5) { continue; }

            /* Call checkSet() to check if the prime concatenating to any prime in the set always results in a prime */
            if (checkSet(prime, set)) {
                /* Initialise newSet and add the prime to the set, then recursively call primePairSet() to find next prime */
                ArrayList<Integer> newSet = new ArrayList<Integer>(set);
                newSet.add(prime);
                lastPrime = prime;
                newSet = primePairSet(noPrime - 1, newSet, lastPrime);
                /* Check if the new set's size matches the number of primes required to be found */
                if (newSet.size() - set.size() == noPrime) {
                    return newSet;  // Return the new set
                }
            }
        }
        return set; // Return the original set if no matching prime is found.
    }

    public static ArrayList<Integer> primePairSet(int noPrime) {
        return primePairSet(noPrime, new ArrayList<Integer>(), 0);
    }

    public static int sumOfPrimePairSet(int noPrime) {
        int sum = 0;
        while (lastPrime < 10000) {
            addNextPrime();
        }

        ArrayList<Integer> set = primePairSet(noPrime);
        if (set.size() < noPrime) {
            System.out.println(set);
            System.out.println("Set not found.");
            return 0;
        }
        for (int prime : set) {
            sum += prime;
        }
        return sum;
    }
}

public class euler_60_prime_pair_sets {
    static int noPrime = 5;    // Number of primes in the set
    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            noPrime = Integer.parseInt(args[0]);
            if (noPrime < 2) 
            {
                System.out.println("The set size cannot be smaller than 2.");
                return ;
            }
        }

        System.out.println(Prime.sumOfPrimePairSet(noPrime));
    }
}
