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
xmlparser.y
--------------------------------------------------------------------------
authors:
Kopetzky, Roland        ikerkope        kopetzky@ike.uni-stuttgart.de
--------------------------------------------------------------------------
version:
1.0
--------------------------------------------------------------------------
compiler:
bison++ Version 1.21-8, adapted from GNU bison by Alain Coetmeur
(coetmeur@icdc.fr)
--------------------------------------------------------------------------
options:
bisonpp -d -o xmlparser.cpp -h xmlparser.h -S bison.cpp -v xmlparser.y
--------------------------------------------------------------------------
content:
Bison specification for InformationItem XML-Import
--------------------------------------------------------------------------
notes/problems:
------------------------------------------------------------------------ */

%name XmlParser

%define LSP_NEEDED
%define ERROR_BODY =0
%define LEX_BODY =0

%header{
#include <string.h>
#include <stdlib.h> 
#include <iostream>
#include <strstream>
#include "xmldef.h"
%}

%union {
	char*       s;
	Attribute*  pAttribute;
	Attribute** pAttributeList;
}

%define LVAL theTokenValue
%define LEX scanXml
%define PARSE parseXml

%define MEMBERS \
	virtual void startDocument(const StartDocumentEvent &) = 0; \
	virtual void startElement(const StartElementEvent &) = 0; \
	virtual void endElement(const EndElementEvent &) = 0;     \
	virtual void data(const DataEvent &) = 0;                 \
	void decode(DataEvent &);                                 \
	StartElementEvent curEvent;                               \
	bool wantDecode;

%define CONSTRUCTOR_CODE \
	curEvent.nAttributes = 0; \
	curEvent.attributes = NULL; \
	wantDecode = false;

%token DOCTYPE EQ CLOSE
%token <s> NAME VALUE DATA START END

%start document

%%

document
	:	prolog element
;

prolog
	:	DOCTYPE
		{
			StartDocumentEvent event;

			event.version.len = strlen("1.0");
			event.version.ptr = "1.0";

			startDocument(event);
		}
;

element
	:	START
		attribute_seq_opt
		{
			curEvent.gi.len = strlen($1);
			curEvent.gi.ptr = $1;

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

			free($1);
		}
		CLOSE
		empty_or_content
;

empty_or_content
	:	content END
		{
			EndElementEvent event;

			event.gi.len = strlen($2);
			event.gi.ptr = $2;

			endElement(event);

			free($2);
		}
;

content
	:	content DATA
		{
			DataEvent event;

			event.data.len = strlen($2);
			event.data.ptr = $2;

			decode(event);
			data(event);

			free($2);
		}
	|	content element
	|	/*empty*/
;

attribute_seq_opt
	:	attribute_seq_opt attribute
	|	/*empty*/
;

attribute
	:	NAME EQ VALUE
		{
			int n    = curEvent.nAttributes;

			curEvent.attributes = (Attribute*)realloc( (void*)curEvent.attributes, sizeof(Attribute) * (n+1) ); 

			curEvent.attributes[n].name.len = strlen($1);
			curEvent.attributes[n].name.ptr = (Char*)malloc( sizeof(Char) * strlen($1) );
			strncpy(curEvent.attributes[n].name.ptr, $1, curEvent.attributes[n].name.len);

			curEvent.attributes[n].data.len = strlen($3);
			curEvent.attributes[n].data.ptr = (Char*)malloc( sizeof(Char) * strlen($3) );
			strncpy(curEvent.attributes[n].data.ptr, $3, curEvent.attributes[n].data.len);

			curEvent.nAttributes++;

			free($1);
			free($3);
		}
;

%%

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
