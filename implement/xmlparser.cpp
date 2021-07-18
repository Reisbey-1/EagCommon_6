#define YY_XmlParser_h_included

/*  A Bison++ parser, made from xmlparser.y  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */


#line 1 "bison.cpp"
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(_WIN32) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
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
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  

/* #line 73 "bison.cpp" */
#line 85 "xmlparser.cpp"
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

#line 73 "bison.cpp"
/* %{ and %header{ and %union, during decl */
#define YY_XmlParser_BISON 1
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
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_XmlParser_STYPE 
#define YY_XmlParser_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_XmlParser_DEBUG
#define  YY_XmlParser_DEBUG YYDEBUG
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

/* #line 117 "bison.cpp" */
#line 167 "xmlparser.cpp"

#line 117 "bison.cpp"
/*  YY_XmlParser_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "bison.cpp" */
#line 176 "xmlparser.cpp"

#line 121 "bison.cpp"
/* prefix */
#ifndef YY_XmlParser_DEBUG

/* #line 123 "bison.cpp" */
#line 183 "xmlparser.cpp"

#line 123 "bison.cpp"
/* YY_XmlParser_DEBUG */
#endif


#ifndef YY_XmlParser_LSP_NEEDED

/* #line 128 "bison.cpp" */
#line 193 "xmlparser.cpp"

#line 128 "bison.cpp"
 /* YY_XmlParser_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_XmlParser_LSP_NEEDED
#ifndef YY_XmlParser_LTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YY_XmlParser_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_XmlParser_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

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
#if YY_XmlParser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_XmlParser_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_XmlParser_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_XmlParser_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_XmlParser_PURE
#ifndef YYPURE
#define YYPURE YY_XmlParser_PURE
#endif
#endif
#ifdef YY_XmlParser_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_XmlParser_DEBUG 
#endif
#endif
#ifndef YY_XmlParser_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_XmlParser_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_XmlParser_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_XmlParser_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "bison.cpp" */
#line 306 "xmlparser.cpp"
#define	DOCTYPE	258
#define	EQ	259
#define	CLOSE	260
#define	NAME	261
#define	VALUE	262
#define	DATA	263
#define	START	264
#define	END	265


#line 236 "bison.cpp"
 /* #defines tokens */
#else
/* CLASS */
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
#ifndef YY_XmlParser_CONSTRUCTOR_CODE
#define YY_XmlParser_CONSTRUCTOR_CODE
#endif
#ifndef YY_XmlParser_CONSTRUCTOR_INIT
#define YY_XmlParser_CONSTRUCTOR_INIT
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

/* #line 280 "bison.cpp" */
#line 364 "xmlparser.cpp"
static const int DOCTYPE;
static const int EQ;
static const int CLOSE;
static const int NAME;
static const int VALUE;
static const int DATA;
static const int START;
static const int END;


#line 280 "bison.cpp"
 /* decl const */
#else
enum YY_XmlParser_ENUM_TOKEN { YY_XmlParser_NULL_TOKEN=0

/* #line 283 "bison.cpp" */
#line 381 "xmlparser.cpp"
	,DOCTYPE=258
	,EQ=259
	,CLOSE=260
	,NAME=261
	,VALUE=262
	,DATA=263
	,START=264
	,END=265


#line 283 "bison.cpp"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_XmlParser_PARSE (YY_XmlParser_PARSE_PARAM);
 virtual void YY_XmlParser_ERROR(char *msg) YY_XmlParser_ERROR_BODY;
#ifdef YY_XmlParser_PURE
#ifdef YY_XmlParser_LSP_NEEDED
 virtual int  YY_XmlParser_LEX (YY_XmlParser_STYPE *YY_XmlParser_LVAL,YY_XmlParser_LTYPE *YY_XmlParser_LLOC) YY_XmlParser_LEX_BODY;
#else
 virtual int  YY_XmlParser_LEX (YY_XmlParser_STYPE *YY_XmlParser_LVAL) YY_XmlParser_LEX_BODY;
#endif
#else
 virtual int YY_XmlParser_LEX() YY_XmlParser_LEX_BODY;
 YY_XmlParser_STYPE YY_XmlParser_LVAL;
#ifdef YY_XmlParser_LSP_NEEDED
 YY_XmlParser_LTYPE YY_XmlParser_LLOC;
#endif
 int   YY_XmlParser_NERRS;
 int    YY_XmlParser_CHAR;
#endif
#if YY_XmlParser_DEBUG != 0
 int YY_XmlParser_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_XmlParser_CLASS(YY_XmlParser_CONSTRUCTOR_PARAM);
public:
 YY_XmlParser_MEMBERS 
};
/* other declare folow */
#if YY_XmlParser_USE_CONST_TOKEN != 0

