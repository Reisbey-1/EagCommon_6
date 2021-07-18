// XYPoligon.cpp: Implementierung der Klasse CXYPoligon.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxtempl.h>
#include "eag_monitor.h"
#include "DString.h"
#include <math.h>

#include "XYPoligon.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace eag {

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CXYPoligon::CXYPoligon()
{
	m_bClosed = false;
	m_iDirection = 0; // 0: no direction, -1: right (clock wise), 1: left (counter clock wise)
	m_dBETWEEN_PRECISION = 0.00000001;
	m_arrayPoints.SetSize(0,5);
}

CXYPoligon::~CXYPoligon()
{
	CleanUp();
}

void CXYPoligon::SetClosed(bool bClosed){
	m_bClosed = bClosed;
};

bool CXYPoligon::GetClosed(){
	return 	m_bClosed ;
};

void CXYPoligon::SetDirection(int iDirection){
	m_iDirection = iDirection;
};

int CXYPoligon::GetDirection(){
	return m_iDirection;
};


int CXYPoligon::AddLine(  double dX, double dY, void * pPointData)
{
	return m_arrayPoints.Add(CPoligonPoint( dX, dY, pPointData));
}


void CXYPoligon::CleanUp()
{
	m_arrayPoints.RemoveAll();
}


bool CXYPoligon::PointNearBy( int &iPoint,  double &dX, double &dY, float fPrecisionX, float fPrecisionY)
{
	m_fPrecisionY = fPrecisionY;
	m_fPrecisionX = fPrecisionX;
 
	if (iPoint < 0 ) {
		// look at every point:
		for ( int i = 0 ; i < m_arrayPoints.GetSize(); i++) {
	
			if ( PointNearBy( m_arrayPoints[i], dX, dY ) ) {
				iPoint = i;
				return true;
			}
		}
	}
	else if ( iPoint < m_arrayPoints.GetSize() ) {

		if ( PointNearBy( m_arrayPoints[iPoint], dX, dY) ) {
			return true;
		}
	}

	return false;
}


#define BETWEEN(x,a,b)\
( x > a - m_dBETWEEN_PRECISION && x < b + m_dBETWEEN_PRECISION || x < a + m_dBETWEEN_PRECISION && x > b - m_dBETWEEN_PRECISION)

bool CXYPoligon::PointNearBy(CPoligonPoint &Point, double &dX, double &dY )
{
	if ( BETWEEN( Point.m_dY, dY-m_fPrecisionY, dY+m_fPrecisionY) &&
		 BETWEEN( Point.m_dX, dX-m_fPrecisionX, dX+m_fPrecisionX))
		 return true;

	return false;

}


