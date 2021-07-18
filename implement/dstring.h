/* Mini String Klasse mit der dynamisch, schnell und effektiv
beliebig (long*long Bytes) grosse Strings verwaltet werden können.

  Groester Vorteil: die Klasse kommt ohne CString, strstream oder andere von
  diesen Klassen abhängigen Teilen aus!
  CString ist auf 32kByte größe Begrenzt und
  strstream ist unakzeptabel langsam
  andere String Klassen mit akzeptablem Funktionsumfang wurden nicht gefunden


--------------------------------------------------------------------------
Autoren:
<Freihofer, Hartmut>	<facg1328>	<freihofer@ike.uni-stuttgart.de>

Beta-Tester:
Dieter Wagner, 

--------------------------------------------------------------------------
Changes:
$Log: dstring.h,v $
Revision 1.2  2004/02/04 17:39:14  h.Freihofer
no message

Revision 1.1.1.1  2002/01/25 16:31:40  h.Freihofer
no message

Revision 1.10  1997/10/15 08:30:16  facg1328
einige Kleinigkeiten

Revision 1.9  1997/10/02 06:45:34  facg1328
const von [] entfernt

Revision 1.8  1997/10/02 06:27:22  facg1328
Suchalgorithmus verbessert, ergaenzt (caseinsensitive) und beschleunigt

Revision 1.7  1997/09/18 12:34:10  facg1328
Suchfunktionen addiert

Revision 1.1.1.1  1997/08/21 11:06:23  facg1328
Beta 1.0

Revision 1.6  1997/08/21 10:05:21  facg1328
Doku verbessert

Revision 1.5  1997/08/21 09:21:15  facg1328
Verschiedene 'cin' Funktionalitaeten hinzugefuegt

Revision 1.1.1.2  1997/07/22 09:03:26  facg1328
Beta 0.9

----------------------------------------------------------------------- */

#ifndef _DString_h
#define _DString_h

//---Compiler-/ Systemabhängige Definitionen---

#ifdef WIN32
	#include "afx.h"
#else
	#define BOOL int
	#define FALSE 0
	#define TRUE 1
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
#endif

//---------------------------------------------

//---Compilerunabhängige Bibis:----------------
#include <iostream> /// DLG
#include <iomanip> /// DLG
//#include <string.h>
#include <string>
#include <sstream>
#include <iosfwd>
#include <limits.h>
//---------------------------------------------

namespace eag {


#ifdef DSTRING_EXPORTS
#define DSTRING_API __declspec(dllexport)
#else
#define DSTRING_API __declspec(dllimport)
#endif

/**@name Definitions */
//@{

