// Billy Kwong
// bqkwong
// Lex.java

import java.io.*;
import java.util.Scanner;

public class Lex{
	public static void main(String[] args) throws IOException{
		
		// Check if two arguments are passed
		if (args.length != 2){
			System.err.println("Usage: Lex input output");
			System.exit(1);
		}
		
		// Variables
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] array = null;
		int lineNumber = 0;
		  
		in = new Scanner(new File(args[0]));

		// Counts lines
		while (in.hasNextLine()){
			++lineNumber;
			in.nextLine();
		}
		in.close();
		in = null;

		List list = new List();
		array = new String[lineNumber];
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		// Add lines from file into array
		for (int i = 0; i < lineNumber; i++){
			line = in.nextLine()+" ";   
			array[i] = line;
		}			

		list.append(0);
		// Insertion sort 
		for (int i = 0; i < lineNumber-1; i++){
			list.moveFront();
			for (int j = -i ; j < 1; j++){
				if (array[list.get()].compareTo(array[i+1])>0){  
					list.insertBefore(i+1);
					j = 1;
				}
				else if (list.index() == list.length()-1){
					list.append(i+1);
					j = 1;
				}		 
				else 
					list.moveNext(); 		  
			}  
		}

		// Reset index to the front of the List
		list.moveFront();
		while (list.index() >= 0){
			out.println(array[list.get()]);
			list.moveNext();
		}
		// Close files
		in.close();
		out.close();
	}
}
			