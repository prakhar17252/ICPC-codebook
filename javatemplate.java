import java.util.*; import java.lang.*;
import java.io.*;

public class Main{
	public static void solve(PrintWriter out) 
														throws Exception{}

 	public static void main(String[] args) 
														throws Exception{
 		PrintWriter out = new PrintWriter(System.out);
 		solve(out); out.close();
 	}

	static class in{
	 static BufferedReader b = new BufferedReader
				(new InputStreamReader(System.in));
	 static StringTokenizer t = 
											new StringTokenizer("");
		static String next() throws Exception{
			while (!t.hasMoreTokens())
				t = new StringTokenizer(b.readLine());
			return t.nextToken();
		} static int nextInt() throws Exception{
			return Integer.parseInt(next());
		}	// Same for Long and Double
	}
}
