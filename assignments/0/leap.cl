(*
 * This program takes an year as input and prints if it is a leap year or not.
 *)
class Main {
	io:IO<-new IO;
	main():Int {{
		let y:Int, x:Int<-0, flag:Bool<-false in {
			io.out_string("Enter the year: ");
			y<-io.in_int();
			if y<0 then	--if negative year
				io.out_string("Invalid year.\n")
			else {
				if (y/100)*100=y then
					flag<-(y/400)*400=y
				else
					flag<-(y/4)*4=y
				fi;
				if flag then 0 else io.out_string("not ") fi;
				io.out_string("leap year\n");
			} fi;
		};
		0;
	}};
};