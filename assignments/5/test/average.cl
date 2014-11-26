(*
 * This program takes several integers as input and prints their average to the nearest integer.
 * The input is stopped when the user enters a 0.
 * eg.
 * Input - 
 * 3
 * 4
 * 6
 * 0
 * Output -
 * 4
 *)
class Main {
	io:IO<-new IO;
	main():Int {
		let x:Int, c:Int<-0, s:Int<-0, flag:Bool<-true in {	--x stores the current number, c stores count of numbers, s stores the sum of the numbers, flag to check if 0 has been entered
			io.out_string("Enter the numbers(0 to end).\n");
			while flag loop {
				x<-io.in_int();
				if x=0 then
					flag<-false
				else {
					c<-c+1;	--increase count
					s<-s+x;	--add to sum
				} fi;
			} pool;
			if c=0 then
				io.out_string("Please enter atleast 1 number.\n")
			else {
				io.out_string("The average of the numbers is ");
				io.out_int(s/c);
				io.out_string(".\n");
			} fi;
			0;
		}
	};
};