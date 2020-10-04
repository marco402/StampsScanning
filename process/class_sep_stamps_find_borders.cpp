// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_sep_stamps_find_borders.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "class_sep_stamps_find_borders.h"
#include "common.h"
#include "constantes.h"
QList<QPointF> findBorders::borderFrameWEstToNorth(struct oneMatrix *theMatrix,QPointF start,int width, int endY)
{
    QList<QPointF> pt ;
    int depXOuest=static_cast<int>(round(start.x()));
    for(int y=static_cast<int>(round(start.y()));y>endY;y--)
    {

        int minX = qMax(0, depXOuest - D_SWEEP_OUT);
        int maxX = qMin(width-1, depXOuest + D_SWEEP_IN);
        int x;
        for (x = minX;x< maxX;x++)
        {
            if (theMatrix->pix[x][y])
            {
                pt.append(QPointF(x, y));//it's the stamp
                depXOuest = x;
                break;
            }
        }
        if (x==maxX)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameWEstToSouth(struct oneMatrix *theMatrix,QPointF start,int width,int height, int endY)
{
    QList<QPointF> pt ;
    int depXOuest = static_cast<int>(round(start.x()));
     int depYOuest = static_cast<int>(round(start.y()));
    //*************************************************
    //two line more with other function
    int maxy = height;
    if (endY > -1)  maxy = qMin(endY, height);
    //**************************************************
    for(int y=depYOuest;y<maxy;y++)
    {
        int minX = qMax(0, depXOuest - D_SWEEP_OUT);
        int maxX = qMin(width-1, depXOuest + D_SWEEP_IN);
        int x;
        for ( x = minX;x< maxX;x++)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                depXOuest = x;
                break;
            }
        }
        if (x==maxX)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameNorthToEast(struct oneMatrix *theMatrix,QPointF start,int width,int height)
{
    QList<QPointF> pt ;
    int startXNord=static_cast<int>(round(start.x()));
    int startYNord  = static_cast<int>(round(start.y()));
    for(int x=startXNord;x<width;x++)
    {
        int minY = qMax(0, startYNord - D_SWEEP_OUT);
        int maxY = qMin(height-1, startYNord + D_SWEEP_IN);
        int y;
        for ( y = minY;y< maxY;y++)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                startYNord = y;
                break;
            }
        }
        if (y==maxY)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameNorthToWest(struct oneMatrix *theMatrix,QPointF start,int height )
{
    QList<QPointF> pt ;
    int startXNord  = static_cast<int>(round(start.x()));
    int startYNord  = static_cast<int>(round(start.y()));
    for(int x=startXNord;x>0;x--)
    {
        int minY = qMax(0, startYNord - D_SWEEP_OUT);
        int maxY = qMin( height-1, startYNord + D_SWEEP_IN);
        int y;
        for ( y = minY;y< maxY;y++)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                startYNord = y;
                break;
            }
        }
        if (y==maxY)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameEastToNorth(struct oneMatrix *theMatrix,QPointF start,int width )
{
    QList<QPointF> pt ;
    int startXEst  = static_cast<int>(round(start.x()));
    int startYEst  = static_cast<int>(round(start.y()));
    for(int y=startYEst;y>0;y--)
    {
        int minX = qMax(0, startXEst - D_SWEEP_IN);
        int maxX = qMin(width-1, startXEst + D_SWEEP_OUT);
        int x;
        for ( x = maxX;x>minX;x--)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                startXEst = x;
                break;
            }
        }
        if (x==minX)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameEastToSouth(struct oneMatrix *theMatrix,QPointF start,int width,int height )
{

    QList<QPointF> pt ;
    int startXEst  = static_cast<int>(round(start.x()));
    int startYEst  = static_cast<int>(round(start.y()));
    for(int y=startYEst;y<height;y++)
    {
        int minX = qMax(0, startXEst - D_SWEEP_IN);
        int  maxX = qMin(width-1, startXEst + D_SWEEP_OUT);
        int x;
        for ( x = maxX;x>minX;x--)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                startXEst = x;
                break;
            }
        }
        if (x==minX)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameSouthToEast(struct oneMatrix *theMatrix,QPointF start,int width,int height )
{
    QList<QPointF> pt ;
    int startXSud  =static_cast<int>(round(start.x()));
    int startYSud  = static_cast<int>(round(start.y()));
    for(int x=startXSud;x<width;x++)
    {
        int  minY = qMax(0, startYSud - D_SWEEP_IN);
        int   maxY = qMin(height-1, startYSud + D_SWEEP_OUT);
        int y;
        for ( y = maxY;y>minY;y--)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                startYSud = y;
                break;
            }
        }
        if (y==minY)
            break;
    }
    return pt;
}
QList<QPointF> findBorders::borderFrameSouthToWest(struct oneMatrix *theMatrix,QPointF start,int height )
{
    QList<QPointF> pt ;
    int startXSud  =static_cast<int>(round(start.x()));
    int startYSud  =static_cast<int>(round(start.y()));

    for(int x=startXSud;x>0;x--)
    {
        int  minY = qMax(0, startYSud - D_SWEEP_IN);
        int  maxY = qMin(height-1, startYSud + D_SWEEP_OUT);
        int y;
        for ( y = maxY;y>minY;y--)
        {
            if (theMatrix->pix[x][y])
            {//it's the stamp
                pt.append(QPointF(x, y));
                startYSud = y;
                break;
            }
        }
        if (y==minY)
            break;
    }
    return pt;
}

