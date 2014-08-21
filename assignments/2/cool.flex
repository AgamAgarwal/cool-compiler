/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
int comment_count=0;
%}

/*
 * Define names for regular expressions here.
 */

DARROW          =>
LE				<=
ASSIGN			<-

%x COMMENT
%%

 /*
  *  Nested comments
  */

--.*	{	/*single line comment*/ }
"*)"	{
		cool_yylval.error_msg="Unmatched *)";
		return (ERROR);
		}
"(*"	{
		BEGIN(COMMENT);	//comment begins
		comment_count++;
		}
<COMMENT>"(*"	{
				comment_count++;
				}
<COMMENT>"*)"	{
				comment_count--;
				if(comment_count==0)
					BEGIN(INITIAL);	//comments ends
				}
<COMMENT>\n		{ curr_lineno++; }
<COMMENT>.	{	/*ignore text inside comments*/ }
<COMMENT><<EOF>>	{
					BEGIN(INITIAL);
					comment_count=0;
					cool_yylval.error_msg="EOF in comment";
					return (ERROR);
					}


 /*
  *  The multiple-character operators.
  */
{DARROW}		{ return (DARROW); }
{LE}			{ return (LE); }
{ASSIGN}		{ return (ASSIGN); }

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
[iI][fF]	{return (IF); }
[tT][hH][eE][nN]	{return {THEN};}
[eE][lL][sS][eE]	{return (ELSE);}
[fF][iI]	{ return (FI); }

[wW][hH][iI][lL][eE]	{ return (WHILE); }
[lL][oO][oO][pP]	{ return (LOOP); }
[pP][oO][oO][lL]	{ return (POOL); }

[lL][eE][tT]	{ return (LET); }
[iI][nN]	{ return (IN); }

[cC][aA][sS][eE]	{ return (CASE); }
[oO][fF]	{ return (OF); }
[eE][sS][aA][cC]	{ return (ESAC); }

[nN][eE][wW]	{ return (NEW); }

[iI][sS][vV][oO][iI][dD]	{ return (ISVOID); }

[nN][oO][tT]	{ return (NOT); }

[cC][lL][aA][sS][sS]	{ return (CLASS); }
[iI][nN][hH][eE][rR][iI][tT][sS]	{ return (INHERITS); }

t[rR][uU][eE]	{ cool_yylval.boolean=true; return (BOOL_CONST); }
f[aA][lL][sS][eE]	{ cool_yylval.boolean=false; return (BOOL_CONST); }


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */


%%
