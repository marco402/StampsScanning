// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_sep_stamps_generales_functions.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QImage>
#include <QColor>
#include "class_sep_stamps_generales_functions.h"
#include "class_generiques_fonctions.h"
#include "class_geometrie.h"
#include "class_sep_stamps_find_borders.h"
#include "constantes.h"
QList<QList<QPointF>> sepStampFunctions::processAroundAndCornersStampClockwise(struct oneMatrix *theMatrix ,QPointF startPoint  ,QPointF &memoX,QImage image)
{
    QList<QList<QPointF>> listPoint ;
    QList<QPointF> ptOuestN = findBorders::borderFrameWEstToNorth(theMatrix, startPoint,image.width(),-1);
    QList<QPointF> ptOuestS;
    if (ptOuestN.count() < NBPOINTMINIXX) 
    {
        double NpixPour1cm =  image.physicalDpiY() / INCH;
        ptOuestS = findBorders::borderFrameWEstToSouth(theMatrix, startPoint,image.width(),image.height(),  static_cast<int>(startPoint.y() + static_cast<int>(NpixPour1cm)));
        if (ptOuestS.count() < NBPOINTMINIXX) return listPoint;
        ptOuestN.clear();
        ptOuestN = findBorders::borderFrameWEstToNorth(theMatrix, ptOuestS.at(ptOuestS.count() - 1),image.width(),-1);
        ptOuestS.clear();
    }
    if (ptOuestN.count() < NBPOINTMINIXX) return listPoint;
    QList<QPointF> ptNord  = findBorders::borderFrameNorthToEast(theMatrix, ptOuestN.at(ptOuestN.count() - 1),image.width(),image.height());
    if (ptNord.count() < NBPOINTMINIXX) return listPoint;
    QList<QPointF> ptEst  = findBorders::borderFrameEastToSouth(theMatrix, ptNord.at(ptNord.count() - 1),image.width(),image.height());
    if (ptEst.count() < NBPOINTMINIXX) return listPoint;
    QList<QPointF> ptSud  = findBorders::borderFrameSouthToWest(theMatrix, ptEst.at(ptEst.count() - 1),image.height());
    if( ptSud.count() < NBPOINTMINIXX) return listPoint;
    std::sort(ptSud.begin(), ptSud.end(), classGeneriquesFonctions::pt1xLessPt2x);
 
    QList<QPointF>::iterator i;
    for (i = ptEst.begin(); i != ptEst.end(); ++i)
        if((qAbs((*i).y()-startPoint.y()))<DBL_EPSILON)
        {
            memoX = *i;
            break;
        }
    if (memoX.x() == 0.0)
        memoX =QPointF( ptEst.at(0).x(),startPoint.y());

    ptOuestS = findBorders::borderFrameWEstToNorth(theMatrix, ptSud.first(),image.width(),-1);
    if (ptOuestS.count() < NBPOINTMINIXX) return listPoint;
    std::sort(ptOuestS.begin(), ptOuestS.end(), classGeneriquesFonctions::pt1yLessPt2y);
    //order is same as Enum sideStamp
    listPoint.append(ptNord);
    listPoint.append(ptEst);
    listPoint.append(ptSud);
    listPoint.append(ptOuestS);
    return listPoint;
}
QList<QList<QPointF>> sepStampFunctions::processAroundAndCornersStampTrigo(struct oneMatrix *theMatrix,QPointF startPoint ,QPointF &memoX,QImage image)
{
    QList<QList<QPointF>> listPoint ;
    QList<QPointF> ptOuestN ;
    QList<QPointF> ptOuestS = findBorders::borderFrameWEstToSouth(theMatrix, startPoint,image.width(),image.height(),-1);
    if (ptOuestS.count() < NBPOINTMINIXX) //Return listPoint
    {
        ptOuestN = findBorders::borderFrameWEstToNorth(theMatrix, startPoint,image.width(), -1);
        if (ptOuestN.count() < NBPOINTMINIXX) return listPoint;
         ptOuestS.clear();
        ptOuestS = findBorders::borderFrameWEstToSouth(theMatrix,ptOuestN.at(ptOuestN.count() - 1),image.width(),image.height(),-1);
        ptOuestN.clear();
    }
    if (ptOuestS.count() < NBPOINTMINIXX) return listPoint;
    QList<QPointF> ptSud = findBorders::borderFrameSouthToEast(theMatrix, ptOuestS.at(ptOuestS.count() - 1),image.width(),image.height());
    if (ptSud.count() < NBPOINTMINIXX) return listPoint;
    QList<QPointF> ptEst = findBorders::borderFrameEastToNorth(theMatrix, ptSud.at(ptSud.count() - 1),image.width());
    if (ptEst.count() < NBPOINTMINIXX) return listPoint;
    QList<QPointF> ptNord = findBorders::borderFrameNorthToWest(theMatrix, ptEst.at(ptEst.count() - 1),image.height());
    if (ptNord.count() < NBPOINTMINIXX) return listPoint;
    std::sort(ptNord.begin(), ptNord.end(), classGeneriquesFonctions::pt1xLessPt2x);
     QList<QPointF>::iterator i;
    for (i = ptEst.begin(); i != ptEst.end(); ++i)
        if((qAbs((*i).y()-startPoint.y()))<DBL_EPSILON)
        {
            memoX = *i;
            break;
        }
    if (memoX.x() == 0.0)
        memoX = QPointF(ptEst.at(0).x(),startPoint.y());
    std::sort(ptEst.begin(), ptEst.end(), classGeneriquesFonctions::pt1yLessPt2y);
    ptOuestN = findBorders::borderFrameWEstToSouth(theMatrix, ptNord.at(0),image.width(),image.height(),-1);
    if (ptOuestN.count() < NBPOINTMINIXX) return listPoint;
    //order is same as Enum sideStamp
    listPoint.append(ptNord);
    listPoint.append(ptEst);
    listPoint.append(ptSud);
    listPoint.append(ptOuestN);
    return listPoint;
}
QList<corners> sepStampFunctions::processClockwiseOrTrigo(corners fourCorner, QList<corners> stampCorners , QList<QList<QPointF>> &lesPointsDesCotes,QPointF &memoX, QList<QList<QPointF>> tempClockwiseOrTrigo ,QPointF memoXHouT)
{
    corners unAngleOut  = classGeneriquesFonctions::addFrame(fourCorner, DXY_BORDER);
    stampCorners.append(unAngleOut);
    lesPointsDesCotes.append(tempClockwiseOrTrigo[static_cast<int>(sideStamp::EAST)]);
    memoX=memoXHouT;
    return stampCorners;
}
