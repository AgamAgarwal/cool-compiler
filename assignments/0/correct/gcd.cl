(*
 * This program takes two numbers as input and finds their greatest common divisor.
 *)
class Main {
	io:IO<-new IO;
	--function to calculate the gcd using Euclidean algorithm
	gcd(a:Int, b:Int):Int {{
		let t:Int in {	--t is temporary variable
			while not b=0 loop {
				t<-b;
				b<-a-(a/b)*b;	--get remainder
				a<-t;
			} pool;
		};
		a;	--return gcd
	}};
	main():Int {
		let x:Int, y:Int in {
			io.out_string("Enter the two numbers:\n");
			x<-io.in_int();
			y<-io.in_int();
			io.out_string("The GCD is ");
			io.out_int(gcd(x, y));
			io.out_string(".\n");
			0;
		}
	};
};