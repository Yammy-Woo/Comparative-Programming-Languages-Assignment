class PrimeSum
{
    private Prime head;
    private Prime tail;
    int sum;
    int length;

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

    public void addTail(Prime tail) // If the linked list is empty
    {
        if (this.head == null)
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

        this.sum += this.tail.value;
        this.length++;
    }

    public boolean removeTail()
    {
        if (this.tail == this.head) 
        {
            return false;
        }
        this.sum -= this.tail.value;
        this.tail = this.tail.prev;
        this.length--;

        return true;
    }

    public boolean shiftRight()
    {
        if (this.tail.next == null)
        {
            return false;
        }
        
        this.sum -= this.head.value;
        this.head = this.head.next;

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

class Prime
{
    int value;
    Prime prev;
    Prime next;

    Prime(int value)
    {
        this.value = value;
        this.prev = null;
        this.next = null;
    }
}

public class euler_50_consecutive_prime_sum 
{
    static final int firstPrime = 2;
    static int limit = 1000000;

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

    public static PrimeSum longestConsecutivePrimeSum()
    {
        PrimeSum primeSum = new PrimeSum();

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
            resultPrimeSum = new PrimeSum(primeSum);

            while (!isPrime(resultPrimeSum.sum) && resultPrimeSum.shiftRight() && resultPrimeSum.sum < limit);
            if (isPrime(resultPrimeSum.sum) && resultPrimeSum.sum < limit) { break; }
            
        } while (primeSum.removeTail());
    
        return resultPrimeSum;
    }

    public static void main(String[] args)
    {
        if (args.length > 0)
        {
            limit = Integer.parseInt(args[1]);
            if (limit <= 2) 
            {
                System.out.println("The input limit cannot be 2 or lower, since 2 is the first prime number." + limit);
                return ;
            }
        }
        
        PrimeSum primeSum = longestConsecutivePrimeSum();

        System.out.println(primeSum.sum);
    }
}