bool CXYPoligon::GetBalancePoint( CPoligonPoint &CPointBalance, double &dTotalArea)
{
	bool bCrossing;
	int i,j,k, Line1a,Line1b,Line2a,Line2b, iIteration, iArraySize, iPointBetween;
	double X11, Y11, X12, Y12, X21, Y21, X22, Y22, X3, Y3, dX, dY;
	

	dTotalArea			= 0;
	CPointBalance.m_dX	= 0;
	CPointBalance.m_dY	= 0;
	
	// check if poligon is closed and data is available:

	iArraySize = m_arrayPoints.GetSize();

	if (! m_bClosed){
		EAG_LOG_NOTICE("CXYPoligon::GetBalancePoint - poligon is not closed")
		return false; 
	}
	
	if ( iArraySize == 0 )  { 
		EAG_LOG_INFO("CXYPoligon::GetBalancePoint - poligon is empty")
		return false;
	}

	if ( iArraySize < 3 )  { 
		EAG_LOG_INFO("CXYPoligon::GetBalancePoint - poligon consists of only two points")
		
		dX			= 0;
		dY			= 0;

		for( i = 0 ; i < iArraySize; i++ ) {
			dX	+= m_arrayPoints[i].m_dX;
			dY	+= m_arrayPoints[i].m_dY;
		}

		CPointBalance.m_dY = dY / iArraySize;
		CPointBalance.m_dX = dX / iArraySize;

		return true;
	}



	// fractonize poligon into n triangles
	// then determin balance points of each triangle
	// and last but not least average each balance point with it's
	// triangle area (should work). 

	// start of triangularization
	CArray <TriangAngleIndex, TriangAngleIndex&> arrayTriangAngleIndex;
	arrayTriangAngleIndex.SetSize(0,iArraySize);

	CArray <LineIndex, LineIndex&> arrayLineIndex;
	arrayLineIndex.SetSize(0,iArraySize*2);

	CArray<int, int&> arrayBoundingBoxIndex;
	arrayBoundingBoxIndex.SetSize(iArraySize);

	// first of all fill line indexes for bounding box:
	for ( i = 0 ; i < iArraySize ; i++ ){

		if ( i == iArraySize -1  )
			arrayLineIndex.Add(LineIndex( i,0 ));
		else 
			arrayLineIndex.Add(LineIndex( i,i+1));

		arrayBoundingBoxIndex[i] = i;
	}

	// for each point generate triangel:
	iIteration		= 0; 
	do {

		// search points for triangle that
		// a. consists of one and the overnext point
		// b. the point in the middle of the connecting line is with in the the poligon
		// c. the connecting lines does not cross any other line
		// then
		// add line index, triangle index, and remove point between from arraybounding box

		//constraint a: find point:
		for ( i = iIteration%2 ; i < arrayBoundingBoxIndex.GetSize() ; i++) {
			
			// index swapping for overnext point:
			j = i + 2;

			if ( j == arrayBoundingBoxIndex.GetSize() ) {
				j = 0;
				iPointBetween = arrayBoundingBoxIndex.GetUpperBound();
			}
			else if ( j == arrayBoundingBoxIndex.GetSize()+1 ) {
				j = 1;
				iPointBetween = 0;
			}
			else {
				iPointBetween = i + 1;
			}

			if ( arrayBoundingBoxIndex.GetSize() == 3 ) { // add last remaining triangle

				// last remaining triangle can't cross any other line and must be inside the poligon.
				// so just add it:
				arrayTriangAngleIndex.Add(TriangAngleIndex( arrayBoundingBoxIndex[0], arrayBoundingBoxIndex[1], arrayBoundingBoxIndex[2]));
				arrayBoundingBoxIndex.RemoveAll(); // add no line
				break;
			}

			Line1a = arrayBoundingBoxIndex[i]; // new triangle line point a
			Line1b = arrayBoundingBoxIndex[j]; // new triangle line point b

			X11 = m_arrayPoints[Line1a].m_dX;
			Y11 = m_arrayPoints[Line1a].m_dY;
			X12 = m_arrayPoints[Line1b].m_dX;
			Y12 = m_arrayPoints[Line1b].m_dY;

			// check if line is inside or outside of Poligon:
			dX = ( X11 + X12 ) / 2;
			dY = ( Y11 + Y12 ) / 2;

			m_dBETWEEN_PRECISION = 0.000000001;
			if ( PointInside( dX, dY ) ) {
	
				// check if line is crossing any other line:
				bCrossing = false;
				for ( k = 0 ; k < arrayLineIndex.GetSize() ; k++) {
				
					Line2a = arrayLineIndex[k].m_a;
					Line2b = arrayLineIndex[k].m_b;
					
					X21 = m_arrayPoints[Line2a].m_dX;
					Y21 = m_arrayPoints[Line2a].m_dY;
					X22 = m_arrayPoints[Line2b].m_dX;
					Y22 = m_arrayPoints[Line2b].m_dY;


					m_dBETWEEN_PRECISION = -0.000000001;
					if ( StraightLinesCross( X11, Y11, X12, Y12, X21, Y21, X22, Y22, dX, dY)) {
						bCrossing = true;
						break;
					}
				}
				
				// no crossing line, so we can:
				if ( !bCrossing){

					arrayTriangAngleIndex.Add(TriangAngleIndex( Line1a, Line1b, arrayBoundingBoxIndex[iPointBetween]));
					arrayLineIndex.Add(LineIndex( Line1a, Line1b));
					// don't forget to remove index from bounding box:
					arrayBoundingBoxIndex.RemoveAt(iPointBetween);
					// now since we removed corner we can count back one index:
					i--;
				}
			
			}
			// else point is outside, try to continue with next point in poligon: i++, j++
		}

		iIteration++;

	} while ( arrayBoundingBoxIndex.GetSize() > 2 && iIteration < iArraySize * iArraySize );

	if ( arrayBoundingBoxIndex.GetSize() > 2 ) {
		EAG_LOG_ERROR("CXYPoligon::GetBalancePoint - iteration exeeded on triangular decomposition")
		return false;
	}
/*
   // let this code in for later usage: may somone wants to have triangles:
	else {
		for (i = 0 ; i < iArraySize ; i++) 
			csLog << "Punkt " << i << ": x: " << arrayPoints[i].m_dX << ", y: " << arrayPoints[i].m_dY << endl;

		for (i = 0 ; i < arrayTriangAngleIndex.GetSize() ; i++) {
		
			TriangAngleIndex &TI = arrayTriangAngleIndex[i];
			csLog << "Triangle " << i << ": a: " << TI.m_a << ", b: " << TI.m_b << ", c: " << TI.m_c <<  endl;
		}

		ofstream fLog("c:/temp/triangle_ok.log");
		fLog << csLog << flush;
	}
*/
	

	// we don't need them any more:
	arrayBoundingBoxIndex.RemoveAll();
	arrayLineIndex.RemoveAll();
	
	// next i need an array for all balance points we have to 
	CArray <double , double&> csaDoubleArrayTriangleAreas;
	CArray <CPoligonPoint, CPoligonPoint&> csaTriangleBalancePoints;


	csaDoubleArrayTriangleAreas.SetSize(arrayTriangAngleIndex.GetSize());
	csaTriangleBalancePoints.SetSize(arrayTriangAngleIndex.GetSize());

	// calculate balance point and area of each triangle:

	for ( i = 0 ; i <  arrayTriangAngleIndex.GetSize() ; i++){
	
		X3 = m_arrayPoints.GetAt(arrayTriangAngleIndex[i].m_c).m_dX; 
		Y3 = m_arrayPoints.GetAt(arrayTriangAngleIndex[i].m_c).m_dY; 

		// Line on Poligon:
		CPoligonPoint &point = m_arrayPoints.GetAt(arrayTriangAngleIndex[i].m_a);
		X11 = point.m_dX;
		Y11 = point.m_dY;

		point = m_arrayPoints.GetAt(arrayTriangAngleIndex[i].m_b);
		X12 = point.m_dX;
		Y12 = point.m_dY;

		// short intermezzo:
		// calculating area of triangle:
		csaDoubleArrayTriangleAreas[i] = TriangleArea( X11, Y11, X12, Y12, X3 , Y3);

		// the middle point of this line:
		dX = (X11 + X12) / 2; 
		dY = (Y11 + Y12) / 2;
		
		// so that the first triangle medium line is:
		X11 = X3;
		Y11 = Y3;
		X12 = dX;
		Y12 = dY; 

		// Next line on Poligon to the point in the middle:
		point = m_arrayPoints.GetAt(arrayTriangAngleIndex[i].m_b);
	
		X21 = point.m_dX;
		Y21 = point.m_dY;
		X22 = X3;
		Y22 = Y3;

		// the middle point of this line:
		dX = (X21 + X22) / 2; 
		dY = (Y21 + Y22) / 2;

		// and the second triangle medium line is:
		X21 = dX;
		Y21 = dY;
		point = m_arrayPoints.GetAt(arrayTriangAngleIndex[i].m_a);
		X22 = point.m_dX;
		Y22 = point.m_dY; 

		// the Balance point of this area is:

		m_dBETWEEN_PRECISION = 0.000000001;
		if (! StraightLinesCross(X11, Y11, X12, Y12, X21, Y21, X22, Y22, dX, dY) ){
			EAG_LOG_INFO("CXYPoligon::GetBalancePoint - can't find triangle balance point")
			return false;
		}

		csaTriangleBalancePoints[i].m_dY	= dY;
		csaTriangleBalancePoints[i].m_dX	= dX;

	}

	// and now last but not least calculate averaged center:
	dX = 0;
	dY = 0;
	dTotalArea = 0;


	for ( i = 0 ; i <  arrayTriangAngleIndex.GetSize() ; i++){

		dX			+= csaTriangleBalancePoints[i].m_dX * csaDoubleArrayTriangleAreas[i];
		dY			+= csaTriangleBalancePoints[i].m_dY * csaDoubleArrayTriangleAreas[i];
		dTotalArea	+= csaDoubleArrayTriangleAreas[i];
	}

	if ( dTotalArea > 0 ) {
		CPointBalance.m_dY = dY / dTotalArea;
		CPointBalance.m_dX = dX / dTotalArea;
	}
	else {
		dX = 0;
		dY = 0;
		dTotalArea = 0;

		//Do a normal average on all points ( may be its a straight line )
		for( i = 0 ; i < iArraySize; i++ ) {
			dX	+= m_arrayPoints[i].m_dX;
			dY	+= m_arrayPoints[i].m_dY;
		}

		CPointBalance.m_dY = dY / iArraySize;
		CPointBalance.m_dX = dX / iArraySize;
	}

	return true;
}


