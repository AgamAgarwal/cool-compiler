(*
 * This program checks if a given number is an armstrong number or not.
 * An armstrong number is one whose value is equal to the sum of the cubes of its digits.
 * eg. 153=1^3 + 5^3 + 3^3
 *)
class Main {
	io:IO<-new IO;	--object for input and output
	main():Int {{
		io.out_string("Enter a number: ");
		let n:Int<-io.in_int(), flag:Bool<-false in {	--getting the number, flag for marking armstrong number
			if 0<=n then {
				let y:Int<-n, d:Int<-0, s:Int<-0 in {	--y stores copy of n, d stores each digit, s stores sum of cubes of digits
					while not y=0 loop {
						d<-y-(y/10)*10;	--getting a digit
						s<-s+d*d*d;	--adding cube of the digit
						y<-y/10;	--removing last digit
					} pool;
					flag<-s=n;	--checking if sum of cubes equals the number or not
				};
			}
			else {0;} fi;
			--output
			io.out_int(n);
			io.out_string(" is");
			if flag then io.out_string("") else io.out_string(" not") fi;
			io.out_string(" an armstrong number.\n");
		};
		0;
	}};
};