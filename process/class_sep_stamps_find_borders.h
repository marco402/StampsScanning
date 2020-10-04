// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_sep_stamps_find_borders.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef FIND_BORDERS_H
#define FIND_BORDERS_H
#include <QPointF>
#include <QList>

class findBorders
{
public:
    findBorders();
    static QList<QPointF> borderFrameWEstToNorth(struct oneMatrix *theMatrix,QPointF start,int width, int endY );
    static QList<QPointF> borderFrameWEstToSouth(struct oneMatrix *theMatrix,QPointF start,int width,int height, int endY );
    static QList<QPointF> borderFrameNorthToEast(struct oneMatrix *theMatrix,QPointF start,int width,int height);
    static QList<QPointF> borderFrameNorthToWest(struct oneMatrix *theMatrix,QPointF start,int height);
    static QList<QPointF> borderFrameEastToNorth(struct oneMatrix *theMatrix,QPointF start,int width);
    static QList<QPointF> borderFrameEastToSouth(struct oneMatrix *theMatrix,QPointF start,int width,int height);
    static QList<QPointF> borderFrameSouthToEast(struct oneMatrix *theMatrix,QPointF start,int width,int height);
    static QList<QPointF> borderFrameSouthToWest(struct oneMatrix *theMatrix,QPointF start,int height);
};

#endif // FIND_BORDERS_H
