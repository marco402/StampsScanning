// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_sep_stamps_generales_functions.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef SEP_STAMPS_FUNCTIONS_H
#define SEP_STAMPS_FUNCTIONS_H
#include <QImage>
#include <QColor>
#include "common.h"
class sepStampFunctions
{
public:
    static QList<corners> processClockwiseOrTrigo(corners fourCorner, QList<corners> stampCorners , QList<QList<QPointF>> &sidesPoints ,QPointF &memoX,QList<QList<QPointF>> tempClockwiseOrTrigo,QPointF memoXHouT);
    static QList<QList<QPointF>> processAroundAndCornersStampClockwise(struct oneMatrix *theMatrix ,QPointF startPoint  ,QPointF &memoX,QImage image );
    static QList<QList<QPointF>> processAroundAndCornersStampTrigo(struct oneMatrix *theMatrix,QPointF startPoint ,QPointF &memoX,QImage image );
private:
};
#endif // SEP_STAMPS_FUNCTIONS_H


