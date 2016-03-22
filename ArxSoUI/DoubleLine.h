#pragma once

//����˫��
class DoubleLine
{
public:
    static AcDbObjectId Draw( const AcGePoint3d& spt, const AcGePoint3d& ept, double width );

public:
    DoubleLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width );
    AcDbObjectId draw();

protected:
    void caclStartPoint( AcGePoint3d& startPt1, AcGePoint3d& startPt2 );
    void caclEndPoint( AcGePoint3d& endPt1, AcGePoint3d& endPt2 );

private:
    AcGePoint3d m_spt, m_ept;
    double m_width;
    //��̬��Ա����������ͳ�ƶ������
    static int count;
};
