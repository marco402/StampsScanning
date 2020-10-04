// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:common.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef COMMON_H
#define COMMON_H

#include <QImage>
enum class sideStamp {NORTH,EAST,SOUTH,WEST};
enum class oppositeSide {NORTHSOUTH,EASTWEST};
enum class xOrY {X,Y};

struct  corners
{
     QPointF NORTH_WEST;
     QPointF NORTH_EAST;
     QPointF SOUTH_WEST;
     QPointF SOUTH_EAST;
};
struct structFormStamp
{
   int index;
   int left;
   int top;
   int border;
   double angleRad;
   double nbTeeth[4];
   QImage oneBmp;
   QColor backColor;
   QString title;
   QString currentPathSave;
   QString yearStamp;
};
struct oneMatrix{
    bool **pix;
    };



#endif // COMMON_H
