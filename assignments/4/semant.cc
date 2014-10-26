

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"


extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}



ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr) {

	int i;
	
	install_basic_classes();
	
	bool Main_class_not_defined_error=true, class_redefinition_error=false;
	//construct inheritance graph
	for(i=classes->first(); classes->more(i); i=classes->next(i)) {
		Class_ cur_class=classes->nth(i);
		
		//check if Main class
		if(cur_class->get_name()==Main)
			Main_class_not_defined_error=false;
		
		//check if redefinition
		if(class_map.find(cur_class->get_name())!=class_map.end()) {
			semant_error(cur_class)<<"Class "<<(cur_class->get_name())<<" was previously defined."<<endl;
			class_redefinition_error=true;
		}
		
		class_map.insert(std::pair<Symbol, Class_>(cur_class->get_name(), cur_class));
	}
	
	if(!check_if_valid_parents() && !class_redefinition_error)
		if(!check_inheritance_cycles())
			if(Main_class_not_defined_error) {
				semant_error()<<"Class Main is not defined."<<endl;
			}
	
	object_table=new SymbolTable<Symbol, Symbol>();
	method_table=new SymbolTable<Symbol, Symbol>();
}

bool ClassTable::check_if_valid_parents() {
	
	bool error=false;
	for(std::map<Symbol, Class_>::iterator it=class_map.begin(); it!=class_map.end(); it++) {
		Symbol child_class_symbol=it->first, parent_class_symbol=it->second->get_parent();
		if(child_class_symbol==Object)
			continue;
		
		//check if parent is defined
		if(class_map.find(parent_class_symbol)==class_map.end()) {
			semant_error(it->second)<<"Class "<<child_class_symbol<<" inherits from an undefined class "<<parent_class_symbol<<"."<<endl;
			error=true;
		}
		
		//check if inheritance from Int, String or Bool
		if(parent_class_symbol==Int || parent_class_symbol==Str || parent_class_symbol==Bool) {
			semant_error(it->second)<<"Class "<<child_class_symbol<<" cannot inherit class "<<parent_class_symbol<<"."<<endl;
			error=true;
		}
	}
	return error;
}

bool ClassTable::check_inheritance_cycles() {
	
	bool error=false;
	for(std::map<Symbol, Class_>::iterator it=class_map.begin(); it!=class_map.end(); it++) {
		Symbol cur_class, slow_class_ref, fast_class_ref;
		cur_class=slow_class_ref=fast_class_ref=it->first;
		
		while(slow_class_ref!=Object && fast_class_ref!=Object && class_map[fast_class_ref]->get_parent()!=Object) {
			slow_class_ref=class_map[slow_class_ref]->get_parent();
			fast_class_ref=class_map[class_map[fast_class_ref]->get_parent()]->get_parent();
			
			//if loop is found
			if(slow_class_ref==fast_class_ref) {
				semant_error(class_map[cur_class])<<"Class "<<cur_class<<", or an ancestor of "<<cur_class<<", is involved in an inheritance cycle."<<endl;
				error=true;
				break;
			}
		}
	}
	return error;
}

void ClassTable::install_basic_classes() {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Class_ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    Class_ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
    Class_ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //       
    Class_ Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       append_Features(
									       single_Features(attr(val, Int, no_expr())),
									       single_Features(attr(str_field, prim_slot, no_expr()))),
							       single_Features(method(length, nil_Formals(), Int, no_expr()))),
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, 
								      no_expr()))),
			       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)), 
								     single_Formals(formal(arg2, Int))),
						      Str, 
						      no_expr()))),
	       filename);
	       
	//add the basic classes to the inheritance graph
	class_map.insert(std::pair<Symbol, Class_>(Object, Object_class));
	class_map.insert(std::pair<Symbol, Class_>(IO, IO_class));
	class_map.insert(std::pair<Symbol, Class_>(Int, Int_class));
	class_map.insert(std::pair<Symbol, Class_>(Bool, Bool_class));
	class_map.insert(std::pair<Symbol, Class_>(Str, Str_class));
}


void ClassTable::check_features() {
	
	//iterate over each class
	for(std::map<Symbol, Class_>::iterator it=class_map.begin(); it!=class_map.end(); it++) {
		
		Class_ cur_class=it->second;
		
		//skip basic classes
		if(cur_class->get_name()==IO || cur_class->get_name()==Int || cur_class->get_name()==Str || cur_class->get_name()==Bool || cur_class->get_name()==Object)
			continue;
		
		Features features=cur_class->get_features();
		
		object_table->enterscope();
		method_table->enterscope();
		
		//iterate over each Feature of the current class and add them
		for(int i=features->first(); features->more(i); i=features->next(i)) {
			Feature feature=features->nth(i);
			feature->add_feature(cur_class);
		}
		
		if(cur_class->get_name()==Main && method_table->probe(main_meth)==NULL)
			semant_error(cur_class)<<"No 'main' method in class Main."<<endl;
		
		//iterate over each Feature of the current class and check their semantics
		for(int i=features->first(); features->more(i); i=features->next(i)) {
			Feature feature=features->nth(i);
			feature->check_feature(cur_class);
		}
		
		object_table->exitscope();
		method_table->exitscope();
	}
}