double CXYPoligon::TriangleArea(double &X11, double &Y11, double &X12, double &Y12, double &X13, double &Y13)
{
	//           X11       | X12 - X11 | 
	//               + R * |           |
	// line 1:   Y11       | Y12 - Y11 | 
	// 

	//			 X12       | X13 - X12 |
	//               + S * |           |
	// line 2:   Y12       | Y13 - Y12 |
	// is not needed in this calculation

	//			 X13       | X11 - X13 |
	//               + Q * |           |
	// line 3:   Y13       | Y11 - Y13 |
	// is also not needed 

	//			 X13       | Y11 - Y12 |
	//               + H * |           |
	// Helpline: Y13       | X12 - X11 |
	// is orthogonal to line 1   

	// first find crossing point of line 1 with Helpline:
	double X ,Y;
	// need a second point for helpline ( set H = 1 ):

	X = X13 + 1.0 * ( Y11 - Y12 );
	Y = Y13 + 1.0 * ( X12 - X11 );

	m_dBETWEEN_PRECISION = 0.000000001;
	StraightLinesCross( X11, Y11, X12, Y12, X13, Y13, X, Y , X, Y); // no matter what result

	// length of line 1:
	double dLength1 = ( X12-X11 ) * ( X12-X11 ) + ( Y12 - Y11 ) *  ( Y12 - Y11 );

	if ( dLength1 < 0.0000000001)
		return 0.0;

	// dLength1 is base length of triangle
	dLength1 = sqrt(dLength1);

	double dHight = ( X13-X ) * ( X13-X ) + ( Y13 - Y ) *  ( Y13 - Y );

	if ( dHight < 0.0000000001)
		return 0.0;

	dHight = sqrt(dHight);

	// so all we habe to do is multiply base with hight and take the halfe:
	return dLength1 * dHight / 2 ;
}




