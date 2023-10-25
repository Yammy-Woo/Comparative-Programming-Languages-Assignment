/* Digit represents a digit */
class Digit {
    int value;              // Value of this Digit node
    Digit prev = null;      // Previous node in the linked list
    Digit next = null;      // Next node in the linked list

    Digit(int value) {
        this.value = value;
    }

    public String toString() {
        return Integer.toString(this.value);
    }
}

/* DigitList is a linked list of Digits representing the digits in the power of 2.
   The numbers are stored in a reverse order, where the last digit of the number is at the head.
*/
class DigitList {
    Digit head;     // First node of the linked list
    Digit tail;     // Last node of the linked list 

    DigitList(int head) {
        this.head = new Digit(head);
        this.tail = this.head;
    }

    // Display the Digits in the linked list
    public String toString() {
        String output = "";

        Digit current = this.tail;
        do
        {
            output += current.value;
            current = current.prev;
        } while (current != null);
        return output;
    }
}

/* PowerDigitSum represents the sum of the digits of 2 power a given exponent */
class PowerDigitSum {
    final int base = 2;
    int exponent;
    DigitList digitList;
    int sum;

    // Constructor initializes the variables and call digitSum() to perform calculation
    PowerDigitSum(int exponent) {
        this.exponent = exponent;
        this.digitList = new DigitList(1);
        
        digitSum();     // Call digitSum() to calculate the power digit sum
    }

    // Calculate the power digit sum with the given exponent
    void digitSum() {
        powerToDigits();    // Call powerToDigits() to calculate the power and convert it to a DigitList

        // Calculate the sum of all Digits in the DigitList
        Digit current = this.digitList.head;
        do
        {
            this.sum += current.value;
            current = current.next;
        } while (current != null);
    }

    // Calculate the nth power of 2 where n is the given exponent and return a DigitList representing the power
    void powerToDigits() {
        int carry;
        Digit current, temp;

        /* Multiply the DigitList by 2 in each loop*/
        for (int i = 0; i < this.exponent; i++)
        {
            current = this.digitList.head;
            carry = 0;

            // Multiply the DigitList by 2
            while (current != null)
            {
                current.value = current.value * this.base + carry;
    
                if (current.value >= 10) 
                {
                    carry = current.value / 10;
                    current.value %= 10;
                }
                else
                {
                    carry = 0;
                }
                current = current.next;
            }

            // Insert carry at the tail
            if (carry > 0)
            {
                temp = new Digit(carry);
                temp.prev = this.digitList.tail;
                this.digitList.tail.next = temp;
                this.digitList.tail = temp;
            }
        }
    }
}

public class euler_16_power_digit_sum {
    public static void main(String[] args)
    {
        int exponent = 1000;    // Default exponent is 1000
        if (args.length > 0)
        {
            exponent = Integer.parseInt(args[0]);   // Get exponent from command line
        }

        PowerDigitSum powerDigitSum = new PowerDigitSum(exponent);  // Initialize a PowerDigitSum object with given exponent
        System.out.println(powerDigitSum.sum);  // Print result
    }
}
