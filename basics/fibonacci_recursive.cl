class Main {
io : IO <- new IO;
n: Int;
main() : IO {{
	io.out_string("Enter the term number: ");
	n <- io.in_int();
	io.out_int(fibonacci((0-1), 1, 0, 1, n));
	io.out_string("\n");
	}};
fibonacci(a: Int, b: Int, c: Int, i: Int, n: Int) : Int {
	if i<n then
		{
		a <- b;
		b <- c;
		c <- (a+b);
		fibonacci(a, b, c, i+1, n);
		}
	else c fi
	};
};