bool CXYPoligon::PointInside(  double &dX, double &dY)
{

	if (! m_bClosed){
		EAG_LOG_INFO("CXYPoligon::PointInside - poligon is not closed")
		return false; 
	}
	else if ( m_arrayPoints.GetSize() < 3 ) {
		EAG_LOG_INFO("CXYPoligon::PointInside - poligon is just a point or straigt line")
		return false; 
	}

	// now lets define a point outside: say
	double dYOutside	= GetMinY() - 10.; // impossible Y value thats outside
	double dXOutside	= GetMinX() - 10.; // impossible X value thats outside

	double X,Y;	// crossing point


	// since all lines are poligons, it's very easy to check:
	// simply count lines, which crosses line between given point and outside point:
	int iCountOfCrosses=0;
	// if iCountOfCrosses % 2 == 0 ( even value ) means point is outside...

	for ( int i = 1 ; i < m_arrayPoints.GetSize() ; i++ ){
	
		if ( StraightLinesCross( dX, dY, dXOutside, dYOutside, 
								m_arrayPoints[i].m_dX, m_arrayPoints[i].m_dY,
								m_arrayPoints[i-1].m_dX, m_arrayPoints[i-1].m_dY,X,Y))
			iCountOfCrosses++;
	}

	if ( StraightLinesCross( dX, dY, dXOutside, dYOutside, 
							 m_arrayPoints[ m_arrayPoints.GetUpperBound()].m_dX, m_arrayPoints[ m_arrayPoints.GetUpperBound()].m_dY,
							 m_arrayPoints[0].m_dX, m_arrayPoints[0].m_dY,X,Y))
		iCountOfCrosses++;

	return ( iCountOfCrosses % 2 ) == 1 ;
}


