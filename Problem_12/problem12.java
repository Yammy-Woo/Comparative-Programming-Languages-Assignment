public class problem12 {
    static int divisors = 500;

    private static int countDivisors(int n)
    {
        int count = 0;
        int i;
        for (i = 1; i * i < n; i++)
        {
            if (n % i == 0) 
            {
                count += 2;
            }
        }

        if (i * i == n) { count++;}

        return count;
    }

    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            divisors = Integer.parseInt(args[0]);
        }
    
        int i = 1;
        int n = 1;
        while(countDivisors(n) <= divisors) { 
            i++;
            n += i;
        }

        System.out.println("The value of the first triangle number to have over " + divisors + " divisors: " + n);
    }
}
