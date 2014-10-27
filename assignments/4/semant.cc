

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
		if(cur_class->get_name()==SELF_TYPE || class_map.find(cur_class->get_name())!=class_map.end()) {
			if(cur_class->get_name()==IO || cur_class->get_name()==Int || cur_class->get_name()==Str || cur_class->get_name()==Bool || cur_class->get_name()==Object || cur_class->get_name()==SELF_TYPE)
				semant_error(cur_class)<<"Redefinition of basic class "<<cur_class->get_name()<<"."<<endl;
			else
				semant_error(cur_class)<<"Class "<<(cur_class->get_name())<<" was previously defined."<<endl;
			class_redefinition_error=true;
		} else
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
	
	method_class* method_ancestor=find_method(enclosing_class->get_parent(), name);
	if(method_ancestor!=NULL) {
		
		//check number of formal parameters
		if(formals->len()!=method_ancestor->formals->len())
			classtable->semant_error(enclosing_class)<<"Incompatible number of formal parameters in redefined method "<<name<<"."<<endl;
		else {
			//check formal types
			for(int i=0; i<formals->len(); i++) {
				if(formals->nth(i)->get_type_decl()!=method_ancestor->formals->nth(i)->get_type_decl()) {
					classtable->semant_error(enclosing_class)<<"In redefined method "<<name<<", parameter type "<<formals->nth(i)->get_type_decl()<<" is different from original type "<<method_ancestor->formals->nth(i)->get_type_decl()<<endl;
					break;
				}
			}
		}
	}
	
	classtable->method_table->addid(name, &return_type);
	
}

void method_class::check_and_add_formals(Class_ enclosing_class) {
	
	for(int i=formals->first(); formals->more(i); i=formals->next(i))
		formals->nth(i)->check_and_add_formal(enclosing_class);
}

