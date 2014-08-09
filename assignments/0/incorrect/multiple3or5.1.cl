class Main inherits IO {
main():IO {
	let X:Int, f:Bool<-false in {	--note that 'X' is an uppercase letter, which is not allowed. In Cool, "object identifiers begin with a lower case letter"
		out_string("Input the number: ");
		X<-in_int();
		f<-X=(X/3)*3;	--check if divisible by 3
		if not f then f<-X=(X/5)*5 else 0 fi;	--if not, check if divisible by 5
		if f then out_string("Multiple of 3 or 5.\n") else out_string("Not multiple of 3 or 5.\n") fi;	--output accordingly
	}};};