bool CXYPoligon::StraightLinesCross(double &X11, double &Y11, double &X12, double &Y12, double &X21, double &Y21, double &X22, double &Y22, double &X, double &Y)
{
	// calculate first of all crossing point:
	// therefore pultiply X evalatation with factor for y elimination:
	
	// line 1:   Y11       | Y12 - Y11 |      Y21       | Y22 - Y21 |
	//               + R * |           |  ==      + S * |           |
	// line 2:   X11       | X12 - X11 |      X21       | X22 - X21 |

	double Z;		// a helping var
	double R;		// for factor of line 1 ( index 1 )
	double S;		// for factor of line 2 ( index 2 )
//	double X,Y;		// crossing point

	if ( X12 - X11 == 0 ) {
		// crossing point is:
		if ( X22 - X21 == 0 ) { // vertical and parallel
			if ( X11 != X22 ) { // and have not same X
				return false;
			}
			else { // both are vertical and have same Y value
				X = X11;

				if (BETWEEN(Y11,Y21,Y22)) {
					Y = Y11;
					return true;
				}

				if (BETWEEN(Y12,Y21,Y22)) {
					Y = Y12;
					return true;
				}

				if (BETWEEN(Y21,Y11,Y12)) {
					Y = Y21;
					return true;
				}

				return false; // almost, but lengthes does not fit
			}
		}
		else {
			// use second line (  X12 - X11 == 0) &&  X22 - X21 != 0:

			// X11 + 0 * ( X12 - X11 ) = X21 + S * (X22 - X21)
			
			S = ( X11 - X21 ) / (X22 - X21);
			X = X21 + S * (X22 - X21);
			Y = Y11 + S * (Y22 - Y21);
		}
	}
	else {
		if ( ( Y22 - Y21 ) != 0 ) { // (not horizontal)

			if ( ( X22 - X21 ) == 0 ){
				// -> X11 + R * ( X12 - X11 ) = X21;
				R = (X21 - X11 ) / ( X12 - X11 );
				X = X11 + R * ( X12 - X11 );
				Y = Y11 + R * ( Y12 - Y11 );
			}
			else {
				Z = - ( Y12 - Y11 ) / ( X12 - X11 );
				// now pultiply second evaluation wiht Z and add first ( R disappears ):
			
				// Y11     + 0 = Y21     + S * ( Y22 - Y21)
				// X11 * Z + 0 = X21 * Z + S * ( X22 - X21 ) * Z
				// -> + 
				// Y11 +  X11 * Z    = X21 * Z + Y21 + S * ( X22 - X21 ) * Z + S * ( Y22 - Y21) 
				// Y11 +  X11 * Z  - X21 * Z -  Y21 =  S * ( ( X22 - X21 ) * Z + ( Y22 - Y21)) 
				
				if ( ( ( X22 - X21 ) * Z + ( Y22 - Y21)) == 0 ){
					// then there is no solution ( lines may be don't cross because they are parrallel and aslope)
					return false;
				}

				S = ( Y11 +  ( X11 - X21 ) * Z - Y21) /  ( ( X22 - X21 ) * Z + ( Y22 - Y21));

				// crossing point:
				X = X21 + S * ( X22 - X21 );
				Y = Y21 + S * ( Y22 - Y21 );
			}

		}
		else {
			// line 1:  Y11 + R * ( Y12 - Y11 ) = Y21 
			// so
			if ( ( Y12 - Y11 ) != 0 ) {
				R = ( Y21 - Y11 ) / ( Y12 - Y11 );
				X = X11 + R * ( X12 - X11 );
				Y = Y11 + R * ( Y12 - Y11 );
			}
			else { // line 1 and 2 are horizontal
				// so check if they have same Y values:
				if ( Y11 != Y21 ) { // they can't fitt
					return false;
				}
				else { // both are horizontal and have same Y value
					Y = Y11;

					if (BETWEEN(X11,X21,X22)) {
						X = X11;
						return true;
					}
				
					if (BETWEEN(X12,X21,X22)) {
						X = X12;
						return true;
					}

					if (BETWEEN(X21,X11,X12)) {
						X = X21;
						return true;
					}

					return false;
	
				}

			}
		
		}
	}

	//now check if crossing point is on both lines:

	if ( BETWEEN(X,X11,X12) ) { // X on line 1
		
		if ( BETWEEN(Y,Y11,Y12) ) { // Y also on line 1
		
			if ( BETWEEN(X,X21,X22) ) { // X on line 2
				
				if ( BETWEEN(Y,Y21,Y22) ) { // Y also on line 2
			
					return true; // so  crossing point is on both lines -> lines crossing
				}
			}
		}
	}
	return false;
}