	/** Wenn mit sehr grossen Speicherblöcken gearbeitet wird, empfiehlt
	es sich VERYLARGE zu definieren um die Laengenprüfung einzuschalten.
	Ist man sicher, daß LONG_MAX nicht überschritten wird, sollte man
	VERYLARGE zugunsten der Performance nicht definiereen (wurde bisher
	noch nicht getestet).
	Durch die Definition von VERYLARGE, erhoeht sich die Kapazitaet nicht!<BR>
	Groesster einzulagernder Block:<BR>
	LONG_MAX        2147483647L          (2.1 GByte)<BR>
	*/
/**#define VERYLARGE*/

//@}



/* Modul-Eintraege fuer DOC++ ---------------------------------- */
/** 	<B>PROJECT: </B><BR>
	DString-Klassse<BR>
	<P>
	<B>MODULBESCHREIBUNG:</B><BR>
	Die Klasse DString wurde geschrieben um "unbegrenzt" große Strings schnell
	und effektiv verwalten zu können.<BR>
	"unbegrenzt" heißt: LONG_MAX       2147483647L   (2.1 GByte)<BR>
	"effektiv" heißt: <BR>
	Es werden immer Speicherblöcke der Größe "WACHSTUM" (im Haeder definiert) mit new
	allokiert. Werden Daten eingelagert, wird zuerst dieser Block vollgeschrieben
	und anschliesend so viele Blöcke mit new gehohlt, bis für alle Daten Platz ist.
	Dies ist zwar etwas verschwenderisch, da für jeden Block 16 Bytes an zusätzlichem
	Speicher benötigt wird, aber die Pervormance wird hierdurch	enorm gesteigert.<BR>
	"schnell" heißt:<BR>
	Wird der interne Speicher zu klein, wird nicht mit 'realloc' oder oder mit 'new' versucht
	neuen, gröseren Speicher anzufordern um anschliesend alles umzukopieren (passiert intern
	auch bei 'realloc'), sondern es werden lediglich neue, konstant große Speicherblöcke allokiert
	und in einer liniearen Liste verkettet.<BR>
	Bei der Ausgabe wird dann lediglich einmal der ganze Inhalt in einen ausreichend großen Puffer 
	umkopiert. Dies kann jedoch ebenfalls umgangen werden indem man den DString über einen ostream
	ausgibt.
	<P>
	Weitere  Features:<BR>
  - bel. wählbares inkrementelles Wachstum des Strings (im Haeder definiert)<BR>
  - bel. Ausgabe von Zeichenketten, Anzahl, Ort. über Funktion<BR>
  - Suchen von Zeichenketten (casesensitive und caseinsensitive)<BR>
  - Automatisches Wachstum (sollange der HS reicht)<BR>
  - Eingabe über >> Operator (z.B. mit "cin >> DString;")<BR>
  - Ausgabe über << Operator (z.B. mit "ofstream << DString;" )<BR>
  - Eingabe über << Operator fuer versch. Typen (wchar_t, wchar_t *,int, long, ...)<BR>
  - Ausgabe über 'read(wchar_t*,int)' -> polimorphisch zu cin. Die hier implementierten Funktionen wurden
	im Hinblich auf die Verwendung als Eingabestream fuer flex++ dazugefuegt.<BR>
  - Vermeidet man die Ausgabe über folgende Funktionen:<BR>
	<UL>
	<LI>getstr(alle Parameter),
	<LI>(DSting1 + DString2) ->bei der Addition zweier DString Objekte wird im Objekt
		'DString2' ein Ausgabefeld erzeugt, sowie beim
	<LI>+=(DString) Anfügen von DString Objekt,
	<LI>(DString)[] holen einzelner Zeichen aus dem Objekt,
	<LI>get() und
	<LI>read(),
	</UL>
	wird weder ein internes Ausgabefeld generiert noch die Daten irgendwohin kopiert. Der Speicher
	kann so effektiv genutzt werden und die Geschwindigkeit laest nichts zu wuenschen uebrig.<BR>
	(Siehe hierzu auch die Methode 'ausgabe_loeschen()').
	<P>
	@memo DString Klasse (Dynamisch wachsender String mit wählbarem "Wachstumsfaktor")
	@author	<A HREF="mailto:freihofer@ike.uni-stuttgart.de">Hartmut Freihofer IKE(WN)</A><P>
	@version $RCSfile: dstring.h,v $
		<BR> $Revision: 1.2 $
		<BR> $State: Exp $
*/

/* ENDE Modul-Eintraege fuer DOC++ ------------------------------------ */


//##ModelId=3978398D0356
class DSTRING_API DString :  public std::wstringstream  /// DLG
{
public:
	
/**@name Attribute Declarations (public) */
//@{
	/**
	Nullterminierter String fuer die Ausgabe (wird intern allokiert und zerstört).<BR>
	@memo Öfentlicher Ausgabestring
	*/
	//##ModelId=3978398E000E
	mutable wchar_t *Ausgabe;

