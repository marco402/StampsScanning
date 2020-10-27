// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_generiques_fonctions.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef CLASSGENERIQUESFONCTIONS_H
#define CLASSGENERIQUESFONCTIONS_H

#include "common.h"
class classGeneriquesFonctions
{
public:
    classGeneriquesFonctions();
    static corners addFrame(corners fourCorner,int width);
    static corners  removeFrame(corners fourCorner ,int width);
    static QList<QPointF> rejectAberrantsPoints(QList<QPointF> thePts , oppositeSide sideNorthOrSouth , int delta  = 1) ;
    static QList<QPointF> rejectAberrantsPoints(xOrY param,QList<int> start) ;
    static QVector<double> rejectAberrantsPoints(QVector<double> thePts , int delta  = 1) ;
    static bool pt1yLessPt2y(const QPointF &pt1, const QPointF &pt2);
    static bool pt2yLessPt1y(const QPointF &pt1, const QPointF &pt2);
    static bool pt1xLessPt2x(const QPointF &pt1, const QPointF &pt2);
    static bool floatCompare(double f1, double f2);
    static bool pt1YComparePt2Y(const QPointF &pt1, const QPointF &pt2);
    static void bitMapToBinary(struct oneMatrix *theMatrix,QImage *image, int treshold,QImage *debugImage=nullptr);
    static QList<QPointF> averageEqualY(QList<QPointF> StartSortNoDouble);
    static QColor getBackColor(QImage image);
private:
    static void processColor(QImage startBitmap,int &a,int &r,int &g,int &b,int x,int y);
    static void cleanMatrix(struct oneMatrix *theMatrix,QImage *image,bool flagDebug);
};

#endif // CLASSGENERIQUESFONCTIONS_H
