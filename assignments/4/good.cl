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
			(new C)=(new A)
		else
			abc<=1
		fi
	};
};

class D inherits E {
	main(a:Int):SELF_TYPE {
		new SELF_TYPE
	};
};

class E inherits F {
xyz():Object{{
	if true then
		4+5+(new String).length()
	else
		while (new A)=(new SELF_TYPE) loop
			let x:Int, x:String in
				(new IO).out_string(x)
		pool
	fi;
}};
};

class F {};

Class Main {
	main():C {
	  (new C).init(1,true)
	};
};