	/** Größe der Speicherblöcke, um die der interner Speicher wächst.<BR>
	Intitialisiert mit 240<BR>
	Bei der Optimierung des 'DString' fuer ein bestimmtes Problem sollte man nicht 
	zurueckschrecken diese Groese zu aendern:<BR>
	<UL>
	<LI>Bei sehr grossen Datenmengen (> 1 MByte) sollte man die Wachstumsgroese auf mindestens 
		(4096 - 2 * sizeof (int)) stellen also bei 32 Bit Maschinen auf 4088.
		Dies ergibt dann bei einem MByte Daten etwa 250 Speicherblöcke und ca. 1 kByte an
		zusaetzlichem Speicher fuer die interne Speicherverwaltung.
	<LI>Es ist zu beachten dass diese Groese bei allen Objekten eines Projektes gilt und 
		durch den Benutzer nicht mehr beinflusst werden kann. Dies gilt insbesondere beim
		Einsatz in Bibliotheken.
	</UL>
	@memo Statische Wachstumsgrösse 
	*/
    enum { WACHSTUM = (256 - 2 * sizeof ( int ))} ;

//@}


protected:
/**@name Attribute Declarations (protected) */
	//@{	
	/**
	Strukt der Speicherteile (Verkettete Liste)
	*/
	typedef struct Speicher_Teil{		//Verkettete Liste (Wie im Lehrbuch)
		wchar_t pC_Buff[WACHSTUM];		//Speicherstelle, an der die Daten gehalten werden
		Speicher_Teil * naechster;		//Näcste Speicherstelle
		Speicher_Teil * vorgaenger;		//vorige Speicherstelle
	} varSpeicher_Teil;

	/**
	Zeiger auf den Anfang des internen Speichers
	*/
	//##ModelId=3978398E0004
	Speicher_Teil* Anfang_Speicher;

	/**
	Zeiger auf das Ende des internen Speichers (hier wird beim Anfügen geschrieben)
	*/
	//##ModelId=3978398D03D0
	Speicher_Teil* Letzter;

	/**
	Aktueller Füllstand des letzten Speicherteils
	*/
	//##ModelId=3978398D03BA
	long Fuellstand;

	/**
	Aktuelle Zahl aller allokierten Speicherteile.
	*/
	//##ModelId=3978398D03B0
	long Anzahl_Speicher_Teile;

	/**
	Formatierung bei float und double Konvertierungen.<BR>
	Kann über << format("Formatierung"); gesetzt werden.<BR>
	*/
	//##ModelId=3978398D03A6
	wchar_t formatstr[20];

	//konvertierung fon floats und doubles mit kommas:
	//##ModelId=3978398D039D
	BOOL Komma;

	/**
	Flag, das die Synchronität zwischen internem Puffer und <BR>
	Ausgabestring anzeigt.<BR>
	->Laufzeitvorteil bei der Ausgabe von größeren Strings über die bei<BR>
	der Methode "ausgabe_loeschen()" beschriebenen  Ausgabemethoden.
	*/
	//##ModelId=3978398D039C
	BOOL A_sync;

	/** Aktuelle Leseposition, wenn aus DString ueber 'cin' gelesen wird*/
	//##ModelId=3978398D0392
	long read_pos;

	/** Anzahl der zuletzt gelesener Zeichen bei unformatiertem lesen*/
	//##ModelId=3978398D038A
	long read_last;

	/** To lock certain kinds of stuff in this class (this mades DString thread-save)*/
//	CCriticalSection m_CriticalSection;

//@}


protected:

/**@name Method Declarations (private) */
//@{
	/**
	Hohlt neuen Speicherteil und setzt interne Variablen.<BR>
	Darf von außen auf gar keinen Fall erreichbar sein.
	@memo Hohle intern neuen Speicherblock
	@return 0 bei Fehlerfreihei, -1 bei Fehler
	*/
	//##ModelId=3978398E0290
	long	neuer_Speicher_Teil();

	/**
	Initialisiere interne Variablen und Zeiger<BR>
	(Nur über Konstruktoren aufrufbar)
	*/
	//##ModelId=3978398E028F
	void init();

	///Interne Umwandlung von Punkt zu Kommata(Excelformat)
	//##ModelId=3978398E0271
	void PunktZuKomma( wchar_t *Zeichen,wchar_t search= _T('.'),wchar_t replace=_T(',') );

//@}

public:
/**@name Method Declarations (public) */
//@{
	/**
	Konstruktor. Allokiert gleich einen ersten Block und initialisiert interne Variablen<BR>
	@memo Konstruktor (Blöckgröße mit '#define WACHSTUM' festgelegen!)
	*/
	//##ModelId=3978398E0253
	DString();

	/**
	Konstruktor mit Initialisierungszeichenkette<BR>
	@memo Initialisierungskonstruktor
	*/
	//##ModelId=3978398E0254
	DString(const wchar_t *initchr);

