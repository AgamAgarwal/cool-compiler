
(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "myparser bad.cl" to see the error messages that your parser
 *  generates
 *)

(* inherits OBJECTID instead of TYPEID *)
class Rakshit inherits agam {
};

class Others inherits Errors {
	x:Int	-- no ;
	y:INt <- ; --no expr
	z:x;	-- Object as Type
	
	startsWithComma(,f1:F2,f3:F4) : Func{
	};
	
	endsWithComma(f1:F2,f3:F4,) :Func{
	};
	
	invalidFormals(x, y, z) :NoType{
	};
	
	invalidFormalSeparator(x:Int; y:A):Semicolon {
	};
	
	noReturnType(x:Int) {};
	
	
	otherErrors() :Errors {{
		z<-Z;
		
		(x+y)@.print();	--no type
		
		a@A.print(2,);	--comma at end
		
		b@B.C(x);
		
		check();
		
		A.print();
		
		if x<0 then negative() fi; --no else
		
		(* C style loop *)
		while (government.isCorrupted()) {
			development.decrease()
		};
		
		{2
		 2};
		
		(* no 'of' keyword *)
		case solved(by)
			sherlock:Holmes=>sleep()
			other:Detective=>hire<-new detective
		esac;
		
		(* arithmetic operators *)
		2+-*/1;
		-1;	-- '-' instead of '~'
		
		(* no greater than sign in COOL grammar *)
		if x>0 then not cool else x<-0;
		
		let me:Have, fun in life();
	}};
	
	guessTheError(something:SomeType): Errors {}
};


(* no error *)
class A {
};

(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error: no semicolon after classes *)
class F {
}

(* error:  closing brace is missing *)
Class E inherits A {
;
