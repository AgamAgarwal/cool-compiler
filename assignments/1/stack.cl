class Node {
value:String;
next:Node;
setValue(val:String):String {{
	value<-val;
	}};
getValue():String {
	if type=1 then
		value
	else
		""
	fi
	};
setNext(n:Node):Node {
	next<-n
	};
getNext():Node {
	next
	};
};

class Stack {
top:Node;
push(s:String):String {
	if isvoid top then {
		top<-new Node;
		top.setValue(s);
		}
	else
		let x:Node<-new Node in {
			x.setValue(s);
			x.setNext(top);
			top<-x;
			s;
			}
	fi
	};
pop():String {
	if not isvoid top then
		let val:String<-top.getValue() in {
			top<-top.getNext();
			val;
			}
	else
		""
	fi
	};
};

class Main {
io:IO<-new IO;
main():Int {{
	let s:Stack<-new Stack in {
		s.push("Agam");
		s.push("Sid");
		io.out_string(s.pop());
		io.out_string(s.pop());
		};
	0;
	}};
};