void formal_class::check_and_add_formal(Class_ enclosing_class) {
	
	//check if invalid type
	if(classtable->class_map.find(type_decl)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Class "<<type_decl<<" of formal parameter "<<name<<" is undefined."<<endl;
		
	//check if 'self'
	if(name==self)
		classtable->semant_error(enclosing_class)<<"'self' cannot be the name of a formal parameter."<<endl;
	//check if redefinition
	else if(classtable->object_table->probe(name)!=NULL)
		classtable->semant_error(enclosing_class)<<"Formal parameter "<<name<<" is multiply defined."<<endl;
	
	//add to object table
	else
		classtable->object_table->addid(name, &type_decl);
	
}

void method_class::check_feature(Class_ enclosing_class) {
	classtable->object_table->enterscope();	//entering a new method
	check_and_add_formals(enclosing_class);
	
	Symbol type_expr=expr->check_expression(enclosing_class);
	
	if(classtable->class_map.find(type_expr)!=classtable->class_map.end()	//type exists
			&& !type_conforms(type_expr, return_type))
		classtable->semant_error(enclosing_class)<<"Inferred return type "<<type_expr<<" of method "<<name<<" does not conform to declared return type "<<return_type<<"."<<endl;
	
	classtable->object_table->exitscope();
}

void attr_class::add_feature(Class_ enclosing_class) {
	
	
	//if valid type declaration
	if(type_decl!=SELF_TYPE && classtable->class_map.find(type_decl)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Class "<<type_decl<<" of attribute "<<name<<" is undefined."<<endl;	
	
	//if redefinition
	if(classtable->object_table->probe(name)!=NULL)
		classtable->semant_error(enclosing_class)<<"Attribute "<<name<<" is multiply defined in class."<<endl;
	
	//check if self
	if(name==self)
		classtable->semant_error(enclosing_class)<<"'self' cannot be the name of an attribute."<<endl;
	//check if inherited attribute
	else if(find_attr(enclosing_class->get_parent(), name)!=NULL)
		classtable->semant_error(enclosing_class)<<"Attribute "<<name<<" is an attribute of an inherited class."<<endl;
	else
		classtable->object_table->addid(name, &type_decl);
	
}

void attr_class::check_feature(Class_ enclosing_class) {
	
	Symbol expr_type=init->check_expression(enclosing_class);
	
	//check type if not No_type
	if(expr_type!=No_type && !type_conforms(expr_type!=SELF_TYPE?expr_type:enclosing_class->get_name(), type_decl))
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

/* find common ancestor */
Symbol find_common_ancestor(Symbol type1, Symbol type2) {
	
	if(type1==No_type)
		return type2;
	if(type2==No_type)
		return type1;
	
	int count1, count2;
	count1=count2=0;
	Symbol temp;
	
	//count first
	for(temp=type1; temp!=Object; temp=classtable->class_map[temp]->get_parent(), count1++);
	
	//count second
	for(temp=type2; temp!=Object; temp=classtable->class_map[temp]->get_parent(), count2++);
	
	while(count1>count2) {
		type1=classtable->class_map[type1]->get_parent();
		count1--;
	}
	
	while(count2>count1) {
		type2=classtable->class_map[type2]->get_parent();
		count2--;
	}
	
	while(true) {	//true because they will ultimately meet at Object (Adam ;-) )
		if(type1==type2)
			break;
		type1=classtable->class_map[type1]->get_parent();
		type2=classtable->class_map[type2]->get_parent();
	}
	
	return type1;
}


/* finds a method in the ancestor list */
method_class* find_method(Symbol class_name, Symbol method_name) {
	
	while(class_name!=No_class) {
		
		//check if class_name exists
		if(classtable->class_map.find(class_name)==classtable->class_map.end())
			break;
		
		//get the Class_ object
		Class_ cur_class=classtable->class_map[class_name];
		
		//get its features
		Features features=cur_class->get_features();
		
		//iterate over features to find the method
		for(int i=features->first(); features->more(i); i=features->next(i)) {
			Feature cur_feature=features->nth(i);
			if(cur_feature->is_method() && cur_feature->get_name()==method_name)
				return (method_class*)cur_feature;
		}
		class_name=cur_class->get_parent();
	}
	return NULL;
}

/* finds an attribute in the ancestor list */
attr_class* find_attr(Symbol class_name, Symbol attr_name) {
	
	while(class_name!=No_class) {
		
		//get the Class_ object
		Class_ cur_class=classtable->class_map[class_name];
		
		//get its features
		Features features=cur_class->get_features();
		
		//iterate over features to find the attr
		for(int i=features->first(); features->more(i); i=features->next(i)) {
			Feature cur_feature=features->nth(i);
			if(!cur_feature->is_method() && cur_feature->get_name()==attr_name)
				return (attr_class*)cur_feature;
		}
		class_name=cur_class->get_parent();
	}
	return NULL;
	
}

/* Expression functions */


Symbol assign_class::check_expression(Class_ enclosing_class) {
	
	//check expression
	Symbol type_expr=expr->check_expression(enclosing_class);
	
	//check if assigning to self
	if(name==self)
		classtable->semant_error(enclosing_class)<<"Cannot assign to 'self'."<<endl;
	
	//check if OBJECTID is declared in this or ancestor scopes
	Symbol *type_object=classtable->object_table->lookup(name);
	attr_class* attr;
	Symbol ancestor_type;
	
	if(name!=self && type_object==NULL) {
		
		//check in ancestor classes
		attr=find_attr(enclosing_class->get_parent(), name);
		if(attr!=NULL) {
			ancestor_type=attr->get_type_decl();
			type_object=&ancestor_type;
		}
		else
			classtable->semant_error(enclosing_class)<<"Assignment to undeclared variable "<<name<<"."<<endl;
	}
	
	//check if type conforms
	if(type_object!=NULL && !type_conforms(type_expr!=SELF_TYPE?type_expr:enclosing_class->get_name(), *type_object))
		classtable->semant_error(enclosing_class)<<"Type "<<type_expr<<" of assigned expression does not conform to declared type "<<*type_object<<" of identifier "<<name<<"."<<endl;
	
	set_type(type_expr);
	return get_type();
}

Symbol static_dispatch_class::check_expression(Class_ enclosing_class) {
	
	Symbol type_expr=expr->check_expression(enclosing_class);
	
	set_type(Object);	//default
	
	//check each of the actuals and set their types
	for(int i=actual->first(); actual->more(i); i=actual->next(i))
		actual->nth(i)->check_expression(enclosing_class);
	
	//check if static dispatch type exists
	if(classtable->class_map.find(type_name)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Static dispatch to undefined class "<<type_name<<"."<<endl;
	
	//check if expr type conforms to static dispatch type
	else if((type_expr==SELF_TYPE || classtable->class_map.find(type_expr)!=classtable->class_map.end())	//type_expr is defined
		&& !type_conforms(type_expr==SELF_TYPE?enclosing_class->get_name():type_expr, type_name))
		classtable->semant_error(enclosing_class)<<"Expression type "<<type_expr<<" does not conform to declared static dispatch type "<<type_name<<"."<<endl;
	
	else {

		method_class* method=NULL;
		
		//find the method in the ancestor list of type_name
		if((method=find_method(type_name, name))==NULL) {
				classtable->semant_error(enclosing_class)<<"Static dispatch to undefined method "<<name<<"."<<endl;
			}
		
		else {
			//compare the formals' and actuals' length
			if(method->get_formals()->len()!=actual->len())
				classtable->semant_error(enclosing_class)<<"Method "<<name<<" called with wrong number of arguments."<<endl;
		
			//compare the formals' and actuals' types
			else {
				Formals formals=method->get_formals();
				
				for(int i=0; i<actual->len(); i++)
					if(!type_conforms(actual->nth(i)->get_type(), formals->nth(i)->get_type_decl()))
						classtable->semant_error(enclosing_class)<<"In call of method "<<name<<", type "<<actual->nth(i)->get_type()<<" of parameter "<<formals->nth(i)->get_name()<<" does not conform to declared type "<<formals->nth(i)->get_type_decl()<<"."<<endl;
			}
			
			set_type(method->get_return_type()!=SELF_TYPE?method->get_return_type():
				(
				type_name==SELF_TYPE?SELF_TYPE:type_name
				)
			);
		}
	}
	
	return get_type();
}

Symbol dispatch_class::check_expression(Class_ enclosing_class) {
	
	Symbol type_name=expr->check_expression(enclosing_class);
	
	set_type(Object);	//default
	method_class* method=NULL;
	
	//check each of the actuals and set their types
	for(int i=actual->first(); actual->more(i); i=actual->next(i))
		actual->nth(i)->check_expression(enclosing_class);
	
	//check if type_name is valid
	if(type_name!=SELF_TYPE && classtable->class_map.find(type_name)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Dispatch on undefined class "<<type_name<<"."<<endl;
	
	//find the method in the ancestor list of type_name
	else if((method=find_method(type_name==SELF_TYPE?enclosing_class->get_name():type_name, name))==NULL)
			classtable->semant_error(enclosing_class)<<"Dispatch to undefined method "<<name<<"."<<endl;
	
	
	else {
		
		//compare the formals' and actuals' length
		if(method->get_formals()->len()!=actual->len())
			classtable->semant_error(enclosing_class)<<"Method "<<name<<" called with wrong number of arguments."<<endl;
	
		//compare the formals' and actuals' types
		else {
			Formals formals=method->get_formals();
			
			for(int i=0; i<actual->len(); i++)
				if(!type_conforms(actual->nth(i)->get_type()!=SELF_TYPE?actual->nth(i)->get_type():enclosing_class->get_name(), formals->nth(i)->get_type_decl()))
					classtable->semant_error(enclosing_class)<<"In call of method "<<name<<", type "<<actual->nth(i)->get_type()<<" of parameter "<<formals->nth(i)->get_name()<<" does not conform to declared type "<<formals->nth(i)->get_type_decl()<<"."<<endl;
		}
		
		set_type(method->get_return_type()!=SELF_TYPE?method->get_return_type():
				(
				type_name==SELF_TYPE?SELF_TYPE:type_name
				)
			);
	}
	return get_type();
}

Symbol cond_class::check_expression(Class_ enclosing_class) {
	
	//check if predicate is Bool
	if(pred->check_expression(enclosing_class)!=Bool)
		classtable->semant_error(enclosing_class)<<"Predicate of 'if' does not have type Bool."<<endl;
	
	Symbol type_then=then_exp->check_expression(enclosing_class);
	Symbol type_else=else_exp->check_expression(enclosing_class);
	
	set_type(find_common_ancestor(type_then, type_else));
	return get_type();
}

Symbol loop_class::check_expression(Class_ enclosing_class) {
	
	//check if predicate is Bool
	if(pred->check_expression(enclosing_class)!=Bool)
		classtable->semant_error(enclosing_class)<<"Loop condition does not have type Bool."<<endl;
	
	//check body
	body->check_expression(enclosing_class);
	
	//type is always Object
	set_type(Object);
	return get_type();
}

Symbol typcase_class::check_expression(Class_ enclosing_class) {
	
	//check expression
	Symbol type_expr=expr->check_expression(enclosing_class);
	
	Symbol return_type=No_type;
	
	std::map<Symbol, bool> types_done;
	
	//check each case
	for(int i=cases->first(); cases->more(i); i=cases->next(i)) {
		
		Case cur_case=cases->nth(i);
		Symbol  cur_case_name=cur_case->get_name();
		Symbol cur_case_type_decl=cur_case->get_type_decl();
		
		
		//enterscope
		classtable->object_table->enterscope();
		
		//check if 'self'
		if(cur_case_name==self)
			classtable->semant_error(enclosing_class)<<"'self' bound in 'case'."<<endl;
		
		//check if type redefined
		if(types_done.find(cur_case_type_decl)!=types_done.end())
			classtable->semant_error(enclosing_class)<<"Duplicate branch "<<cur_case_type_decl<<" in case statement."<<endl;
		else
			types_done[cur_case_type_decl]=true;	//put into the map
		
		//check if valid type
		if(classtable->class_map.find(cur_case_type_decl)==classtable->class_map.end())
			classtable->semant_error(enclosing_class)<<"Class "<<cur_case_type_decl<<" of case branch is undefined."<<endl;
		
		classtable->object_table->addid(cur_case_name, &cur_case_type_decl);
		
		//check expression
		Symbol type_branch=cur_case->get_expr()->check_expression(enclosing_class);
		
		//set return type as the common ancestor
		return_type=find_common_ancestor(return_type, type_branch);
		
		//exitscope
		classtable->object_table->exitscope();
		
	}
	
	set_type(return_type);
	return get_type();
}

Symbol block_class::check_expression(Class_ enclosing_class) {
	
	Symbol type_expr;
	
	//iterate over list of Expressions in the block
	for(int i=body->first(); body->more(i); i=body->next(i))
		type_expr=body->nth(i)->check_expression(enclosing_class);
	
	set_type(type_expr);
	return get_type();
	
}

Symbol let_class::check_expression(Class_ enclosing_class) {
	
	//check expression
	Symbol type_init=init->check_expression(enclosing_class);
	
	
	//check if type_decl is not SELF_TYPE and doesn't exists
	if(type_decl!=SELF_TYPE && classtable->class_map.find(type_decl)==classtable->class_map.end())
		classtable->semant_error(enclosing_class)<<"Class "<<type_decl<<" of let-bound identifier "<<identifier<<" is undefined."<<endl;
	
	//check if type_init conforms with declared type
	else if(type_init!=No_type	//if init is given
			&& !type_conforms(type_init, type_decl))
		classtable->semant_error(enclosing_class)<<"Inferred type "<<type_init<<" of initialization of "<<identifier<<" does not conform to identifier's declared type "<<type_decl<<"."<<endl;
	
	
	//enter a new scope
	classtable->object_table->enterscope();
	
	//check if 'self'
	if(identifier==self)
		classtable->semant_error(enclosing_class)<<"'self' cannot be bound in a 'let' expression."<<endl;
	else
		classtable->object_table->addid(identifier, &type_decl);
	
	set_type(body->check_expression(enclosing_class));
	
	//exit the scope
	classtable->object_table->exitscope();
	
	return get_type();
}

Symbol plus_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" + "<<type2<<endl;
	
	set_type(Int);
	return get_type();
}

Symbol sub_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" - "<<type2<<endl;
	
	set_type(Int);
	return get_type();
}

Symbol mul_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" * "<<type2<<endl;
	
	set_type(Int);
	return get_type();
}

Symbol divide_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" / "<<type2<<endl;
	
	set_type(Int);
	return get_type();
}

Symbol neg_class::check_expression(Class_ enclosing_class) {
	
	Symbol type1=e1->check_expression(enclosing_class);
	
	//check if type is Int
	if(type1!=Int)
		classtable->semant_error(enclosing_class)<<"Argument of '~' has type "<<type1<<" instead of Int."<<endl;
	
	set_type(Int);
	return get_type();
}

Symbol lt_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" < "<<type2<<endl;
	
	set_type(Bool);
	return get_type();
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
	
	set_type(Bool);
	return get_type();
}

