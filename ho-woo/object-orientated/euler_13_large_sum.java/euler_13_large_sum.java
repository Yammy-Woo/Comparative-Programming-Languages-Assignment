import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.ArrayList;
import java.util.Collections;

class LongInteger {
    ArrayList<Integer> number;

    LongInteger() {
        this.number = new ArrayList<Integer>();
        this.number.add(0);
    }

    LongInteger(ArrayList<Integer> number) {
        this.number = number;
    }

    LongInteger(String line) {
        this();
        for (char c : line.toCharArray()) {
            this.number.add(Character.getNumericValue(c));
        }
    }

    public int size() {
        return this.number.size();
    }

    public int get(int index) {
        if (index >= this.number.size() || index < 0) {
            return 0;
        }
        return this.number.get(index);
    }

    public void add(int index, int digit) {
        this.number.add(index, digit);
    }

    public String toString() {
        String output = "";
        for (int i : this.number) {
            output += i;
        }
        return output;
    }

    public LongInteger plus(LongInteger other) {
        ArrayList<Integer> sum = new ArrayList<Integer>();
        int length = Math.max(this.size(), other.size());
        int carry = 0;

        for (int i = 0; i < length; i++) {
            int sumDigit = this.get(this.size() - i - 1) + other.get(other.size() - i - 1) + carry;

            if (sumDigit >= 10) {
                carry = sumDigit / 10;
                sumDigit %= 10;
            }
            else {
                carry = 0;
            }
            
            sum.add(i, sumDigit);
        }

        Collections.reverse(sum);

        if (carry > 0) {
            sum.add(0, carry);
        }

        return new LongInteger(sum);
    }

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
        String fileName = "numbers.txt";    // numbers.txt for testing
        if (args.length > 0)
        {
            fileName = args[0];
        }

        ArrayList<LongInteger> numbers = new ArrayList<LongInteger>();
        try {
            File file = new File(fileName);
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                numbers.add(new LongInteger(line));
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("Failed to open file.");
            System.exit(-1);
        }

        LongInteger sum = new LongInteger();
        for (LongInteger number : numbers) {
            sum = sum.plus(number);
        }
        System.out.println(sum.trim(10));
    }
}