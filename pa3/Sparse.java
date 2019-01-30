// Billy Kwong
// bqkwong
// Pa3
// Sparse.java

import java.io.*;
import java.util.Scanner;

public class Sparse {

	public static void main(String[] args) throws IOException {
		//checks to see if 2 arguement lines
		if (args.length != 2) {
			System.out.println("Usage: Sparse infile outfile");
			System.exit(1);
		}

		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		int n = in.nextInt();
		int a = in.nextInt();
		int b = in.nextInt();
		int row, column;
		double value;
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		for (int i = 0; i < a; i++) {
			row = in.nextInt();
			column = in.nextInt();
			value = in.nextDouble();
			A.changeEntry(row, column, value);
		}

		for (int i = 0; i < b; i++) {
			row = in.nextInt();
			column = in.nextInt();
			value = in.nextDouble();
			B.changeEntry(row, column, value);
		}
		in.close();// close input file
	
		//printing
		out.println("A has " + a + " non-zero entries:\n" + A);
		out.println("B has " + b + " non-zero entries:\n" + B);
		out.println("(1.5)*A = \n" + A.scalarMult(1.5));
		out.println("A+B = \n" + A.add(B));
		out.println("A+A = \n" + A.add(A));
		out.println("B-A = \n" + B.sub(A));
		out.println("A-A = \n" + A.sub(A));
		out.println("Transpose(A) = \n" + A.transpose());
		out.println("A*B = \n" + A.mult(B));
		out.println("B*B = \n" + B.mult(B));
		out.close();
	}
}