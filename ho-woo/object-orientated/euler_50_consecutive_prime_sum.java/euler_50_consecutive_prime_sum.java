/* PrimeSum class represents a list of consecutive primes as a linked list */
class PrimeSum
{
    private Prime head;     // Head of the linked list
    private Prime tail;     // Tail of the linked list
    int sum;                // Sum of all primes in the list
    int length;             // Number of primes in the list
    
    /* Constructors */
    PrimeSum ()
    {
        this.head = null;
        this.tail = null;
        this.sum = 0;
        this.length = 0;
    }

    PrimeSum (PrimeSum primeSum)
    {
        this.head = primeSum.head;
        this.tail = primeSum.tail;
        this.sum = primeSum.sum;
        this.length = primeSum.length;
    }

    /* Add new prime node to the tail */
    public void addTail(Prime tail) 
    {
        if (this.head == null)  // If the linked list is empty, set both head and tail to the new element
        {
            this.head = tail;
            this.tail = this.head;
        }
        else
        {
            tail.prev = this.tail;
            this.tail.next = tail;
            this.tail = tail;
        }

        this.sum += this.tail.value;    // Add the new prime to the sum
        this.length++;                  // Increment the length of the list
    }
    
    /* Remove the tail of the list and return whether the operation succeeded */
    public boolean removeTail()
    {
        if (this.tail == this.head)     // If there is only one element in the list
        {
            return false;
        }
        this.sum -= this.tail.value;    // Subtract removed prime from the sum
        this.tail = this.tail.prev;     // Set tail to the previous node
        this.length--;                  // Reduce length by 1

        return true;
    }
    
    /* Shift the list of primes to right, i.e. set head and tail to their next node respectively,
       and return whether the operation succeeded
     */
    public boolean shiftRight()
    {
        if (this.tail.next == null)     // If the list has reached the end
        {
            return false;
        }
        
        /* Shift head to the next node */
        this.sum -= this.head.value;    
        this.head = this.head.next;

        /* Shift tail to the next node */
        this.tail = this.tail.next;
        this.sum += this.tail.value;

        return true;
    }

    public String toString()
    {
        String s = "";
        Prime current = this.head;

        while (current != this.tail)
        {
            s += current.value + " + ";
            current = current.next;
        }

        s += current.value + " = " + this.sum;

        return s;
    }
}

/* Prime class represents a prime number as a node in a linked list */
class Prime
{
    int value;
    Prime prev;
    Prime next;

    Prime(int value)
    {
        this.value = value;     // The prime number
        this.prev = null;       // The previous prime number
        this.next = null;       // The next prime number
    }
}

public class euler_50_consecutive_prime_sum 
{
    static final int firstPrime = 2;
    static int limit = 1000000;     // Limit value of the sum set to 1000000 as default as required in the original problem

    /* Check whether n is a prime number */
    public static boolean isPrime(int n)
    {
        for (int i = firstPrime; i <= n / 2; i++)
        {
            if (n % i == 0) 
            {
                return false;   // False if the given number is not a prime number
            }
        }
        return true;    // True if the given number is a prime number
    }

    /* Find the longest sum of consecutive primes that adds to a prime below limit */
    public static PrimeSum longestConsecutivePrimeSum()
    {
        /* Initialize a PrimeSum object */
        PrimeSum primeSum = new PrimeSum();

        /* Append primes into PrimeSum until the sum of the primes reaches limit */
        int i = firstPrime;
        while (primeSum.sum < limit)
        {
            if (isPrime(i)) 
            {
                primeSum.addTail(new Prime(i));
            }
            i++;
        }

        PrimeSum resultPrimeSum;
        do
        {
            resultPrimeSum = new PrimeSum(primeSum);    // Make a copy of primeSum

            /* Shift the copied PrimeSum to right until the sum of the primes is a prime, 
               the sum exceed the limit or reaching the end of the list */
            while (!isPrime(resultPrimeSum.sum) && resultPrimeSum.shiftRight() && resultPrimeSum.sum < limit);
            // If the result sum is a prime and does not exceed limit, leave the loop and return the result PrimeSum
            if (isPrime(resultPrimeSum.sum) && resultPrimeSum.sum < limit) { break; }
            
        } while (primeSum.removeTail());    // Remove tail from primeSum, i.e. reduce the length of the consecutive primes list
    
        return resultPrimeSum;
    }

    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            limit = Integer.parseInt(args[1]);  // Read input limit from command line
            if (limit <= 2) 
            {
                System.out.println("The input limit cannot be 2 or lower, since 2 is the first prime number." + limit);
                return ;
            }
        }
        
        PrimeSum primeSum = longestConsecutivePrimeSum();   // Call longestConsecutivePrimeSum() to find the matching list of consecutive primes

        System.out.println(primeSum.sum);   // Output the sum
    }
}