/* #line 314 "bison.cpp" */
#line 426 "xmlparser.cpp"
const int YY_XmlParser_CLASS::DOCTYPE=258;
const int YY_XmlParser_CLASS::EQ=259;
const int YY_XmlParser_CLASS::CLOSE=260;
const int YY_XmlParser_CLASS::NAME=261;
const int YY_XmlParser_CLASS::VALUE=262;
const int YY_XmlParser_CLASS::DATA=263;
const int YY_XmlParser_CLASS::START=264;
const int YY_XmlParser_CLASS::END=265;


#line 314 "bison.cpp"
 /* const YY_XmlParser_CLASS::token */
#endif
/*apres const  */
YY_XmlParser_CLASS::YY_XmlParser_CLASS(YY_XmlParser_CONSTRUCTOR_PARAM) YY_XmlParser_CONSTRUCTOR_INIT
{
#if YY_XmlParser_DEBUG != 0
YY_XmlParser_DEBUG_FLAG=0;
#endif
YY_XmlParser_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "bison.cpp" */
#line 451 "xmlparser.cpp"


#define	YYFINAL		19
#define	YYFLAG		-32768
#define	YYNTBASE	11

#define YYTRANSLATE(x) ((unsigned)(x) <= 265 ? yytranslate[x] : 19)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10
};

#if YY_XmlParser_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     5,     6,    12,    15,    18,    21,    22,    25,
    26
};

static const short yyrhs[] = {    12,
    13,     0,     3,     0,     0,     9,    17,    14,     5,    15,
     0,    16,    10,     0,    16,     8,     0,    16,    13,     0,
     0,    17,    18,     0,     0,     6,     4,     7,     0
};

#endif

#if YY_XmlParser_DEBUG != 0
static const short yyrline[] = { 0,
    83,    87,    99,   123,   127,   141,   153,   154,   158,   159,
   163
};

static const char * const yytname[] = {   "$","error","$illegal.","DOCTYPE",
"EQ","CLOSE","NAME","VALUE","DATA","START","END","document","prolog","element",
"@1","empty_or_content","content","attribute_seq_opt","attribute",""
};
#endif

static const short yyr1[] = {     0,
    11,    12,    14,    13,    15,    16,    16,    16,    17,    17,
    18
};

static const short yyr2[] = {     0,
     2,     1,     0,     5,     2,     2,     2,     0,     2,     0,
     3
};

static const short yydefact[] = {     0,
     2,     0,    10,     1,     3,     0,     0,     9,     0,     8,
    11,     4,     0,     6,     5,     7,     0,     0,     0
};

static const short yydefgoto[] = {    17,
     2,     4,     7,    12,    13,     5,     8
};

static const short yypact[] = {     0,
-32768,    -5,-32768,-32768,    -1,     2,     3,-32768,     4,-32768,
-32768,-32768,    -8,-32768,-32768,-32768,     7,     9,-32768
};