double CXYPoligon::GetMaxX()
{
	double dMaxX = -1.7E308;

	if ( m_arrayPoints.GetSize() == 0 )
		return dMaxX;

	for (int i = 0 ; i < m_arrayPoints.GetSize() ; i++ )
		dMaxX = dMaxX > m_arrayPoints[i].m_dX ? dMaxX : m_arrayPoints[i].m_dX;

	return dMaxX;
}

double CXYPoligon::GetMinX()
{
	double dMinX = 1.7E308;

	if ( m_arrayPoints.GetSize() == 0 )
		return dMinX;

	for (int i = 0 ; i < m_arrayPoints.GetSize() ; i++ )
		dMinX = dMinX < m_arrayPoints[i].m_dX ? dMinX : m_arrayPoints[i].m_dX;

	return dMinX;
}

double CXYPoligon::GetMaxY()
{
	double dMaxY = -1.7E308;

	if ( m_arrayPoints.GetSize() == 0 )
		return dMaxY;

	for (int i = 0 ; i < m_arrayPoints.GetSize() ; i++ )
		dMaxY = dMaxY > m_arrayPoints[i].m_dY ? dMaxY : m_arrayPoints[i].m_dY;

	return dMaxY;

}

double CXYPoligon::GetMinY()
{
	double dMinY = 1.7E308;

	if ( m_arrayPoints.GetSize() == 0 )
		return dMinY;

	for (int i = 0 ; i < m_arrayPoints.GetSize() ; i++ )
		dMinY = dMinY < m_arrayPoints[i].m_dY ? dMinY : m_arrayPoints[i].m_dY;

	return dMinY;

}

} // end of namespace

