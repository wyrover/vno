#pragma once

#include <math.h>

#define PI 3.1415926535897932384626433832795
//����ת����
#define DegToRad(x) x*0.01745329251994329576923690768489
//����ת����
#define RadToDeg(x) x*57.295779513082320876798154814105
//ƽ��
#define square(x)  x*x
//����
#define cot(x) 1.0/tan(x)

//����ͼ���ƻ���
class BaseGraph
{
public:
    //����������
    virtual ~BaseGraph() {}
    //��ͼ(ú�㡢������곡����ס��װ������)
    void draw();
    //���û�ͼ��������
    void setPoint( const AcGePoint3d& pt );
    //��ȡ��ͼ��������
    AcGePoint3d getPoint() const;

protected:
    //ִ�о���Ļ�ͼ����(����ú�㡢������������곡����ס��װ�����ȵ�)
    virtual void subDraw() = 0;

protected:
    //���캯��
    BaseGraph();
    //����ucs����ϵ(������������Ҫ,Ӧ�ڹ��캯���е��ø÷���)
    void setUcs( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis );

    /** ������ͼ����. */
protected:
    AcDbObjectId drawRect( const AcGePoint3d& cnt, double angle, double width, double height );
    AcDbObjectId drawRect2( const AcGePoint3d& pt, double angle, double width, double height );
    AcDbObjectId drawCircle( const AcGePoint3d& pt, double radius );
    AcDbObjectId drawDoubleLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width );
	AcDbObjectId drawMText( const AcGePoint3d& pt, double angle, const CString& text, double height, AcDbMText::AttachmentPoint ap = AcDbMText::kMiddleLeft  );
    AcDbObjectId drawLine( const AcGePoint3d& pt, double angle, double length );
    AcDbObjectId drawLine( const AcGePoint3d& spt, const AcGePoint3d& ept );
    AcDbObjectId drawAlignedDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2, const CString& text=_T(""), double offset = 30, bool clockwise = true, const CString& dimStyle=_T("") );
	AcDbObjectId drawPolygonHatch(const AcGePoint3dArray& pts, const CString& patName, double scale);
    //��¼�����Ƶ�ͼԪ(��BaseGraph���ڲ�ʹ��)
    void addEnt( const AcDbObjectId& objId );

    /** ucs��ص�����. */
private:
    AcGePoint3d m_basePt;      // ��ͼ����
    AcDbObjectIdArray m_ents;  // ���л��Ƶ�ͼԪ
    AcGeMatrix3d m_mat;        // ucs����ϵ�任����

}; // class Graph