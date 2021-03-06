#ifndef FLEX_HEADER_xmlscanner_h
#define FLEX_HEADER_xmlscanner_h
#define YY_XmlScanner_CHAR unsigned char
#line 1 "flexskel.h"
/* A lexical scanner header generated by flex */
/* MODIFIED FOR C++ CLASS BY Alain Coetmeur: coetmeur(at)icdc.fr */
/* Note that (at) mean the 'at' symbol that I cannot write */
/* because it is expanded to the class name */
/* made at Informatique-CDC, Research&development department */
/* company from the Caisse Des Depots et Consignations */


/*********************************************/
/* SYSTEM dependent declaration, includes... */
/*********************************************/
/* cfront 1.2 defines "c_plusplus" instead of "__cplusplus" */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_PROTOS
#define YY_USE_PROTOS
#endif
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else	/* ! __cplusplus */
#ifdef __STDC__
#ifdef __GNUC__
#else
#endif	/* __GNUC__ */
#ifndef YY_USE_PROTOS
#define YY_USE_PROTOS
#endif
#endif	/* __STDC__ */
#endif	/* ! __cplusplus */
/*********************************************/
/* COMPILER DEPENDENT   MACROS               */
/*********************************************/
/* use prototypes in function declarations */
#ifndef YY_PROTO
#ifdef YY_USE_PROTOS
#define YY_PROTO(proto) proto
#else
#define YY_PROTO(proto) ()
#endif
#endif
#include <stdio.h>




/* % here is the declaration from section1 %header{  */ 
#line 39 "xmlscanner.l"
#define YY_XmlScanner_INHERIT 
#line 40 "xmlscanner.l"
#define YY_XmlScanner_IOSTREAM 
#line 41 "xmlscanner.l"
#define YY_XmlScanner_LEX_RETURN  int
#line 42 "xmlscanner.l"
#define YY_XmlScanner_LEX  scanValue
#line 43 "xmlscanner.l"
#define YY_XmlScanner_LEX_PARAM  YY_XmlParser_STYPE &yylval
#line 45 "xmlscanner.l"
#define YY_XmlScanner_OFILE  std::strstream
#line 46 "xmlscanner.l"
#define YY_XmlScanner_OFILE_DEFAULT  &strOut
#line 47 "xmlscanner.l"
#define YY_XmlScanner_ERRFILE  strError
#line 49 "xmlscanner.l"
#define YY_XmlScanner_CONSTRUCTOR_CODE  ;
#line 50 "xmlscanner.l"
#define YY_XmlScanner_MEMBERS               \
	public:                  \
		std::strstream strOut;   \
		std::strstream strError;
#line 56 "xmlscanner.l"
#include "xmlparser.h"
#line 90 "xmlscanner.l"
#line 52 "flexskel.h"

#ifdef YY_USE_CLASS
#ifdef YY_XmlScanner_IOSTREAM
#include <iostream>	/// DLG

#ifndef YY_XmlScanner_IFILE
#define YY_XmlScanner_IFILE std::istream
#endif

#ifndef YY_XmlScanner_OFILE 
#define YY_XmlScanner_OFILE std::ostream
#endif

#ifndef YY_XmlScanner_ERRFILE
#define YY_XmlScanner_ERRFILE cerr
#endif

#ifndef YY_XmlScanner_IFILE_DEFAULT
#define YY_XmlScanner_IFILE_DEFAULT &std::cin
#endif

#ifndef YY_XmlScanner_OFILE_DEFAULT
#define YY_XmlScanner_OFILE_DEFAULT &std::cout
#endif

#endif
#endif

#ifndef YY_XmlScanner_IFILE
#define YY_XmlScanner_IFILE FILE 
#endif

#ifndef YY_XmlScanner_OFILE
#define YY_XmlScanner_OFILE FILE 
#endif

#ifndef YY_XmlScanner_ERRFILE
#define YY_XmlScanner_ERRFILE stderr
#endif

#ifndef YY_XmlScanner_IFILE_DEFAULT
#define YY_XmlScanner_IFILE_DEFAULT stdin
#endif

#ifndef YY_XmlScanner_OFILE_DEFAULT
#define YY_XmlScanner_OFILE_DEFAULT stdout
#endif