	/**
	Der Destruktor stellt sicher, daß aller Speicher freigegeben wird (KEINE Dummi-Funktion).<BR>
	@memo Destruktor. Gibt allen allokierten Speicher wieder frei.
	*/
	//##ModelId=3978398E0249
	~DString();

	/**
	Copy Konstruktor (WICHTIG: DString verwendet intern verkettete Liste):
	*/
	//##ModelId=3978398E025E
	DString(const DString& s);
	DString(const CString& s);  /// MD



public:

	/**
	Löscht bisherigen String und lagert übergebenen ein (wie Operator =).<BR>
	@memo Lagert übergebenen String ein (alte Daten werden gelöscht).<BR>
	@param zeichen Zeiger auf nullterminierten wchar_t String.
	@return Zahl geschriebener Bytes
	*/
	//##ModelId=3978398E022B
	long
	putstr(const wchar_t *zeichen);

	/**
	Löscht bisherigen String und lagert übergebenen ein (wie Operator =).<BR>
	@memo Lagert übergebenen String ein (alte Daten werden gelöscht).<BR>
	@param zeichen Zeiger auf nullterminierten wchar_t String.
	@return Zahl geschriebener Bytes
	*/
	//##ModelId=3978398E0235
	long
	putstr(const wchar_t *zeichen,
				 const long anzahl);


	/**
	Hängt übergebenen nullterminierten String an<BR>
	@memo Hängt übergebenen nullterminierten String an.<BR>
	@param zeichen Zeiger auf nullterminierten wchar_t String.
	@return Zahl geschriebener Bytes
	*/
	//##ModelId=3978398E020D
	long
	addstr(const wchar_t  *zeichen);

	/**
	Hängt übergebenen String an<BR>
	@memo Hängt übergebenen String an.<BR>
	@param zeichen Zeiger auf NICHT nullterminierten wchar_t String.
	@param anzahl Anzahl zu schreibender Bytes
	@return Zahl geschriebener Bytes
	*/
	//##ModelId=3978398E0217
	long
	addstr(const wchar_t *zeichen,
		  const long bytes_in_zeichen);

	/**
	Gibt kompletten String als 'scratch' String aus.
	Das heißt der zurückgelieferte Speicherplatz wird als 'non const' Zurückgeliefer 
	(der Benutzer kann damit machen was er will) <BR>
	@memo Ausgabe des gesamten Strings in wchar_t Feld.<BR>
	ACHTUNG: jedes getstr() loescht vorheriges wchar_t Feld und allokiert dann neuen Speicher.<BR>
	Das heißt: der zurückgegebene Zeiger ist nur bis zum nächsten getstr() gültig
	bzw. bis zum Ende der Gültigkeitsdauer des DStream Objektes.
	@return wchar_t* Zeiger auf nullterminiertes wchar_takter Feld.<BR>
	Es koennen jedoch auch Binaerdaten ausgegeben werden. Die Laenge des Feldes ohne 
	abschliesende NULL, ist dann mit der Funktion 'DString::laenge()' zu erfahren (
	Diese Funktion ist ohnehin 'strlen()' vorzuziehen!).
	*/
	//##ModelId=3978398E01E6
	wchar_t *
	getstr();

	/**
	Gibt Teilstring aus. Hierzu muß EXTERN Speicher allokiert werden.<BR>
	@memo Ausgabe des gesamten Strings in wchar_t Feld.<BR>
	@param String Zeiger auf extern allokierten Speicherplatz (wird nicht überprüft ob ausreichend).
	@param begin Stelle, an der mit Kopieren begonnen werden soll (0: erstes Zeichen).
	@param anzahl Anzahl Bytes, die zu kopieren sind (\0 wird nicht angehängt).
	@return Anzahl geschriebener Bytes. Bei Fehler -1.
	*/
	//##ModelId=3978398E01EF
	long
	getstr(wchar_t * Rueckgabe,
			const long begin,
			const long anzahl);

	/**Gibt die momentane Laenge zurueck. Kann die Laenge grösser LONG_MAX werden,
	(VERYLARGE definiert) sollte man diese Methode etwas umschreiben.
	@memo Länge des eingelagerten Strings
	@return Länge des intern gespeicherten Strings
	*/
	//##ModelId=3978398E01DB
	long
	laenge() const;

