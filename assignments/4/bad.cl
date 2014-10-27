class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		self;
           }
	};
};

class A inherits C {
	abc(x:String, abc:Int):Bool {
		if 5<x.length() then
			(new C)<(new SELF_TYPE)
		else
			abc<=new A
		fi
	};
};


class D inherits E {
	main(a:Int):SELF_TYPE {
		new A
	};
};

class E inherits F {
xyz():Object{{
	if true then
		4+5+(new String)
	else
		while (new A)=(new IO) loop
			let x:Int, x:String in
				(new IO).out_string(x, x)
		pool
	fi;
}};
};

class F inherits D {};

Class Main {
	main():C {
	 {
	  (new C).init(1,1);
	  (new C).init(1,true,3);
	  (new C).iinit(1,true);
	  (new C);
	 }
	};
};