#ifndef YY_XmlScanner_TEXT
#define YY_XmlScanner_TEXT yytext
#endif
#ifndef YY_XmlScanner_LENG
#define YY_XmlScanner_LENG yyleng
#endif
#ifndef YY_XmlScanner_IN
#define YY_XmlScanner_IN yyin
#endif
#ifndef YY_XmlScanner_OUT
#define YY_XmlScanner_OUT yyout
#endif

#ifndef YY_XmlScanner_LEX_RETURN
#define YY_XmlScanner_LEX_RETURN int
#else
#ifndef YY_XmlScanner_LEX_DEFINED
#define YY_XmlScanner_LEX_DEFINED 
#endif
#endif

#ifndef YY_XmlScanner_LEX
#define YY_XmlScanner_LEX yylex
#else
#ifndef YY_XmlScanner_LEX_DEFINED
#define YY_XmlScanner_LEX_DEFINED 
#endif
#endif

#ifndef YY_XmlScanner_LEX_PARAM
#ifndef YY_USE_PROTOS
#define YY_XmlScanner_LEX_PARAM 
#else
#define YY_XmlScanner_LEX_PARAM void
#endif
#else
#ifndef YY_XmlScanner_LEX_DEFINED
#define YY_XmlScanner_LEX_DEFINED 
#endif
#endif

#ifndef YY_XmlScanner_LEX_PARAM_DEF
#define YY_XmlScanner_LEX_PARAM_DEF
#else
#ifndef YY_XmlScanner_LEX_DEFINED
#define YY_XmlScanner_LEX_DEFINED 
#endif
#endif

#ifndef YY_XmlScanner_RESTART
#define YY_XmlScanner_RESTART yyrestart
#endif
#ifndef YY_XmlScanner_SWITCH_TO_BUFFER
#define YY_XmlScanner_SWITCH_TO_BUFFER yy_switch_to_buffer
#endif
#ifndef YY_XmlScanner_LOAD_BUFFER_STATE
#define YY_XmlScanner_LOAD_BUFFER_STATE yy_load_buffer_state
#endif

#ifndef YY_XmlScanner_CREATE_BUFFER
#define YY_XmlScanner_CREATE_BUFFER yy_create_buffer
#ifndef YY_USE_CLASS
#ifndef yy_new_buffer
#define yy_new_buffer yy_create_buffer
#endif
#endif
#endif
#ifndef YY_XmlScanner_DELETE_BUFFER
#define YY_XmlScanner_DELETE_BUFFER yy_delete_buffer
#endif
#ifndef YY_XmlScanner_INIT_BUFFER
#define YY_XmlScanner_INIT_BUFFER yy_init_buffer
#endif



#ifdef YY_XmlScanner_FLEX_DEBUG
#ifndef YY_XmlScanner_DEBUG
#define YY_XmlScanner_DEBUG 1
#endif
#else
#ifndef YY_XmlScanner_DEBUG
#define YY_XmlScanner_DEBUG 0
#endif
#endif

#if YY_XmlScanner_DEBUG != 0
#ifndef YY_XmlScanner_DEBUG_FLAG
#define YY_XmlScanner_DEBUG_FLAG yy_flex_debug
#endif
#ifndef YY_XmlScanner_DEBUG_INIT
#define YY_XmlScanner_DEBUG_INIT 1
#endif
#endif




#ifndef YY_USE_CLASS
#ifndef YY_XmlScanner_CURRENT_BUFFER
#define YY_XmlScanner_CURRENT_BUFFER yy_current_buffer
#endif
typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern void YY_XmlScanner_RESTART YY_PROTO(( YY_XmlScanner_IFILE *input_file ));
extern void YY_XmlScanner_SWITCH_TO_BUFFER YY_PROTO(( YY_BUFFER_STATE new_buffer ));
extern void YY_XmlScanner_LOAD_BUFFER_STATE YY_PROTO(( void ));
extern YY_BUFFER_STATE YY_XmlScanner_CREATE_BUFFER YY_PROTO(( YY_XmlScanner_IFILE *file, int size ));
extern void YY_XmlScanner_DELETE_BUFFER YY_PROTO(( YY_BUFFER_STATE b ));
extern void YY_XmlScanner_INIT_BUFFER YY_PROTO(( YY_BUFFER_STATE b, YY_XmlScanner_IFILE *file ));

