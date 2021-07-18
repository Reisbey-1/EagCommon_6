

#include "stdafx.h"

#include "MOCEvaluator.h"
#include "MathUtility.h"
#include "StringUtility.h""


namespace eag {

MOCEvaluator::MOCEvaluator()
{
	init();
};


MOCEvaluator::MOCEvaluator(const char * expression, CArray <CString, CString& > & CArrayOperants)
{
	init();
	SetNewExpression(expression, CArrayOperants);
};


MOCEvaluator::MOCEvaluator(const char * expression, CString COperant)
{
	init();
	SetNewExpression(expression, COperant);
};

void
MOCEvaluator::init(){

	verbs[0]  = operators ('+',  "+",        22 ) ;
	verbs[1]  = operators ('-',  "-",        23 ) ;
	verbs[2]  = operators ('*',  "*",        24 ) ;
	verbs[3]  = operators ('/',  "/",        25 ) ;
	verbs[4]  = operators ('%',  "%",        25 ) ;
	verbs[5]  = operators ('^',  "^",        26 ) ;
	verbs[6]  = operators ('(',  "(",        0  ) ;
	verbs[7]  = operators (')',  ")",        99 ) ;
	verbs[8]  = operators ('s',  "SIN(",     0  ) ;
	verbs[9]  = operators ('c',  "COS(",     0  ) ;
	verbs[10] = operators ('a',  "ABS(",     0  ) ;
	verbs[11] = operators ('l',  "LN(",      0  ) ;
	verbs[12] = operators ('e',  "EXP(",     0  ) ;
	verbs[13] = operators ('d',  "ATAN(",    0  ) ;
	verbs[14] = operators ('r',  "SQRT(",    0  ) ;
	verbs[15] = operators ('i',  "<=",		 12 ) ;
	verbs[16] = operators ('g',  ">=",		 11 ) ;
	verbs[17] = operators ('<',  "<",		 10 ) ;
	verbs[18] = operators ('>',  ">",		 9  ) ;
	verbs[19] = operators ('&',  "&&",		 6  ) ;
	verbs[20] = operators ('|',  "||",		 5  ) ;
	verbs[21] = operators ('x',  "^|",		 4  ) ;
	verbs[22] = operators ('=',  "==",		 3  ) ;
	verbs[23] = operators ('!',  "!=",		 2  ) ;
	verbs[24] = operators ('n',  "!",		 99 ) ;
	verbs[25] = operators ('t',  "TAN(",	 0  ) ;
	verbs[26] = operators ('0',  "ROUND0(",	 0  ) ;
	verbs[27] = operators ('2',  "ROUND2(",	 0  ) ;
	verbs[28] = operators ('3',  "ROUND3(",	 0  ) ;
//	verbs[28] = operators ('p',  "PI",		 99 ) ; // Problem with names -> not solved jet

//	Pi = 3.14159265358979323846;
	m_dEqualPrecision = 0.0 ;
	m_dTrue = 1.0;
	m_pcExpresion = NULL;
	m_bCheckMode = false;
	m_iErrorPosition = -1;
};


MOCEvaluator::~MOCEvaluator(){
	delete	m_pcExpresion ;
};

void MOCEvaluator::PrintError(CString csError)
{
	if ( ! m_bCheckMode )
	{
		EAG_LOG_ERROR(csError);
	}
}

void MOCEvaluator::SetNewExpression(const char *newExpresion, CArray <CString, CString& > & CArrayOperands)
{
	delete m_pcExpresion;
	m_pcExpresion = new char[strlen(newExpresion)+1];
	strcpy(m_pcExpresion,newExpresion);
	m_pcExpresion[strlen(newExpresion)] =0;

	char * pcEx= m_pcExpresion ;

	strupr(pcEx);
	rmallws(pcEx);

	m_iErrorPosition = -1;

	m_CArrayOperants.RemoveAll();
	m_CArrayOperants.Copy( CArrayOperands );
	for (int i=0; i <m_CArrayOperants.GetSize(); i++) {

		m_CArrayOperants[i].MakeUpper( );
		m_CArrayOperants[i].TrimLeft();
		m_CArrayOperants[i].TrimRight();
	}
}

void MOCEvaluator::SetNewExpression(const char * newExpresion, CString CStrOperand)
{
	CArray <CString, CString& > CArrayOperands;

	if (CStrOperand.GetLength() == 0 ) {
		CString def = ("X");
		CArrayOperands.Add ( def );
	}
	else
		CArrayOperands.Add ( CStrOperand );

	SetNewExpression(newExpresion,CArrayOperands);
}


BOOL 
MOCEvaluator::evaluate(double &result, double OpValue, bool bCheckOnly)
{
	try
	{
		m_bCheckMode = bCheckOnly;

		CArray <double , double & > OpValues;
		OpValues.Add( OpValue ); 

		return evaluate(result, OpValues);
	}
	catch(...)
	{
		return FALSE;
	}
};


BOOL MOCEvaluator::CheckIfStatement(double &result, char * pcExpresion)
{
//CheckIfStatement will be recursed called, until all ifstatements are done
	int iExLength = strlen(pcExpresion);

	BOOL bIfStatement=FALSE;


	for (int i = 0 ; i < iExLength; i++){

		if ('?' == pcExpresion[i]) {

			bIfStatement = TRUE;

			char * pcsQuestionExpression = new char [i+1];
			strncpy(pcsQuestionExpression, pcExpresion, i );
			pcsQuestionExpression[i]=0;

			if ( ! evaluate( result, pcsQuestionExpression  ) ) {
				delete pcsQuestionExpression;
				return FALSE;
			}
			delete pcsQuestionExpression;

			//search the next expresion for CheckIfStatement:
			int iQuestionMarks=0;
			i++; //I'm no longer interested in the questionmark!
			int j = 0;   /// dlg
			for ( j = i ; j < iExLength ; j++) {
				if ('?' == pcExpresion[j]) {
					iQuestionMarks++;
				} 
				else if (':' == pcExpresion[j]) {
					if (0 == iQuestionMarks )
						break;
					else 
						iQuestionMarks--;
				}
			}
			//now j has the count of the next valid ':' sign
			//i has the count after the questionmark
			
			// next Check If there is another If-Statement:
			char * pcResultExpression = new char [iExLength+1];

			if ( fabs(result) >= m_dTrue ) {
				strncpy( pcResultExpression , pcExpresion + i , j-i ); 
				pcResultExpression[j-i]=0;
			}
			else {
				if ( iExLength-j-1 < 0 )
				{
					// cleanup
					delete pcResultExpression;
					return FALSE;
				}
				strncpy( pcResultExpression , pcExpresion + j + 1 , iExLength-j-1 ); 
				pcResultExpression[iExLength-j-1]=0;
			}


			if ( ! CheckIfStatement(result, pcResultExpression) ){
				delete pcResultExpression;
				return FALSE;
			}

			delete pcResultExpression;
			return TRUE;
		}

	}

	if (!bIfStatement)  {
		return evaluate( result, pcExpresion );
	}
	return 	TRUE;
	
}


BOOL 
MOCEvaluator::evaluate(double &result, CArray <double , double & > &OpValues, bool bCheckOnly)
{
	m_bCheckMode = bCheckOnly;

	m_CArraydValues.RemoveAll();
	m_CArraydValues.Copy( OpValues ); //all occurences of CArrayOperants within the expression will be replaced by 
								// the coresponding value from this array!

	if (m_CArraydValues.GetSize() != m_CArrayOperants.GetSize()) {
		PrintError("MOCEvaluator::evaluate -> Size of values does not fit size of operants!");
		return false;
	}
	
	double dresult = 0;

	char * pcExpresion = m_pcExpresion;

	if ( CheckIfStatement(dresult, pcExpresion ) ) { 
		result = dresult;
		return TRUE;
	 }

return FALSE;
};


int MOCEvaluator::evaluate(double &result, const char * pcExpresion  )
{
    double arg;
	
	char *str, *endptr;
    int ercode;
	int i=0;
    operators *op;
    int state;  // 0 = Awaiting expression ( X 1 5 7 -3 .... )
                // 1 = Awaiting operators ( * - + / ... )


	char * ptr = (char*)pcExpresion;

	m_iErrorPosition = (int)ptr;

    state = op_sptr = arg_sptr = parens = 0;

    while (*ptr)
    {
            switch (state)
            {
            case 0:
                  if (NULL != (str = get_exp(ptr)))
                  {
                        if (NULL != (op = get_op(str)) &&
                              strlen(str) == op->taglen)
                        {
                              push_op(op->token);
                              ptr += op->taglen;
                              break;
                        }

                        if (0 == strcmp(str, "-"))
                        {
							push_op(*str);
                            ++ptr;
                            break;
                        }

//                        if (0 == strcmp(str, "PI")) {
//							push_arg(Pi);
//							break;
//						}

						for (i=0; i<m_CArrayOperants.GetSize() ; i++ ) {
							USES_CONVERSION;
							const char* cstr = T2A(m_CArrayOperants[i].GetBuffer());

								if (0 == strcmp(str, cstr)) {
										push_arg(m_CArraydValues[i]);
								i=-1;
								break;
							}
						}

						if (i !=-1) 
	                    {
                              if (( 0.0 == (arg = strtod(str, &endptr) )) &&
                                  ( NULL == strchr(str, '0') )	||
								  ( '\0' != *endptr) )
                              {
								  CString csError;
								  csError.Format(_T("MOCEvaluator::evaluate-> unknown argument: '%s'"), str);
								  PrintError( csError);
							  	  m_iErrorPosition = (int)ptr - m_iErrorPosition;
                                  return FALSE;
                              }
                              push_arg(arg);
                        }

                        ptr += strlen(str);
                  }
                  else  {
				  	  m_iErrorPosition = (int)ptr - m_iErrorPosition;
				  	  return FALSE;
				  }

                  state = 1;
                  break;

            case 1:
                  if (NULL != (op = get_op(ptr)))
                  {
                        if (')' == *ptr || ( '!' == *ptr && '=' != ptr[1] ) )
                        {
							if (0 > (ercode = do_paren())) {
						  	  m_iErrorPosition = (int)ptr - m_iErrorPosition;
                              return ercode;
							}
                        }
                        else
                        {
							while (op_sptr && op->precedence <= getTOSprec() )
								{
									ercode = do_op();
								}
								push_op(op->token);
								state = 0;
                        }

                        ptr += op->taglen;
                  }
                  else  {
				  	  m_iErrorPosition = (int)ptr - m_iErrorPosition;
					  return FALSE;
				  }

                  break;
            }
      }

      while (1 < arg_sptr)
      {
		  if (0 > (ercode = do_op())) { 
		  	  m_iErrorPosition = (int)ptr - m_iErrorPosition;
              return ercode;
		  }
      }
      if (!op_sptr) {
	  	  m_iErrorPosition = -1;
          return pop_arg(result);
	  }
      else {
	  	  m_iErrorPosition = (int)ptr - m_iErrorPosition;
		  return FALSE;
	  }
}


//  Evaluate stacked arguments and operands

int MOCEvaluator::do_op(void)
{
      double arg1, arg2;
      int op;

      if (! pop_op(&op))
            return R_ERROR;

      pop_arg(arg1);
      pop_arg(arg2);

      switch (op)
      {
      case '*':
            push_arg(arg2 * arg1);
            break;

      case '+':
            push_arg(arg2 + arg1);
            break;

      case '-':
            push_arg(arg2 - arg1);
            break;

      case '/':
		  if (0.0 == arg1) {
				PrintError("MOCEvaluator::do_op -> Division through zero is not defined.");
				return R_ERROR;
           }
			push_arg(arg2 / arg1);
            break;

      case '%':
		  if (0.0 == arg1) {
				PrintError("MOCEvaluator::do_op -> Division through zero is not defined.");
                return R_ERROR;
		  }
            push_arg(fmod(arg2, arg1));
            break;

      case '^':
            push_arg(pow(arg2, arg1));
            break;

      case 'd':
            ++arg_sptr;
            push_arg(atan(arg1));
            break;

      case 't':
		  if (0.0 == arg1) {
				PrintError("MOCEvaluator::do_op -> Tangens of zero is not defined.");
				return R_ERROR;
		  }
            ++arg_sptr;
            push_arg(tan(arg1));
            break;

      case 's':
            ++arg_sptr;
            push_arg(sin(arg1));
            break;

      case 'r':
		  if (0.0 > arg2) {
				PrintError("MOCEvaluator::do_op -> Square root of zero is not defined.");
                return R_ERROR;
		  }
            ++arg_sptr;
            push_arg(sqrt(arg1));
            break;

      case 'c':
            ++arg_sptr;
            push_arg(cos(arg1));
            break;

      case 'a':
            ++arg_sptr;
            push_arg(fabs(arg1));
            break;

      case 'l':
            if (0.0 < arg1)
            {
                  ++arg_sptr;
                  push_arg(log(arg1));
                  break;
            }
            else  {
				PrintError("MOCEvaluator::do_op -> Logarithm of zero or less than zero is not defined.");
				return R_ERROR;
			}

      case 'e':
            ++arg_sptr;
            push_arg(exp(arg1));
            break;

      case '(':
            arg_sptr += 2;
            break;

//Logical expression follows:
      
	  case '<':
			push_arg( ((arg2 + m_dEqualPrecision) < arg1) ? m_dTrue : 0 );
            break;

      case '>':
            push_arg( ( arg2 > (arg1+m_dEqualPrecision)) ? m_dTrue : 0  );
            break;

      case '=':
			if ( (arg2 >= (arg1 - m_dEqualPrecision) ) && 
				 (arg2 <= (arg1 + m_dEqualPrecision) ) )
				push_arg( m_dTrue );
			else 
				push_arg( 0 );
            break;

      case '!':
			if ( (fabs(arg2) < (fabs(arg1) - m_dEqualPrecision) ) || 
				 (fabs(arg2) > (fabs(arg1) + m_dEqualPrecision) ) )
				push_arg( m_dTrue  );
			else 
				push_arg( 0 );
            break;

      case 'i':
    		push_arg( (arg2 <= (arg1 + m_dEqualPrecision)) ? m_dTrue : 0 ); // less or equal
            break;

      case 'g':
            push_arg( (arg2 >= (arg1 - m_dEqualPrecision)) ? m_dTrue : 0 );  // greater or equal
            break;

      case '&':
            if ( ( fabs(arg1) >= m_dTrue - m_dEqualPrecision) && 
				 ( fabs(arg2) >= m_dTrue - m_dEqualPrecision))
	            push_arg(m_dTrue);
			else
	            push_arg(0);
            break;

      case '|':
            if ( ( fabs(arg1) >= m_dTrue - m_dEqualPrecision) || 
				 ( fabs(arg2) >= m_dTrue - m_dEqualPrecision))
	            push_arg(m_dTrue);
			else
	            push_arg(0);
            break;

      case 'x':
           if ( ( fabs(arg1) >= m_dTrue - m_dEqualPrecision) ^ ( fabs(arg2) >= m_dTrue - m_dEqualPrecision))
	            push_arg(m_dTrue);
			else
	            push_arg(0);
             break;

      case 'n':			// _n_egate (reverse) argument
            push_arg( (fabs(arg1) >= m_dTrue ) ?  0 :m_dTrue );
            break;

	  case '0':
			push_arg( CMathUtility::RoundDouble(arg1,0));
			break;

	  case '2':
			push_arg( CMathUtility::RoundDouble(arg1,2));
			break;

	  case '3':
			push_arg( CMathUtility::RoundDouble(arg1,3));
			break;

//      case 'p':		
//            push_arg( Pi );
//            break;

      default:
            return UNKNOWN_OPERATOR;
      }
      if (1 > arg_sptr)
          return R_ERROR;
      else  
		  return op;
}


//  Evaluate one level

int MOCEvaluator::do_paren(void)
{
      int op;

      if (1 > parens--)
            return FALSE;
      do
      {
            if (0 > (op = do_op()))
                  break;
      } while (getprec((char)op));
      return op;
}


//  Stack operations

void MOCEvaluator::push_op(char op)
{
      if (!getprec(op))
            ++parens;
      op_stack[op_sptr++] = op;
}

int MOCEvaluator::pop_op(int *op)
{
      if (!op_sptr)
            return FALSE;
      *op = op_stack[--op_sptr];
      return TRUE;
}


void MOCEvaluator::push_arg(double arg)
{
      arg_stack[arg_sptr++] = arg;
}

int MOCEvaluator::pop_arg(double &arg)
{
      arg = arg_stack[--arg_sptr];
      if (0 > arg_sptr)
            return FALSE;
      else  
		  return TRUE;
}


//  Get an expression

char * MOCEvaluator::get_exp(char *str)
{
      char *ptr = str, *tptr = token;
      operators *op;

//      if (0 == strncmp(str, "PI", 2))
//            return strcpy(token, "PI");


      while (*ptr)
      {
            if (NULL != (op = get_op(ptr)))
            {
                  if ('-' == *ptr)
                  {
//                      if (str != ptr && 'E' != ptr[-1])
//                            break;
                        if (str == ptr && !isdigit(ptr[1]) && '.' != ptr[1])
					  {
		                      push_arg(0.0);
						strcpy(token, op->tag);
						return token;
					  }
					  else
						  break;
                  }

                  else if ('!' == *ptr && '=' != ptr[1] )
                  {
	                   push_arg(0.0);
                       strcpy(token, op->tag);
                       return token;
                  }

                  else if (str == ptr)
                  {
                        strcpy(token, op->tag);
                        return token;
                  }

                  else break;
            }

            *tptr++ = *ptr++;
      }
      *tptr = NULL;

      return token;
}


//  Get an operators


MOCEvaluator::operators * MOCEvaluator::get_op(char *str)
{

      for (int i = 0 ; i < SIZEOFOPERATORS ; i++)
      {
            if (0 == strncmp(str, verbs[i].tag, verbs[i].taglen))
                  return &verbs[i];
      }
      return NULL;
}


// Get precedence of a token

int MOCEvaluator::getprec(char token)
{

      for (int i = 0 ; i < SIZEOFOPERATORS ; i++)
      {
            if (token == verbs[i].token)
                  return verbs[i].precedence;
      }
   return 0;
}



int MOCEvaluator::getTOSprec(void)
{
      if (!op_sptr)
            return 0;
      return getprec(op_stack[op_sptr - 1]);
}



char * MOCEvaluator::rmallws(char *str)
{
      char *obuf, *nbuf;

      if (str)
      {
           for (obuf = str, nbuf = str; *obuf; ++obuf)
            {
                  if (!isspace(*obuf))
                        *nbuf++ = *obuf;
            }
            *nbuf = NULL;
      }
      return str;
}

void MOCEvaluator::SetEqualPrecision(double EqualPrecision)
{
	m_dEqualPrecision =  EqualPrecision;
}

void MOCEvaluator::SetTrueValue(double TrueValue)
{
	m_dTrue = TrueValue;
}

int MOCEvaluator::GetErrorPosition()
{
	return m_iErrorPosition;
}


}; // end of namespace
