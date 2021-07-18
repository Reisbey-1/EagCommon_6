// XYPoligon.h: Schnittstelle für die Klasse CXYPoligon.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XYPOLIGON_H__38689BB2_10DA_43DF_B9E1_1A90C09B2642__INCLUDED_)
#define AFX_XYPOLIGON_H__38689BB2_10DA_43DF_B9E1_1A90C09B2642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace eag {

#ifdef MATHUTILITY_EXPORTS
#define MATHUTILITY_API __declspec(dllexport)
#else
#define MATHUTILITY_API __declspec(dllimport)
#endif

class MATHUTILITY_API CPoligonPoint {
public:

	double m_dY;
	double m_dX;
	void * m_pPointData;
	

	CPoligonPoint( double &dX, double &dY,	void * pPointData) :
		m_dY(dY),
		m_dX(dX),
		m_pPointData(pPointData)	{
	};
	
	CPoligonPoint(){};
};

class MATHUTILITY_API CXYPoligon  
{
public:
	CXYPoligon();
	virtual ~CXYPoligon();
	double GetMinY();
	double GetMaxY();
	double GetMinX();
	double GetMaxX();

	CArray < CPoligonPoint, CPoligonPoint&> m_arrayPoints;
	void * m_pPoligonData;

	// manage poligon
	int AddLine( double dX, double dY, void * pPointData);
	void CleanUp();

	// function on poligons:
	bool PointNearBy( int &iPoint, double& m_dX,  double& m_dY, float fPrecisionX, float fPrecisionY);

	bool StraightLinesCross( double &X11, double &Y11, double &X12, double &Y12, double &X21, double &Y21, double &X22, double &Y22, double &X, double &Y);
	bool PointInside(  double & dX, double &dY);
	double TriangleArea(double &X11, double &Y11, double &X12, double &Y12, double &X13, double &Y13);
	bool GetBalancePoint( CPoligonPoint &CPointBalance, double &dTotalArea);

	void SetClosed(bool bClosed);
	bool GetClosed();

	void SetDirection(int iDirection);
	int GetDirection();

protected:
	bool m_bClosed;
	int m_iDirection; // 0: no direction, -1: right (clock wise), 1: left (counter clock wise)

	float m_fPrecisionY;
	float m_fPrecisionX;
	double m_dBETWEEN_PRECISION;

	bool PointNearBy( CPoligonPoint& Point, double& dX, double& dY );

	class TriangAngleIndex{
	public:
		int m_a,m_b,m_c;
		TriangAngleIndex(){};
		TriangAngleIndex(int a, int b, int c) :
			m_a(a),m_b(b),m_c(c) {};
	};

	class LineIndex {
	public:
		int m_a,m_b;
		LineIndex(){};
		LineIndex(int a, int b) :
			m_a(a),m_b(b) {};
	};
};

}; // end of namespace
 
#endif // !defined(AFX_XYPOLIGON_H__38689BB2_10DA_43DF_B9E1_1A90C09B2642__INCLUDED_)