#if YY_XmlScanner_DEBUG != 0
extern int YY_XmlScanner_DEBUG_FLAG ;
#endif
extern YY_XmlScanner_CHAR  *YY_XmlScanner_TEXT;
extern int YY_XmlScanner_LENG;
extern YY_XmlScanner_IFILE *YY_XmlScanner_IN;
extern YY_XmlScanner_OFILE *YY_XmlScanner_OUT;
#ifdef YY_XmlScanner_LEX_DEFINED
extern YY_XmlScanner_LEX_RETURN YY_XmlScanner_LEX ( YY_XmlScanner_LEX_PARAM )
YY_XmlScanner_LEX_PARAM_DEF
#else
#ifndef YY_DECL
extern YY_XmlScanner_LEX_RETURN YY_XmlScanner_LEX ( YY_XmlScanner_LEX_PARAM )
YY_XmlScanner_LEX_PARAM_DEF
#else
/* no declaration if oldstyle flex */
#endif
#endif
#else

#ifndef YY_XmlScanner_CURRENT_BUFFER
#define YY_XmlScanner_CURRENT_BUFFER YY_CURRENT_BUFFER
#endif
#ifndef YY_XmlScanner_CLASS
#define YY_XmlScanner_CLASS XmlScanner
#endif
#ifndef YY_XmlScanner_ECHO
#define YY_XmlScanner_ECHO yy_echo
#endif
#ifdef YY_XmlScanner_ECHO_PURE
#define YY_XmlScanner_ECHO_NOCODE
#endif

#ifndef YY_XmlScanner_ECHO_CODE
#ifndef YY_XmlScanner_IOSTREAM
#define YY_XmlScanner_ECHO_CODE fwrite( (char *) YY_XmlScanner_TEXT, YY_XmlScanner_LENG, 1, YY_XmlScanner_OUT );
#else
#define YY_XmlScanner_ECHO_CODE (YY_XmlScanner_OUT->write( (char *) YY_XmlScanner_TEXT, YY_XmlScanner_LENG));
#endif
#endif

#ifndef YY_XmlScanner_INPUT
#define YY_XmlScanner_INPUT yy_input
#endif
#ifdef YY_XmlScanner_INPUT_PURE
#define YY_XmlScanner_INPUT_NOCODE
#endif

#ifndef YY_XmlScanner_INPUT_CODE
#ifndef YY_XmlScanner_IOSTREAM
#define YY_XmlScanner_INPUT_CODE return result= fread(  buffer, 1,max_size,YY_XmlScanner_IN );
#else
#define YY_XmlScanner_INPUT_CODE if(YY_XmlScanner_IN->eof())  result=0;else {YY_XmlScanner_IN->read(buffer,max_size);result=YY_XmlScanner_IN->gcount();YY_XmlScanner_IN->clear(YY_XmlScanner_IN->rdstate()&(~std::ios::failbit));if(YY_XmlScanner_IN->bad()) result= -1;} return result;
#endif
#endif

#ifdef YY_XmlScanner_FATAL_ERROR_PURE
#define YY_XmlScanner_FATAL_ERRO_NOCODE
#endif
#ifndef YY_XmlScanner_FATAL_ERROR
#define YY_XmlScanner_FATAL_ERROR yy_fatal_error
#endif

#ifndef YY_XmlScanner_FATAL_ERROR_CODE
#ifndef YY_XmlScanner_IOSTREAM
#define YY_XmlScanner_FATAL_ERROR_CODE fputs( msg, YY_XmlScanner_ERRFILE );putc( '\n', YY_XmlScanner_ERRFILE );exit( 1 );
#else
#define YY_XmlScanner_FATAL_ERROR_CODE YY_XmlScanner_ERRFILE<< msg <<std::endl;exit( 1 );
#endif
#endif

#ifndef YY_XmlScanner_WRAP
#define YY_XmlScanner_WRAP yy_wrap
#endif
#ifdef YY_XmlScanner_WRAP_PURE
#define YY_XmlScanner_WRAP_NOCODE
#endif
#ifndef YY_XmlScanner_WRAP_CODE
#define YY_XmlScanner_WRAP_CODE return 1;
#endif


