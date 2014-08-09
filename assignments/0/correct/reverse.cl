(*
 * This program takes a string as an input and prints its reverse.
 * eg.
 * Input - Cool
 * Output - looC
 *)
class Main {
	io:IO<-new IO;
	main():Int {{
		io.out_string("Enter the string: ");
		let s:String<-io.in_string(), i:Int<-s.length() in --get the string and its length
			while 0<i loop {	--check if i is more than 0
				i<-i-1;	--decrease i
				io.out_string(s.substr(i, 1));	--print character
			} pool;
		io.out_string("\n");
		0;
	}};
};