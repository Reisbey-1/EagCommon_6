/* Mini String Klasse, mit dynamisch, schnell und effektiv
  beliebig große Strings verwaltet werden können.
*/

#include "stdafx.h"
#include "DString.h"

namespace eag {

//##ModelId=3978398E0253
DString::DString(){//Konstruktor ohne initialisierung

	init();

	//Setzte Formatierung für float und double.
	//Kann mit '<< format("formatstring")' geändert werden.
	wcscpy(formatstr,L"%12.3f");
};


//##ModelId=3978398E0254
DString::DString(const wchar_t *initchr){//Konstruktor mit initialisierung

	init();
	wcscpy(formatstr,L"%12.3f");
	addstr(initchr);
};


//=====================COPY===========================================
//##ModelId=3978398E025E
DString::DString(const DString& s){ //Copyconstructor: WICHTIG

	init();

	//===========================================
	// this ist jetzt initialisiert, das heißt
	// kopiere jetzt die einzelnen Speicherblöcke:
	//===========================================

	*this=s;
};

//=====================COPY===========================================
//##ModelId=3978398E025E   /// MD
DString::DString(const CString& s) { //Copyconstructor: WICHTIG

	init();

	//===========================================
	// this ist jetzt initialisiert, das heißt
	// kopiere jetzt die einzelnen Speicherblöcke:
	//===========================================

	*this = s;
};
//=====================COPY===========================================

//##ModelId=3978398E028F
void
DString::init() {
		//initialisiere Globals:
		Anfang_Speicher=NULL;		//noch kein Anfang am Anfang

		Letzter=NULL;				//noch nichts zugeordnet

		Anzahl_Speicher_Teile=0;	//am Anfang =0

		//hole gleich ersten Speicher Teil und initialisiere ihn:
		neuer_Speicher_Teil();

		//setze Anfangszeiger:
		Anfang_Speicher	=Letzter;

		//Ausgabezeiger auf NULL setzten:
		Ausgabe=NULL;
		//Ausgabe ist nicht aktuell:
		A_sync = FALSE;

		read_pos = 0; //Aktuelle Leseposition
		read_last =0; //Anzahl der zuletzt gelesener Zeichen der folgenden Funktionen

		Komma=FALSE;
};


//##ModelId=3978398E0249
DString::~DString(){//Standartdestruktor:
	// WICHTIG: Hier wird aller allokierter Speicher wieder freigegeben.

	 Speicher_Teil *vorgaenger=NULL; //von hinten den Speicher aufrollen

		for (long i=0;i<Anzahl_Speicher_Teile;i++){

			vorgaenger=Letzter->vorgaenger; //sichern fuer naechstes delete

			delete Letzter;				// dann Adressteil zerstoeren

			if  (vorgaenger==NULL)
				break;
			else
				Letzter=vorgaenger;
		};

  ausgabe_loeschen();		// zum Schluss den noch eventuell angelegten
};


//---------------------------------------------------------------
// DString Verwaltung (put, get, add, laege, ...)
//--------------------------------------------------------------

//##ModelId=3978398E022B
long	//gibt anzahl geschriebener Bytes zurueck
DString::putstr(const wchar_t * zeichen){			//Lagert übergebenen String ein

	leere();										//loesche alte Daten
	long bytes_in_zeichen=wcslen(zeichen);

	return 	addstr(zeichen, bytes_in_zeichen);	//fuege neue Daten ein
};


//##ModelId=3978398E0235
long	//gibt anzahl geschriebener Bytes zurueck
DString::putstr(const wchar_t * zeichen,
					 const long anzahl){//Lagert übergebenen String ein

	leere();					//loesche alte Daten

	return 	(addstr(zeichen,anzahl));//fuege neue Daten ein
};


//##ModelId=3978398E020D
long	//gibt anzahl geschriebener Bytes zurueck
DString::addstr (const wchar_t * zeichen){	//fügt Nullterminierten String an

	long bytes_in_zeichen=wcslen(zeichen);

	return addstr(zeichen, bytes_in_zeichen);
};


// nur in Methode addstr(c,l) wird geschrieben !
// alle anderen schreibenden Methoden verwenden diese Funktion
//##ModelId=3978398E0217
long	//gibt anzahl geschriebener Bytes zurueck
DString::addstr(const wchar_t * zeichen,
					const long bytes_in_zeichen){// fügt nicht Nullterminierten String an

//	 m_CriticalSection.Lock();

	 static long frei;		//freie bytes in Buffer
	 static long schreibe;	//geschriebene Bytes in Schleife

	 #ifdef VERYLARGE
		if (bytes_in_zeichen < 0) return 0;//hat ein Ueberlauf stattgefunden?
	 #endif

		for (long zu_schreiben=bytes_in_zeichen;zu_schreiben>0;){

			frei=WACHSTUM-Fuellstand;

			schreibe=zu_schreiben>frei ? frei:zu_schreiben; //in dieser Schleife geschriebene Bytes

			if (frei>0){
				/// memcpy(Letzter->pC_Buff + Fuellstand, \   /// md
				wmemcpy(Letzter->pC_Buff + Fuellstand, \
						zeichen+bytes_in_zeichen-zu_schreiben,\
						schreibe);
					zu_schreiben-=schreibe;
					Fuellstand+=schreibe;
			}
			else
				neuer_Speicher_Teil();
		}
		A_sync=FALSE;	//Ausgabestring ist jetzt nicht mehr synchron
		
//		m_CriticalSection.Unlock();

  return bytes_in_zeichen;
};


//##ModelId=3978398E01E6
wchar_t *	//gibt Zeiger auf nulltermierten String zurueck.
		//Kann auch binary, abschliesende 0 ist dann jedoch sinnlos
        //die laenge ist dann ueber laenge() zu erfahren
DString::getstr(){	//gibt ganzen String aus

	 if (A_sync==FALSE){ //hat sich seit der letzten Ausgabe etwas verändert?

//		m_CriticalSection.Lock();

		Speicher_Teil * aktuell=Anfang_Speicher;//erster zu kopierender Speicher_Teil

		ausgabe_loeschen();	//alte Ausgabe löschen

		Ausgabe = new wchar_t[laenge()+1];
		if (Ausgabe==NULL) {
//			m_CriticalSection.Unlock();
			return 0;
		}

		for (long i=0;i<(Anzahl_Speicher_Teile-1);i++){		//letzten extra kopieren
			wmemcpy(Ausgabe+i*WACHSTUM,aktuell->pC_Buff,WACHSTUM);    // md
			aktuell=aktuell->naechster;
		}
		/*memcpy(Ausgabe + (Anzahl_Speicher_Teile - 1)*WACHSTUM, Letzter->pC_Buff, Fuellstand);   /// md
		memcpy(Ausgabe + (Anzahl_Speicher_Teile - 1)*WACHSTUM + Fuellstand, _T("\x0"), 1);		  /// md */
		
		wmemcpy(Ausgabe + (Anzahl_Speicher_Teile - 1)*WACHSTUM, Letzter->pC_Buff, Fuellstand);   /// md
		wmemcpy(Ausgabe + (Anzahl_Speicher_Teile - 1)*WACHSTUM + Fuellstand, _T("\x0"), 1);		  /// md

		A_sync=TRUE; //Ausgabestring ist jetzt wieder up to date
	
//		m_CriticalSection.Unlock();

	}//ende Aktualliesiere Ausgabe

 return Ausgabe;
};


//##ModelId=3978398E01EF
long			// gibt Anzahl gelesener Bytes zurueck
DString::getstr(wchar_t *Rueckgabe,	// NICHT const: hier wird geschrieben
		const long begin,  	// 0 ist erstes Element
		const long anzahl){ // anzahl zu  holender Chars

		long geschrieben=0;

	 //Eingangskontrollen:
		if (begin<0) return 0;                //Unsinn
		if (begin>laenge()) return 0;         //Unsinn
		if ((begin+anzahl)>laenge())
			geschrieben=laenge()-begin; // Ausgabe sinnvoll begrenzen
		else
			geschrieben=anzahl;

	 // Ganzen DString in Ausgabepuffer stellen (linear):
		getstr();
	 // Dies ist die einfach-primitiv Version!
		// Optimiert:
		// 0. hole passenden Speicher fuer die Ausgabe,
		// 1. stelle temporaeren zeiger des internen Buffers auf ersten zu lesen block.
		// 2. lese aus diesem Block die maximal mögliche (noetige) Anzahl Bytes
		// 3. lese 0-n-weitere Bloecke
		// 4. lese im letzten zu kopierenden Block die noetige Anzahl an Bytes
		// Dieser Aufwand lohnt sich fuer mich nicht, da ich diese Funktion nicht brauche.
		// Wozu auch?

	 // Daten kopieren:
		memcpy(Rueckgabe,Ausgabe+begin,geschrieben);
 return geschrieben;
};


//##ModelId=3978398E01DB
long
DString::laenge() const{				//gibt die momentane Laenge aus

	 #ifdef VERYLARGE
		if (((Anzahl_Speicher_Teile-1) * WACHSTUM) < 0) // Überlauf
			return 0;				// das sollte eigentlich ein Fehler geben.
								// Aber wer hat denn schon so viel Speicher?
	 #endif

	 return ((Anzahl_Speicher_Teile-1) * WACHSTUM + Fuellstand);
};


//##ModelId=3978398E01D2
long
DString::leere(){//leert gesamten Speicher und setzt DString auf Anfang

//	m_CriticalSection.Lock();

	Speicher_Teil *vorgaenger=NULL;

		for (long i=0;i<(Anzahl_Speicher_Teile-1);i++){ //bis auf einen alle loeschen

			vorgaenger=Letzter->vorgaenger; //sichern fuer naechstes delete

			delete Letzter;					// dann Adressteil zerstoeren

			if  (vorgaenger==NULL) {
//				m_CriticalSection.Unlock();
				return -1;					//interner Fehler aufgetreten
			}
			else
				Letzter=vorgaenger;
		}

		Letzter->naechster=NULL;	//Es gibt dann auch keinen naechsten mehr
		Anzahl_Speicher_Teile=1;	//bis auf einen
		Fuellstand=0;			//bei 0 beginnen zu lesen und zu schreiben

		read_pos = 0; 			//Aktuelle Leseposition an den Anfang stellen
		A_sync=FALSE;

//	m_CriticalSection.Unlock();

	return 0;
};


//##ModelId=3978398E0290
long										//gibt 0 zurueck wenn alles geklappt Hat
DString::neuer_Speicher_Teil(){				//hohlt neuen Speicher und verkettet ihn mit
											//dem Vorgaenger

	// Dieser Teil darf nicht gelockt werden da bereits 
	// addstr gelockt ist

		Speicher_Teil * TempST;					// temporaerer Zwischenpuffer

		TempST	=new Speicher_Teil;				//Hohle neuen Speicher Teil

		if (Letzter)							//Am Anfang ist Letzter NULL
			Letzter->naechster=TempST;			//Weise  naechsten neue Adresse zu

		TempST->vorgaenger=Letzter;				//Vorgaenger des neuen Speichers

		Letzter=TempST;							//neue freie Adresse

		Letzter->naechster=NULL;				//naechste ist dann wieder NULL

		Anzahl_Speicher_Teile++;				//erhoehe dann die Zahl der Teile

		Fuellstand=0;							//neuer Speicher ist natürlich noch leer

return 0;
};


//##ModelId=3978398E01D1
void
DString::ausgabe_loeschen(){

		delete [] Ausgabe;	// Ausgabespeicher loeschen.

		Ausgabe=NULL;		// Zeigerwert löschen (Wichtig fuer naechste Abfrage)

		A_sync=FALSE;		// Ausgabe nicht mehr aktuell
};


//-----------------------------------------------------------
// Implementierung der Operatoren +=, ==, [], =, ...
//----------------------------------------------------------

//##ModelId=3978398E01A9
long	//gibt Anzahl geschriebener Bytes zurueck
DString::operator += (const wchar_t * zeichen){	//fügt Nullterminierten String an

		long bytes_in_zeichen=wcslen(zeichen);

 return addstr(zeichen,  bytes_in_zeichen); /// MD
};


//##ModelId=3978398E0181
long	//gibt anzahl geschriebener Bytes zurueck
DString::operator =(const wchar_t *zeichen){//fügt Nullterminierten String an

	leere();							//loesche alte Daten

	return (*this += (zeichen));		//fuege neue Daten ein  
};


/// MD
DString&	//gibt anzahl geschriebener Bytes zurueck
DString::operator =(const CString& zeichen) {//fügt Nullterminierten String an

	leere();							//loesche alte Daten

	USES_CONVERSION;
	wchar_t* wstr_name = (WCHAR*)zeichen.GetString();
	(*this += (wstr_name));		//fuege neue Daten ein
	return *this;
};


//##ModelId=3978398E0177
wchar_t
DString::operator[](const long n)  {    //gib Zeichen an Stelle n zurueck
	if	( (n >= laenge()) ||	// ist n ueberhaupt kurz genug ?
		  (n < 0))           // ist n lang genug ?
		 return 0;

	Speicher_Teil *pBlock = Anfang_Speicher; //Beginne am Anfang

	// gehe zu speicherblock m:
	long lBlockNumber = n/WACHSTUM;
	for (long l = 0 ; l < lBlockNumber; l++)
		pBlock = pBlock->naechster;

	return pBlock->pC_Buff[n-lBlockNumber*WACHSTUM];
};

bool
DString::operator== (const DString& ob){

	if ( this == &ob) return true; // selbes objekt 

	//pruefe auf laenge;
	if (ob.laenge() != laenge()) return false;

	Speicher_Teil *ob_Block	= ob.Anfang_Speicher; //Beginne am Anfang
	Speicher_Teil *Block	= Anfang_Speicher; //Beginne am Anfang
//soweit so gut:

	for (;Block;){  //nun teste alle einzelne Bloecke:
		
		if ( Block == Letzter )
			if ( 0 != wcsncmp(ob_Block->pC_Buff, Block->pC_Buff, Fuellstand) ) return false;
		else
			if ( 0 != wcsncmp(ob_Block->pC_Buff, Block->pC_Buff, WACHSTUM) ) return false;


		Block=Block->naechster;
		ob_Block=ob_Block->naechster;

	}; // alles geprueft

	return true;	//gebe dieses zurück
};


//##ModelId=3978398E018B
DString&
DString::operator= (const DString& ob){

	if ( this != &ob) { // ist this == ob wuerde im naechsten Schritt alles geloescht werden!!
	
		leere();		//dieses objekt säubern

		Speicher_Teil *s_Block= ob.Anfang_Speicher; //Beginne am Anfang

//		m_CriticalSection.Lock();

		for (;;){                      				//und kopiere einfach alles
			//memcpy(Letzter, s_Block->pC_Buff, WACHSTUM);		/// md
			wmemcpy((wchar_t*)Letzter, s_Block->pC_Buff, WACHSTUM);
			s_Block=s_Block->naechster;
			if (s_Block)
				neuer_Speicher_Teil();
			else
				break;
		}; // alles kopiert (naechster ==0 )

		Fuellstand=ob.Fuellstand;			//Übernehme Füllstand

		wcscpy(formatstr,ob.formatstr); //Übernehme formatstr
		
//		m_CriticalSection.Unlock();
	}

return *this;			//gebe dieses zurück
};

//##ModelId=3978398E01BD
DString&
DString::operator+= (DString& ob1){

	addstr( ob1.getstr(), ob1.laenge()) ;
	return *this;

};


///Just for fun: implementierung des Multiplikators:
//##ModelId=3978398E0196
DString&
DString::operator*= (int Faktor){
	
	long laenge_von_this=laenge();
	getstr();
	
	for (int i=0 ; i < Faktor ; i++)
		addstr(Ausgabe,laenge_von_this);

	return *this;
};



//---------------------------------------------------------------------
//Polimorphische Implementierung verschiedener 'cin'Funktionen:
//---------------------------------------------------------------------

//##ModelId=3978398E00CD
DString&
DString::read( wchar_t *buf, int laenge){

	read_last = getstr(buf, read_pos, (long)laenge);
	read_pos += read_last;
	return *this;
};


//##ModelId=3978398E00B8
DString&
DString::get( wchar_t *buf, int laenge_buf , wchar_t stop){
	long zaehler = 0;
	getstr();			// Ausgabe aktualisieren  


	for ( zaehler=0 ; ((zaehler < laenge_buf-1) && (read_pos < laenge() ) ) ; zaehler++) {

		if (Ausgabe[read_pos] == stop) break;
		buf[zaehler]=Ausgabe[read_pos];
		
		read_pos++;
	}

	buf[zaehler]=0;			//muß das sein ?
	read_last=zaehler;
	return *this;
};


//##ModelId=3978398E00AE
int            // ist die Leseposition gleich der Laenge?
DString::eof(){return (read_pos != laenge() ? 0:1 ); };


//##ModelId=3978398E00A5
int
DString::gcount(){return (int)read_last; };

//##ModelId=3978398E00A4
int
DString::tellg(){return (int)read_pos; };

//##ModelId=3978398E0090
int
DString::bad(){ return FALSE;};  //hier gibt es keine Hardwarefehler


//##ModelId=3978398E009A
void
DString::clear(int ) { // tue nichts

	return;
};


//##ModelId=3978398E0073
void
DString::rewind(void){
 
	read_pos = 0; //Aktuelle Leseposition zuruecksetzen
};


//##ModelId=3978398E007D
void
DString::rewind(int positions){
	
	read_pos -= positions; //Aktuelle Leseposition um 'positions' zuruecksetzen

	if (read_pos < 0)			read_pos = 0 ;
	if (read_pos > laenge() )	read_pos = laenge(); // means eof()

};


//----------------------------------------------------------
// streamable <<, und >> operatoren
//----------------------------------------------------------

DString&
DString::operator<<(const int n){	// s << int
		wchar_t temp[64];					//temporärer Buffer
		_ultow(n,temp,10);				//konvertiere
		*this += temp;					//hänge an
	 return *this;
};


DString&
DString::operator<<(const unsigned int n){	// s << int
		wchar_t temp[64];							//temporärer Buffer
		_ultow((unsigned long)n,temp,10);		//konvertiere
		*this += temp;							//hänge an
 return *this;
};


DString&
DString::operator<<(const wchar_t c)
	 {
		addstr(&c,1);	// Füge String mit der Länge 1 an
		return *this;
};


DString&
DString::operator<<(const wchar_t* p)	//füge nullterminierten String an
	 {
		*this += p;
		return *this;
};


DString&
DString::operator<<(const long n)
	 {
	wchar_t num[64];
	_ultow(n, num, 10);   // _ultow
	addstr(num);
	return *this;
};


DString&
DString::operator<<(const unsigned long n)
	 {
		wchar_t num[64];
		//// md ultoa(n, num, 10);   // _ultow
		_ultow(n, num, 10);   // _ultow
		addstr(num);
		return *this;
};


//##ModelId=3978398E00F4
DString&
DString::format(const wchar_t *form)
	 {
		if (form)
			wcscpy(this->formatstr,form);

		return *this;
};


DString&
DString::operator<<(const float f)
	 {
	wchar_t w = (wchar_t)f;

	if (Komma == TRUE) PunktZuKomma(&w);
	addstr(&w);
	return *this;
};


DString&
DString::operator<<(const double d)
	 {
		//wchar_t num[64] = (wchar_t)d;
		wchar_t w = (wchar_t)d;

		if (Komma==TRUE) PunktZuKomma(&w);
		addstr(&w);
		return *this;
};

//-----------------------------------------------------------------------------------
// Hilfroutinen: insert  ...
//-----------------------------------------------------------------------------------

//##ModelId=3978398E005E
BOOL DString::insertstr(wchar_t * is, long size, long pos)
{
	long SizeOfThis = laenge(); //we have to save the length!!
	if (pos > SizeOfThis) return false; 

	wchar_t * pc_tmp_Buffer = getstr(); // save content of this DString

	leere();			// because we delete it here
	addstr(pc_tmp_Buffer , pos) ;		
	addstr(is,size);
	addstr(pc_tmp_Buffer , SizeOfThis - pos);

	return true;
}

//-----------------------------------------------------------------------------------
// Hilfroutinen: suche, ...
//-----------------------------------------------------------------------------------


DWORD 
DString::HashKey(){

	DWORD dwHashKey=0;
	getstr();
	
	long lSize = laenge() > 32 ? 32 : laenge() ; //just hash first 32 bytes

	for (long i = 0 ; i < lSize ; i++)
		dwHashKey += (Ausgabe[i] << (lSize-i) ) ; //count first chars more

	return dwHashKey;
};


//##ModelId=3978398E004B
long
DString::suche(const wchar_t * Suchstring){
return suche_ab_position(Suchstring,0L);
};

//##ModelId=3978398E002D
long
DString::suche_ab_position(const wchar_t * Suchstring, long suchbegin){

	long pos_this;	    // Position im zu suchenden String
	long ende = laenge(); // Just for performance
	long laenge_suchstr=wcslen(Suchstring);
	long pos_such;	    // Position im suchenden String

	if	((suchbegin > (ende-laenge_suchstr))||	// ist suchbegin kurz genug ?
		 (suchbegin < 0))           			// ist suchbegin lang genug ?
		  return -1;
	//getstr();				   // stelle sicher, dass 'Ausgabe' aktuell ist

	for (pos_this = suchbegin ; pos_this <= (ende - laenge_suchstr) ; pos_this++) //Schleife über alle Zeichen

		for (pos_such=0 ; pos_such < laenge_suchstr+1;pos_such++){  //Schleife über Suchstring

			if (pos_such == laenge_suchstr) 
				return pos_this;	  //Substring gefunden

			if ((*this)[pos_this+pos_such] != Suchstring[pos_such])
				break;
			}
return -1;
};


//##ModelId=3978398E0040
long
DString::suche_case_insensitive(const wchar_t * Suchstring){
return suche_case_insensitive_ab_position(Suchstring,0L);
};

//##ModelId=3978398E0018
long
DString::suche_case_insensitive_ab_position(const wchar_t * Suchstring,long suchbegin){

	long pos_this;	    			// Position im zu suchenden String
	long ende = laenge(); 			// Just for performance
	long laenge_suchstr=wcslen(Suchstring);

	long pos_such;	    			// Position im suchenden String

	if	((suchbegin > (ende-laenge_suchstr))||	// ist suchbegin kurz genug ?
		 (suchbegin < 0))           			// ist suchbegin lang genug ?
		  return -1;

	char *pSuchstring = new char[laenge_suchstr+1];

	for(pos_such=0;pos_such<laenge_suchstr;pos_such++)  // Wandle Suchstring in Grossbuchstaben um
		pSuchstring[pos_such]=toupper(Suchstring[pos_such]);

	pSuchstring[laenge_suchstr]='\000';

	getstr();				   // stelle sicher, dass 'Ausgabe' aktuell ist

	for (pos_this=suchbegin;pos_this <= (ende - laenge_suchstr);pos_this++)				  //Schleife über alle Zeichen

		for (pos_such=0 ; pos_such < laenge_suchstr + 1 ; pos_such++){  //Schleife über Suchstring

			if (pos_such == laenge_suchstr) {
				delete pSuchstring;
				return pos_this;	  //Substring gefunden
			}

			if (toupper(Ausgabe[pos_this+pos_such]) != pSuchstring[pos_such])
				break;
		}

	delete pSuchstring;
	return -1;
}


//##ModelId=3978398E0271
void
DString::PunktZuKomma(wchar_t *Zeichen, wchar_t search , wchar_t replace){
	int laenge=wcslen(Zeichen);
	for (int i= 0; i<laenge; i++)
		if (Zeichen[i] == search) Zeichen[i]=replace;
};


/*------------------------------------------------------------------------
---- DString + gibt KEINE Referenz rurueck, dies ist volle Absicht: ----
Weiterhin muss die Routine intern ein Temporaeres DString Objekt erzeugen
um dieses zurueckzugeben. Der Compiler verwendet dieses
temporaere Objekt dann fuer weitere Operationen (=, +, ...).
Aus diesem Grund sollte das Addieren zweier DString Objekte ueber diesen
Operator vermieden werden. */
DString
operator + (const DString& ob1, DString& ob2){

	DString tmp;							//erzeuge temporäres Objekt
	tmp=ob1;								//Kopiere interne Daten
	tmp.addstr(ob2.getstr(),ob2.laenge());	//Füge ob2 an temp an

  return tmp; //gebe Objekt selbst und nicht Referenz auf Objekt zurueck!!
};


//-----------------------------------------------------------------------------------
//Implementierung der Freunde der Klasse DString  (iostream Funktionen)
//----------------------------------------------------------------------------------

//std::wostream&  operator << (std::wostream& os, DString& ob){ // Ausgabe in fremdes objekt  /// DLG
std::wostringstream&  operator << (std::wostringstream& os, DString& ob) { // Ausgabe in fremdes objekt  /// DLG
	DString::Speicher_Teil * aktuell=ob.Anfang_Speicher;//erster zu kopierender Speicher_Teil

//	ob.m_CriticalSection.Lock();

		for (long i=0;i<(ob.Anzahl_Speicher_Teile-1);i++){
			os.write(aktuell->pC_Buff, DString::WACHSTUM );			//Blockweise rausschreiben
			aktuell=aktuell->naechster;
		}
		os.write(aktuell->pC_Buff, ob.Fuellstand);					//letzten wieder extra Schreiben

//	ob.m_CriticalSection.Unlock();

    return os;
};


std::wistringstream& operator>> ( std::wistringstream& is, DString& ob ){  /// DLG

	// Dieser Teil darf nicht gelockt werden da bereits 
	// addstr gelockt ist

	wchar_t tempbuf[DString::WACHSTUM];

		is.ipfx( 1 );					//unformatiertes einlesen
		do {
			//Einlesen auf WACHSTUM Bytes begrenzen (nur wegen tempbuff):
			is.read(tempbuf,DString::WACHSTUM);
			ob.addstr(tempbuf,is.gcount());	// Einlagern
			} while (is.gcount());           // abbrechen wenn keine Daten mehr da

 return is;
};

} // namespace

