public class problem3 {
    static final int firstPrime = 2;
    static long n = 600851475143L;

    private static long largestPrimeFactor()
    {
        long maxPrimeFactor = -1;
        long i = firstPrime;

        while (n >= firstPrime)
        {
            /* If n is divisible by i, divide n by i until the new n is not divisible by i. 
            Since n is not divisible by i, it is not divisible by any number which has i as a n.
            As a result, non-prime numbers are filtered out. */
            while (n % i == 0)
            {
                n /= i;
                maxPrimeFactor = i;
            }   

            i++; // Increment i
            
            /* After the above while loop, the n variable is not divisible by any value smaller than i. 
            For any number j smaller than i, i * j is not divisible by n. 
            Therefore, if i * i > n, it is guaranteed that n is not divisible by any number equal to or larger than i. 
            This proves that n is a prime number. */
            if (i * i > n) 
            {
                if (n > maxPrimeFactor)
                {
                    maxPrimeFactor = n;
                }
                break;
            }
        }
        return maxPrimeFactor;
    }

    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            n = Long.parseLong(args[0]);
        }
    
        long maxPrimeFactor = largestPrimeFactor();
        if (maxPrimeFactor < 0)
        {
            System.out.println("No prime factor found.");
        }
        else
        {
            System.out.println("Largest prime factor: " + maxPrimeFactor);
        }
    }
}
