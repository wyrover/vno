#pragma once

#include <core/SkPaint.h>
#include <core/SkCanvas.h>
#include <core/sktdarray.h>

class SkTextLayoutEx {
public:
    //not support for DT_PREFIXONLY
    void init(const wchar_t text[], size_t length,SkRect rc, const SkPaint &paint,UINT uFormat);

    SkRect draw(SkCanvas* canvas);

private:
    SkScalar drawLineEndWithEllipsis(SkCanvas *canvas, SkScalar x, SkScalar y, int iBegin,int iEnd,SkScalar fontHei,SkScalar maxWidth);

    SkScalar drawLine(SkCanvas *canvas, SkScalar x, SkScalar y, int iBegin,int iEnd,SkScalar fontHei);

    void buildLines();

private:
    SkTDArray<wchar_t> m_text;   //�ı�����
    SkTDArray<int>  m_prefix;    //ǰ׺������
    SkTDArray<int> m_lines;      //��������
    UINT            m_uFormat;    //��ʾ��־
    SkRect          m_rcBound;    //���ƾ���
    const SkPaint  *m_paint;
};


SkRect DrawText_Skia(SkCanvas* canvas,const wchar_t *text,int len,SkRect box,const SkPaint& paint,UINT uFormat);
