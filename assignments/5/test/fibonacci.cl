class Main inherits IO {
	main():IO {{
		out_string("Enter the term number: ");
		let n:Int<-in_int() in
			out_string("Output: ").out_int(fibo(n)).out_string("\n");
	}};
	fibo(n:Int):Int {
		if(n<=0) then
			0
		else
			if(n=1) then
				1
			else
				fibo(n-1)+fibo(n-2)
			fi
		fi
			
	};
};