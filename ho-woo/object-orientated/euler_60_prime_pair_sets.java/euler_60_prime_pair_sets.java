import java.util.ArrayList;

class Prime {
    final static int firstPrime = 2;
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    private static ArrayList<Integer> sizedPrimes;
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

    public static boolean checkSet(ArrayList<Integer> set) {
        if (set.size() < 2) { return false; }
        for (int prime1 : set) {
            for (int prime2 :set) {
                if (prime1 >= prime2) { continue; }
                if (!checkPrimeConcat(prime1, prime2)) {
                    return false;
                }
            }
        }
        return true;
    }

    public static ArrayList<Integer> primePairSet(int noPrime, ArrayList<Integer> set, int lastPrime) {
        if (noPrime < 1) { return set; }

        for (int prime : sizedPrimes) {
            if (prime <= lastPrime) { continue; }
            if (prime == 2 || prime == 5) { continue; }
            set.add(prime);
            lastPrime = prime;
            ArrayList<Integer> newSet = new ArrayList<Integer>(primePairSet(noPrime - 1, set, lastPrime));
            if (checkSet(newSet)) { 
                return newSet; 
            }
            //System.out.println(newSet);
            if (set.isEmpty()) { continue; }
            set.remove(set.size() - 1);
            
        }
        //if (!set.isEmpty()) { set.remove(set.size() - 1); }
        
        return set;
    }

    public static ArrayList<Integer> primePairSet(int noPrime) {
        return primePairSet(noPrime, new ArrayList<Integer>(), 0);
    }

    // public static ArrayList<Integer> primePairSet(int noPrime) {
    //     ArrayList<Integer> set = new ArrayList<Integer>();
    //     for (int prime1 : primes) {
    //         set.add(prime1);

    //         for (int prime2 : primes) {
    //             if (prime1 >= prime2) { continue; }
    //             set.add(prime2);

    //             for (int prime3 : primes) {
    //                 if (prime2 >= prime3) { continue; }
    //                 set.add(prime3);

    //                 for (int prime4 : primes) {
    //                     if (prime3 >= prime4) { continue; }
    //                     set.add(prime4);

    //                     for (int prime5 : primes) {
    //                         if (prime4 >= prime5) { continue; }
    //                         set.add(prime5);
    //                         System.out.println(set);

    //                         if (checkSet(set)) { return set; }
    //                         set.remove(4);
    //                     }
    //                     set.remove(3);
    //                 }
    //                 set.remove(2);
    //             }
    //             set.remove(1);
    //         }
    //         set.remove(0);
    //     }
    //     return null;
    // }

    // public static ArrayList<Integer> primePairSet(ArrayList<Integer> set, ArrayList<Integer> primeList, int noPrime) {
    //     if (noPrime < 1) { return set; }

    //     for (int prime1 : primeList) {
    //         if (set.isEmpty()) {
    //             set.add(prime1);
    //             return primePairSet(set, primeList, noPrime - 1);
    //         }
    //         boolean flag = true;
    //         for (int prime2 : set) {
    //             if (noPrime == 1 && prime2 >= 109) { System.out.println(prime1 + " " + prime2); }
                
    //             if (prime1 <= prime2 || !checkPrimeConcat(prime1, prime2)) {
    //                 flag = false; 
    //                 break; 
    //             }
    //         }
    //         if (flag) {
    //             set.add(prime1);
    //             System.out.println("Recur " + set);

    //             return primePairSet(set, primeList, noPrime - 1);
    //         }
    //     }
    //     System.out.println("Fail " + set);
    //     primeList.remove(set.get(set.size() - 1));
    //     if (primeList.isEmpty()) {
    //        for (int i = 0; i < 100; i++) {
    //             addNextPrime();
    //         }
    //     }
    //     set.remove(set.size() - 1);
        
    //     return primePairSet(set, primeList, noPrime + 1);
    // }

    public static int sumOfPrimePairSet(int noPrime) {
        int sum = 0;
        while (lastPrime < 10000) {
            addNextPrime();
        }
        sizedPrimes = new ArrayList<Integer>(primes);

        //ArrayList<Integer> set = primePairSet(new ArrayList<Integer>(), new ArrayList<>(primes), noPrime);
        ArrayList<Integer> set = primePairSet(noPrime);
        if (set.size() < noPrime) {
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

        //System.out.println(Prime.isPrime(13409));
        System.out.println(Prime.sumOfPrimePairSet(noPrime));
    }
}
