// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_perforation.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef CLASS_PERFORATION_H
#define CLASS_PERFORATION_H
#include "common.h"
#include "constantes.h"
class class_perforation
{
#ifdef DEBUGDISPLAYIMAGE
public:
    static double processPerforation(sideStamp H, struct oneMatrix *theMatrix,QImage fullStampRectified,QList<QPointF> &listPtDebug,int borderDebug,double ratioPerforation);
private:
    static double perforationAtX(QList<QPointF> listStartPix,QImage fullStampRectified ,int resolution,QList<QPointF> &listPtDebug,double ratioPerforation);
#else
public:
    static double processPerforation(sideStamp H, struct oneMatrix *theMatrix,QImage fullStampRectified,double ratioPerforation);
private:
    static double perforationAtX(QList<QPointF> listStartPix,QImage fullStampRectified ,int resolution,double ratioPerforation);
#endif
private:
    static QList<QPointF> getBasePerforation(QList<QPointF>listStartSortNoDouble,double test);
    static double calcPerfo(QVector<double> newListClean,double nPixels);
    static QList<QPointF> getNbPtForEachPt(QList<QPointF> listStartPix,QImage fullStampRectified);
    static QVector<double> getBestPoint(QList<QPointF>  listNbPoint,QList<QPointF> listStartPix);
    static double getBestPoint(QVector<double>thePoints,double nbPixels);
    static double calcPerforation(QVector<double>thePoints,double nbPixels);
};
#endif // CLASS_PERFORATION_H