	/**Leert gesamten Speicher und setzt DString auf Anfang
	@memo Stellt Initialisierungszustand wieder her
	@return 0 Fehlerfrei, -1 Fehler aufgetreten
	*/
	//##ModelId=3978398E01D2
	long
	leere();

	/**
	Löscht Ausgabestring<BR>
	Kann bei größeren Strings ganz nützlich sein, um Speicher freizugeben.<BR>
	Der Ausgabestring wird bei folgenden Methoden angelegt:<BR>
	<UL>
	<LI>getstr(alle Parameter),
	<LI>(DSting1 + DString2) ->bei der Addition zweier DString Objekte wird im Objekt
		'DString2' ein Ausgabefeld erzeugt,
	<LI>+=(DString ob) nur bei Objekt 'ob'.
	<LI>(DString)[] holen einzelner Zeichen aus dem Objekt,
	<LI>get() 
	<LI>read()
	</UL>
	Frage:<BR>
	Wie bekomme ich, ohne einen Ausgabestring anzulegen, die gespeicherten Daten?<BR>
	Antwort:<BR>
	Über den 'operator<<' kann das betreffende DString Objekt an jeden beliebigen
	Ausgabestream ausgegeben werden. Die Daten werden dann in Blöcken der Größe 'WACHSTUM'
	in den Ausgabestream kopiert. Hierzu wird intern kein weiterer Speicher allokiert.<BR>
	Beim Zerstören des DString's wird der Ausgabestring mit zerstört.
	*/
	//##ModelId=3978398E01D1
	void
	ausgabe_loeschen();

//@}

public:
/**@name Operator Declarations (public) */
//@{
	/**
	Hängt nullterminierten String an.
	@memo Fügt scnell und effektiv nullterminierten String an.
	@return Anzahl geschriebener Bytes
	*/
	//##ModelId=3978398E01A9
	long
	operator += (const wchar_t * zeichen);

	///Implementierung des Multiplikators (vervielfacht den Inhalt):
	//##ModelId=3978398E0196
	DString&
	operator *= (int Faktor);

	/**
	Löscht bisherigen String und lagert übergebenen ein.<BR>
	(Siehe auch 'putstr(wchar_t *)'.<BR>
	@memo Weist nullterminierten String zu
	@return Anzahl geschriebener Bytes
	*/
	//##ModelId=3978398E0181
	long
		operator = (const wchar_t * zeichen);
	
	///////////////// md
	DString&
		operator = (const CString&  zeichen);

	
	///Gibt Zeichen an Stelle n zurueck
	//##ModelId=3978398E0177
	wchar_t
	operator[](const long n) ;


	/// DString << wchar_t
	//##ModelId=3978398E00FE
	DString& operator<<(const wchar_t c);
	/// DString << wchar_t *
	//##ModelId=3978398E0109
	DString& operator<<(const wchar_t* p);
	/// DString << signed int
	//##ModelId=3978398E011C
	DString& operator<<(const int n);
	/// DString << unsigned int
	//##ModelId=3978398E0126
	DString& operator<<(const unsigned int n);
	/// DString << signed long
	//##ModelId=3978398E0130
	DString& operator<<(const long n);
	/// DString << unsigned long
	//##ModelId=3978398E013B
	DString& operator<<(const unsigned long n);

	/** DString << format (Setze Formatierung fuer float und double Konvertierung)<BR>
	@memo Setzte Formatierung
	@param wchar_t Formatierstring (Bsp.: "%12.3f ")
	*/
	//##ModelId=3978398E00F4
	DString& format(const wchar_t *form);

	//##ModelId=3978398E00EB
	void SetKomma(){Komma=true;};

	//##ModelId=3978398E00EA
	void SetPunkt(){Komma=false;};

	/// DString << float
	//##ModelId=3978398E014F
	DString& operator<<(const float n);
	/// DString << double
	//##ModelId=3978398E0159
	DString& operator<<(const double n);

	/**
	Weist DString DString zu
	@return DString Zeiger
	*/
	//##ModelId=3978398E018B
	DString& operator= (const DString& ob);

	bool operator== (const DString& ob);

	bool operator!= (const DString& ob) {return !( *this == ob); } ;

