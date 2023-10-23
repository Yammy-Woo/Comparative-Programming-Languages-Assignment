class Digit {
    int value;
    Digit prev = null;
    Digit next = null;

    Digit(int value) {
        this.value = value;
    }

    public String toString() {
        return Integer.toString(this.value);
    }
}

class DigitList {
    Digit head;
    Digit tail;

    DigitList(int head) {
        this.head = new Digit(head);
        this.tail = this.head;
    }

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

class PowerDigitSum {
    final int base = 2;
    int exponent;
    DigitList digitList;
    int sum;

    PowerDigitSum(int exponent) {
        this.exponent = exponent;
        this.digitList = new DigitList(1);
        
        digitSum();
    }

    void digitSum() {
        powerToDigits();

        Digit current = this.digitList.head;
        do
        {
            this.sum += current.value;
            current = current.next;
        } while (current != null);
    }

    void powerToDigits() {
        int carry;
        Digit current, temp;

        for (int i = 0; i < this.exponent; i++)
        {
            current = this.digitList.head;
            carry = 0;

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
        int exponent = 1000;
        if (args.length > 0)
        {
            exponent = Integer.parseInt(args[0]);
        }

        PowerDigitSum powerDigitSum = new PowerDigitSum(exponent);
        System.out.println(powerDigitSum.sum);
    }
}
