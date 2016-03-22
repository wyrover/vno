#pragma once

#include <ArxHelper/XData.h>
#include <ArxHelper/ExtDictData.h>

class TestData : public XData
{
public:
    TestData() : m_width( 0 ), m_height( 0 ), m_projType( 0 )
    {

    }
protected:
    virtual void regDatas()
    {
        mapString( 0, &m_name );
        mapDouble( 1, &m_width );
        mapDouble( 2, &m_height );
        mapInt( 3, &m_projType );
    }

public:
    CString m_name;
    double m_width;
    double m_height;
    int m_projType;
};


class TunnelData : public ExtDictData
{
public:
    TunnelData() : m_width( 0 ), m_height( 0 ), m_projType( 0 )
    {

    }
protected:
    virtual void regDatas()
    {
        mapString( _T( "名称" ), &m_name );
        mapDouble( _T( "宽度" ), &m_width );
        mapDouble( _T( "高度" ), &m_height );
        mapInt( _T( "投影类型" ), &m_projType );
    }

public:
    CString m_name;
    double m_width;
    double m_height;
    int m_projType;
};

class CoalData : public ExtDictData
{
public:
    CoalData() : m_thick( 0 ), m_angle( 0 ), m_width( 0 ), m_height( 0 )
    {
    }
protected:
    virtual void regDatas()
    {
        mapString( _T( "名称" ), &m_name );
        mapDouble( _T( "厚度" ), &m_thick );
        mapDouble( _T( "倾角" ), &m_angle );
        mapPoint( _T( "中心点坐标" ), &m_pt );
        mapVector( _T( "平面法向量" ), &m_normV );
        mapVector( _T( "煤层走向向量" ), &m_headV );
        mapVector( _T( "煤层倾向向量" ), &m_dipV );
        mapDouble( _T( "走向长度" ), &m_width );
        mapDouble( _T( "倾向长度" ), &m_height );
    }

public:
    CString m_name;
    double m_thick;
    double m_angle;
    double m_width;
    double m_height;
    //坐标内部存储是用字符串表示的,xyz之间通过逗号分隔
    AcGePoint3d m_pt;
    AcGeVector3d m_normV;
    AcGeVector3d m_headV;
    AcGeVector3d m_dipV;
};

class DrillSiteData : public ExtDictData
{
public:
    DrillSiteData() : m_width( 0 ), m_height( 0 )
    {

    }
protected:
    virtual void regDatas()
    {
        mapString( _T( "名称" ), &m_name );
        mapDouble( _T( "宽度" ), &m_width );
        mapDouble( _T( "高度" ), &m_height );
    }

public:
    CString m_name;
    double m_width;
    double m_height;
};

class DrillPoreData : public ExtDictData
{
public:
    DrillPoreData() : m_pore_num( 0 ), m_pore_size( 0 )
    {

    }
protected:
    virtual void regDatas()
    {
        mapInt( _T( "编号" ), &m_pore_num );
        mapDouble( _T( "孔径" ), &m_pore_size );
        mapPoint( _T( "坐标" ), &m_pt );
    }

public:
    int m_pore_num;
    double m_pore_size;
    AcGePoint3d m_pt;
};