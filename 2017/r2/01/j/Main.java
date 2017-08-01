import java.io.*; 
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) throws Exception {  
        Scanner cin = new Scanner(System.in);
        int T = cin.nextInt();
        int[] C = new int[2048];
        for(int j = 0;j < T;++j) {
            int n = cin.nextInt(), m = cin.nextInt();
            BigInteger bm = BigInteger.valueOf(m);
            for(int i = 0;i < n;++i)
                C[i] = cin.nextInt();
            BigInteger gtx = BigInteger.valueOf(0);
            for(int i = 0;i < n-1;++i)
                if(C[i+1]>C[i])
                {
                    gtx = gtx.add(bm.divide(BigInteger.valueOf(C[i])));
                    bm = bm.remainder(BigInteger.valueOf(C[i]));
                } else if(C[i+1]<C[i]) {
                    bm = bm.add(gtx.multiply(BigInteger.valueOf(C[i])));
                    gtx = BigInteger.valueOf(0);
                }
            bm = bm.add(gtx.multiply(BigInteger.valueOf(C[n-1])));
            System.out.println("Case #"+(j+1)+": "+bm.remainder(BigInteger.valueOf(1000000007)).toString());
        }
    }  
}
