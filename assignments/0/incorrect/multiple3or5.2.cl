class Main inherits IO {
main():IO {
	let x:Int, f:Bool<-false in {
		out_string("Input the number: ");
		x<-in_int();
		f<-x=(x/3)*3;
		if not f then f<-x=(x/5)*5 else 0 fi;
		if f then out_string("Multiple of 3 or 5.\n") else out_string("Not multiple of 3 or 5.
		") fi;	--note that there is an non-escaped newline character, but in Cool, "a non-escaped newline character may not appear in a string". The program may be fixed by escaping the newline character using a '\'.
	}};};