Symbol leq_class::check_expression(Class_ enclosing_class)	{
	
	Symbol type1=e1->check_expression(enclosing_class);
	Symbol type2=e2->check_expression(enclosing_class);
	
	//check if both are not Int
	if(type1!=Int || type2!=Int)
		classtable->semant_error(enclosing_class)<<"non-Int arguments: "<<type1<<" <= "<<type2<<endl;
	
	set_type(Bool);
	return get_type();
}

Symbol comp_class::check_expression(Class_ enclosing_class) {
	
	Symbol type=e1->check_expression(enclosing_class);
	
	//if not Bool
	if(type!=Bool)
		classtable->semant_error(enclosing_class)<<"Argument of 'not' has type "<<type<<" instead of Bool."<<endl;
	
	set_type(Bool);
	return get_type();
}

Symbol int_const_class::check_expression(Class_ enclosing_class) {
	set_type(Int);
	return get_type();
}

Symbol bool_const_class::check_expression(Class_ enclosing_class) {
	set_type(Bool);
	return get_type();
}

Symbol string_const_class::check_expression(Class_ enclosing_class) {
	set_type(Str);
	return get_type();
}

Symbol new__class::check_expression(Class_ enclosing_class) {
	
	//check if type is SELF_TYPE or does not exist
	if(type_name!=SELF_TYPE && classtable->class_map.find(type_name)==classtable->class_map.end()) {
		classtable->semant_error(enclosing_class)<<"'new' used with undefined class "<<type_name<<"."<<endl;
		set_type(Object);
	} else
		set_type(type_name);
	
	return get_type();
}

Symbol isvoid_class::check_expression(Class_ enclosing_class) {
	
	//just check the expression. No need to check its type
	e1->check_expression(enclosing_class);
	
	set_type(Bool);
	return get_type();
}

Symbol no_expr_class::check_expression(Class_ enclosing_class) {
	set_type(No_type);
	return get_type();
}

Symbol object_class::check_expression(Class_ enclosing_class) {
	
	//check in current scope
	Symbol *type_obj;
	
	//find in ancestors
	attr_class* attr=find_attr(enclosing_class->get_parent(), name);
	Symbol inherited_attr_type;
	
	//if ancestors had this attr
	if(attr!=NULL)
		inherited_attr_type=attr->get_type_decl();
	
	if(name==self)
		set_type(SELF_TYPE);
	else if((type_obj=classtable->object_table->lookup(name))==NULL
			&& (attr==NULL || (type_obj=&inherited_attr_type)==NULL)) {
		classtable->semant_error(enclosing_class)<<"Undeclared identifier "<<name<<"."<<endl;
		set_type(Object);
	} else
		set_type(*type_obj);
	
	return get_type();
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