void method_class::add_feature(Class_ enclosing_class) {
	
	//if valid return type
	if(return_type!=SELF_TYPE && classtable->class_map.find(return_type)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Undefined return type "<<return_type<<" in method "<<name<<"."<<endl;
	
	//if redefinition
	if(classtable->method_table->probe(name)!=NULL)
		classtable->semant_error(enclosing_class)<<"Method "<<name<<" is multiply defined."<<endl;
	
	//TODO: check overridden functions
	
	classtable->method_table->addid(name, &return_type);
	
}

void method_class::check_and_add_formals(Class_ enclosing_class) {
	
	for(int i=formals->first(); formals->more(i); i=formals->next(i))
		formals->nth(i)->check_and_add_formal(enclosing_class);
}

void formal_class::check_and_add_formal(Class_ enclosing_class) {
	
	//check if redefinition
	if(classtable->object_table->probe(name)!=NULL)
		classtable->semant_error(enclosing_class)<<"Formal parameter "<<name<<" is multiply defined."<<endl;
	
	//check if invalid type
	if(classtable->class_map.find(type_decl)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Class "<<type_decl<<" of formal parameter "<<name<<" is undefined."<<endl;
	
	//add to object table
	classtable->object_table->addid(name, &type_decl);
	
}

void method_class::check_feature(Class_ enclosing_class) {
	classtable->object_table->enterscope();	//entering a new method
	check_and_add_formals(enclosing_class);
	
	Symbol type=expr->check_expression(enclosing_class);
	
	if(!type_conforms(type, return_type))
		classtable->semant_error(enclosing_class)<<"Inferred return type "<<type<<" of method "<<name<<" does not conform to declared return type "<<return_type<<"."<<endl;
	
	classtable->object_table->exitscope();
}

void attr_class::add_feature(Class_ enclosing_class) {
	
	
	//if valid type declaration
	if(type_decl!=SELF_TYPE && classtable->class_map.find(type_decl)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Class "<<type_decl<<" of attribute "<<name<<" is undefined."<<endl;	
	
	//if redefinition
	if(classtable->object_table->probe(name)!=NULL)
		classtable->semant_error(enclosing_class)<<"Attribute "<<name<<" is multiply defined in class."<<endl;
	
	classtable->object_table->addid(name, &type_decl);
	
}

void attr_class::check_feature(Class_ enclosing_class) {
	
	Symbol expr_type=init->check_expression(enclosing_class);
	
	//check type if not No_type
	if(expr_type!=No_type && !type_conforms(expr_type, type_decl))
		classtable->semant_error(enclosing_class)<<"Inferred type "<<expr_type<<" of initialization of attribute "<<name<<" does not conform to declared type "<<type_decl<<"."<<endl;
}


/* check if conforming types */
bool type_conforms(Symbol child, Symbol parent) {
	
	while(child!=No_class) {
		if(child==parent)
			return true;
		child=classtable->class_map[child]->get_parent();
	}
	return false;
}

/* Expression functions */

//TODO: remove this function when done all
Symbol Expression_class::check_expression(Class_)	{
	return No_type;
}

Symbol plus_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" + "<<type2<<endl;
	
	return Int;
}

Symbol sub_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" - "<<type2<<endl;
	
	return Int;
}

Symbol mul_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" * "<<type2<<endl;
	
	return Int;
}

Symbol divide_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" / "<<type2<<endl;
	
	return Int;
}

Symbol neg_class::check_expression(Class_ enclosing_class) {
	
	Symbol type1=e1->check_expression(enclosing_class);
	
	//check if type is Int
	if(type1!=Int)
		classtable->semant_error(enclosing_class)<<"Argument of '~' has type "<<type1<<" instead of Int."<<endl;
	
	return Int;
}

Symbol lt_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" < "<<type2<<endl;
	
	return Bool;
}

Symbol eq_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if basic type and uncompatible
	if(((type1==Int || type2==Int)
			|| (type1==Str || type2==Str)
			|| (type1==Bool || type2==Bool))
		&& type1!=type2)
		classtable->semant_error(enclosing_class)<<"Illegal comparison with a basic type."<<endl;
	
	return Bool;
}

Symbol leq_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" <= "<<type2<<endl;
	
	return Bool;
}

Symbol comp_class::check_expression(Class_ enclosing_class) {
	
	Symbol type=e1->check_expression(enclosing_class);
	
	//if not Bool
	if(type!=Bool)
		classtable->semant_error(enclosing_class)<<"Argument of 'not' has type "<<type<<" instead of Bool."<<endl;
	
	return Bool;
}

Symbol int_const_class::check_expression(Class_ enclosing_class) {
	return Int;
}

Symbol bool_const_class::check_expression(Class_ enclosing_class) {
	return Bool;
}

Symbol string_const_class::check_expression(Class_ enclosing_class) {
	return Str;
}

Symbol new__class::check_expression(Class_ enclosing_class) {
	
	//check if type exists
	if(classtable->class_map.find(type_name)==classtable->class_map.end()) {
		classtable->semant_error(enclosing_class)<<"'new' used with undefined class "<<type_name<<"."<<endl;
		return Object;
	}
	
	return type_name;
}

Symbol isvoid_class::check_expression(Class_ enclosing_class) {
	
	//just check the expression. No need to check its type
	e1->check_expression(enclosing_class);
	
	return Bool;
}

Symbol no_expr_class::check_expression(Class_ enclosing_class) {
	return No_type;
}

Symbol object_class::check_expression(Class_ enclosing_class) {
	
	//check in current scope
	Symbol *type;
	if((type=classtable->object_table->lookup(name))==NULL) {
		classtable->semant_error(enclosing_class)<<"Undeclared identifier "<<name<<"."<<endl;
		return Object;
	}
	
	return *type;
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 



/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    classtable = new ClassTable(classes);

    /* some semantic analysis code may go here */
	classtable->check_features();


    if (classtable->errors()) {
	cerr << "Compilation halted due to static semantic errors." << endl;
	exit(1);
    }
}


