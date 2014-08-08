class Shape {
dimension: Int;
init(d:Int): SELF_TYPE {{
	dimension <- d;
	self;
	}};
dimension():Int{dimension};
perimeter(): Int {{
	(new IO).out_string("Unknown shape: ");
	0;
	}};
area(): Int {{
	(new IO).out_string("Unknown shape: ");
	0;
	}};
};
class Circle inherits Shape {
perimeter():Int {
	2*22*dimension/7
	};
area():Int {
	22*dimension*dimension/7
	};
};
class Square inherits Shape {
perimeter():Int {
	4*dimension
	};
area():Int {
	dimension*dimension
	};
};
class Main {
io:IO<-new IO;
s1:Shape;
s2:Shape;
s3:Shape;
display(s:Shape):IO {{
	io.out_string("Dimension: ");
	io.out_int(s.dimension());
	io.out_string("\nPerimeter: ");
	io.out_int(s.perimeter());
	io.out_string("\nArea: ");
	io.out_int(s.area());
	io.out_string("\n");
	}};
main(): Int {{
	s1<-new Shape;
	s1.init(3);
	s2<-new Circle;
	s2.init(3);
	s3<-new Square;
	s3.init(3);
	display(s1);
	io.out_string("\n");
	display(s2);
	io.out_string("\n");
	display(s3);
	0;
	}};
};