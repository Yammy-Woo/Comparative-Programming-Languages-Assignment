static class Combination {
    public static BigInteger factorial(int n) {
        if (n <= 1) {
            return 1;
        }
        return n * factorial(n - 1);
    }
}

class Row {
    int totalUnits;
    final static int red = 2;
    final static int green = 3;
    final static int blue = 4;

    Row(int totalUnits) {
        this.totalUnits = totalUnits;
    }


}

public class problem117 
{
    public static void main(String[] args) {
        int totalUnits = 50;
        if (args.length > 0)
        {
            totalUnits = Integer.parseInt(args[0]);
        }
        Row row = new Row(totalUnits);
        BigInteger count;
        
    }
}