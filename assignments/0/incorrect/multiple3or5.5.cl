class Main inherits IO {
main():IO {
	let x:Int, f:Bool<-false in {
		out_string("Input the number: ");
		x<-in_int();
		f<-x=(x/3)*3;	--check if divisible by 3
		if not_f then f<-x=(x/5)*5 else 0 fi;	--if not, check if divisible by 5. Note that "not" and "f" are separated by an underscore character, while in Cool, whitespace consists of only "blank (ascii 32), \n (newline, ascii 10), \f (form feed, ascii 12), \r (carriage return, ascii 13), \t (tab, ascii 9), \v (vertical tab, ascii 11)"
		if f then out_string("Multiple of 3 or 5.\n") else out_string("Not multiple of 3 or 5.\n") fi;	--output accordingly
	}};};