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
        mapString( _T( "����" ), &m_name );
        mapDouble( _T( "���" ), &m_width );
        mapDouble( _T( "�߶�" ), &m_height );
        mapInt( _T( "ͶӰ����" ), &m_projType );
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
        mapString( _T( "����" ), &m_name );
        mapDouble( _T( "���" ), &m_thick );
        mapDouble( _T( "���" ), &m_angle );
        mapPoint( _T( "���ĵ�����" ), &m_pt );
        mapVector( _T( "ƽ�淨����" ), &m_normV );
        mapVector( _T( "ú����������" ), &m_headV );
        mapVector( _T( "ú����������" ), &m_dipV );
        mapDouble( _T( "���򳤶�" ), &m_width );
        mapDouble( _T( "���򳤶�" ), &m_height );
    }

public:
    CString m_name;
    double m_thick;
    double m_angle;
    double m_width;
    double m_height;
    //�����ڲ��洢�����ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
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
        mapString( _T( "����" ), &m_name );
        mapDouble( _T( "���" ), &m_width );
        mapDouble( _T( "�߶�" ), &m_height );
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
        mapInt( _T( "���" ), &m_pore_num );
        mapDouble( _T( "�׾�" ), &m_pore_size );
        mapPoint( _T( "����" ), &m_pt );
    }

public:
    int m_pore_num;
    double m_pore_size;
    AcGePoint3d m_pt;
};