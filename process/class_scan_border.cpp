// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:partial_form_main_manage_separate_stamps_thread.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "class_scan_border.h"
#include "class_generiques_fonctions.h"
//detection on the first true pixel in x increasing for each y
QList<QPointF> scanBorder::detectFirstPixXTrue(struct oneMatrix *theMatrix, int maxX, int maxY )
{
    QList<int> startX;
    for (int y=0;y< maxY;y++)
    {
        for (int x=0;x< maxX;x++)
        {
            if (theMatrix->pix[x][y])
            {
                        startX.append(x-1);
                        break;
            }
        }
    }
    return classGeneriquesFonctions::rejectAberrantsPoints(xOrY::Y, startX);
}
//detection on the first true pixel in y increasing for each x
QList<QPointF> scanBorder::detectFirstPixYTrue(struct oneMatrix *theMatrix, int maxX, int maxY )
{
    QList<int> startY;
    for (int x=0;x< maxX;x++)
    {
        for (int y=0;y< maxY;y++)
        {
            if (theMatrix->pix[x][y])
            {
                        startY.append(y-1);
                        break;
            }
        }
    }
    return classGeneriquesFonctions::rejectAberrantsPoints(xOrY::X, startY);
}
//detection on the last true pixel in x increasing for each y
QList<QPointF> scanBorder::detectLastPixXTrue(struct oneMatrix *theMatrix, int maxX, int maxY )
{
    QList<int> startX;
    for (int y=0;y< maxY;y++)
    {
        for (int x=maxX-1;x> 0;x--)
        {
            if (theMatrix->pix[x][y])
            {
                        startX.append(x+1);
                        break;
            }
        }
    }
    return classGeneriquesFonctions::rejectAberrantsPoints(xOrY::Y, startX);
}
// detection on the last true pixel in y increasing for each x
QList<QPointF> scanBorder::detectLastPixYTrue(struct oneMatrix *theMatrix, int maxX, int maxY )
{
    QList<int> startY;
    for (int x=0;x< maxX;x++)
    {
        for (int y=maxY-1;y> 0;y--)
        {
            if (theMatrix->pix[x][y])
            {
                        startY.append(y+1);
                        break;
            }
        }
    }
    return classGeneriquesFonctions::rejectAberrantsPoints(xOrY::X, startY);
}