static const short yypgoto[] = {-32768,
-32768,    -3,-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		11


static const short yytable[] = {    14,
     3,    15,     1,     3,     6,     9,    18,    10,    19,    16,
    11
};

static const short yycheck[] = {     8,
     9,    10,     3,     9,     6,     4,     0,     5,     0,    13,
     7
};

#line 325 "bison.cpp"
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#if YY_XmlParser_USE_GOTO != 0
/* 
 SUPRESSION OF GOTO : on some C++ compiler (sun c++)
  the goto is strictly forbidden if any constructor/destructor
  is used in the whole function (very stupid isn't it ?)
 so goto are to be replaced with a 'while/switch/case construct'
 here are the macro to keep some apparent compatibility
*/
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
/* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
  YYDECLARELABEL(yynewstate)
  YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
  YYDECLARELABEL(yydefault)
  YYDECLARELABEL(yyreduce)
  YYDECLARELABEL(yyerrlab)   /* here on detecting error */
  YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
  YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
  YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
  YYDECLARELABEL(yyerrhandle)  
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __XmlParser_alloca_free_ptr(char *ptr,char *ref)
{if(ptr!=ref) free(ptr);
 return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __XmlParser_alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_XmlParser_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_XmlParser_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_XmlParser_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_XmlParser_CHAR = (token), YY_XmlParser_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_XmlParser_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_XmlParser_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_XmlParser_PURE
/* UNPURE */
#define YYLEX           YY_XmlParser_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_XmlParser_CHAR;                      /*  the lookahead symbol        */
YY_XmlParser_STYPE      YY_XmlParser_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_XmlParser_NERRS;                 /*  number of parse errors so far */
#ifdef YY_XmlParser_LSP_NEEDED
YY_XmlParser_LTYPE YY_XmlParser_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_XmlParser_LSP_NEEDED
#define YYLEX           YY_XmlParser_LEX(&YY_XmlParser_LVAL, &YY_XmlParser_LLOC)
#else
#define YYLEX           YY_XmlParser_LEX(&YY_XmlParser_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_XmlParser_DEBUG != 0
int YY_XmlParser_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy (char *from, char *to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy (char *from, char *to, int count)
#else
static void __yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
#endif
#endif
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
 YY_XmlParser_CLASS::
#endif
     YY_XmlParser_PARSE(YY_XmlParser_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_XmlParser_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_XmlParser_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_XmlParser_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_XmlParser_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_XmlParser_LSP_NEEDED
  YY_XmlParser_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_XmlParser_LTYPE *yyls = yylsa;
  YY_XmlParser_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_XmlParser_PURE
  int YY_XmlParser_CHAR;
  YY_XmlParser_STYPE YY_XmlParser_LVAL;
  int YY_XmlParser_NERRS;
#ifdef YY_XmlParser_LSP_NEEDED
  YY_XmlParser_LTYPE YY_XmlParser_LLOC;
#endif
#endif

  YY_XmlParser_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_XmlParser_NERRS = 0;
  YY_XmlParser_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_XmlParser_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
YYLABEL(yynewstate)

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_XmlParser_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_XmlParser_LSP_NEEDED
      YY_XmlParser_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_XmlParser_LSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_XmlParser_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_XmlParser_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_XmlParser_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_XmlParser_LSP_NEEDED
      yyls = (YY_XmlParser_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_XmlParser_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_XmlParser_DEBUG != 0
      if (YY_XmlParser_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  YYGOTO(yybackup);
YYLABEL(yybackup)

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* YYLABEL(yyresume) */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yydefault);

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_XmlParser_CHAR == YYEMPTY)
    {
#if YY_XmlParser_DEBUG != 0
      if (YY_XmlParser_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_XmlParser_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_XmlParser_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_XmlParser_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_XmlParser_DEBUG != 0
      if (YY_XmlParser_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_XmlParser_CHAR);

#if YY_XmlParser_DEBUG != 0
      if (YY_XmlParser_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_XmlParser_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_XmlParser_CHAR, YY_XmlParser_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    YYGOTO(yydefault);

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrlab);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrlab);

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_XmlParser_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_XmlParser_CHAR != YYEOF)
    YY_XmlParser_CHAR = YYEMPTY;

  *++yyvsp = YY_XmlParser_LVAL;
#ifdef YY_XmlParser_LSP_NEEDED
  *++yylsp = YY_XmlParser_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  YYGOTO(yynewstate);

/* Do the default action for the current state.  */
YYLABEL(yydefault)

  yyn = yydefact[yystate];
  if (yyn == 0)
    YYGOTO(yyerrlab);

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
YYLABEL(yyreduce)
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


/* #line 811 "bison.cpp" */
#line 1047 "xmlparser.cpp"

  switch (yyn) {

case 2:
#line 88 "xmlparser.y"
{
			StartDocumentEvent event;

			event.version.len = strlen("1.0");
			event.version.ptr = "1.0";

			startDocument(event);
		;
    break;}
case 3:
#line 101 "xmlparser.y"
{
			curEvent.gi.len = strlen(yyvsp[-1].s);
			curEvent.gi.ptr = yyvsp[-1].s;

			startElement(curEvent);

			// cleanup
			if ( curEvent.nAttributes > 0 ) {
				for (unsigned i=0; i<curEvent.nAttributes; i++)
				{
					free(curEvent.attributes[i].name.ptr);
					free(curEvent.attributes[i].data.ptr);
				}
				free(curEvent.attributes);
	
				curEvent.attributes = NULL;
				curEvent.nAttributes = 0;
			}

			free(yyvsp[-1].s);
		;
    break;}
case 5:
#line 128 "xmlparser.y"
{
			EndElementEvent event;

			event.gi.len = strlen(yyvsp[0].s);
			event.gi.ptr = yyvsp[0].s;

			endElement(event);

			free(yyvsp[0].s);
		;
    break;}
case 6:
#line 142 "xmlparser.y"
{
			DataEvent event;

			event.data.len = strlen(yyvsp[0].s);
			event.data.ptr = yyvsp[0].s;

			decode(event);
			data(event);

			free(yyvsp[0].s);
		;
    break;}
case 11:
#line 164 "xmlparser.y"
{
			int n    = curEvent.nAttributes;

			curEvent.attributes = (Attribute*)realloc( (void*)curEvent.attributes, sizeof(Attribute) * (n+1) ); 

			curEvent.attributes[n].name.len = strlen(yyvsp[-2].s);
			curEvent.attributes[n].name.ptr = (Char*)malloc( sizeof(Char) * strlen(yyvsp[-2].s) );
			strncpy(curEvent.attributes[n].name.ptr, yyvsp[-2].s, curEvent.attributes[n].name.len);

			curEvent.attributes[n].data.len = strlen(yyvsp[0].s);
			curEvent.attributes[n].data.ptr = (Char*)malloc( sizeof(Char) * strlen(yyvsp[0].s) );
			strncpy(curEvent.attributes[n].data.ptr, yyvsp[0].s, curEvent.attributes[n].data.len);

			curEvent.nAttributes++;

			free(yyvsp[-2].s);
			free(yyvsp[0].s);
		;
    break;}
}

#line 811 "bison.cpp"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_XmlParser_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_XmlParser_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_XmlParser_LLOC.first_line;
      yylsp->first_column = YY_XmlParser_LLOC.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  YYGOTO(yynewstate);

YYLABEL(yyerrlab)   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_XmlParser_NERRS;

#ifdef YY_XmlParser_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_XmlParser_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_XmlParser_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_XmlParser_ERROR_VERBOSE */
	YY_XmlParser_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_XmlParser_CHAR == YYEOF)
	YYABORT;

#if YY_XmlParser_DEBUG != 0
      if (YY_XmlParser_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_XmlParser_CHAR, yytname[yychar1]);
#endif

      YY_XmlParser_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  YYGOTO(yyerrhandle);

YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) YYGOTO(yydefault);
#endif

YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_XmlParser_LSP_NEEDED
  yylsp--;
#endif

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

YYLABEL(yyerrhandle)

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yyerrdefault);

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    YYGOTO(yyerrdefault);

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrpop);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrpop);

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_XmlParser_DEBUG != 0
  if (YY_XmlParser_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_XmlParser_LVAL;
#ifdef YY_XmlParser_LSP_NEEDED
  *++yylsp = YY_XmlParser_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */

/* #line 1010 "bison.cpp" */
#line 1338 "xmlparser.cpp"
#line 184 "xmlparser.y"


void XmlParser::decode(DataEvent &event)
{
	// check on decode
	if ( !wantDecode )
		return;

	int nCode(0);
	Char cCode[3];
	bool bFound(false);
	size_t count(0);

	for (size_t i=0; i<event.data.len; i++)
	{
		if ( event.data.ptr[i] == '&' )
		{
			// check on following code
			if ( i < event.data.len-5 )
			{
				if ( event.data.ptr[i+1] == '#' && event.data.ptr[i+5] == ';' )
				{
					cCode[0] = event.data.ptr[i+2];
					cCode[1] = event.data.ptr[i+3];
					cCode[2] = event.data.ptr[i+4];
					nCode = atoi(cCode);
					bFound = true;

					switch(nCode)
					{
						case 161: { event.data.ptr[count++] = '¡'; break; }
						case 162: { event.data.ptr[count++] = '¢'; break; }
						case 163: { event.data.ptr[count++] = '£'; break; }
						case 164: { event.data.ptr[count++] = '¤'; break; }
						case 165: { event.data.ptr[count++] = '¥'; break; }
						case 166: { event.data.ptr[count++] = '¦'; break; }
						case 167: { event.data.ptr[count++] = '§'; break; }
						case 168: { event.data.ptr[count++] = '¨'; break; }
						case 169: { event.data.ptr[count++] = '©'; break; }
						case 170: { event.data.ptr[count++] = 'ª'; break; }
						case 171: { event.data.ptr[count++] = '«'; break; }
						case 172: { event.data.ptr[count++] = '¬'; break; }
						case 173: { event.data.ptr[count++] = '­'; break; }
						case 174: { event.data.ptr[count++] = '®'; break; }
						case 175: { event.data.ptr[count++] = '¯'; break; }
						case 176: { event.data.ptr[count++] = '°'; break; }
						case 177: { event.data.ptr[count++] = '±'; break; }
						case 178: { event.data.ptr[count++] = '²'; break; }
						case 179: { event.data.ptr[count++] = '³'; break; }
						case 180: { event.data.ptr[count++] = '´'; break; }
						case 181: { event.data.ptr[count++] = 'µ'; break; }
						case 182: { event.data.ptr[count++] = '¶'; break; }
						case 183: { event.data.ptr[count++] = '·'; break; }
						case 184: { event.data.ptr[count++] = '¸'; break; }
						case 185: { event.data.ptr[count++] = '¹'; break; }
						case 186: { event.data.ptr[count++] = 'º'; break; }
						case 187: { event.data.ptr[count++] = '»'; break; }
						case 188: { event.data.ptr[count++] = '¼'; break; }
						case 189: { event.data.ptr[count++] = '½'; break; }
						case 190: { event.data.ptr[count++] = '¾'; break; }
						case 191: { event.data.ptr[count++] = '¿'; break; }
						case 192: { event.data.ptr[count++] = 'À'; break; }
						case 193: { event.data.ptr[count++] = 'Á'; break; }
						case 194: { event.data.ptr[count++] = 'Â'; break; }
						case 195: { event.data.ptr[count++] = 'Ã'; break; }
						case 196: { event.data.ptr[count++] = 'Ä'; break; }
						case 197: { event.data.ptr[count++] = 'Å'; break; }
						case 198: { event.data.ptr[count++] = 'Æ'; break; }
						case 199: { event.data.ptr[count++] = 'Ç'; break; }
						case 200: { event.data.ptr[count++] = 'È'; break; }
						case 201: { event.data.ptr[count++] = 'É'; break; }
						case 202: { event.data.ptr[count++] = 'Ê'; break; }
						case 203: { event.data.ptr[count++] = 'Ë'; break; }
						case 204: { event.data.ptr[count++] = 'Ì'; break; }
						case 205: { event.data.ptr[count++] = 'Í'; break; }
						case 206: { event.data.ptr[count++] = 'Î'; break; }
						case 207: { event.data.ptr[count++] = 'Ï'; break; }
						case 208: { event.data.ptr[count++] = 'Ð'; break; }
						case 209: { event.data.ptr[count++] = 'Ñ'; break; }
						case 210: { event.data.ptr[count++] = 'Ò'; break; }
						case 211: { event.data.ptr[count++] = 'Ó'; break; }
						case 212: { event.data.ptr[count++] = 'Ô'; break; }
						case 213: { event.data.ptr[count++] = 'Õ'; break; }
						case 214: { event.data.ptr[count++] = 'Ö'; break; }
						case 215: { event.data.ptr[count++] = '×'; break; }
						case 216: { event.data.ptr[count++] = 'Ø'; break; }
						case 217: { event.data.ptr[count++] = 'Ù'; break; }
						case 218: { event.data.ptr[count++] = 'Ú'; break; }
						case 219: { event.data.ptr[count++] = 'Û'; break; }
						case 220: { event.data.ptr[count++] = 'Ü'; break; }
						case 221: { event.data.ptr[count++] = 'Ý'; break; }
						case 222: { event.data.ptr[count++] = 'Þ'; break; }
						case 223: { event.data.ptr[count++] = 'ß'; break; }
						case 224: { event.data.ptr[count++] = 'à'; break; }
						case 225: { event.data.ptr[count++] = 'á'; break; }
						case 226: { event.data.ptr[count++] = 'â'; break; }
						case 227: { event.data.ptr[count++] = 'ã'; break; }
						case 228: { event.data.ptr[count++] = 'ä'; break; }
						case 229: { event.data.ptr[count++] = 'å'; break; }
						case 230: { event.data.ptr[count++] = 'æ'; break; }
						case 231: { event.data.ptr[count++] = 'ç'; break; }
						case 232: { event.data.ptr[count++] = 'è'; break; }
						case 233: { event.data.ptr[count++] = 'é'; break; }
						case 234: { event.data.ptr[count++] = 'ê'; break; }
						case 235: { event.data.ptr[count++] = 'ë'; break; }
						case 236: { event.data.ptr[count++] = 'ì'; break; }
						case 237: { event.data.ptr[count++] = 'í'; break; }
						case 238: { event.data.ptr[count++] = 'î'; break; }
						case 239: { event.data.ptr[count++] = 'ï'; break; }
						case 240: { event.data.ptr[count++] = 'ð'; break; }
						case 241: { event.data.ptr[count++] = 'ñ'; break; }
						case 242: { event.data.ptr[count++] = 'ò'; break; }
						case 243: { event.data.ptr[count++] = 'ó'; break; }
						case 244: { event.data.ptr[count++] = 'ô'; break; }
						case 245: { event.data.ptr[count++] = 'õ'; break; }
						case 246: { event.data.ptr[count++] = 'ö'; break; }
						case 247: { event.data.ptr[count++] = '÷'; break; }
						case 248: { event.data.ptr[count++] = 'ø'; break; }
						case 249: { event.data.ptr[count++] = 'ù'; break; }
						case 250: { event.data.ptr[count++] = 'ú'; break; }
						case 251: { event.data.ptr[count++] = 'û'; break; }
						case 252: { event.data.ptr[count++] = 'ü'; break; }
						case 253: { event.data.ptr[count++] = 'ý'; break; }
						case 254: { event.data.ptr[count++] = 'þ'; break; }
						case 255: { event.data.ptr[count++] = 'ÿ'; break; }
						default:
							bFound = false;
					}

					if ( bFound )
					{
						// skip code characters
						i+=5;
						continue;
					}
				}
				else if ( event.data.ptr[i+1] == 'g' && event.data.ptr[i+2] == 't' && event.data.ptr[i+3] == ';' )
				{
					event.data.ptr[count++] = '>';
					i+=3;
					continue;
				}
				else if ( event.data.ptr[i+1] == 'l' && event.data.ptr[i+2] == 't' && event.data.ptr[i+3] == ';' )
				{
					event.data.ptr[count++] = '<';
					i+=3;
					continue;
				}
				else if ( event.data.ptr[i+1] == 'a' && event.data.ptr[i+2] == 'm' && event.data.ptr[i+3] == 'p' && event.data.ptr[i+4] == ';' )
				{
					event.data.ptr[count++] = '&';
					i+=4;
					continue;
				}
			}
			else if ( i < event.data.len-4 )
			{
				if ( event.data.ptr[i+1] == 'g' && event.data.ptr[i+2] == 't' && event.data.ptr[i+3] == ';' )
				{
					event.data.ptr[count++] = '>';
					i+=3;
					continue;
				}
				else if ( event.data.ptr[i+1] == 'l' && event.data.ptr[i+2] == 't' && event.data.ptr[i+3] == ';' )
				{
					event.data.ptr[count++] = '<';
					i+=3;
					continue;
				}
				else if ( event.data.ptr[i+1] == 'a' && event.data.ptr[i+2] == 'm' && event.data.ptr[i+3] == 'p' && event.data.ptr[i+4] == ';' )
				{
					event.data.ptr[count++] = '&';
					i+=4;
					continue;
				}
			}
			else if ( i < event.data.len-3 )
			{
				if ( event.data.ptr[i+1] == 'g' && event.data.ptr[i+2] == 't' && event.data.ptr[i+3] == ';' )
				{
					event.data.ptr[count++] = '>';
					i+=3;
					continue;
				}
				else if ( event.data.ptr[i+1] == 'l' && event.data.ptr[i+2] == 't' && event.data.ptr[i+3] == ';' )
				{
					event.data.ptr[count++] = '<';
					i+=3;
					continue;
				}
			}
		}

		event.data.ptr[count++] = event.data.ptr[i];
	}

	// rewrite length
	event.data.len = count;
}


/* -----------------------------------------------------------------------
                                 E O F         
----------------------------------------------------------------------- */
