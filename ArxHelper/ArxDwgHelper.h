#pragma once

#include "dlimexp.h"

/**
* dwg���ݿ⸨��������.
*/
class ARXHELPER_API ArxDwgHelper
{
public:
    //����dwg�ļ�
    static bool InsertDwg( const CString& dwgFilePath );

    //����ͼ��
    static void UpdateDwg();
};
