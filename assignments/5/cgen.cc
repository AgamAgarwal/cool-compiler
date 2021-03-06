
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include "cgen.h"
#include "cgen_gc.h"

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol 
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

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


//  BoolConst is a class that implements code generation for operations
//  on the two booleans, which are given global names here.
BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

reg new_reg() {
	return cur_register++;
}

reg last_reg() {
	return cur_register-1;
}

reg reset_cur_register() {
	return (cur_register=1);
}

void program_class::cgen(ostream &os) 
{
  // llvm wants comments to start with ';'
  os << "; start of generated code\n";

  initialize_constants();
  codegen_classtable = new CgenClassTable(classes,os);
  codegen_classtable->code();
  os << "\n; end of generated code\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_load(char *dest_reg, int offset, char *source_reg, ostream& s)
{
  s << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" 
    << endl;
}

static void emit_store(char *source_reg, int offset, char *dest_reg, ostream& s)
{
  s << SW << source_reg << " " << offset * WORD_SIZE << "(" << dest_reg << ")"
      << endl;
}

static void emit_load_imm(char *dest_reg, int val, ostream& s)
{ s << LI << dest_reg << " " << val << endl; }

static void emit_load_address(char *dest_reg, char *address, ostream& s)
{ s << LA << dest_reg << " " << address << endl; }

static void emit_partial_load_address(char *dest_reg, ostream& s)
{ s << LA << dest_reg << " "; }

static void emit_load_bool(char *dest, const BoolConst& b, ostream& s)
{
  emit_partial_load_address(dest,s);
  b.code_ref(s);
  s << endl;
}

static void emit_load_string(char *dest, StringEntry *str, ostream& s)
{
  emit_partial_load_address(dest,s);
  str->code_ref(s);
  s<<str->get_string();
  s << endl;
}

static void emit_load_int(char *dest, IntEntry *i, ostream& s)
{
  emit_partial_load_address(dest,s);
  i->code_ref(s);
  s<<i->get_string();
  s << endl;
}

static void emit_move(char *dest_reg, char *source_reg, ostream& s)
{ s << MOVE << dest_reg << " " << source_reg << endl; }

static void emit_neg(char *dest, char *src1, ostream& s)
{ s << NEG << dest << " " << src1 << endl; }

static void emit_add(char *dest, char *src1, char *src2, ostream& s)
{ s << ADD << dest << " " << src1 << " " << src2 << endl; }

static void emit_addu(char *dest, char *src1, char *src2, ostream& s)
{ s << ADDU << dest << " " << src1 << " " << src2 << endl; }

static void emit_addiu(char *dest, char *src1, int imm, ostream& s)
{ s << ADDIU << dest << " " << src1 << " " << imm << endl; }

static void emit_div(char *dest, char *src1, char *src2, ostream& s)
{ s << DIV << dest << " " << src1 << " " << src2 << endl; }

static void emit_mul(char *dest, char *src1, char *src2, ostream& s)
{ s << MUL << dest << " " << src1 << " " << src2 << endl; }

static void emit_sub(char *dest, char *src1, char *src2, ostream& s)
{ s << SUB << dest << " " << src1 << " " << src2 << endl; }

static void emit_sll(char *dest, char *src1, int num, ostream& s)
{ s << SLL << dest << " " << src1 << " " << num << endl; }

static void emit_jalr(char *dest, ostream& s)
{ s << JALR << "\t" << dest << endl; }

static void emit_jal(char *address,ostream &s)
{ s << JAL << address << endl; }

static void emit_return(ostream& s)
{ s << RET << endl; }

static void emit_gc_assign(ostream& s)
{ s << JAL << "_GenGC_Assign" << endl; }

static void emit_disptable_ref(Symbol sym, ostream& s)
{  s << sym << DISPTAB_SUFFIX; }

static void emit_init_ref(Symbol sym, ostream& s)
{ s << sym << CLASSINIT_SUFFIX; }

static void emit_label_ref(int l, ostream &s)
{ s << "label" << l; }

static void emit_protobj_ref(Symbol sym, ostream& s)
{ s << sym << PROTOBJ_SUFFIX; }

static void emit_method_ref(Symbol classname, Symbol methodname, ostream& s)
{ s << classname << METHOD_SEP << methodname; }

static void emit_label_def(int l, ostream &s)
{
  emit_label_ref(l,s);
  s << ":" << endl;
}

static void emit_beqz(char *source, int label, ostream &s)
{
  s << BEQZ << source << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_beq(char *src1, char *src2, int label, ostream &s)
{
  s << BEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bne(char *src1, char *src2, int label, ostream &s)
{
  s << BNE << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bleq(char *src1, char *src2, int label, ostream &s)
{
  s << BLEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blt(char *src1, char *src2, int label, ostream &s)
{
  s << BLT << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blti(char *src1, int imm, int label, ostream &s)
{
  s << BLT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bgti(char *src1, int imm, int label, ostream &s)
{
  s << BGT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_branch(int l, ostream& s)
{
  s << BRANCH;
  emit_label_ref(l,s);
  s << endl;
}

//
// Push a register on the stack. The stack grows towards smaller addresses.
//
static void emit_push(char *reg, ostream& str)
{
  emit_store(reg,0,SP,str);
  emit_addiu(SP,SP,-4,str);
}

//
// Fetch the integer value in an Int object.
// Emits code to fetch the integer value of the Integer object pointed
// to by register source into the register dest
//
static void emit_fetch_int(char *dest, char *source, ostream& s)
{ emit_load(dest, DEFAULT_OBJFIELDS, source, s); }

//
// Emits code to store the integer value contained in register source
// into the Integer object pointed to by dest.
//
static void emit_store_int(char *source, char *dest, ostream& s)
{ emit_store(source, DEFAULT_OBJFIELDS, dest, s); }


static void emit_test_collector(ostream &s)
{
  emit_push(ACC, s);
  emit_move(ACC, SP, s); // stack end
  emit_move(A1, ZERO, s); // allocate nothing
  s << JAL << gc_collect_names[cgen_Memmgr] << endl;
  emit_addiu(SP,SP,4,s);
  emit_load(ACC,0,SP,s);
}

static void emit_gc_check(char *source, ostream &s)
{
  if (source != (char*)A1) emit_move(A1, source, s);
  s << JAL << "_gc_check" << endl;
}


///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type StringEntry.  StringEntry methods are defined both for String
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream& s)
{
  s << STRCONST_PREFIX << index;
}

//
// Emit code for a constant String.
// You should fill in the code naming the dispatch table.
//

void StringEntry::code_def(ostream& s, int stringclasstag)
{
  IntEntryP lensym = inttable.add_int(len);

  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s  << LABEL                                             // label
      << WORD << stringclasstag << endl                                 // tag
      << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len+4)/4) << endl // size
      << WORD;


 /***** Add dispatch information for class String ******/

      s << endl;                                              // dispatch table
      s << WORD;  lensym->code_ref(s);  s << endl;            // string length
  emit_string_constant(s,str);                                // ascii string
  s << ALIGN;                                                 // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the 
// stringtable.
//
void StrTable::code_string_table(ostream& s, int stringclasstag)
{  
  for (List<StringEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,stringclasstag);
}

//
// Ints
//
void IntEntry::code_ref(ostream &s)
{
  s << INTCONST_PREFIX << index;
}

//
// Emit code for a constant Integer.
// You should fill in the code naming the dispatch table.
//

void IntEntry::code_def(ostream &s, int intclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                // label
      << WORD << intclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl  // object size
      << WORD; 

 /***** Add dispatch information for class Int ******/

      s << endl;                                          // dispatch table
      s << WORD << str << endl;                           // integer value
}


//
// IntTable::code_string_table
// Generate an Int object definition for every Int constant in the
// inttable.
//
void IntTable::code_string_table(ostream &s, int intclasstag)
{
  for (List<IntEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,intclasstag);
}


//
// Bools
//
BoolConst::BoolConst(int i) : val(i) { assert(i == 0 || i == 1); }

void BoolConst::code_ref(ostream& s) const
{
  s << BOOLCONST_PREFIX << val;
}
  
//
// Emit code for a constant Bool.
// You should fill in the code naming the dispatch table.
//

void BoolConst::code_def(ostream& s, int boolclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                  // label
      << WORD << boolclasstag << endl                       // class tag
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl   // object size
      << WORD;

 /***** Add dispatch information for class Bool ******/

      s << endl;                                            // dispatch table
      s << WORD << val << endl;                             // value (0 or 1)
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//***************************************************
//
//  Emit code to start the .data segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_data()
{
  Symbol main    = idtable.lookup_string(MAINNAME);
  Symbol string  = idtable.lookup_string(STRINGNAME);
  Symbol integer = idtable.lookup_string(INTNAME);
  Symbol boolc   = idtable.lookup_string(BOOLNAME);

  str << "\t.data\n" << ALIGN;
  //
  // The following global names must be defined first.
  //
  str << GLOBAL << CLASSNAMETAB << endl;
  str << GLOBAL; emit_protobj_ref(main,str);    str << endl;
  str << GLOBAL; emit_protobj_ref(integer,str); str << endl;
  str << GLOBAL; emit_protobj_ref(string,str);  str << endl;
  str << GLOBAL; falsebool.code_ref(str);  str << endl;
  str << GLOBAL; truebool.code_ref(str);   str << endl;
  str << GLOBAL << INTTAG << endl;
  str << GLOBAL << BOOLTAG << endl;
  str << GLOBAL << STRINGTAG << endl;

  //
  // We also need to know the tag of the Int, String, and Bool classes
  // during code generation.
  //
  str << INTTAG << LABEL
      << WORD << intclasstag << endl;
  str << BOOLTAG << LABEL 
      << WORD << boolclasstag << endl;
  str << STRINGTAG << LABEL 
      << WORD << stringclasstag << endl;    
}


//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_text()
{
  str << GLOBAL << HEAP_START << endl
      << HEAP_START << LABEL 
      << WORD << 0 << endl
      << "\t.text" << endl
      << GLOBAL;
  emit_init_ref(idtable.add_string("Main"), str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Int"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("String"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Bool"),str);
  str << endl << GLOBAL;
  emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
  str << endl;
}

void CgenClassTable::code_bools(int boolclasstag)
{
  falsebool.code_def(str,boolclasstag);
  truebool.code_def(str,boolclasstag);
}

void CgenClassTable::code_select_gc()
{
  //
  // Generate GC choice constants (pointers to GC functions)
  //
  str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
  str << "_MemMgr_INITIALIZER:" << endl;
  str << WORD << gc_init_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
  str << "_MemMgr_COLLECTOR:" << endl;
  str << WORD << gc_collect_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_TEST" << endl;
  str << "_MemMgr_TEST:" << endl;
  str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}


//********************************************************
//
// Emit code to reserve space for and initialize all of
// the constants.  Class names should have been added to
// the string table (in the supplied code, is is done
// during the construction of the inheritance graph), and
// code for emitting string constants as a side effect adds
// the string's length to the integer table.  The constants
// are emmitted by running through the stringtable and inttable
// and producing code for each entry.
//
//********************************************************

void CgenClassTable::code_constants()
{
  //
  // Add constants that are required by the code generator.
  //
  stringtable.add_string("");
  inttable.add_string("0");

  stringtable.code_string_table(str,stringclasstag);
  inttable.code_string_table(str,intclasstag);
  code_bools(boolclasstag);
}


CgenClassTable::CgenClassTable(Classes classes, ostream& s) : nds(NULL) , str(s)
{
   stringclasstag = 0 /* Change to your String class tag here */;
   intclasstag =    0 /* Change to your Int class tag here */;
   boolclasstag =   0 /* Change to your Bool class tag here */;

   enterscope();
   if (cgen_debug) cout << "Building CgenClassTable" << endl;
   install_basic_classes();
   install_classes(classes);
   build_inheritance_tree();

   exitscope();
}

void CgenClassTable::install_basic_classes()
{

// The tree package uses these globals to annotate the classes built below.
  //curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");

//
// A few special class names are installed in the lookup table but not
// the class list.  Thus, these classes exist, but are not part of the
// inheritance hierarchy.
// No_class serves as the parent of Object and the other special classes.
// SELF_TYPE is the self class; it cannot be redefined or inherited.
// prim_slot is a class known to the code generator.
//
  addid(No_class,
	new CgenNode(class_(No_class,No_class,nil_Features(),filename),
			    Basic,this));
  addid(SELF_TYPE,
	new CgenNode(class_(SELF_TYPE,No_class,nil_Features(),filename),
			    Basic,this));
  addid(prim_slot,
	new CgenNode(class_(prim_slot,No_class,nil_Features(),filename),
			    Basic,this));

// 
// The Object class has no parent class. Its methods are
//        cool_abort() : Object    aborts the program
//        type_name() : Str        returns a string representation of class name
//        copy() : SELF_TYPE       returns a copy of the object
//
// There is no need for method bodies in the basic classes---these
// are already built in to the runtime system.
//
  install_class(
   new CgenNode(
    class_(Object, 
	   No_class,
	   append_Features(
           append_Features(
           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
           single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	   filename),
    Basic,this));

// 
// The IO class inherits from Object. Its methods are
//        out_string(Str) : SELF_TYPE          writes a string to the output
//        out_int(Int) : SELF_TYPE               "    an int    "  "     "
//        in_string() : Str                    reads a string from the input
//        in_int() : Int                         "   an int     "  "     "
//
   install_class(
    new CgenNode(
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
	   filename),	    
    Basic,this));

//
// The Int class has no methods and only a single attribute, the
// "val" for the integer. 
//
   install_class(
    new CgenNode(
     class_(Int, 
	    Object,
            single_Features(attr(val, prim_slot, no_expr())),
	    filename),
     Basic,this));

//
// Bool also has only the "val" slot.
//
    install_class(
     new CgenNode(
      class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename),
      Basic,this));

//
// The class Str has a number of slots and operations:
//       val                                  ???
//       str_field                            the string itself
//       length() : Int                       length of the string
//       concat(arg: Str) : Str               string concatenation
//       substr(arg: Int, arg2: Int): Str     substring
//       
   install_class(
    new CgenNode(
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
	     filename),
        Basic,this));

}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_class(CgenNodeP nd)
{
  Symbol name = nd->get_name();

  if (probe(name))
    {
      return;
    }

  // The class name is legal, so add it to the list of classes
  // and the symbol table.
  nds = new List<CgenNode>(nd,nds);
  addid(name,nd);
}

void CgenClassTable::install_classes(Classes cs)
{
  for(int i = cs->first(); cs->more(i); i = cs->next(i))
    install_class(new CgenNode(cs->nth(i),NotBasic,this));
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree()
{
  for(List<CgenNode> *l = nds; l; l = l->tl())
      set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd)
{
  CgenNode *parent_node = probe(nd->get_parent());
  nd->set_parentnd(parent_node);
  parent_node->add_child(nd);
}

void CgenNode::add_child(CgenNodeP n)
{
  children = new List<CgenNode>(n,children);
}

void CgenNode::set_parentnd(CgenNodeP p)
{
  assert(parentnd == NULL);
  assert(p != NULL);
  parentnd = p;
}

reg CgenClassTable::get_reg_from_object(Symbol name) {
	for(int i=object_reg_map.size()-1; i>=0; i--) {
		if(object_reg_map[i].first==name)
			return object_reg_map[i].second;
	}
	return -1;
}

int CgenClassTable::get_class_size(Symbol class_name) {
	
	if(class_name==Object)
		return 1;
	if(class_name==Str)
		return 17;
	if(class_name==Bool)
		return 2;
	if(class_name==Int)
		return 5;
	if(class_name==IO)
		return 1;
	
	
	for(List<CgenNode> *l=nds; l!=NULL; l=l->tl()) {
	  CgenNode *cur_node=l->hd();
	  if(cur_node->get_name()==class_name) {
		 return get_class_size(cur_node);
	  }
	}
	return 0;	//unreachable
}

int CgenClassTable::get_class_size(CgenNode* class_node) {
	
	if(class_node->get_name()==Object || class_node->get_name()==IO)
		return 1;
	
	int size=0;
	
	//iterate over features, for each attribute, add 8
	for(int i=class_node->features->first(); class_node->features->more(i); i=class_node->features->next(i))
		if(class_node->features->nth(i)->is_attr())
			size+=8;
	
	size+=get_class_size(class_node->get_parentnd());
	
	return size;
}

/* finds a method in the ancestor list */
method_class* CgenClassTable::find_method(Symbol class_name, Symbol method_name) {
	
	for(List<CgenNode> *l=nds; l!=NULL; l=l->tl()) {
	  CgenNode *cur_node=l->hd();
	  if(cur_node->get_name()==class_name) {
		  while(true) {
			  for(int i=cur_node->features->first(); cur_node->features->more(i); i=cur_node->features->next(i)) {
				  Feature cur_feature=cur_node->features->nth(i);
				  if(cur_feature->is_method() && ((method_class*)cur_feature)->name==method_name) {
					  method_class* method=(method_class*)cur_feature;
					  method->set_enclosing_class((class__class*)cur_node);
					  return method;
				  }
			  }
			  cur_node=cur_node->get_parentnd();
		  }
	  }
	}
	return NULL;	//never reached
}

CgenNode* CgenClassTable::find_attr_enclosing_class(Symbol class_name, Symbol attr_name) {
	
	for(List<CgenNode> *l=nds; l!=NULL; l=l->tl()) {
		CgenNode *cur_node=l->hd();
		if(cur_node->get_name()==class_name) {
			while(true) {
				for(int i=cur_node->features->first(); cur_node->features->more(i); i=cur_node->features->next(i)) {
					Feature cur_feature=cur_node->features->nth(i);
					if(cur_feature->is_attr() && ((attr_class*)cur_feature)->name==attr_name)
						return cur_node;
				}
				cur_node=cur_node->get_parentnd();
			}
		}
	}
	return NULL;	//never reached
}

void CgenClassTable::emit_method_name(Symbol class_name, Symbol method_name) {
	str<<"@_ZN"<<class_name->get_len()<<class_name<<method_name->get_len()<<method_name;
}

void CgenClassTable::emit_constructor_name(Symbol class_name) {
	str<<"@_ZN"<<class_name->get_len()<<class_name<<"C2Ev";
}

void CgenClassTable::emit_method_call(Symbol class_name, Symbol method_name) {
	method_class* method=find_method(class_name, method_name);
	str<<"\tcall void ";
	emit_method_name(method->get_enclosing_class()->get_name(), method->name);
	str<<"(";
	//TODO: write return and this arguments
	str<<")\n";
}

void CgenClassTable::emit_class_name(Symbol name) {
	str<<"%class."<<name->get_string();
}

void CgenClassTable::emit_class_declaration(CgenNode *class_node) {
	emit_class_name(class_node->get_name());
	str<<" = type { ";
	
	//get parent name
	emit_class_name(class_node->get_parentnd()->get_name());
	for(int i=class_node->features->first();class_node->features->more(i); i=class_node->features->next(i)) {
		Feature f=class_node->features->nth(i);
		if(f->is_attr()) {
			str<<", ";
			emit_class_name(((attr_class*)f)->get_type_decl());
			str<<"*";
		}
	}
	str<<" }\n";
}

void CgenClassTable::emit_main_method() {
	str<<"\ndefine i32 @main() {\n";
	str<<"\t%1 = call i8* @_Znwm(i64 "<<get_class_size(Main)<<")\n";
	str<<"\t%2 = bitcast i8* %1 to ";
	emit_class_name(Main);
	str<<"*\n";
	
	method_class* method=find_method(Main, main_meth);

	str<<"\tcall void ";
	emit_constructor_name(Main);
	str<<"(";
	emit_class_name(Main);
	str<<"* %2)\n";

	str<<"\t%3 = call ";
	emit_class_name(method->return_type);
	str<<"* ";
	emit_method_name(method->get_enclosing_class()->get_name(), method->name);
	str<<"(";
	
	emit_class_name(Main);
	str<<"* %2";
	
	str<<")\n";
	str<<"\t"<<RET<<" i32 0\n";
	str<<"}\n";
}

void CgenClassTable::emit_method_definition(Symbol class_name, method_class* method) {
	str<<"\ndefine linkonce_odr ";
	emit_class_name(method->return_type);
	str<<"* ";
	emit_method_name(class_name, method->name);
	str<<"(";
	
	//this
	emit_class_name(class_name);
	str<<"* "<<THIS;
	
	for(int i=method->formals->first(); method->formals->more(i); i=method->formals->next(i)) {
		formal_class *formal=(formal_class*)method->formals->nth(i);
		str<<", ";
		emit_class_name(formal->type_decl);
		str<<"* byval align 8 %"<<formal->name;
	}
	
	
	str<<") align 2 {\n";
	reset_cur_register();
	
	//get all formals into temp registers
	for(int i=method->formals->first(); method->formals->more(i); i=method->formals->next(i)) {
		formal_class *formal=(formal_class*)method->formals->nth(i);
		str<<"\t%"<<new_reg()<<" = bitcast ";
		emit_class_name(formal->type_decl);
		str<<"* %"<<formal->name<<" to ";
		emit_class_name(formal->type_decl);
		str<<"*\n";
		
		object_reg_map.push_back(std::make_pair(formal->name, last_reg()));
	}
	
	method->expr->code(str);
	
	
	reg last_result=last_reg(), converted_result=new_reg();
	str<<"\t%"<<converted_result<<" = bitcast ";
	emit_class_name(method->expr->get_type()!=SELF_TYPE?method->expr->get_type():class_name);
	str<<"* %"<<last_result<<" to ";
	emit_class_name(method->return_type!=SELF_TYPE?method->return_type:class_name);
	str<<"*\n";
	
	str<<"\t"<<RET<<" ";
	emit_class_name(method->return_type);
	str<<"* %"<<converted_result<<"\n";
	str<<"}\n";
	
	for(int i=method->formals->first(); method->formals->more(i); i=method->formals->next(i))
		object_reg_map.pop_back();
}

void CgenClassTable::emit_methods_definitions(CgenNode *class_node) {
	for(int i=class_node->features->first();class_node->features->more(i); i=class_node->features->next(i)) {
		Feature f=class_node->features->nth(i);
		if(f->is_method()) {
			cur_method=(method_class*)f;
			emit_method_definition(class_node->get_name(), (method_class*)f);
		}
	}
}

void CgenClassTable::emit_basic_methods() {
	
	reg val_ptr, val;
	
	//IO.out_int
	{
	reset_cur_register();
	str<<"\ndefine linkonce_odr ";
	emit_class_name(IO);
	str<<"* ";
	emit_method_name(IO, out_int);
	str<<"(";
	emit_class_name(IO);
	str<<"* %this, ";
	emit_class_name(Int);
	str<<"* %i) align 2 {\n";
	
	str<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %i, i32 0, i32 1\n";
	
	str<<"\t%"<<(val=new_reg())<<" = load i32* %"<<val_ptr<<", align 4\n";
	
	str<<"\t%"<<new_reg()<<" = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str_int, i32 0, i32 0), i32 %"<<val<<")\n";
	
	str<<"\tret ";
	emit_class_name(IO);
	str<<"* %this\n";
	
	str<<"}\n";
	}
	
	//IO.out_string
	{
	reset_cur_register();
	str<<"\ndefine linkonce_odr ";
	emit_class_name(IO);
	str<<"* ";
	emit_method_name(IO, out_string);
	str<<"(";
	emit_class_name(IO);
	str<<"* %this, ";
	emit_class_name(Str);
	str<<"* %s) align 2 {\n";
	
	str<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %s, i32 0, i32 2\n";
	
	str<<"\t%"<<(val=new_reg())<<" = load i8** %"<<val_ptr<<", align 8\n";
	
	str<<"\t%"<<new_reg()<<" = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str_string, i32 0, i32 0), i8* %"<<val<<")\n";
	
	str<<"\tret ";
	emit_class_name(IO);
	str<<"* %this\n";
	
	str<<"}\n";
	}
	
	//IO.in_int
	{
	reset_cur_register();
	str<<"\ndefine linkonce_odr ";
	emit_class_name(Int);
	str<<"* ";
	emit_method_name(IO, in_int);
	str<<"(";
	emit_class_name(IO);
	str<<"* %this) align 2 {\n";
	
	reg heap_obj, new_obj, new_val_ptr, new_obj_ptr, final_res_ptr, final_res;
	
	str<<"\t%"<<(heap_obj=new_reg())<<" = call noalias i8* @_Znwm(i64 "<<get_class_size(Int)<<")\n";
	
	str<<"\t%"<<(new_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	emit_class_name(Int);
	str<<"*\n";
	
	str<<"\t%"<<(new_val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %"<<new_obj<<", i32 0, i32 1\n";
	
	str<<"\t%"<<new_reg()<<" = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str_int, i32 0, i32 0), i32* %"<<new_val_ptr<<")\n";
	
	str<<"\tret ";
	emit_class_name(Int);
	str<<"* %"<<new_obj<<"\n";
	
	str<<"}\n";
	}
	
	//IO.in_string
	{
	reset_cur_register();
	str<<"\ndefine linkonce_odr ";
	emit_class_name(Str);
	str<<"* ";
	emit_method_name(IO, in_string);
	str<<"(";
	emit_class_name(IO);
	str<<"* %this) align 2 {\n";
	
	reg in_string, in_size_32_ptr, in_size_32_val, in_size_32_val_inc, in_size_64, heap_string, heap_obj, heap_string_obj, heap_string_ptr;
	
	str<<"\t%"<<(in_string=new_reg())<<" = alloca i8, align 8\n";
	
	str<<"\t%"<<(in_size_32_ptr=new_reg())<<" = alloca i32, align 8\n";
	
	str<<"\t%"<<new_reg()<<" = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([5 x i8]* @.str_string_in, i32 0, i32 0), i8* %"<<in_string<<", i32* %"<<in_size_32_ptr<<")\n";
	
	str<<"\t%"<<(in_size_32_val=new_reg())<<" = load i32* %"<<in_size_32_ptr<<", align 4\n";
	
	str<<"\t%"<<(in_size_32_val_inc=new_reg())<<" = add nsw i32 %"<<in_size_32_val<<", 1\n";
	
	str<<"\t%"<<(in_size_64=new_reg())<<" = zext i32 %"<<in_size_32_val_inc<<" to i64\n";
	
	str<<"\t%"<<(heap_string=new_reg())<<" = call noalias i8* @_Znwm(i64 %"<<in_size_64<<")\n";
	
	str<<"\tcall void @llvm.memcpy.p0i8.p0i8.i64(i8* %"<<heap_string<<", i8* %"<<in_string<<", i64 %"<<in_size_64<<", i32 1, i1 false)\n";
	
	str<<"\t%"<<(heap_obj=new_reg())<<" = call noalias i8* @_Znwm(i64 "<<get_class_size(Str)<<")\n";
	
	str<<"\t%"<<(heap_string_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	emit_class_name(Str);
	str<<"*\n";
	
	reg heap_len_obj, heap_len_val, str_len_obj_ptr;
	str<<"\t%"<<(heap_obj=new_reg())<<" = call noalias i8* @_Znwm(i64 "<<get_class_size(Int)<<")\n";
	
	str<<"\t%"<<(heap_len_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	emit_class_name(Int);
	str<<"*\n";
	
	str<<"\t%"<<(heap_len_val=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %"<<heap_len_obj<<", i32 0, i32 1\n";
	
	str<<"\tstore i32 %"<<in_size_32_val<<", i32* %"<<heap_len_val<<"\n";
	
	str<<"\t%"<<(str_len_obj_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %"<<heap_string_obj<<", i32 0, i32 1\n";
	
	str<<"\tstore ";
	emit_class_name(Int);
	str<<"* %"<<heap_len_obj<<", ";
	emit_class_name(Int);
	str<<"** %"<<str_len_obj_ptr<<"\n";
	
	str<<"\t%"<<(heap_string_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %"<<heap_string_obj<<", i32 0, i32 2\n";
	
	str<<"\tstore i8* %"<<heap_string<<", i8** %"<<heap_string_ptr<<", align 8\n";
	
	str<<"\tret ";
	emit_class_name(Str);
	str<<"* %"<<heap_string_obj<<"\n";
	
	str<<"}\n";
	}
	
	//String.length()
	{
	reset_cur_register();
	str<<"\ndefine linkonce_odr ";
	emit_class_name(Int);
	str<<"* ";
	emit_method_name(Str, length);
	str<<"(";
	emit_class_name(Str);
	str<<"* %this) align 2 {\n";
	
	reg len_obj_ptr, res_obj;
	str<<"\t%"<<(len_obj_ptr=new_reg())<<" = getelementptr ";
	emit_class_name(Str);
	str<<"* %this, i32 0, i32 1\n";
	
	//load the Int* pointer into the last register
	str<<"\t%"<<(res_obj=new_reg())<<" = load ";
	emit_class_name(Int);
	str<<"** %"<<len_obj_ptr<<"\n";
	 
	str<<"\tret ";
	emit_class_name(Int);
	str<<"* %"<<res_obj<<"\n";
	
	str<<"}\n";
	}
	
	//String.concat()
	{
	reset_cur_register();
	str<<"\ndefine linkonce_odr ";
	emit_class_name(Str);
	str<<"* ";
	emit_method_name(Str, concat);
	str<<"(";
	emit_class_name(Str);
	str<<"* %this, ";
	emit_class_name(Str);
	str<<"* %s) align 2 {\n";
	
	reg len1_obj, len1_ptr, len1, len2_obj, len2_ptr, len2, final_len, final_len_inc, val1_ptr, val1, val2_ptr, val2;
	
	str<<"\t%"<<(len1_obj=new_reg())<<" = call ";
	emit_class_name(Int);
	str<<"* ";
	emit_method_name(Str, length);
	str<<"(";
	emit_class_name(Str);
	str<<"* %this)\n";
	
	str<<"\t%"<<(len1_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %"<<len1_obj<<", i32 0, i32 1\n";
	
	str<<"\t%"<<(len1=new_reg())<<" = load i32* %"<<len1_ptr<<"\n";
	
	str<<"\t%"<<(len2_obj=new_reg())<<" = call ";
	emit_class_name(Int);
	str<<"* ";
	emit_method_name(Str, length);
	str<<"(";
	emit_class_name(Str);
	str<<"* %s)\n";
	
	str<<"\t%"<<(len2_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %"<<len2_obj<<", i32 0, i32 1\n";
	
	str<<"\t%"<<(len2=new_reg())<<" = load i32* %"<<len2_ptr<<"\n";
	
	str<<"\t%"<<(final_len=new_reg())<<" = add nsw i32 %"<<len1<<", %"<<len2<<"\n";
	
	reg final_len_heap, final_len_obj, final_len_val_ptr;
	
	str<<"\t%"<<(final_len_heap=new_reg())<<" = call i8* @_Znwm(i64 "<<get_class_size(Int)<<")\n";
	str<<"\t%"<<(final_len_obj=new_reg())<<" = bitcast i8* %"<<final_len_heap<<" to ";
	emit_class_name(Int);
	str<<"*\n";
	
	str<<"\t%"<<(final_len_val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %"<<final_len_obj<<", i32 0, i32 1\n";
	
	str<<"\tstore i32 %"<<final_len<<", i32* %"<<final_len_val_ptr<<"\n";
	
	//creating final String obj on heap
	reg res_heap, res_obj, res_len_ptr, res_val_ptr;
	
	str<<"\t%"<<(res_heap=new_reg())<<" = call i8* @_Znwm(i64 "<<get_class_size(Str)<<")\n";
	str<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<res_heap<<" to ";
	emit_class_name(Str);
	str<<"*\n";
	
	str<<"\t%"<<(res_len_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	str<<"\tstore ";
	emit_class_name(Int);
	str<<"* %"<<final_len_obj<<", ";
	emit_class_name(Int);
	str<<"** %"<<res_len_ptr<<"\n";
	
	str<<"\t%"<<(res_val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %"<<res_obj<<", i32 0, i32 2\n";
	
	//final length for allocation
	str<<"\t%"<<(final_len_inc=new_reg())<<" = add nsw i32 %"<<final_len<<", 1\n";
	reg temp=final_len_inc;
	str<<"\t%"<<(final_len_inc=new_reg())<<" = zext i32 %"<<temp<<" to i64\n";
	
	reg res_val;
	str<<"\t%"<<(res_val=new_reg())<<" = call i8* @_Znwm(i64 %"<<final_len_inc<<")\n";
	str<<"\tstore i8* %"<<res_val<<", i8** %"<<res_val_ptr<<"\n";
	
	str<<"\t%"<<(val1_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %this, i32 0, i32 2\n";
	str<<"\t%"<<(val1=new_reg())<<" = load i8** %"<<val1_ptr<<"\n";
	
	str<<"\t%"<<(val2_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %s, i32 0, i32 2\n";
	str<<"\t%"<<(val2=new_reg())<<" = load i8** %"<<val2_ptr<<"\n";
	
	str<<"\t%"<<new_reg()<<" = call i8* @strcpy(i8* %"<<res_val<<", i8* %"<<val1<<")\n";
	str<<"\t%"<<new_reg()<<" = call i8* @strcat(i8* %"<<res_val<<", i8* %"<<val2<<")\n";
	
	str<<"\tret ";
	emit_class_name(Str);
	str<<"* %"<<res_obj<<"\n";
	
	str<<"}\n";
	}

	//Object.abort()
	{
	str<<"\ndefine linkonce_odr ";
	emit_class_name(Object);
	str<<"* ";
	emit_method_name(Object, cool_abort);
	str<<"(";
	emit_class_name(Object);
	str<<"* %this) align 2 {\n";
	
	str<<"\tcall void @exit(i32 0)";
	
	str<<"\tunreachable\n}\n";
	}

	//Object.copy()
	{
	
	}
}

void CgenClassTable::emit_constructor(CgenNode *class_node) {
	str<<"define linkonce_odr void ";
	emit_constructor_name(class_node->get_name());
	str<<"(";
	emit_class_name(class_node->get_name());
	str<<"* %this) unnamed_addr align 2 {\n";
	
	reset_cur_register();
	reg obj_ptr, this_val_ptr, parent_obj;
	
	str<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
	emit_class_name(class_node->get_name());
	str<<"*, align 8\n";
	
	str<<"\tstore ";
	emit_class_name(class_node->get_name());
	str<<"* %this, ";
	emit_class_name(class_node->get_name());
	str<<"** %"<<obj_ptr<<", align 8\n";
	
	str<<"\t%"<<(this_val_ptr=new_reg())<<" = load ";
	emit_class_name(class_node->get_name());;
	str<<"** %"<<obj_ptr<<"\n";
	
	//convert to parent and call its constructor
	str<<"\t%"<<(parent_obj=new_reg())<<" = bitcast ";
	emit_class_name(class_node->get_name());
	str<<"* %"<<this_val_ptr<<" to ";
	emit_class_name(class_node->get_parentnd()->get_name());
	str<<"*\n";
	
	str<<"\tcall void ";
	emit_constructor_name(class_node->get_parentnd()->get_name());
	str<<"(";
	emit_class_name(class_node->get_parentnd()->get_name());
	str<<"* %"<<parent_obj<<")\n";
	
	
	//iterate over all features and call constructors for each attribute
	Features features=class_node->features;
	int index;
	for(int i=features->first(), index=1; features->more(i); i=features->next(i), index++) {
		if(!features->nth(i)->is_attr())
			continue;
		
		attr_class* cur_attr=(attr_class*)features->nth(i);
		
		reg cur_attr_ptr=new_reg();
		str<<"\t%"<<cur_attr_ptr<<" = getelementptr inbounds ";
		emit_class_name(class_node->get_name());
		str<<"* %"<<this_val_ptr<<", i32 0, i32 "<<index<<"\n";
		
		if(cur_attr->init->get_type()!=NULL) { //if init is given
			cur_attr->init->code(str);
			
			reg init_val=last_reg(), init_casted_val;
			
			str<<"\t%"<<(init_casted_val=new_reg())<<" = bitcast ";
			emit_class_name(cur_attr->init->get_type());
			str<<"* %"<<init_val<<" to ";
			emit_class_name(cur_attr->get_type_decl());
			str<<"*\n";
			
			//store casted last reg value into this attribute's pointer
			str<<"\tstore ";
			emit_class_name(cur_attr->get_type_decl());
			str<<"* %"<<init_casted_val<<", ";
			emit_class_name(cur_attr->get_type_decl());
			str<<"** %"<<cur_attr_ptr<<", align 8\n";
		} else {	//if no init is given
			if(cur_attr->get_type_decl()==Int || cur_attr->get_type_decl()==Bool || cur_attr->get_type_decl()==Str) {
				str<<"\t%"<<new_reg()<<" = load ";
				emit_class_name(cur_attr->get_type_decl());
				str<<"** %"<<cur_attr_ptr<<", align 8\n";
				
				str<<"\tcall void ";
				emit_constructor_name(cur_attr->get_type_decl());
				str<<"(";
				emit_class_name(cur_attr->get_type_decl());
				str<<"* %"<<last_reg()<<")\n";
			} else {
				str<<"\tstore ";
				emit_class_name(cur_attr->get_type_decl());
				str<<"* null, ";
				emit_class_name(cur_attr->get_type_decl());
				str<<"** %"<<cur_attr_ptr<<", align 8\n";
			}
		}
	}
	
	str<<"\tret void\n}\n\n";
}

void CgenClassTable::emit_basic_constructors() {
	
	reg obj_ptr, this_val_ptr, parent_obj, val_ptr;
	
	//Object class
	str<<"define linkonce_odr void ";
	emit_constructor_name(Object);
	str<<"(";
	emit_class_name(Object);
	str<<"* %this) unnamed_addr align 2 {\n\tret void\n}\n";
	
	//IO class
	reset_cur_register();
	str<<"define linkonce_odr void ";
	emit_constructor_name(IO);
	str<<"(";
	emit_class_name(IO);
	str<<"* %this) unnamed_addr align 2 {\n";
	
	str<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
	emit_class_name(IO);
	str<<"*, align 8\n";
	
	str<<"\tstore ";
	emit_class_name(IO);
	str<<"* %this, ";
	emit_class_name(IO);
	str<<"** %"<<obj_ptr<<", align 8\n";
	
	str<<"\t%"<<(this_val_ptr=new_reg())<<" = load ";
	emit_class_name(IO);;
	str<<"** %"<<obj_ptr<<"\n";
	
	//convert to parent and call its constructor
	str<<"\t%"<<(parent_obj=new_reg())<<" = bitcast ";
	emit_class_name(IO);
	str<<"* %"<<this_val_ptr<<" to ";
	emit_class_name(Object);
	str<<"*\n";
	
	str<<"\tcall void ";
	emit_constructor_name(Object);
	str<<"(";
	emit_class_name(Object);
	str<<"* %"<<parent_obj<<")\n";

	str<<"\tret void\n}\n";
	
	//Int class
	reset_cur_register();
	str<<"define linkonce_odr void ";
	emit_constructor_name(Int);
	str<<"(";
	emit_class_name(Int);
	str<<"* %this) unnamed_addr align 2 {\n";
	
	str<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
	emit_class_name(Int);
	str<<"*, align 8\n";
	
	str<<"\tstore ";
	emit_class_name(Int);
	str<<"* %this, ";
	emit_class_name(Int);
	str<<"** %"<<obj_ptr<<", align 8\n";
	
	str<<"\t%"<<(this_val_ptr=new_reg())<<" = load ";
	emit_class_name(Int);;
	str<<"** %"<<obj_ptr<<"\n";
	
	//convert to parent and call its constructor
	str<<"\t%"<<(parent_obj=new_reg())<<" = bitcast ";
	emit_class_name(Int);
	str<<"* %"<<this_val_ptr<<" to ";
	emit_class_name(Object);
	str<<"*\n";
	
	str<<"\tcall void ";
	emit_constructor_name(Object);
	str<<"(";
	emit_class_name(Object);
	str<<"* %"<<parent_obj<<")\n";
	
	str<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Int);
	str<<"* %"<<this_val_ptr<<", i32 0, i32 1\n";
	
	str<<"\tstore i32 0, i32* %"<<val_ptr<<", align 4\n";
	
	str<<"\tret void\n}\n";
	
	//Bool class
	reset_cur_register();
	str<<"define linkonce_odr void ";
	emit_constructor_name(Bool);
	str<<"(";
	emit_class_name(Bool);
	str<<"* %this) unnamed_addr align 2 {\n";
	
	str<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
	emit_class_name(Bool);
	str<<"*, align 8\n";
	
	str<<"\tstore ";
	emit_class_name(Bool);
	str<<"* %this, ";
	emit_class_name(Bool);
	str<<"** %"<<obj_ptr<<", align 8\n";
	
	str<<"\t%"<<(this_val_ptr=new_reg())<<" = load ";
	emit_class_name(Bool);;
	str<<"** %"<<obj_ptr<<"\n";
	
	//convert to parent and call its constructor
	str<<"\t%"<<(parent_obj=new_reg())<<" = bitcast ";
	emit_class_name(Bool);
	str<<"* %"<<this_val_ptr<<" to ";
	emit_class_name(Object);
	str<<"*\n";
	
	str<<"\tcall void ";
	emit_constructor_name(Object);
	str<<"(";
	emit_class_name(Object);
	str<<"* %"<<parent_obj<<")\n";
	
	str<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Bool);
	str<<"* %"<<this_val_ptr<<", i32 0, i32 1\n";
	
	str<<"\tstore i8 0, i8* %"<<val_ptr<<", align 1\n";
	
	str<<"\tret void\n}\n";
	
	//String class
	reset_cur_register();
	str<<"define linkonce_odr void ";
	emit_constructor_name(Str);
	str<<"(";
	emit_class_name(Str);
	str<<"* %this) unnamed_addr align 2 {\n";
	
	str<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
	emit_class_name(Str);
	str<<"*, align 8\n";
	
	str<<"\tstore ";
	emit_class_name(Str);
	str<<"* %this, ";
	emit_class_name(Str);
	str<<"** %"<<obj_ptr<<", align 8\n";
	
	str<<"\t%"<<(this_val_ptr=new_reg())<<" = load ";
	emit_class_name(Str);;
	str<<"** %"<<obj_ptr<<"\n";
	
	//convert to parent and call its constructor
	str<<"\t%"<<(parent_obj=new_reg())<<" = bitcast ";
	emit_class_name(Str);
	str<<"* %"<<this_val_ptr<<" to ";
	emit_class_name(Object);
	str<<"*\n";
	
	str<<"\tcall void ";
	emit_constructor_name(Object);
	str<<"(";
	emit_class_name(Object);
	str<<"* %"<<parent_obj<<")\n";
	
	str<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %"<<this_val_ptr<<", i32 0, i32 1\n";
	
	reg heap_obj, casted_heap_obj;
	str<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
	str<<"\t%"<<(casted_heap_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Int);
	str<<"*\n";
	
	str<<"\tcall void ";
	emit_constructor_name(Int);
	str<<"(";
	emit_class_name(Int);
	str<<"* %"<<casted_heap_obj<<")\n";
	
	str<<"\tstore ";
	cgct->emit_class_name(Int);
	str<<"* %"<<casted_heap_obj<<", ";
	cgct->emit_class_name(Int);
	str<<"** %"<<val_ptr<<"\n";
	
	str<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	emit_class_name(Str);
	str<<"* %"<<this_val_ptr<<", i32 0, i32 2\n";
	
	reg str_ptr;
	
	str<<"\t%"<<(str_ptr=new_reg())<<" = call i8* @_Znwm(i64 1)\n";
	
	str<<"\tstore i8* %"<<str_ptr<<", i8** %"<<val_ptr<<"\n";
	
	str<<"\tcall i8* @strcpy(i8* %"<<str_ptr<<", i8* getelementptr inbounds ([1 x i8]* @.str0, i32 0, i32 0))\n";
	
	str<<"\tret void\n}\n";
	
}

void CgenClassTable::code()
{
  if(cgen_debug)	cout<<"coding llvm data"<<endl;
  str<<"target datalayout = \"e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32\"\ntarget triple = \"i386-pc-linux-gnu\"\n\n";
  
  for(List<CgenNode> *l=nds; l!=NULL; l=l->tl()) {
	  CgenNode *cur_node=l->hd();
	  if(!cur_node->basic())
		emit_class_declaration(cur_node);
  }
  
  //defining basic types
  str<<"%class.String = type { %class.Object, %class.Int*, i8* }\n";
  str<<"%class.Bool = type { %class.Object, i8 }\n";
  str<<"%class.Int = type { %class.Object, i32 }\n";
  str<<"%class.IO = type { %class.Object }\n";
  str<<"%class.Object = type { i8 }\n\n";
  
  //declare strings for printf
  str<<"@.str_int = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1\n";
  str<<"@.str_string = private unnamed_addr constant [3 x i8] c\"%s\\00\", align 1\n";
  str<<"@.str_string_in = private unnamed_addr constant [5 x i8] c\"%s%n\\00\", align 1\n";
  
  
  //declare empty string, for use in string constructor
  str<<"@.str0 = private unnamed_addr constant [1 x i8] c\"\\00\", align 1\n";
  
  //get all strings from the string table into the map
  for(int i=stringtable.next(stringtable.first()); stringtable.more(i); i=stringtable.next(i)) {
	  StringEntry *cur_string=stringtable.lookup(i);
	  strings.insert(std::pair<StringEntry*, int>(cur_string, i));
	  str<<"@.str"<<i<<" = private unnamed_addr constant ["<<(cur_string->get_len()+1)<<" x i8] c\"";
	  for(int j=0;j<cur_string->get_len();j++)
		if(cur_string->get_string()[j]=='\"')
			str<<"\\22";
		else
			str<<cur_string->get_string()[j];
	  str<<"\\00\", align 1\n";
  }
  
  str<<"\n";
  
  //generate main function to call the Main.main() method
  emit_main_method();
  
  //generate all functions
  for(List<CgenNode> *l=nds; l!=NULL; l=l->tl()) {
	  CgenNode *cur_node=l->hd();
	  if(!cur_node->basic())
		emit_methods_definitions(cur_node);
  }
  
  emit_basic_methods();
  
  //generate all constructors
  for(List<CgenNode> *l=nds; l!=NULL; l=l->tl()) {
	  CgenNode *cur_node=l->hd();
	  if(!cur_node->basic())
		emit_constructor(cur_node);
  }
  
  emit_basic_constructors();
  
  //generate inbuilt declaration
  str<<"\n\n";
  str<<"declare noalias i8* @_Znwm(i64)\n";
  str<<"declare i8* @strcpy(i8*, i8*)\n";
  str<<"declare i32 @strcmp(i8*, i8*)\n";
  str<<"declare i8* @strcat(i8*, i8*)\n";
  str<<"declare i64 @strlen(i8*)\n";
  str<<"declare i32 @printf(i8*, ...)\n";
  str<<"declare i32 @scanf(i8*, ...)\n";
  str<<"declare void @exit(i32)\n";
  str<<"declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1)\n";
  /*
  if (cgen_debug) cout << "coding global data" << endl;
  code_global_data();

  if (cgen_debug) cout << "choosing gc" << endl;
  code_select_gc();

  if (cgen_debug) cout << "coding constants" << endl;
  code_constants();

//                 Add your code to emit
//                   - prototype objects
//                   - class_nameTab
//                   - dispatch tables
//

  if (cgen_debug) cout << "coding global text" << endl;
  code_global_text();

//                 Add your code to emit
//                   - object initializer
//                   - the class methods
//                   - etc...
*/
}


CgenNodeP CgenClassTable::root()
{
   return probe(Object);
}


///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) :
   class__class((const class__class &) *nd),
   parentnd(NULL),
   children(NULL),
   basic_status(bstatus)
{ 
   stringtable.add_string(name->get_string());          // Add class name to string table
}


//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************

void assign_class::code(ostream &s) {
	
	expr->code(s);
	
	reg expr_res=last_reg(), expr_casted_res;
	s<<"\t%"<<(expr_casted_res=new_reg())<<" = bitcast ";
	cgct->emit_class_name(expr->get_type());
	s<<"* %"<<expr_res<<" to ";
	cgct->emit_class_name(get_type());
	s<<"*\n";
	
	//update object_reg_map, if present
	for(int i=cgct->object_reg_map.size()-1; i>=0; i--) {
		if(cgct->object_reg_map[i].first==name) {
			reg new_val;
			s<<"\t%"<<(new_val=new_reg())<<" = load ";
			cgct->emit_class_name(get_type());
			s<<"* %"<<expr_casted_res<<"\n";
			
			s<<"\tstore ";
			cgct->emit_class_name(get_type());
			s<<" %"<<new_val<<", ";
			cgct->emit_class_name(get_type());
			s<<"* %"<<cgct->object_reg_map[i].second<<"\n";
			
			s<<"\t%"<<new_reg()<<" = bitcast ";
			cgct->emit_class_name(get_type());
			s<<"* %"<<expr_casted_res<<" to ";
			cgct->emit_class_name(get_type());
			s<<"*\n";
			
			return;
		}
	}
	
	//search in class hierarchy
	CgenNode *enclosing_class=cgct->find_attr_enclosing_class(cgct->cur_method->get_enclosing_class()->get_name(), name);
	
	int i;
	Features features=enclosing_class->features;
	for(i=features->first(); features->more(i); i=features->next(i))
		if(features->nth(i)->is_attr() && ((attr_class*)features->nth(i))->name==name)
			break;
	
	reg casted_this, val_ptr;
	
	s<<"\t%"<<(casted_this=new_reg())<<" = bitcast ";
	cgct->emit_class_name(cgct->cur_method->get_enclosing_class()->get_name());
	s<<"* %this to ";
	cgct->emit_class_name(enclosing_class->get_name());
	s<<"*\n";
	
	s<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(enclosing_class->get_name());
	s<<"* %"<<casted_this<<", i32 0, i32 "<<(i+1)<<"\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(((attr_class*)features->nth(i))->type_decl);
	s<<"* %"<<expr_casted_res<<", ";
	cgct->emit_class_name(((attr_class*)features->nth(i))->type_decl);
	s<<"** %"<<val_ptr<<", align 8\n";
	
	s<<"\t%"<<new_reg()<<" = load ";
	cgct->emit_class_name(get_type());
	s<<"** %"<<val_ptr<<", align 8\n";
}

void static_dispatch_class::code(ostream &s) {
	method_class *method=cgct->find_method(type_name, name);
	
	expr->code(s);
	reg expr_last=last_reg(), expr_reg;
	
	s<<"\t%"<<(expr_reg=new_reg())<<" = bitcast ";
	cgct->emit_class_name(expr->get_type());
	s<<"* %"<<expr_last<<" to ";
	cgct->emit_class_name(method->get_enclosing_class()->get_name());
	s<<"*\n";
	
	std::vector<reg> actuals_reg;
	
	//evaluate each actual and push return register in the actuals_reg vector
	for(int i=actual->first(); actual->more(i); i=actual->next(i)) {
		actual->nth(i)->code(s);
		actuals_reg.push_back(last_reg());
	}
	
	reg final_res=new_reg();
	
	s<<"\t%"<<final_res<<" = call ";
	cgct->emit_class_name(method->return_type!=SELF_TYPE?method->return_type:method->get_enclosing_class()->get_name());
	s<<"* ";
	cgct->emit_method_name(method->get_enclosing_class()->get_name(), method->name);
	s<<"(";
	
	//emit 'this'
	cgct->emit_class_name(method->get_enclosing_class()->get_name());
	s<<"* %"<<expr_reg;
	
	//emit all actuals with their type
	for(int i=actual->first(); actual->more(i); i=actual->next(i)) {
		s<<", ";
		cgct->emit_class_name(actual->nth(i)->get_type());
		s<<"* %"<<actuals_reg[i];
	}
	
	s<<")\n";
	
	if(method->return_type==SELF_TYPE) {
		s<<"\t%"<<new_reg()<<" = bitcast ";
		cgct->emit_class_name(method->get_enclosing_class()->get_name());
		s<<"* %"<<final_res<<" to ";
		cgct->emit_class_name(expr->get_type());
		s<<"*\n";
	}
}

void dispatch_class::code(ostream &s) {
	method_class *method=cgct->find_method(expr->get_type()!=SELF_TYPE?expr->get_type():cgct->cur_method->get_enclosing_class()->get_name(), name);
	
	expr->code(s);
	reg expr_last=last_reg(), expr_reg;

	s<<"\t%"<<(expr_reg=new_reg())<<" = bitcast ";
	cgct->emit_class_name(expr->get_type()!=SELF_TYPE?expr->get_type():cgct->cur_method->get_enclosing_class()->get_name());
	s<<"* %"<<expr_last<<" to ";
	cgct->emit_class_name(method->get_enclosing_class()->get_name());
	s<<"*\n";
	
	std::vector<reg> actuals_reg;
	
	//evaluate each actual and push return register in the actuals_reg vector
	for(int i=actual->first(); actual->more(i); i=actual->next(i)) {
		actual->nth(i)->code(s);
		actuals_reg.push_back(last_reg());
	}
	
	reg final_res=new_reg();
	
	s<<"\t%"<<final_res<<" = call ";
	cgct->emit_class_name(method->return_type!=SELF_TYPE?method->return_type:method->get_enclosing_class()->get_name());
	s<<"* ";
	cgct->emit_method_name(method->get_enclosing_class()->get_name(), method->name);
	s<<"(";
	
	//emit 'this'
	cgct->emit_class_name(method->get_enclosing_class()->get_name());
	s<<"* %"<<expr_reg;
	
	//emit all actuals with their type
	for(int i=actual->first(); actual->more(i); i=actual->next(i)) {
		s<<", ";
		cgct->emit_class_name(actual->nth(i)->get_type());
		s<<"* %"<<actuals_reg[i];
	}
	
	s<<")\n";
	
	if(method->return_type==SELF_TYPE) {
		s<<"\t%"<<new_reg()<<" = bitcast ";
		cgct->emit_class_name(method->get_enclosing_class()->get_name());
		s<<"* %"<<final_res<<" to ";
		cgct->emit_class_name(expr->get_type()!=SELF_TYPE?expr->get_type():cgct->cur_method->get_enclosing_class()->get_name());
		s<<"*\n";
	}
}

void cond_class::code(ostream &s) {
	
	//code predicate
	pred->code(s);
	
	//get predicate's Bool obj
	reg pred_obj=last_reg();
	
	//get Bool obj i1 value into reg <pred>
	reg bool_val_ptr, bool_val_i8, bool_val_i1;
	s<<"\t%"<<(bool_val_ptr=new_reg())<<" = getelementptr inbounds %class.Bool* %"<<pred_obj<<", i32 0, i32 1\n";
	s<<"\t%"<<(bool_val_i8=new_reg())<<" = load i8* %"<<bool_val_ptr<<", align 1\n";
	s<<"\t%"<<(bool_val_i1=new_reg())<<" = trunc i8 %"<<bool_val_i8<<" to i1\n";
	
	//create pointer for result of both branches
	s<<"\t%ifres"<<bool_val_i1<<" = alloca ";
	cgct->emit_class_name(get_type());
	s<<"*, align 8\n";
	
	//break on this boolean value to then<pred> and else<pred>
	s<<"\tbr i1 %"<<bool_val_i1<<", label %then"<<bool_val_i1<<", label %else"<<bool_val_i1<<"\n";
	
	//label:then<pred>
	s<<"then"<<bool_val_i1<<":\n";
	//code then_exp and store result into reg ifres<pred>
	then_exp->code(s);
	reg then_obj_ptr, then_obj_after_cast;
	then_obj_ptr=last_reg();
	s<<"\t%"<<(then_obj_after_cast=new_reg())<<" = bitcast ";
	cgct->emit_class_name(then_exp->get_type());
	s<<"* %"<<then_obj_ptr<<" to ";
	cgct->emit_class_name(get_type());
	s<<"*\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(get_type());
	s<<"* %"<<then_obj_after_cast<<", ";
	cgct->emit_class_name(get_type());
	s<<"** %ifres"<<bool_val_i1<<", align 8\n";
	
	//branch to fi<pred>
	s<<"\tbr label %fi"<<bool_val_i1<<"\n";
	
	//label:else<pred>
	s<<"else"<<bool_val_i1<<":\n";
	//code else_exp and store result into reg ifres<pred>
	else_exp->code(s);
	reg else_obj_ptr, else_obj_after_cast;
	else_obj_ptr=last_reg();
	s<<"\t%"<<(else_obj_after_cast=new_reg())<<" = bitcast ";
	cgct->emit_class_name(else_exp->get_type());
	s<<"* %"<<else_obj_ptr<<" to ";
	cgct->emit_class_name(get_type());
	s<<"*\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(get_type());
	s<<"* %"<<else_obj_after_cast<<", ";
	cgct->emit_class_name(get_type());
	s<<"** %ifres"<<bool_val_i1<<", align 8\n";
	
	//branch to fi<pred>
	s<<"\tbr label %fi"<<bool_val_i1<<"\n";
	
	//label:fi<pred>
	s<<"fi"<<bool_val_i1<<":\n";
	
	//bitcast ifres<pred> to same type and store in last register
	s<<"\t%"<<new_reg()<<" = load ";
	cgct->emit_class_name(get_type());
	s<<"** %ifres"<<bool_val_i1<<", align 8\n";
}

void loop_class::code(ostream &s) {
	reg pred_no=new_reg();
	
	//branch to label pred_no
	s<<"\tbr label %"<<pred_no<<"\n";
	
	//label pred_no
	s<<"; <label>:"<<pred_no<<"\n";
	//code predicate
	pred->code(s);
	
	//get predicate's Bool obj
	reg pred_obj=last_reg();
	
	//get Bool obj i1 value into reg <pred>
	reg bool_val_ptr, bool_val_i8, bool_val_i1;
	s<<"\t%"<<(bool_val_ptr=new_reg())<<" = getelementptr inbounds %class.Bool* %"<<pred_obj<<", i32 0, i32 1\n";
	s<<"\t%"<<(bool_val_i8=new_reg())<<" = load i8* %"<<bool_val_ptr<<", align 1\n";
	s<<"\t%"<<(bool_val_i1=new_reg())<<" = trunc i8 %"<<bool_val_i8<<" to i1\n";
	
	//branch to labels loop<pred_no> and pool<pred_no> based on the i1 value
	s<<"\tbr i1 %"<<bool_val_i1<<", label %loop"<<pred_no<<", label %pool"<<pred_no<<"\n";
	
	//label loop<pred_no>
	s<<"loop"<<pred_no<<":\n";
	
	//code body
	body->code(s);
	
	//branch to label pred_no
	s<<"\tbr label %"<<pred_no<<"\n";
	
	//label pool<pred_no>
	s<<"pool"<<pred_no<<":\n";
	
	s<<"\t%"<<new_reg()<<" = alloca ";
	cgct->emit_class_name(Object);
	s<<", align 4\n";
}

void typcase_class::code(ostream &s) {
}

void block_class::code(ostream &s) {
	//iterate over each expression in the block and code them
	for(int i=body->first(); body->more(i); i=body->next(i))
		body->nth(i)->code(s);
}

void let_class::code(ostream &s) {
	
	reg final_reg;
	
	if(init->get_type()!=NULL) { //if init is given
		
		init->code(s);
		
		reg init_val=last_reg(), init_casted_val;
		
		s<<"\t%"<<(init_casted_val=new_reg())<<" = bitcast ";
		cgct->emit_class_name(init->get_type());
		s<<"* %"<<init_val<<" to ";
		cgct->emit_class_name(type_decl);
		s<<"*\n";
		
		final_reg=init_casted_val;
	} else {	//if no init is given
		if(type_decl==Int || type_decl==Bool || type_decl==Str) {
			reg obj_ptr;
			s<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
			cgct->emit_class_name(type_decl);
			s<<", align 8\n";
			
			s<<"\tcall void ";
			cgct->emit_constructor_name(type_decl);
			s<<"(";
			cgct->emit_class_name(type_decl);
			s<<"* %"<<obj_ptr<<")\n";
			
			final_reg=obj_ptr;
			
		} else {
			
			reg obj_ptr_ptr, obj_ptr;
			
			s<<"\t%"<<(obj_ptr_ptr=new_reg())<<" = alloca ";
			cgct->emit_class_name(type_decl);
			s<<"*, align 8\n";
			
			s<<"\tstore ";
			cgct->emit_class_name(type_decl);
			s<<"* null, ";
			cgct->emit_class_name(type_decl);
			s<<"** %"<<obj_ptr_ptr<<", align 8\n";
			
			s<<"\t%"<<(obj_ptr=new_reg())<<" = load ";
			cgct->emit_class_name(type_decl);
			s<<"** %"<<obj_ptr_ptr<<", align 8\n";
			
			final_reg=obj_ptr;
		}
	}
	
	cgct->object_reg_map.push_back(std::make_pair(identifier, final_reg));
	
	body->code(s);
	
	cgct->object_reg_map.pop_back();
	
}

void plus_class::code(ostream &s) {
	
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	//code e2
	e2->code(s);
	
	//get register number of second 'y'
	reg y=last_reg();
	
	reg x_pointer, x_value, y_pointer, y_value, res_value, res_obj, res_pointer, res_obj_pointer, final_res;
	
	//get element pointer to value of first ('x') to 'y+1'
	s<<"\t%"<<(x_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<x<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+2'
	s<<"\t%"<<(x_value=new_reg())<<" = load i32* %"<<x_pointer<<", align 4\n";
	
	//get element pointer to value of second ('y') to 'y+3'
	s<<"\t%"<<(y_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<y<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+4'
	s<<"\t%"<<(y_value=new_reg())<<" = load i32* %"<<y_pointer<<", align 4\n";
	
	//add 'y+2' and 'y+4' and store it to 'y+5'
	s<<"\t%"<<(res_value=new_reg())<<" = add nsw i32 %"<<x_value<<", %"<<y_value<<"\n";
	
	//allocate memory to a new Int for sum at 'y+6'
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Int);
	s<<"*\n";
	
	//get element pointer to value of sum ('y+6') to 'y+7'
	s<<"\t%"<<(res_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//store 'y+5' to 'y+7'
	s<<"\tstore i32 %"<<(res_value)<<", i32* %"<<(res_pointer)<<", align 4\n";
	
	//copy 'y+6' to new Int (to get it to last register)
	
	//allocate a pointer and store address of 'y+6'
	s<<"\t%"<<(res_obj_pointer=new_reg())<<" = alloca ";
	cgct->emit_class_name(Int);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<", align 8\n";
	
	//store the value of x into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<"\n";
}

void sub_class::code(ostream &s) {
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	//code e2
	e2->code(s);
	
	//get register number of second 'y'
	reg y=last_reg();
	
	reg x_pointer, x_value, y_pointer, y_value, res_value, res_obj, res_pointer, res_obj_pointer, final_res;
	
	//get element pointer to value of first ('x') to 'y+1'
	s<<"\t%"<<(x_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<x<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+2'
	s<<"\t%"<<(x_value=new_reg())<<" = load i32* %"<<x_pointer<<", align 4\n";
	
	//get element pointer to value of second ('y') to 'y+3'
	s<<"\t%"<<(y_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<y<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+4'
	s<<"\t%"<<(y_value=new_reg())<<" = load i32* %"<<y_pointer<<", align 4\n";
	
	//add 'y+2' and 'y+4' and store it to 'y+5'
	s<<"\t%"<<(res_value=new_reg())<<" = sub nsw i32 %"<<x_value<<", %"<<y_value<<"\n";
	
	//allocate memory to a new Int for sum at 'y+6'
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Int);
	s<<"*\n";
	
	//get element pointer to value of sum ('y+6') to 'y+7'
	s<<"\t%"<<(res_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//store 'y+5' to 'y+7'
	s<<"\tstore i32 %"<<(res_value)<<", i32* %"<<(res_pointer)<<", align 4\n";
	
	//copy 'y+6' to new Int (to get it to last register)
	
	//allocate a pointer and store address of 'y+6'
	s<<"\t%"<<(res_obj_pointer=new_reg())<<" = alloca ";
	cgct->emit_class_name(Int);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<", align 8\n";
	
	//store the value of x into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<"\n";
}

void mul_class::code(ostream &s) {
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	//code e2
	e2->code(s);
	
	//get register number of second 'y'
	reg y=last_reg();
	
	reg x_pointer, x_value, y_pointer, y_value, res_value, res_obj, res_pointer, res_obj_pointer, final_res;
	
	//get element pointer to value of first ('x') to 'y+1'
	s<<"\t%"<<(x_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<x<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+2'
	s<<"\t%"<<(x_value=new_reg())<<" = load i32* %"<<x_pointer<<", align 4\n";
	
	//get element pointer to value of second ('y') to 'y+3'
	s<<"\t%"<<(y_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<y<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+4'
	s<<"\t%"<<(y_value=new_reg())<<" = load i32* %"<<y_pointer<<", align 4\n";
	
	//add 'y+2' and 'y+4' and store it to 'y+5'
	s<<"\t%"<<(res_value=new_reg())<<" = mul nsw i32 %"<<x_value<<", %"<<y_value<<"\n";
	
	//allocate memory to a new Int for sum at 'y+6'
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Int);
	s<<"*\n";
	
	//get element pointer to value of sum ('y+6') to 'y+7'
	s<<"\t%"<<(res_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//store 'y+5' to 'y+7'
	s<<"\tstore i32 %"<<(res_value)<<", i32* %"<<(res_pointer)<<", align 4\n";
	
	//copy 'y+6' to new Int (to get it to last register)
	
	//allocate a pointer and store address of 'y+6'
	s<<"\t%"<<(res_obj_pointer=new_reg())<<" = alloca ";
	cgct->emit_class_name(Int);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<", align 8\n";
	
	//store the value of x into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<"\n";
}

void divide_class::code(ostream &s) {
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	//code e2
	e2->code(s);
	
	//get register number of second 'y'
	reg y=last_reg();
	
	reg x_pointer, x_value, y_pointer, y_value, res_value, res_obj, res_pointer, res_obj_pointer, final_res;
	
	//get element pointer to value of first ('x') to 'y+1'
	s<<"\t%"<<(x_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<x<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+2'
	s<<"\t%"<<(x_value=new_reg())<<" = load i32* %"<<x_pointer<<", align 4\n";
	
	//get element pointer to value of second ('y') to 'y+3'
	s<<"\t%"<<(y_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<y<<", i32 0, i32 1\n";
	
	//load value from the pointer to 'y+4'
	s<<"\t%"<<(y_value=new_reg())<<" = load i32* %"<<y_pointer<<", align 4\n";
	
	//add 'y+2' and 'y+4' and store it to 'y+5'
	s<<"\t%"<<(res_value=new_reg())<<" = sdiv i32 %"<<x_value<<", %"<<y_value<<"\n";
	
	//allocate memory to a new Int for sum at 'y+6'
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Int);
	s<<"*\n";
	
	//get element pointer to value of sum ('y+6') to 'y+7'
	s<<"\t%"<<(res_pointer=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//store 'y+5' to 'y+7'
	s<<"\tstore i32 %"<<(res_value)<<", i32* %"<<(res_pointer)<<", align 4\n";
	
	//copy 'y+6' to new Int (to get it to last register)
	
	//allocate a pointer and store address of 'y+6'
	s<<"\t%"<<(res_obj_pointer=new_reg())<<" = alloca ";
	cgct->emit_class_name(Int);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<", align 8\n";
	
	//store the value of x into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_pointer<<"\n";
}

void neg_class::code(ostream &s) {
	reg given_obj, given_val_ptr, given_val, res_val, res_obj, res_val_ptr, res_obj_ptr, final_res;
	
	e1->code(s);
	
	given_obj=last_reg();
	
	s<<"\t%"<<(given_val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<given_obj<<", i32 0, i32 1\n";
	
	s<<"\t%"<<(given_val=new_reg())<<" = load i32* %"<<given_val_ptr<<", align 4\n";
	
	s<<"\t%"<<(res_val=new_reg())<<" = sub nsw i32 0, %"<<given_val<<"\n";
	
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Int);
	s<<"*\n";
	
	s<<"\t%"<<(res_val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	s<<"\tstore i32 %"<<res_val<<", i32* %"<<res_val_ptr<<", align 4\n";
	
	//copy the res_obj to last reg
	s<<"\t%"<<(res_obj_ptr=new_reg())<<" = alloca ";
	cgct->emit_class_name(Int);
	s<<"*, align 8\n";
	
	s<<"store ";
	cgct->emit_class_name(Int);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_ptr<<", align 8\n";
	
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Int);
	s<<"** %"<<res_obj_ptr<<"\n";
}

void lt_class::code(ostream &s) {
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	//code e2
	e2->code(s);
	
	//get register number of second 'y'
	reg y=last_reg();
	
	reg x_ptr, x_value, y_ptr, y_value, res_value, res_obj, res_ptr, converted_res_val, res_obj_ptr, final_res;
	
	//get element pointer to value of first obj
	s<<"\t%"<<(x_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<x<<", i32 0, i32 1\n";
	
	//load value from the pointer of first
	s<<"\t%"<<(x_value=new_reg())<<" = load i32* %"<<x_ptr<<", align 4\n";
	
	//get element pointer to value of second obj
	s<<"\t%"<<(y_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<y<<", i32 0, i32 1\n";
	
	//load value from the pointer of second
	s<<"\t%"<<(y_value=new_reg())<<" = load i32* %"<<y_ptr<<", align 4\n";
	
	//compare both values
	s<<"\t%"<<(res_value=new_reg())<<" = icmp slt i32 %"<<x_value<<", %"<<y_value<<"\n";
	
	//allocate memory to a new Bool for result
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Bool)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
	
	//get element pointer to value of result
	s<<"\t%"<<(res_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//convert i1 to i8
	s<<"\t%"<<(converted_res_val=new_reg())<<" = zext i1 %"<<res_value<<" to i8\n";
	
	//storec converted value to resulted
	s<<"\tstore i8 %"<<(converted_res_val)<<", i8* %"<<(res_ptr)<<", align 4\n";
	
	//copy final obj to last register
	
	//allocate a pointer and store address of final obj
	s<<"\t%"<<(res_obj_ptr=new_reg())<<" = alloca ";
	cgct->emit_class_name(Bool);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Bool);
	s<<"** %"<<res_obj_ptr<<", align 8\n";
	
	//store the value of result into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Bool);
	s<<"** %"<<res_obj_ptr<<"\n";
}

void eq_class::code(ostream &s) {
	reg e1_res, e2_res, comp_val, heap_obj, res_obj, res_val_ptr, converted_res_val;
	
	//code e1 and get res
	e1->code(s);
	e1_res=last_reg();
	
	//code e2 and get res
	e2->code(s);
	e2_res=last_reg();
	
	//check if basic and compare val if yes
	
	if(e1->get_type()==Int) {
		reg e1_val_ptr, e1_val, e2_val_ptr, e2_val;
		s<<"\t%"<<(e1_val_ptr=new_reg())<<" = getelementptr inbounds ";
		cgct->emit_class_name(Int);
		s<<"* %"<<e1_res<<", i32 0, i32 1\n";
		
		//load value from the pointer of first
		s<<"\t%"<<(e1_val=new_reg())<<" = load i32* %"<<e1_val_ptr<<", align 4\n";
		
		//get element pointer to value of second obj
		s<<"\t%"<<(e2_val_ptr=new_reg())<<" = getelementptr inbounds ";
		cgct->emit_class_name(Int);
		s<<"* %"<<e2_res<<", i32 0, i32 1\n";
		
		//load value from the pointer of second
		s<<"\t%"<<(e2_val=new_reg())<<" = load i32* %"<<e2_val_ptr<<", align 4\n";
		
		//compare both values
		s<<"\t%"<<(comp_val=new_reg())<<" = icmp eq i32 %"<<e1_val<<", %"<<e2_val<<"\n";
	} else if(e1->get_type()==Bool) {
		reg e1_val_ptr, e1_val, e2_val_ptr, e2_val;
		s<<"\t%"<<(e1_val_ptr=new_reg())<<" = getelementptr inbounds ";
		cgct->emit_class_name(Bool);
		s<<"* %"<<e1_res<<", i32 0, i32 1\n";
		
		//load value from the pointer of first
		s<<"\t%"<<(e1_val=new_reg())<<" = load i8* %"<<e1_val_ptr<<", align 1\n";
		
		//get element pointer to value of second obj
		s<<"\t%"<<(e2_val_ptr=new_reg())<<" = getelementptr inbounds ";
		cgct->emit_class_name(Bool);
		s<<"* %"<<e2_res<<", i32 0, i32 1\n";
		
		//load value from the pointer of second
		s<<"\t%"<<(e2_val=new_reg())<<" = load i8* %"<<e2_val_ptr<<", align 1\n";
		
		//compare both values
		s<<"\t%"<<(comp_val=new_reg())<<" = icmp eq i8 %"<<e1_val<<", %"<<e2_val<<"\n";
		
	} else if(e1->get_type()==Str) {
		reg e1_val_ptr, e1_val, e2_val_ptr, e2_val, strcmp_val;
		s<<"\t%"<<(e1_val_ptr=new_reg())<<" = getelementptr inbounds ";
		cgct->emit_class_name(Str);
		s<<"* %"<<e1_res<<", i32 0, i32 2\n";
		
		//load value from the pointer of first
		s<<"\t%"<<(e1_val=new_reg())<<" = load i8** %"<<e1_val_ptr<<", align 8\n";
		
		//get element pointer to value of second obj
		s<<"\t%"<<(e2_val_ptr=new_reg())<<" = getelementptr inbounds ";
		cgct->emit_class_name(Str);
		s<<"* %"<<e2_res<<", i32 0, i32 2\n";
		
		//load value from the pointer of second
		s<<"\t%"<<(e2_val=new_reg())<<" = load i8** %"<<e2_val_ptr<<", align 8\n";
		
		//compare strings
		s<<"\t%"<<(strcmp_val=new_reg())<<" = call i32 @strcmp(i8* %"<<e1_val<<", i8* %"<<e2_val<<")\n";
		
		//compare value with 0
		s<<"\t%"<<(comp_val=new_reg())<<" = icmp eq i32 %"<<strcmp_val<<", 0\n";
	} else { //else comp pointers
		reg e1_i8_ptr, e2_i8_ptr;
		s<<"\t%"<<(e1_i8_ptr=new_reg())<<" = bitcast ";
		cgct->emit_class_name(e1->get_type());
		s<<"* %"<<e1_res<<" to i8*\n";
		
		s<<"\t%"<<(e2_i8_ptr=new_reg())<<" = bitcast ";
		cgct->emit_class_name(e2->get_type());
		s<<"* %"<<e2_res<<" to i8*\n";
		
		s<<"\t%"<<(comp_val=new_reg())<<" = icmp eq i8* %"<<e1_i8_ptr<<", %"<<e2_i8_ptr<<"\n";
	}
	
	//make new Bool obj on heap
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Bool)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
	
	//set value of new Bool obj
	s<<"\t%"<<(res_val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//convert i1 to i8
	s<<"\t%"<<(converted_res_val=new_reg())<<" = zext i1 %"<<comp_val<<" to i8\n";
	
	//store converted value to result
	s<<"\tstore i8 %"<<(converted_res_val)<<", i8* %"<<res_val_ptr<<", align 1\n";
	
	//bitcast to bring to last register (Kludge)
	s<<"\t%"<<new_reg()<<" = bitcast ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
}

void leq_class::code(ostream &s) {
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	//code e2
	e2->code(s);
	
	//get register number of second 'y'
	reg y=last_reg();
	
	reg x_ptr, x_value, y_ptr, y_value, res_value, res_obj, res_ptr, converted_res_val, res_obj_ptr, final_res;
	
	//get element pointer to value of first obj
	s<<"\t%"<<(x_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<x<<", i32 0, i32 1\n";
	
	//load value from the pointer of first
	s<<"\t%"<<(x_value=new_reg())<<" = load i32* %"<<x_ptr<<", align 4\n";
	
	//get element pointer to value of second obj
	s<<"\t%"<<(y_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Int);
	s<<"* %"<<y<<", i32 0, i32 1\n";
	
	//load value from the pointer of second
	s<<"\t%"<<(y_value=new_reg())<<" = load i32* %"<<y_ptr<<", align 4\n";
	
	//compare both values
	s<<"\t%"<<(res_value=new_reg())<<" = icmp sle i32 %"<<x_value<<", %"<<y_value<<"\n";
	
	//allocate memory to a new Bool for result
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Bool)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
	
	
	//get element pointer to value of result
	s<<"\t%"<<(res_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//convert i1 to i8
	s<<"\t%"<<(converted_res_val=new_reg())<<" = zext i1 %"<<res_value<<" to i8\n";
	
	//store converted value to resulted
	s<<"\tstore i8 %"<<(converted_res_val)<<", i8* %"<<(res_ptr)<<", align 4\n";
	
	//copy final obj to last register
	
	//allocate a pointer and store address of final obj
	s<<"\t%"<<(res_obj_ptr=new_reg())<<" = alloca ";
	cgct->emit_class_name(Bool);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Bool);
	s<<"** %"<<res_obj_ptr<<", align 8\n";
	
	//store the value of result into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Bool);
	s<<"** %"<<res_obj_ptr<<"\n";
}

void comp_class::code(ostream &s) {
	e1->code(s);
	
	reg expr_res=last_reg(), expr_val_ptr, expr_val, comp_val, res_obj, res_val_ptr;
	
	s<<"\t%"<<(expr_val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<expr_res<<", i32 0, i32 1\n";
	
	s<<"\t%"<<(expr_val=new_reg())<<" = load i8* %"<<expr_val_ptr<<", align 1\n";
	
	s<<"\t%"<<(comp_val=new_reg())<<" = sub nsw i8 1, %"<<expr_val<<"\n";
	
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Bool)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
	
	s<<"\t%"<<(res_val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	s<<"\tstore i8 %"<<comp_val<<", i8* %"<<res_val_ptr<<", align 1\n";
	
	//get result to last register
	s<<"\t%"<<new_reg()<<" = bitcast ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
}

void int_const_class::code(ostream& s)  
{
  //
  // Need to be sure we have an IntEntry *, not an arbitrary Symbol
  //
  //emit_load_int(ACC,inttable.lookup_string(token->get_string()),s);
  
  reg heap_obj, obj, val_pointer, obj_pointer, final_res;
  
  //Allocate an object of Int class in cur_register
  
  s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Int)<<")\n";
  s<<"\t%"<<(obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
  cgct->emit_class_name(Int);
  s<<"*\n";
  
  //get ptr of val from the pointer 'x' and store it to 'x+1'
  s<<"\t%"<<(val_pointer=new_reg())<<" = getelementptr inbounds ";
  cgct->emit_class_name(Int);
  s<<"* %"<<obj<<", i32 0, i32 1\n";
  
  //store actual value of integer to *'x+1'
  s<<"\tstore i32 "<<token->get_string()<<", i32* %"<<val_pointer<<", align 4\n";
  
  //allocate a pointer and store address of 'x'
  s<<"\t%"<<(obj_pointer=new_reg())<<" = alloca ";
  cgct->emit_class_name(Int);
  s<<"*, align 8\n";
  
  s<<"\tstore ";
  cgct->emit_class_name(Int);
  s<<"* %"<<obj<<", ";
  cgct->emit_class_name(Int);
  s<<"** %"<<obj_pointer<<", align 8\n";
  
  //store the value of x into last register.
  s<<"\t%"<<(final_res=new_reg())<<" = load ";
  cgct->emit_class_name(Int);
  s<<"** %"<<obj_pointer<<"\n";
  
}

void string_const_class::code(ostream& s)
{
  //emit_load_string(ACC,stringtable.lookup_string(token->get_string()),s);
  StringEntry *str_entry=stringtable.lookup_string(token->get_string());
  reg heap_obj, obj, val_ptr, val_ptr_ptr, len_obj_ptr,casted_len_obj_ptr, len_val_ptr, obj_ptr, final_res;
  
  //Allocate an object of Str class in cur_register='x'
  s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Str)<<")\n";
  s<<"\t%"<<(obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
  cgct->emit_class_name(Str);
  s<<"*\n";
 
  //allocate a new i8* block in heap for Int object for length
  s<<"\t%"<<(len_obj_ptr=new_reg())<<" = call i8* @_Znwm(i64 "<<(cgct->get_class_size(Int))<<")\n";
  s<<"\t%"<<(casted_len_obj_ptr=new_reg())<<" = bitcast i8* %"<<(len_obj_ptr)<<" to ";
  cgct->emit_class_name(Int);
  s<<"*\n";
  
  //store length of string constant into the Int object in heap
  s<<"\t%"<<(len_val_ptr=new_reg())<<" = getelementptr inbounds ";
  cgct->emit_class_name(Int);
  s<<"* %"<<casted_len_obj_ptr<<", i32 0, i32 1\n";
  s<<"\tstore i32 "<<(str_entry->get_len())<<", i32* %"<<len_val_ptr<<", align 4\n";
  
  //store pointer to Int obj in heap into the Int* slot in String obj
  reg len_obj_ptr_ptr;
  s<<"\t%"<<(len_obj_ptr_ptr=new_reg())<<" = getelementptr inbounds ";
  cgct->emit_class_name(Str);
  s<<"* %"<<(obj)<<", i32 0, i32 1\n";
  
  s<<"\tstore ";
  cgct->emit_class_name(Int);
  s<<"* %"<<casted_len_obj_ptr<<", ";
  cgct->emit_class_name(Int);
  s<<"** %"<<len_obj_ptr_ptr<<"\n";
   
  //get ptr of val from the pointer 'x' and store it to 'x+1'
  s<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
  cgct->emit_class_name(Str);
  s<<"* %"<<obj<<", i32 0, i32 2\n";
   
  //allocate a new i8* block in heap of the size of the string constant
  s<<"\t%"<<(val_ptr_ptr=new_reg())<<" = call i8* @_Znwm(i64 "<<(str_entry->get_len()+1)<<")\n";
  s<<"\tstore i8* %"<<val_ptr_ptr<<", i8** %"<<val_ptr<<"\n";
  
  //call strcpy to copy string from constant to 'x+2'
  s<<"\t%"<<new_reg()<<" = call i8* @strcpy(i8* %"<<val_ptr_ptr<<", i8* getelementptr inbounds (["<<(str_entry->get_len()+1)<<" x i8]* @.str"<<cgct->strings[str_entry]<<", i32 0, i32 0))\n";
  
  //allocate a pointer and store address of 'x'
  s<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
  cgct->emit_class_name(Str);
  s<<"*, align 8\n";
  
  s<<"\tstore ";
  cgct->emit_class_name(Str);
  s<<"* %"<<obj<<", ";
  cgct->emit_class_name(Str);
  s<<"** %"<<obj_ptr<<", align 8\n";
  
  //store the value of x into last register.
  s<<"\t%"<<(final_res=new_reg())<<" = load ";
  cgct->emit_class_name(Str);
  s<<"** %"<<obj_ptr<<"\n";
}

void bool_const_class::code(ostream& s)
{
  //emit_load_bool(ACC, BoolConst(val), s);
  
  reg heap_obj, obj, val_ptr, obj_ptr, final_res;
  
  //Allocate an object of Int class in cur_register='x'
  s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Bool)<<")\n";
  s<<"\t%"<<(obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
  cgct->emit_class_name(Bool);
  s<<"*\n";
  
  //get ptr of val from the pointer 'x' and store it to 'x+1'
  s<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
  cgct->emit_class_name(Bool);
  s<<"* %"<<obj<<", i32 0, i32 1\n";
  
  //store actual value of boolean to *'x+1'
  s<<"\tstore i8 "<<val<<", i8* %"<<val_ptr<<", align 1\n";
  
  //allocate a pointer and store address of 'x'
  s<<"\t%"<<(obj_ptr=new_reg())<<" = alloca ";
  cgct->emit_class_name(Bool);
  s<<"*, align 1\n";
  
  s<<"\tstore ";
  cgct->emit_class_name(Bool);
  s<<"* %"<<obj<<", ";
  cgct->emit_class_name(Bool);
  s<<"** %"<<obj_ptr<<", align 1\n";
  
  //store the value of x into last register.
  s<<"\t%"<<(final_res=new_reg())<<" = load ";
  cgct->emit_class_name(Bool);
  s<<"** %"<<obj_ptr<<"\n";
}

void new__class::code(ostream &s) {
	reg new_obj, casted_new_obj;
	
	//allocate memory from heap
	s<<"\t%"<<(new_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(type_name)<<")\n";
	
	s<<"\t%"<<(casted_new_obj=new_reg())<<" = bitcast i8* %"<<new_obj<<" to ";
	cgct->emit_class_name(type_name);
	s<<"*\n";
	
	//call constructor
	s<<"\tcall void ";
	cgct->emit_constructor_name(type_name);
	s<<"(";
	cgct->emit_class_name(type_name);
	s<<"* %"<<casted_new_obj<<")\n";
}

void isvoid_class::code(ostream &s) {
	//code e1
	e1->code(s);
	
	//get register number of first 'x'
	reg x=last_reg();
	
	reg res_value, res_obj, res_ptr, converted_res_val, res_obj_ptr, final_res;
	
	//compare both values
	s<<"\t%"<<(res_value=new_reg())<<" = icmp eq ";
	cgct->emit_class_name(e1->get_type());
	s<<"* %"<<x<<", null\n";
	
	//allocate memory to a new Bool for result
	reg heap_obj;
	s<<"\t%"<<(heap_obj=new_reg())<<" = call i8* @_Znwm(i64 "<<cgct->get_class_size(Bool)<<")\n";
	
	s<<"\t%"<<(res_obj=new_reg())<<" = bitcast i8* %"<<heap_obj<<" to ";
	cgct->emit_class_name(Bool);
	s<<"*\n";
	
	
	//get element pointer to value of result
	s<<"\t%"<<(res_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", i32 0, i32 1\n";
	
	//convert i1 to i8
	s<<"\t%"<<(converted_res_val=new_reg())<<" = zext i1 %"<<res_value<<" to i8\n";
	
	//storec converted value to resulted
	s<<"\tstore i8 %"<<(converted_res_val)<<", i8* %"<<(res_ptr)<<", align 4\n";
	
	//copy final obj to last register
	
	//allocate a pointer and store address of final obj
	s<<"\t%"<<(res_obj_ptr=new_reg())<<" = alloca ";
	cgct->emit_class_name(Bool);
	s<<"*, align 8\n";
	
	s<<"\tstore ";
	cgct->emit_class_name(Bool);
	s<<"* %"<<res_obj<<", ";
	cgct->emit_class_name(Bool);
	s<<"** %"<<res_obj_ptr<<", align 8\n";
	
	//store the value of result into last register.
	s<<"\t%"<<(final_res=new_reg())<<" = load ";
	cgct->emit_class_name(Bool);
	s<<"** %"<<res_obj_ptr<<"\n";
}

void no_expr_class::code(ostream &s) {
}

void object_class::code(ostream &s) {
	
	//if self
	if(name==self) {
		s<<"\t%"<<new_reg()<<" = bitcast ";
		cgct->emit_class_name(cgct->cur_method->get_enclosing_class()->get_name());
		s<<"* %this to ";
		cgct->emit_class_name(cgct->cur_method->get_enclosing_class()->get_name());
		s<<"*\n";
		return;
	}
	
	//search in object_reg_map
	reg let_reg=cgct->get_reg_from_object(name);
	if(let_reg!=-1) {
		s<<"\t%"<<new_reg()<<" = bitcast ";
		cgct->emit_class_name(get_type());
		s<<"* %"<<let_reg<<" to ";
		cgct->emit_class_name(get_type());
		s<<"*\n";
		return;
	}
	
	//search in class hierarchy
	CgenNode *enclosing_class=cgct->find_attr_enclosing_class(cgct->cur_method->get_enclosing_class()->get_name(), name);
	
	int i;
	Features features=enclosing_class->features;
	for(i=features->first(); features->more(i); i=features->next(i))
		if(features->nth(i)->is_attr() && ((attr_class*)features->nth(i))->name==name)
			break;
	
	reg casted_this, val_ptr;
	
	s<<"\t%"<<(casted_this=new_reg())<<" = bitcast ";
	cgct->emit_class_name(cgct->cur_method->get_enclosing_class()->get_name());
	s<<"* %this to ";
	cgct->emit_class_name(enclosing_class->get_name());
	s<<"*\n";
	
	s<<"\t%"<<(val_ptr=new_reg())<<" = getelementptr inbounds ";
	cgct->emit_class_name(enclosing_class->get_name());
	s<<"* %"<<casted_this<<", i32 0, i32 "<<(i+1)<<"\n";
	
	s<<"\t%"<<new_reg()<<" = load ";
	cgct->emit_class_name(get_type());
	s<<"** %"<<val_ptr<<", align 8\n";
}