	/**
	cast operator
	@return wchar_t *
	*/
	//##ModelId=3978398E00E0
	operator wchar_t* () { return getstr();};

	DWORD HashKey();

	operator DWORD () { return HashKey();};

	/**
	Addiert DString zu DString
	@param ob1 zu addierendes DString Objekt<BR>
	darf nicht const sein, da intern getstr() aufgerufen wird
	@return DString& Zeiger auf Summenobjekt
	*/
	//##ModelId=3978398E01BD
	DString& operator+= (DString& ob1);

	/**Addition zweier DString objekte<BR>
	Sollte aus Gründen der Effiziens vermieden werden!<BR>
	Muß zeitaufwendig instanziert, initialisiert,<BR>
	kopiert, nochmals zugewiesen(=) und letztendlich wieder zerstört werden werden!
	Wo möglich sollte deshalb der += Operator Verwendung finden.<BR>
	ob2 darf NICHT 'const' sein, da hier der Ausgabestring geschrieben werden muß.
	@param ob1 erstes objekt
	@param ob2 zu addierendes objekt
	@return DString :temparäres DString Objekt  <BR>
	
	*/
	//##ModelId=3978398D0361
	friend DSTRING_API DString operator+ (const DString& ob1, DString& ob2);

    /**Ausgabe mit Operator << an Ausgabestream<BR>
	Beispiel: cout << DString; (gibt ganzen String an Console aus)
	@memo Schnelle, effektive Ausgabe des gesamten DStrings.
	@param os ostream Objekt (wird vom Compiler generiert)
	@param ob DString Objekt
	@return Zeiger auf ostream
	*/
	//##ModelId=3978398D036C
	friend DSTRING_API std::wostringstream&  operator<< ( std::wostringstream& os, DString& ob );  /// DLG

	/**Eingabe mit Operator >> aus Inputstream <BR>
	Beispiel: cin >> DString; (liest bis EOF)
	@memo Hängt istream an internen Buffer an.
	@param is istream Objekt (wird vom Compiler generiert)
	@param ob DString Objekt
	@return Zeiger auf istream
	*/
	//##ModelId=3978398D037F
	friend DSTRING_API std::wistringstream& operator>> ( std::wistringstream& is, DString& ob );   /// DLG


	/**Parameterlose inline Funktionen.<BR>
	Implementiert die Standardfunktionen: endl, flush und ends<BR>
	Weitere nichtstandards: tab, ...?
	@param _f Funktionszeiger
	@param DString&	Referenz auf DString Objekt
	@return DString& Referenz auf übergebenes Objekt
	*/
	
	//##ModelId=3978398E0163
	inline	DString& operator<<(DString& (__cdecl * _f)(DString&));
//@}


public:
/**@name Polymorphische Implementierung einiger der 'cin' Funktionen <BR>
	(DString wird zu 'cin' opjekt)*/
//@{
	/** 
	Ausgabe ueber read() in wchar_t Feld<BR>
	Eigenschaften: Siehe Mehtode'get()'<BR>
	@memo 	Ausgabe ueber get() in wchar_t Feld<BR>
	@param wchar_t Externer Buffer
	@param int	Länge des Externen Buffers bzw. der zu schreibenden Zeichen
	@return DString& 
	*/
	//##ModelId=3978398E00CD
	DString&
	read( wchar_t  *buf, int laenge);

	/** 
	Ausgabe ueber get() in wchar_t Feld<BR>
	Die Methode kopiert solange Zeichen von DString in 'buf' bis:<BR> 
	<UL>
	<LI>len Zeichen geschrieben sind, <BR>
	<LI>das Zeichen 'stop' gefunden wurde (Zeichen 'stop' BLEIBT im Puffer!) oder<BR>
	<LI>das Ende des DString's erreicht ist.<BR>
	</UL>
	Wiederholtes 'get' beginnt an der zuletzt abgebrochenen Leseposition.<BR>
	Über die Methode 'gcount()', ist die Anzahl der geschriebenen Zeichen zu erfahren.<BR>
	Mit 'rewind()' laest sich der interne Lesezeiger zurückstellen.<BR>
	Es wird KEINE abschliesende 0 angehaengt!<BR>
	@memo 	Ausgabe ueber get() in wchar_t Feld ('cin' konform)<BR>
	@param buf Externer Buffer
	@param len	Länge des Externen Buffers bzw. der zu schreibenden Zeichen
	@param stop liest bis Zeichen 'stop' oder EOF
	@return DString& 
	*/
	//##ModelId=3978398E00B8
	DString&
	get( wchar_t * buf, int laenge_buf,wchar_t stop);

