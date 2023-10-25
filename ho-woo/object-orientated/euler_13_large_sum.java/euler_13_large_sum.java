import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

/* LongInteger represents a long integer using an integer array, where each element is a single digit */
class LongInteger {
    ArrayList<Integer> number;

    /* Constructors */
    // Default constructor: initialize the number to 0
    LongInteger() {
        this.number = new ArrayList<Integer>();
    }
    // Initialize the number to the given integer array
    LongInteger(ArrayList<Integer> number) {
        this();
        this.number = number;
    }
    // Initialize the number to the given string converted to an integer array
    LongInteger(String line) {
        this();
        for (char c : line.toCharArray()) {
            this.number.add(Character.getNumericValue(c));
        }
    }
    // Return array size
    public int size() {
        return this.number.size();
    }
    // Return an element in the array by index
    public int get(int index) {
        if (index >= this.number.size() || index < 0) {
            return 0;
        }
        return this.number.get(index);
    }
    // Insert a new element into the array by index
    public void add(int index, int digit) {
        this.number.add(index, digit);
    }
    // Return a string to display the array
    public String toString() {
        if (this.size() == 0) {     // Return 0 if the array is empty
            return "0";
        }
        String output = "";
        for (int i : this.number) {
            output += i;
        }
        return output;
    }
    // Return the sum of the given LongInteger and this LongInteger
    public LongInteger plus(LongInteger other) {
        ArrayList<Integer> sum = new ArrayList<Integer>();
        int length = Math.max(this.size(), other.size());
        int carry = 0;
        // Iterate through the arrays
        for (int i = 0; i < length; i++) {
            // Calculate each digit starting from the last digit
            int sumDigit = this.get(this.size() - i - 1) + other.get(other.size() - i - 1) + carry;
            // If the sum of the two digits >= 10, minus the sum by 10 and store the carry
            if (sumDigit >= 10) {
                carry = sumDigit / 10;
                sumDigit -= 10;
            }
            else {
                carry = 0;  // Else set carry to 0
            }
            
            sum.add(i, sumDigit);   // Append the digit to the sum array
        }

        /* Since the sum was calculated in a reverse order (from last digit to first digit), 
           the sum array needs to be reversed after the calculation */
        Collections.reverse(sum);

        // Insert the carry
        if (carry > 0) {
            sum.add(0, carry);
        }

        return new LongInteger(sum);
    }

    // Return the first n digits of the LongInteger where n is a parameter
    public LongInteger trim(int digits) {
        if (this.size() <= digits) 
        {
            return this;
        }
        LongInteger trimmed = new LongInteger();
        for (int i = 0; i < digits; i++) {
            trimmed.add(i, this.get(i));
        }
        return trimmed;
    }
}

public class euler_13_large_sum {
    public static void main(String[] args) {
        String fileName = "numbers.txt";    // Default fileName is numbers.txt for testing
        if (args.length > 0)
        {
            fileName = args[0];     // Get file name from command line
        }

        // Initialize an array of LongIntegers to contain the large numbers
        ArrayList<LongInteger> numbers = new ArrayList<LongInteger>();
        /* Read file */
        try {
            File file = new File(fileName);
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();       // Read line from file
                numbers.add(new LongInteger(line));     // Store the line as LongInteger
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("Failed to open file.");
            System.exit(-1);
        }

        // Find the sum of all LongIntegers in the array
        LongInteger sum = new LongInteger();
        for (LongInteger number : numbers) {
            sum = sum.plus(number);
        }
        System.out.println(sum.trim(10));   // Print result
    }
}