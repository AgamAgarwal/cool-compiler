#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

#include <map>	/* for inheritance_graph */

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {
private:
  int semant_errors;
  void install_basic_classes();
  ostream& error_stream;

public:
  std::map<Symbol, Class_> class_map;
  SymbolTable<Symbol, Symbol> *object_table;
  SymbolTable<Symbol, Symbol> *method_table;
  bool inheritance_cycles;
  
  ClassTable(Classes);
  bool check_if_valid_parents();
  bool check_inheritance_cycles();
  void check_features();
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
};

bool type_conforms(Symbol, Symbol);
Symbol find_common_ancestor(Symbol, Symbol);
method_class* find_method(Symbol, Symbol);
attr_class* find_attr(Symbol, Symbol);
ClassTable *classtable;

#endif

