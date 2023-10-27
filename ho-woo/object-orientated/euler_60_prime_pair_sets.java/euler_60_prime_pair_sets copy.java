import java.util.ArrayList;
import java.util.Iterator;

class Prime {
    final static int firstPrime = 2;
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    private static int lastPrime = 0;           // Last element in primes, which is also the largest prime in primes

    public static boolean isPrime(int n) {
        while (lastPrime < n) {
            addNextPrime();
            //System.out.println(lastPrime);
        }

        if (primes.contains(n)) { return true; }

        return isPrimeByList(n);
    }

    private static boolean isPrimeByList(int n) {
        for (int prime : primes)
        {   
            if (n % prime == 0) 
            {
                return false;   // False if the given number is not a prime number
            }
            if (prime >= n / firstPrime) {
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

        if (!Prime.isPrime(concat12) || !Prime.isPrime(concat21)) {
            return false;
        }
        return true;
    }

    public static ArrayList<Integer> primePairSet(ArrayList<Integer> set, ArrayList<Integer> primeList, int noPrime) {
        if (noPrime < 1) { return set; }

        for (int prime1 : primeList) {
            if (set.isEmpty()) {
                set.add(prime1);
                return primePairSet(set, primeList, noPrime - 1);
            }
            boolean flag = true;
            for (int prime2 : set) {
                if (noPrime == 1 && prime2 >= 109) { System.out.println(prime1 + " " + prime2); }
                
                if (prime1 <= prime2 || !checkPrimeConcat(prime1, prime2)) {
                    flag = false; 
                    break; 
                }
            }
            if (flag) {
                set.add(prime1);
                System.out.println("Recur " + set);

                return primePairSet(set, primeList, noPrime - 1);
            }
        }
        System.out.println("Fail " + set);
        primeList.remove(set.get(set.size() - 1));
        if (primeList.isEmpty()) {
           for (int i = 0; i < 100; i++) {
                addNextPrime();
            }
        }
        set.remove(set.size() - 1);
        
        return primePairSet(set, primeList, noPrime + 1);
    }

    public static int sumOfPrimePairSet(int noPrime) {
        int sum = 0;
        for (int i = 0; i < 5000; i++) {
            addNextPrime();
        }
        ArrayList<Integer> set = primePairSet(new ArrayList<Integer>(), new ArrayList<>(primes), noPrime);
        for (int prime : set) {
            sum += prime;
        }
        return sum;
    }
}

class PrimePairSet {
    static ArrayList<Integer> set = new ArrayList<Integer>();
    static int primeIndex = 5;           // Index of the [last prime number in set] in Prime.primes. Initialized to 1 (primes[1] = 3).
    static int lastPrime = 7;
    /* 3 is the first prime which can result in prime number when concatenating with other primes in any order. 
       2, the first prime, always result in non-prime numbers when concatenating with other primes with 2 at the end, e.g. 32. */ 

    public static int sumOfPrimePairSet(int noPrime) {
        for (int i = 0; i < noPrime; i++) {
            addNextPrime();
            System.out.println(set);
        }

        int sum = 0;
        for (int prime : set) {
            sum += prime;
        }
        return sum;
    }

    public static void addNextPrime() {
        // int prime;
        // do {
        //    prime = Prime.get(primeIndex++);
        //    System.out.println(prime);
        // } while (!checkPrimeConcat(prime) && prime < 10000);
        
        // set.add(prime);
        int n = lastPrime;
        while (n < 10000 && (!Prime.isPrime(n) || !checkPrimeConcat(n))) {
           n += 2;
        }
        lastPrime = n;
        set.add(lastPrime);
    }

    public static boolean checkPrimeConcat(int n) {
        String strN = Integer.toString(n);

        for (int prime : set) {
            String strPrime = Integer.toString(prime);
            int nPrime = Integer.parseInt(strN + strPrime);
            int primeN = Integer.parseInt(strPrime + strN);

            if (!Prime.isPrime(nPrime) || !Prime.isPrime(primeN)) {
                return false;
            }
        }
        return true;
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

        //System.out.println(Prime.isPrime(13409));
        System.out.println(Prime.sumOfPrimePairSet(noPrime));
    }
}
