#ifndef YY_XmlParser_h_included
#define YY_XmlParser_h_included

#line 1 "bison.h"
/* before anything */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#endif
#include <stdio.h>

/* #line 14 "bison.h" */
#line 21 "xmlparser.h"
#define YY_XmlParser_LSP_NEEDED 
#define YY_XmlParser_ERROR_BODY  =0
#define YY_XmlParser_LEX_BODY  =0
#line 43 "xmlparser.y"

#include <string.h>
#include <stdlib.h> 
#include <iostream>
#include <strstream>
#include "xmldef.h"

#line 51 "xmlparser.y"
typedef union {
	char*       s;
	Attribute*  pAttribute;
	Attribute** pAttributeList;
} yy_XmlParser_stype;
#define YY_XmlParser_STYPE yy_XmlParser_stype
#define YY_XmlParser_LVAL  theTokenValue
#define YY_XmlParser_LEX  scanXml
#define YY_XmlParser_PARSE  parseXml
#define YY_XmlParser_MEMBERS  \
	virtual void startDocument(const StartDocumentEvent &) = 0; \
	virtual void startElement(const StartElementEvent &) = 0; \
	virtual void endElement(const EndElementEvent &) = 0;     \
	virtual void data(const DataEvent &) = 0;                 \
	void decode(DataEvent &);                                 \
	StartElementEvent curEvent;                               \
	bool wantDecode;
#define YY_XmlParser_CONSTRUCTOR_CODE  \
	curEvent.nAttributes = 0; \
	curEvent.attributes = NULL; \
	wantDecode = false;

#line 14 "bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_XmlParser_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_XmlParser_COMPATIBILITY 1
#else
#define  YY_XmlParser_COMPATIBILITY 0
#endif
#endif

#if YY_XmlParser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_XmlParser_LTYPE
#define YY_XmlParser_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_XmlParser_STYPE 
#define YY_XmlParser_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_XmlParser_DEBUG
#define  YY_XmlParser_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
#endif
#endif
#ifdef YY_XmlParser_STYPE
#ifndef yystype
#define yystype YY_XmlParser_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_XmlParser_USE_GOTO
#define YY_XmlParser_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_XmlParser_USE_GOTO
#define YY_XmlParser_USE_GOTO 0
#endif

#ifndef YY_XmlParser_PURE

/* #line 63 "bison.h" */
#line 108 "xmlparser.h"

#line 63 "bison.h"
/* YY_XmlParser_PURE */
#endif

/* #line 65 "bison.h" */
#line 115 "xmlparser.h"

#line 65 "bison.h"
/* prefix */
#ifndef YY_XmlParser_DEBUG

/* #line 67 "bison.h" */
#line 122 "xmlparser.h"

#line 67 "bison.h"
/* YY_XmlParser_DEBUG */
#endif
#ifndef YY_XmlParser_LSP_NEEDED

/* #line 70 "bison.h" */
#line 130 "xmlparser.h"

#line 70 "bison.h"
 /* YY_XmlParser_LSP_NEEDED*/
#endif
/* DEFAULT LTYPE*/
#ifdef YY_XmlParser_LSP_NEEDED
#ifndef YY_XmlParser_LTYPE
typedef
  struct XmlParser_yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  XmlParser_yyltype;

#define YY_XmlParser_LTYPE XmlParser_yyltype
#endif
#endif
/* DEFAULT STYPE*/
#ifndef YY_XmlParser_STYPE
#define YY_XmlParser_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_XmlParser_PARSE
#define YY_XmlParser_PARSE yyparse
#endif
#ifndef YY_XmlParser_LEX
#define YY_XmlParser_LEX yylex
#endif
#ifndef YY_XmlParser_LVAL
#define YY_XmlParser_LVAL yylval
#endif
#ifndef YY_XmlParser_LLOC
#define YY_XmlParser_LLOC yylloc
#endif
#ifndef YY_XmlParser_CHAR
#define YY_XmlParser_CHAR yychar
#endif
#ifndef YY_XmlParser_NERRS
#define YY_XmlParser_NERRS yynerrs
#endif
#ifndef YY_XmlParser_DEBUG_FLAG
#define YY_XmlParser_DEBUG_FLAG yydebug
#endif
#ifndef YY_XmlParser_ERROR
#define YY_XmlParser_ERROR yyerror
#endif