#ifndef YY_XmlScanner_INHERIT
#define YY_XmlScanner_INHERIT
#endif
#ifndef YY_XmlScanner_MEMBERS
#define YY_XmlScanner_MEMBERS 
#endif
#ifndef YY_XmlScanner_CONSTRUCTOR_PARAM
#define YY_XmlScanner_CONSTRUCTOR_PARAM
#endif
#ifndef YY_XmlScanner_CONSTRUCTOR_CODE
#define YY_XmlScanner_CONSTRUCTOR_CODE
#endif
#ifndef YY_XmlScanner_CONSTRUCTOR_INIT
#define YY_XmlScanner_CONSTRUCTOR_INIT
#endif
#ifndef YY_XmlScanner_DESTRUCTOR_CODE
#define YY_XmlScanner_DESTRUCTOR_CODE
#endif
typedef struct yy_buffer_state *YY_BUFFER_STATE;

class YY_XmlScanner_CLASS YY_XmlScanner_INHERIT
{
 private:/* data */
 YY_XmlScanner_CHAR  *yy_c_buf_p;
 YY_XmlScanner_CHAR  yy_hold_char;
 int yy_n_chars;
 int yy_init;
 int yy_start;
 int yy_did_buffer_switch_on_eof;
 private: /* functions */
 void yy_initialize();
 int input();
 int yyinput() {return input();};
 int yy_get_next_buffer();
 void yyunput( YY_XmlScanner_CHAR  c, YY_XmlScanner_CHAR  *buf_ptr );
 /* use long instead of yy_state_type because it is undef */
 long yy_get_previous_state_ ( void );
 long yy_try_NUL_trans_  ( long current_state_ );
 protected:/* non virtual */
 YY_BUFFER_STATE YY_XmlScanner_CURRENT_BUFFER;
 void YY_XmlScanner_RESTART ( YY_XmlScanner_IFILE *input_file );
 void YY_XmlScanner_SWITCH_TO_BUFFER( YY_BUFFER_STATE new_buffer );
 void YY_XmlScanner_LOAD_BUFFER_STATE( void );
 YY_BUFFER_STATE YY_XmlScanner_CREATE_BUFFER( YY_XmlScanner_IFILE *file, int size );
 void YY_XmlScanner_DELETE_BUFFER( YY_BUFFER_STATE b );
 void YY_XmlScanner_INIT_BUFFER( YY_BUFFER_STATE b, YY_XmlScanner_IFILE *file );
 protected: /* virtual */
 virtual void YY_XmlScanner_ECHO()
#ifdef YY_XmlScanner_ECHO_PURE
  =0
#endif
  ;
 virtual int  YY_XmlScanner_INPUT(char  *buf,int &result,int max_size)
#ifdef YY_XmlScanner_INPUT_PURE
  =0
#endif
  ;
 virtual void  YY_XmlScanner_FATAL_ERROR(char *msg)
#ifdef YY_XmlScanner_FATAL_ERROR_PURE
  =0
#endif
  ;
 virtual int  YY_XmlScanner_WRAP()
#ifdef YY_XmlScanner_WRAP_PURE
  =0
#endif
  ;
 public:
 YY_XmlScanner_CHAR  *YY_XmlScanner_TEXT;
 int YY_XmlScanner_LENG;
 YY_XmlScanner_IFILE *YY_XmlScanner_IN;
 YY_XmlScanner_OFILE *YY_XmlScanner_OUT;
 YY_XmlScanner_LEX_RETURN YY_XmlScanner_LEX ( YY_XmlScanner_LEX_PARAM);
 YY_XmlScanner_CLASS(YY_XmlScanner_CONSTRUCTOR_PARAM) ;
 virtual ~YY_XmlScanner_CLASS() ;
#if YY_XmlScanner_DEBUG != 0
 int YY_XmlScanner_DEBUG_FLAG;
#endif
 public: /* added members */
 YY_XmlScanner_MEMBERS 
};
#endif



/* declaration of externs for public use of yylex scanner */

/* % here is the declaration from section2 %header{ */ 
#line 142 "xmlscanner.l"
#endif
#line 384 "flexskel.h"

/* end of generated header */
