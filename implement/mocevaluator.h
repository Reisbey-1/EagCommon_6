  //(c) Copyrigth by ennovatis GmbH 2001


//  MOCEvaluator.Cpp - A simple mathematical expression evaluator in CPP  
                                                                      
//  operators supported: Operator               Precedence             
// 
//                         (                     Lowest 
//                         )                     Highest
//                         +   (addition)        Low    
//                         -   (subtraction)     Low    
//                         *   (multiplication)  Medium 
//                         /   (division)        Medium 
//                         \   (modulus)         High   
//                         ^   (exponentiation)  High   
//                         sin(                  Lowest 
//                         cos(                  Lowest 
//                         atan(                 Lowest 
//                         abs(                  Lowest 
//                         sqrt(                 Lowest 
//                         ln(                   Lowest 
//                         exp(                  Lowest 
//						   "<=",		less or equal 
//						   ">=",		greater or equal
//						   "<",			less than	
//						   ">",			greater than
//						   "LT",		Less Than
//						   "GT",		Greater Than
//						   "AND",		And
//						   "OR",		Or
//						   "XOR",		exclusive Or
//						   "==",		Equal (remember the equalprecision)
//						   "!=",		Not equal
//						   "!",			Negate the following operant
//
//////////////////////////////////////////////////////////////////////////
//
// new supported facility since October 1999: -If- Statements in the form:
//
//	(any expression) ? ( any expression if TRUE):(any expression if FALSE)
//
//	Conditional expressions can have recursivly as much as needed further
//  conditional expressions.
//
//	Restriction: Brackets ARROUND conditional expressions ar NOT allowed!:
//
//
//////////////////////////////////////////////////////////////////////////

/*
  Basically, EVAL.C converts infix notation to postfix notation. If you're
not familiar with these terms, infix notation is standard human-readable
equations such as you write in a C program. Postfix notation is most familiar
as the "reverse Polish" notation used in Hewlett Packard calculators and in
the Forth language. Internally, all languages work by converting to postfix
evaluation. Only Forth makes it obvious to the programmer.

  EVAL.C performs this conversion by maintaining 2 stacks, an operand stack
and an operators stack. As it scans the input, each time it comes across a
numerical value, it pushes it onto the operand stack. Whenever it comes
across an operators, it pushes it onto the operators stack. Once the input
expression has been scanned, it evaluates it by popping operands off the
operand stack and applying the operators to them.

 For example the simple expression "2+3-7" would push the values 2, 3, and 7
onto the operand stack and the operators "+" and "-" onto the operators stack.
When evaluating the expression, it would first pop 3 and 7 off the operand
stack and then pop the "-" operators off the operators stack and apply it. This
would leave a value of -4 on the stack. Next the value of 2 would be popped
from the operand stack and the remaining operators off of the operators stack.
Applying the "+" operators to the values 2 and -4 would leave the result of
the evaluation, -2, on the stack to be returned.

  The only complication of this in EVAL.C is that instead of raw operators
(which would all have to be 1 character long), I use operators tokens which
allow multicharacter operators and precedence specification. What I push on
the operators stack is still a single character token, but its the operators
token which is defined in the 'verbs' array of valid tokens. Multicharacter
tokens are always assumed to include any leading parentheses. For example, in
the expression "SQRT(37)", the token is "SQRT(".

  Using parentheses forces evaluation to be performed out of the normal
sequence. I use the same sort of mechanism to implement precedence rules.
Unary negation is yet another feature which takes some explicit exception
processing to process. Other than these exceptions, it's pretty
straightforward stuff.
*/

#ifndef _MOCEvaluator_H_
#define _MOCEvaluator_H_

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <afxtempl.h>

#include "eag_Monitor.h"

