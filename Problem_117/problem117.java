import java.math.BigInteger;

class Combination {
    public static BigInteger factorial(BigInteger n) {
        if (n.compareTo(BigInteger.valueOf(1)) <= 0) {
            return BigInteger.valueOf(1);
        }
        return n.multiply(factorial(n.subtract(BigInteger.valueOf(1))));
    }

    public static BigInteger combination(int n, int r) {
        BigInteger bigN = BigInteger.valueOf(n);
        BigInteger bigR = BigInteger.valueOf(r);
        return factorial(bigN).divide(factorial(bigR).multiply(factorial(bigN.subtract(bigR))));
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

    BigInteger countCombinations() {
        BigInteger count = BigInteger.valueOf(0);
        for (int i = 0; i * red <= this.totalUnits; i++) { // Start from 1 and increment the number of red/green/blue tiles
            for (int j = 0; i * red + j * green <= this.totalUnits; j++) {
                for (int k = 0; i * red + j * green + k * blue <= this.totalUnits; k++) {
                    int tiles = i + j + k + (this.totalUnits - red * i - green * j - blue * k);   // Find the number of tiles in the row
                    count = count.add(Combination.combination(tiles, i).multiply(Combination.combination(tiles - i, j)).multiply(Combination.combination(tiles - i - j, k)));
                }
            }      
        }
        return count;
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
        System.out.println(row.countCombinations());
    }
}