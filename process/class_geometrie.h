// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_geometrie.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef CLASSGEOMETRIE_H
#define CLASSGEOMETRIE_H

#include "common.h"
#include "constantes.h"

class classGeometrie
{
public:
    static double getRotateAngleRad(corners listeSideStampAtAxesLevel);
    static bool getLineAveragePoints(QList<QPointF> data , double &Ai, double &Bi);
    static corners getCrossLines(double tabAi[],double tabBi[], bool &indicOK);
    static QPointF getCross2Lines(double Ai1,double Bi1,double Ai2,double Bi2, bool &indicOK);
    static corners processAngles( QList<QList<QPointF>> theData, bool &indicOK ,double ai[] ,double bi[]);
    static bool isInside(QPointF pt[],QPointF ref);
    static QImage rotateBitmap(QImage &bm_in,double angleRad,corners stampCorners,QColor backColor);

private:
    static QPolygonF rotatePoint(QPolygonF original,QPointF center,double angleDeg , double deltaX = 0.0, double deltaY = 0.0);
    static QPointF rotatePoint(QPointF lePoint,QPointF center,double angleDeg, double deltaX = 0.0, double deltaY = 0.0) ;
public:
    static QImage rotateImage(QImage bitmap,double angleDeg,QPointF &deltaBound,QColor backColor);
};

#endif // CLASSGEOMETRIE_H