	/**
	Gibt !=0 zurück, falls das Ende erreicht wurde
	*/
	//##ModelId=3978398E00AE
	int 
	eof();

	/**
	Liefert die Anzahl der zuletzt gelesenen Zeichen
	*/
	//##ModelId=3978398E00A5
	int 
	gcount();

	/**
	Liefert die Leseposition
	*/
	//##ModelId=3978398E00A4
	int tellg();

	/**	Löscht interne Fehlerflags und setzt die Leseposition auf den Anfang*/
	//##ModelId=3978398E009A
	void clear(int);

	/**	Gibt internen Zustand zurück */
	//##ModelId=3978398E0090
	int bad(void);

	/** Setzt Leseposition an den Anfang */
	//##ModelId=3978398E0073
	void rewind(void);

	/** Stellt Leseposition um 'positions' zurueck */
	//##ModelId=3978398E007D
	void rewind(int positions);

//@}

public:
	//##ModelId=3978398E005E
	BOOL insertstr(wchar_t * is, long size, long pos);
/**@name Hilfsroutinen <BR> */
//@{
	/**
	Suche nach Substrings 'casesensitive'<BR>
	@param wchar_t* Zu suchender nullterminierter Substring
	@return Position des Suchstrings im DString.  Andernfalls -1 <BR>
	Achtung: Position kann auch -0- sein!
	*/
	//##ModelId=3978398E004B
	long
	suche(const wchar_t  *Suchstring );

	/**
	Suche nach Substrings 'caseinsensitive'<BR>
	@param wchar_t* Zu suchender nullterminierter Substring
	@return Position des Suchstrings im DString. Andernfalls -1 <BR>
	Achtung: Position kann auch -0- sein!
	*/
	//##ModelId=3978398E0040
	long
	suche_case_insensitive(const wchar_t  *Suchstring );

	/**
	Suche nach Substrings 'casesensitive'<BR>
	@param wchar_t* Zu suchender nullterminierter Substring
	@param pos Position, ab der gesucht wird
	@return Position des Suchstrings im DString.  Andernfalls -1 <BR>
	Achtung: Position kann auch -0- sein!
	*/
	//##ModelId=3978398E002D
	long
	suche_ab_position(const wchar_t  *Suchstring ,long suchbegin);

	/**
	Suche nach Substrings 'caseinsensitive'<BR>
	@param wchar_t* Zu suchender nullterminierter Substring
	@param pos Position, ab der gesucht wird
	@return Position des Suchstrings im DString. Andernfalls -1 <BR>
	Achtung: Position kann auch -0- sein!
	*/
	//##ModelId=3978398E0018
	long
	suche_case_insensitive_ab_position(const wchar_t  *Suchstring ,long suchbegin);

}; // ende der Deklarationen der Klasse DString


/**@name Inline Funktionen*/
//@{
/**Löst zugehörige inline Funktion auf<BR>
@memo Löst Zeiger auf inline Funktionen auf
@param f Aufzurufende Funktion
@param DString objekt
@return DString Zeiger auf übergebenes DString Objekt
*/
inline DString& DString::operator<<(DString& (__cdecl * _f)(DString&)) { (*_f)(*this); return *this; }

/**endl:<BR>
Fügt neue Zeile ein
*/
inline DString& __cdecl endl(DString& ds) { return ds << L'\n' ; }

/**flush:<BR>
Tut nichts (hier nicht notwendig)
*/
inline DString& __cdecl flush(DString& ds) { return ds ; } 

/**ends:<BR>
Fügt return ein
*/
inline DString& __cdecl ends(DString& ds) { return ds << L'\r' ; }

/**tab:<BR>
Fügt ein Tab ein
*/
inline DString& __cdecl tab(DString& ds) { return ds << L'\t' ; } 
//@}

} // namespace


#endif
