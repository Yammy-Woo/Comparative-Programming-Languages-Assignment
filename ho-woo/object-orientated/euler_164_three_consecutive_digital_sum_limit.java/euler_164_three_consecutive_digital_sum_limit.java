import java.util.HashMap;

class ThreeConsecutiveDigitalSumLimit {
    static HashMap<Integer, Long> cache;
    public static int nextMaxDigit(int lastDigit, int currentDigit) {
        return 9 - lastDigit - currentDigit;
    }

    public static long countCombination(int lastDigit, int currentDigit, int noDigit) {
        if (noDigit == 0) { return currentDigit == 0 ? 0 : 1; }     // Leading zero not allowed

        int key = lastDigit + currentDigit * 10 + noDigit * 100;
        if (cache.containsKey(key)) {
            return cache.get(key);
        }

        int maxDigit = nextMaxDigit(lastDigit, currentDigit);
        long count = 0;

        for (int nextDigit = 0; nextDigit <= maxDigit; nextDigit++) {
            count += countCombination(currentDigit, nextDigit, noDigit - 1);
        }
        
        cache.put(key, count);
        return count;
    }

    public static long countCombination(int noDigit) {
        cache = new HashMap<Integer, Long>();
        return countCombination(0, 0, noDigit);
    }
}

public class euler_164_three_consecutive_digital_sum_limit {
    static int noDigit = 20;    // Set number of digits to 20 by default as required in the original question
    public static void main(String[] args)
    {
        if (args.length > 0)
        {
           noDigit = Integer.parseInt(args[0]);
        }

        System.out.println(ThreeConsecutiveDigitalSumLimit.countCombination(noDigit));
    }
}
