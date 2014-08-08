class Main {
io : IO <- new IO;
n: Int;
main() : IO {{
	io.out_string("Enter the term number: ");
	n <- io.in_int();
	io.out_int(fibonacci(n));
	io.out_string("\n");
	}};
fibonacci(n : Int) : Int {{
	let a: Int <- (0-1), b: Int <- 1, i: Int <- 1, c: Int <- (a+b) in
		{
		while i<n loop
			{
			i <- i+1;
			a <- b;
			b <- c;
			c <- (a+b);
			}
		pool;
		c;
		};
	}};
};