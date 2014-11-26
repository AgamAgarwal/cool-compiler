class Convertor {
	convert(n:Int):String {
		if(n=0) then
			"0"
		else
			let s:String<-new String in {
				while(0<n) loop
					let r:Int<-n-(n/2)*2 in {
						if(r=0) then
							s<-"0".concat(s)
						else
							s<-"1".concat(s)
						fi;
						n<-n/2;
					}
				pool;
				s;
			}
		fi
	};
};

class Main inherits IO {
	con:Convertor<-new Convertor;
	main():Object {{
		out_string("Enter number: ");
		let n:Int<-in_int() in
			out_int(n).out_string(" in binary is ".concat(con.convert(n)).concat("\n"));
	}};
};