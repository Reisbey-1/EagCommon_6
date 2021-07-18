/* -----------------------------------------------------------------------
(c) Copyrigth 1999
University of Stuttgart
Institute for Nuclear Energy and Energy Systems (IKE)
Dept. for Knowledge Engineering and Numerics (WN)
--------------------------------------------------------------------------
  ###   #    #  #######               #         #     # #     #
   #    #   #   #                    #          #  #  # ##    #
   #    #  #    #                   #           #  #  # # #   #
   #    ###     #####              #            #  #  # #  #  #
   #    #  #    #                 #             #  #  # #   # #
   #    #   #   #                #              #  #  # #    ##
  ###   #    #  #######         #                ## ##  #     #
--------------------------------------------------------------------------
file:
xmlscanner.y
--------------------------------------------------------------------------
authors:
Kopetzky, Roland        ikerkope        kopetzky@ike.uni-stuttgart.de
--------------------------------------------------------------------------
version:
1.0
--------------------------------------------------------------------------
compiler:
flex++ Version 2.3.8-7, adapted from GNU flex by Alain Coetmeur
(coetmeur@icdc.fr)
--------------------------------------------------------------------------
options:
flexpp -8 -hxmlscanner.h -oxmlscanner.cpp -Sflexskel.cpp xmlscanner.l
--------------------------------------------------------------------------
content:
Flex specification for the InformationItem XML-Import
--------------------------------------------------------------------------
notes:
------------------------------------------------------------------------ */

%name XmlScanner

%define INHERIT
%define IOSTREAM
%define LEX_RETURN int
%define LEX scanValue
%define LEX_PARAM YY_XmlParser_STYPE &yylval

%define OFILE std::strstream
%define OFILE_DEFAULT &strOut
%define ERRFILE strError

%define CONSTRUCTOR_CODE ;
%define MEMBERS              \
	public:                  \
		std::strstream strOut;   \
		std::strstream strError;

%header{
#include "xmlparser.h"
%}

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <strstream>

%}


NL			(\r\n|\r|\n)
WS			[ \t\r\n]+
OPEN		"<"
CLOSE		">"
NAMESTART	[A-Za-z\200-\377_]
NAMECHAR	[A-Za-z\200-\377_0-9.-]
ESC			"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
NAME		{NAMESTART}{NAMECHAR}*
STRING		\"([^"&]|{ESC})*\"|\'([^'&]|{ESC})*\'

DOCTYPE		{OPEN}"!DOCTYPE"{WS}{NAME}{WS}"SYSTEM"({WS}{STRING})?{WS}{STRING}{CLOSE}
XMLTYPE     {OPEN}"?xml"({WS}{NAME}{WS}?"="{WS}?{STRING})*"?"{CLOSE}
STARTTAG	{OPEN}{NAME}({WS}{NAME}{WS}?"="{WS}?{STRING})*{CLOSE}
ENDTAG		{OPEN}"/"{NAME}{CLOSE}
DATA		[^<]+


%x ST
%x CONTENT

%%

{DOCTYPE}	            {
							BEGIN(CONTENT);
							return XmlParser::DOCTYPE;
						}
{XMLTYPE}	            {
							BEGIN(CONTENT);
							return XmlParser::DOCTYPE;
						}
<ST,INITIAL>{WS}	    {	/* ignore */	}

<ST>{OPEN}{NAME}		{
							yylval.s = strdup((const char *)yytext+1);
							return XmlParser::START;
						}
<ST>{NAME}				{
							yylval.s = strdup((const char *)yytext);
							return XmlParser::NAME;
						}
<ST>"="					{	return XmlParser::EQ;	}
<ST>{STRING}			{
							strncpy((char*)yytext+yyleng-1,"\0",1);
							yylval.s = strdup((const char *)yytext+1);
							return XmlParser::VALUE;
						}
<ST>{CLOSE}				{
							BEGIN(CONTENT);
							return XmlParser::CLOSE;
						}
<CONTENT>{STARTTAG}		{
							yyless(0);
							BEGIN(ST);
						}
<CONTENT>{WS}			{	/* ignore */	}
<CONTENT>{ENDTAG}		{
							strncpy((char*)yytext+yyleng-1,"\0",1);
							yylval.s = strdup((const char *)yytext+2);
							return XmlParser::END;
						}
<CONTENT>{DATA}			{
							yylval.s = strdup((const char *)yytext);
							return XmlParser::DATA;
						}
<CONTENT>{OPEN}			{
							yylval.s = strdup((const char *)yytext);
							return XmlParser::DATA;
						}
<CONTENT,ST,INITIAL>.	{
							strError << "UNDEFINED: " << yytext << std::endl;
						}

%%

/* -----------------------------------------------------------------------
                                 E O F         
----------------------------------------------------------------------- */