/**
    <B>PROJECT:</B><BR>
    MOCEvaluator<BR>
    <P>
    <B>MODULBESCHREIBUNG:</B><BR>
    Evaluates mathematical expression with variables <br>
	Example: ("sqrt(x)*sin(x)+34*x*x")<BR>

	Usage of this class:<P>

  Generate  a  new object and provide an mathematical expression as CString.<BR>
  Call as often as needed the evaluation method with an value x for the replacement
  within the mathematical expression.<BR>
  If an error occurs, the value x stays unchanged.<BR>
  If the expression could be evaluated then value x contains the result.<BR>
*/
namespace eag {

#ifdef MOCEVALUATOR_EXPORTS
#define MOCEVALUATOR_API __declspec(dllexport)
#else
#define MOCEVALUATOR_API __declspec(dllimport)
#endif
	
class MOCEVALUATOR_API MOCEvaluator 
{

	typedef enum {SIZEOFOPERATORS=29};

	typedef enum {R_ERROR = -2, OK=0, UNKNOWN_OPERATOR, INVALID_ARGUMENT, NON_FITTING_SIZE_OF_OPERANTS} ;


class operators {

public:
    char			token;
    char			tag[10];
	unsigned int	taglen;
    int				precedence;

operators(char to, char *ta, int p) {
	token	= to;
	strcpy(tag,	ta);
	taglen = strlen(ta);
	precedence	=p;
};

operators(){};
};


char *rmallws(char *);

operators verbs[SIZEOFOPERATORS];


char   op_stack[256];                    /* operators stack       */
double arg_stack[256];                   /* Argument stack       */
char   token[256];                       /* Token buffer         */
int    op_sptr,                          /* op_stack pointer     */
       arg_sptr,                         /* arg_stack pointer    */
       parens;                           /* Nesting level        */

//double Pi;

CArray <double , double & > m_CArraydValues;

CArray <CString, CString& > m_CArrayOperants;

char * m_pcExpresion;

int              do_op(void);
int              do_paren(void);
void             push_op(char);
void             push_arg(double);
int              pop_arg(double &);
int              pop_op(int *);
char             *get_exp(char *);
MOCEvaluator::operators *get_op(char *);
int              getprec(char);
int              getTOSprec(void);


int evaluate(double &result, const char * pcExpression);

public:
	int GetErrorPosition();

	/*
	Define at which value an expression is true.
	Be careful: comparison results also in this value!
	*/
	void SetTrueValue(double TrueValue = 1 );
	
	/*
	Define how exact equality should be.
	Its NOT relative, its taken absolute!
	*/
	void SetEqualPrecision(double EqualPrecision = 0.0);

	/*
	Set new multible expression.
	Attention: Order of operants MUST correspond to the order of the array 'values'
	in the evaluate operation!
	*/
	void SetNewExpression(const char * expression,CArray <CString, CString& > & CArrayOperands );

	/*
	Set new single expression.
	If the operand is not given, x is assumed.
	*/
	void SetNewExpression(const char * expression, CString CStrOperand="X" );
	
	/*
	Calculate for multible operant.
	Attention: Order of values MUST correspond to the order of the array 'CArrayOperands'
	in the set Expression operations (Constructor and SetNewExpression)!
	*/
	BOOL evaluate(double &result, CArray <double , double & > &values, bool bCheckOnly=false);

	/*
	Calculate for single operants.
	*/
	BOOL evaluate(double &result, double value, bool bCheckOnly=false);

	MOCEvaluator();

	/*
	Constructor for multible ops.
	*/
	MOCEvaluator(const char * expression, CArray <CString, CString& > & CArrayOperants);

	/*
	Constructor for single op.
	*/
	MOCEvaluator(const char * expression, CString COperant);

~MOCEvaluator();

private:
	int m_iErrorPosition;
	BOOL CheckIfStatement(double &result, char * pcExpression);
	double m_dEqualPrecision;
	double m_dTrue;

	bool m_bCheckMode;

	/*
	Must be called once.
	*/
	void init();

	/*
	document error
	*/
	void PrintError(CString csError);

	/*
	Assignment operator is set to private (no sense).
	*/
	int operator=(const MOCEvaluator&) {return 0;};
};

};// end of namespace
#endif

