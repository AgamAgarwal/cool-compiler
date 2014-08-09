class Main inherits IO {
main():IO {
	let x:Int, f:Bool<-False IN {	--note that "False" begins with an uppercase letter, also that "IN" has all uppercase letters. In Cool, "Except for the constants true and false, keywords are case insensitive. To conform to the rules for other objects, the first letter of true and false must be lowercase; the trailing letters may be upper or lower case. "
		out_string("Input the number: ");
		x<-in_int();
		f<-x=(x/3)*3;	--check if divisible by 3
		if not f then f<-x=(x/5)*5 else 0 fi;	--if not, check if divisible by 5
		if f then out_string("Multiple of 3 or 5.\n") else out_string("Not multiple of 3 or 5.\n") fi;	--output accordingly
	}};};