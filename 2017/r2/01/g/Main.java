import java.io.*; 
import java.util.*;
import java.math.*;

public class Main {
    public static BigInteger getFactorial(int num) {
        BigInteger fact = BigInteger.valueOf(1);
        for (int i = 1; i <= num; i++)
            fact = fact.multiply(BigInteger.valueOf(i));
        return fact;
    }
    public static void main(String[] args) throws Exception {  
        Scanner cin = new Scanner(System.in); 
        int T = cin.nextInt();
        for(int j = 0;j < T;++j) {
            int n = cin.nextInt();
            BigInteger fac = getFactorial(n);
            BigInteger ans = BigInteger.valueOf(0);
            for(int i = 1;i <= n;++i)
                ans = ans.add(fac.divide(BigInteger.valueOf(i)));
            System.out.println(ans.toString()+".0");
        }
    }  
}