#ifndef YY_XmlParser_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_XmlParser_PARSE_PARAM
#ifndef YY_XmlParser_PARSE_PARAM_DEF
#define YY_XmlParser_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_XmlParser_PARSE_PARAM
#define YY_XmlParser_PARSE_PARAM void
#endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_XmlParser_PURE
extern YY_XmlParser_STYPE YY_XmlParser_LVAL;
#endif


/* #line 143 "bison.h" */
#line 208 "xmlparser.h"
#define	DOCTYPE	258
#define	EQ	259
#define	CLOSE	260
#define	NAME	261
#define	VALUE	262
#define	DATA	263
#define	START	264
#define	END	265


#line 143 "bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
#ifndef YY_XmlParser_CLASS
#define YY_XmlParser_CLASS XmlParser
#endif

#ifndef YY_XmlParser_INHERIT
#define YY_XmlParser_INHERIT
#endif
#ifndef YY_XmlParser_MEMBERS
#define YY_XmlParser_MEMBERS 
#endif
#ifndef YY_XmlParser_LEX_BODY
#define YY_XmlParser_LEX_BODY  
#endif
#ifndef YY_XmlParser_ERROR_BODY
#define YY_XmlParser_ERROR_BODY  
#endif
#ifndef YY_XmlParser_CONSTRUCTOR_PARAM
#define YY_XmlParser_CONSTRUCTOR_PARAM
#endif
/* choose between enum and const */
#ifndef YY_XmlParser_USE_CONST_TOKEN
#define YY_XmlParser_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_XmlParser_USE_CONST_TOKEN != 0
#ifndef YY_XmlParser_ENUM_TOKEN
#define YY_XmlParser_ENUM_TOKEN yy_XmlParser_enum_token
#endif
#endif

class YY_XmlParser_CLASS YY_XmlParser_INHERIT
{
public: 
#if YY_XmlParser_USE_CONST_TOKEN != 0
/* static const int token ... */

/* #line 182 "bison.h" */
#line 261 "xmlparser.h"
static const int DOCTYPE;
static const int EQ;
static const int CLOSE;
static const int NAME;
static const int VALUE;
static const int DATA;
static const int START;
static const int END;


#line 182 "bison.h"
 /* decl const */
#else
enum YY_XmlParser_ENUM_TOKEN { YY_XmlParser_NULL_TOKEN=0

/* #line 185 "bison.h" */
#line 278 "xmlparser.h"
	,DOCTYPE=258
	,EQ=259
	,CLOSE=260
	,NAME=261
	,VALUE=262
	,DATA=263
	,START=264
	,END=265


#line 185 "bison.h"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_XmlParser_PARSE(YY_XmlParser_PARSE_PARAM);
 virtual void YY_XmlParser_ERROR(char *msg) YY_XmlParser_ERROR_BODY;
#ifdef YY_XmlParser_PURE
#ifdef YY_XmlParser_LSP_NEEDED
 virtual int  YY_XmlParser_LEX(YY_XmlParser_STYPE *YY_XmlParser_LVAL,YY_XmlParser_LTYPE *YY_XmlParser_LLOC) YY_XmlParser_LEX_BODY;
#else
 virtual int  YY_XmlParser_LEX(YY_XmlParser_STYPE *YY_XmlParser_LVAL) YY_XmlParser_LEX_BODY;
#endif
#else
 virtual int YY_XmlParser_LEX() YY_XmlParser_LEX_BODY;
 YY_XmlParser_STYPE YY_XmlParser_LVAL;
#ifdef YY_XmlParser_LSP_NEEDED
 YY_XmlParser_LTYPE YY_XmlParser_LLOC;
#endif
 int YY_XmlParser_NERRS;
 int YY_XmlParser_CHAR;
#endif
#if YY_XmlParser_DEBUG != 0
public:
 int YY_XmlParser_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_XmlParser_CLASS(YY_XmlParser_CONSTRUCTOR_PARAM);
public:
 YY_XmlParser_MEMBERS 
};
/* other declare folow */
#endif


#if YY_XmlParser_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_XmlParser_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_XmlParser_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_XmlParser_DEBUG 
#define YYDEBUG YY_XmlParser_DEBUG
#endif
#endif

#endif
/* END */

/* #line 236 "bison.h" */
#line 343 "xmlparser.h"
#endif
