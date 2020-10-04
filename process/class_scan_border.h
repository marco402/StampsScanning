// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_scan_border.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef SCANBORDER_H
#define SCANBORDER_H
#include <QPointF>

class scanBorder
{
public:
    static QList<QPointF> detectFirstPixXTrue(struct oneMatrix *theMatrix,  int maxX,int maxY ) ;
    static QList<QPointF> detectFirstPixYTrue(struct oneMatrix *theMatrix, int maxX,int maxY ) ;
    static QList<QPointF> detectLastPixXTrue(struct oneMatrix *theMatrix, int maxX,int maxY ) ;
    static QList<QPointF> detectLastPixYTrue(struct oneMatrix *theMatrix, int maxX,int maxY ) ;
};

#endif // SCANBORDER_H
