#pragma once

#include <math.h>

#define PI 3.1415926535897932384626433832795
//度数转弧度
#define DegToRad(x) x*0.01745329251994329576923690768489
//弧度转度数
#define RadToDeg(x) x*57.295779513082320876798154814105
//平方
#define square(x)  x*x
//余切
#define cot(x) 1.0/tan(x)

//剖面图绘制基类
class BaseGraph
{
public:
    //虚析构函数
    virtual ~BaseGraph() {}
    //绘图(煤层、巷道、钻场、钻孔、底板岩巷等)
    void draw();
    //设置绘图基点坐标
    void setPoint( const AcGePoint3d& pt );
    //获取绘图基点坐标
    AcGePoint3d getPoint() const;

protected:
    //执行具体的绘图工作(绘制煤层、工作面巷道、钻场、钻孔、底板岩巷等等)
    virtual void subDraw() = 0;

protected:
    //构造函数
    BaseGraph();
    //设置ucs坐标系(派生类如有需要,应在构造函数中调用该方法)
    void setUcs( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis );

    /** 辅助绘图方法. */
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
    //记录所绘制的图元(仅BaseGraph类内部使用)
    void addEnt( const AcDbObjectId& objId );

    /** ucs相关的数据. */
private:
    AcGePoint3d m_basePt;      // 绘图基点
    AcDbObjectIdArray m_ents;  // 所有绘制的图元
    AcGeMatrix3d m_mat;        // ucs坐标系变换矩阵

}; // class Graph