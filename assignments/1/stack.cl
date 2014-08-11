(*
 * This program creates a stack which is then used for an interpreter of the defined language.
 * Author - Agam Agarwal (CS12B1003)
 * Compilation - coolc stack.cl atoi.cl
 * Execution - spim stack.s
 *)

class Node {	--represents each item on the stack
	value:String;	--each item has a string value
	next:Node;	--object below this item, void if this is the last item
	setValue(val:String):String {	--sets the value of the item as the given value
		value<-val
	};
	getValue():String {	--returns the current value stored by this item
		value
	};
	setNext(n:Node):Node {	--sets the next object as the given object
		next<-n
	};
	getNext():Node {	--returns the object below this
		next
	};
};

class Stack {	--implementation of a single stack
	top:Node;	--object storing the reference to the top of the stack
	push(s:String):String {	--pushes the given string to the top of the stack
		let x:Node<-new Node in {	--create a new node
			x.setValue(s);	--set the value of the node as the value to be pushed
			x.setNext(top);	--link its next object to the current top. Note this will also work if top is currently void
			top<-x;	--make x the new top
			s;	--return the string currently pushed
		}
	};
	pop():String {	--removes the topmost item from the stack and returns its value
		if not isvoid top then	--if stack is not empty
			let val:String<-top.getValue() in {	--get the value of the top of the stack
				top<-top.getNext();	--set the top variable to refer to the item below it. Note that Cool has automatic memory management, so the previous top object's memory will be deallocated by the garbage collector
				val;	--return the value popped
			}
		else
			""	--return an empty string if stack is empty
		fi
	};
	peek():String {	--returns the value stored by the topmost item without removing it
		if not isvoid top then
			top.getValue()
		else
			""
		fi
	};
	display():Object {	--prints the current stack from top to bottom, one item per line
		let io:IO<-new IO, node:Node<-top in	--initialize the object for input-output, and a Node object for traversal through the stack
			while not isvoid node loop {	--until the node object becomes void, ie. until the bottom of the stack is reached
				io.out_string(node.getValue().concat("\n"));	--print the value of the item followed by a newline character
				node<-node.getNext();	--move the node object 1 item below
			} pool
	};
};

class Main {
	io:IO<-new IO;	--object for input-output operations
	stack:Stack<-new Stack;
	evaluate():Object {	--evaluates the top of the stack based on the given rules
		let topValue:String<-stack.peek() in	--peek and get the value of the item at the top of the stack
			if topValue="+" then
				let plus:String<-stack.pop(), a2i:A2I<-new A2I, first:Int<-a2i.a2i(stack.pop()), second:Int<-a2i.a2i(stack.pop()) in	--plus: gets the '+' sign(unused), a2i: object of A2I class for conversion between integer and string, first and second: The top two items as integers
					stack.push(a2i.i2a(first+second))	--calculate the sum, convert to string and push into the stack
			else
				if topValue="s" then
					let swap:String<-stack.pop(), first:String<-stack.pop(), second:String<-stack.pop() in {	--swap: gets the 's'(unused), first and second: top two items as strings
						stack.push(first);
						stack.push(second);	--pushed the items in reverse item. Note that the item 'first' was above 'second' previous, while now 'second' is above 'first'
					}
				else
					0	--do nothing in other cases
				fi
			fi
	};
	main():Int {{	--function where the execution begins
		let run:Bool<-true, command:String in	--run: marks if the program has to keep running, command: stores the commands given as input
			while run loop {
				io.out_string("> ");	--print the prompt
				command<-io.in_string();	--read the next command
				if command="d" then stack.display() else	--display the contents of the stack if the command is 'd'
				if command="x" then run<-false else	--set the run variable to false if the command is 'x', so that the program terminates
				if command="e" then evaluate() else	--evaluate the top of the stack if the command is 'e'
				stack.push(command)	--Push the command if it is 's', '+' or an integer. Note that the given programs are claimed to be error free, so the command will be one of these three
				fi fi fi;
			} pool;
		0;
	}};
};