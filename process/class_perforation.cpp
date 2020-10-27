// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_perforation.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QtMath>
#include "class_perforation.h"
#include "class_geometrie.h"
#include "class_generiques_fonctions.h"
#include "common.h"
#include "constantes.h"
#include "class_scan_border.h"
#include "QVector"
#include "class_sep_stamps_thread.h"

//return the number of teeth per 2 cm. or other see setting for one direction H.
#ifdef DEBUGDISPLAYIMAGE
double class_perforation::processPerforation(sideStamp H, struct oneMatrix *theMatrix,QImage fullStampRectified,QList<QPointF> &listPtDebug ,int borderDebug,double ratioPerforation)
#else
double class_perforation::processPerforation(sideStamp H, struct oneMatrix *theMatrix,QImage fullStampRectified,double ratioPerforation)
#endif
{
#ifdef DEBUGDISPLAYIMAGE
    QList<QPointF> list1PtDebug;
#endif
    QList<QPointF> listStartPix;
    int nbLine=fullStampRectified.height();
    int nbColumn=fullStampRectified.width();
    double teeth=0;
    switch (H)
    {
        case sideStamp::NORTH:
        {
            listStartPix = scanBorder::detectFirstPixYTrue(theMatrix,nbColumn ,nbLine);
            //for debug list in perforationAtX
#ifdef DEBUGDISPLAYIMAGE
            teeth= perforationAtX(listStartPix, fullStampRectified, fullStampRectified.physicalDpiX(),list1PtDebug, ratioPerforation);
            foreach (QPointF pt, list1PtDebug)
                listPtDebug.append (QPointF(pt.x()+borderDebug, pt.y()+borderDebug));
#else
    teeth= perforationAtX(listStartPix, fullStampRectified, fullStampRectified.physicalDpiX(), ratioPerforation);
#endif
            break;
        }
        case sideStamp::SOUTH:
        {
            listStartPix = scanBorder::detectLastPixYTrue(theMatrix,nbColumn ,nbLine);
            QList<QPointF> listStartPixAdditionY;
            foreach (QPointF pt, listStartPix)
                listStartPixAdditionY.append (QPointF(pt.x(), nbLine - pt.y()));

#ifdef DEBUGDISPLAYIMAGE
            teeth=  perforationAtX(listStartPixAdditionY, fullStampRectified, fullStampRectified.physicalDpiX(),list1PtDebug, ratioPerforation);
            //for debug list in perforationAtX

            foreach (QPointF pt, list1PtDebug)
                listPtDebug.append (QPointF(pt.x()+borderDebug,nbLine - pt.y()+borderDebug));
#else
    teeth=  perforationAtX(listStartPixAdditionY, fullStampRectified, fullStampRectified.physicalDpiX(), ratioPerforation);
#endif
            break;
        }
        case sideStamp::WEST:
        {
            listStartPix = scanBorder::detectFirstPixXTrue(theMatrix,nbColumn ,nbLine);
            QList<QPointF> listStartPixInvertedXY;
            foreach (QPointF pt, listStartPix)
                listStartPixInvertedXY.append (QPointF(pt.y(),  pt.x()));
            //for debug list in perforationAtX
#ifdef DEBUGDISPLAYIMAGE
            teeth=  perforationAtX(listStartPixInvertedXY, fullStampRectified, fullStampRectified.physicalDpiY(),list1PtDebug, ratioPerforation);
            foreach (QPointF pt, list1PtDebug)
                listPtDebug.append (QPointF(pt.y()+borderDebug,  pt.x()+borderDebug));
#else
            teeth=  perforationAtX(listStartPixInvertedXY, fullStampRectified, fullStampRectified.physicalDpiY(), ratioPerforation);
#endif
            break;
        }
        case sideStamp::EAST:
        {
            listStartPix = scanBorder::detectLastPixXTrue(theMatrix,nbColumn ,nbLine);
            QList<QPointF> listStartPixInvertedComplementX;
            foreach (QPointF pt, listStartPix)
                listStartPixInvertedComplementX.append (QPointF(pt.y(),nbColumn - pt.x()));
            //for debug list in perforationAtX
#ifdef DEBUGDISPLAYIMAGE
            teeth=  perforationAtX(listStartPixInvertedComplementX, fullStampRectified, fullStampRectified.physicalDpiY(),list1PtDebug, ratioPerforation);
            foreach (QPointF pt, list1PtDebug)
                listPtDebug.append (QPointF(nbColumn-pt.y()+borderDebug,pt.x()+borderDebug));
#else
            teeth=  perforationAtX(listStartPixInvertedComplementX, fullStampRectified, fullStampRectified.physicalDpiY(), ratioPerforation);
#endif
             break;
         }
    }
#ifdef DEBUGDISPLAYIMAGE
// listPtDebug+=listStartPix;// for display all pts
#endif
    return teeth;
}
#ifdef DEBUGDISPLAYIMAGE
    double class_perforation::perforationAtX(QList<QPointF> listStartPix,QImage fullStampRectified,int resolution,QList<QPointF> &listPtDebug ,double ratioPerforation)
#else
    double class_perforation::perforationAtX(QList<QPointF> listStartPix,QImage fullStampRectified,int resolution ,double ratioPerforation)
#endif
{
    //counts the number of each deviation
    QList<QPointF>  listNbPoint=class_perforation::getNbPtForEachPt(listStartPix,fullStampRectified);
    //take the larger N and the adjacent 2, le petit prince nord:8--->7.8.9
    QVector<double>thePoints=getBestPoint(listNbPoint,listStartPix);
//reject spaces trop shorts
#ifdef DEBUGDISPLAYIMAGE
//    foreach (double pt, thePoints)
//        listPtDebug.append(QPointF(pt,9));
    //after this, values are not point /image-->modif if you want last points used for calculate
#endif
    double nPixels2cm=resolution*ratioPerforation;       // after calibration: "le petit prince":12.9,13.1,13.0,13.3
     return class_perforation::calcPerforation(thePoints,nPixels2cm);
}
QVector<double> class_perforation::getBestPoint(QList<QPointF>  listNbPoint,QList<QPointF> listStartPix)
{
    int mini=static_cast<int>(listNbPoint.at(0).x())-2;  //-2 for > and not >=
    int maxi=mini+4;
    QVector<double>thePoints;
    bool start=false;
    double xStart=0;
    foreach (QPointF pt, listStartPix)
    {
        if (!start)
        {
            if (pt.y()>mini && pt.y()<maxi )
            {
                start=true;
                xStart=pt.x();
            }
        }
        else
        {
            if (pt.y()<=mini || pt.y()>=maxi )
            {
                thePoints.append(xStart+(pt.x()-xStart)/2);
                start=false;
                xStart=0;
            }
        }
    }
    return thePoints;
}
double class_perforation::calcPerforation(QVector<double>thePoints,double nbPixels)
{
    QVector<double>theDeltas;

    for (int i=0;i<thePoints.count()-1;i++)
        theDeltas.append(thePoints.at(i+1)-thePoints.at(i));
    QVector<double> theDeltasClean = classGeneriquesFonctions::rejectAberrantsPoints(theDeltas,  0);
      double   ret=calcPerfo(theDeltasClean,nbPixels);
         if(ret>0)
              return ret;
        ret=calcPerfo(theDeltasClean,nbPixels/2);  //tested with stamp "bonne vacances" side West
        if(ret>0)
            return ret*2;
        return 0;
}
QList<QPointF> class_perforation::getNbPtForEachPt(QList<QPointF> listStartPix,QImage fullStampRectified)
{
    int number=qMax(fullStampRectified.width(), fullStampRectified.height());
    QVector<int>nbPoint(number);   
    foreach (QPointF pt, listStartPix)
        nbPoint[static_cast<int>( pt.y())] += 1;
    //        '*********transfer to a list of points to keep the clue lost during the sort for debug display********
    QList<QPointF>listNbPoint ;
    for (int i  = 0 ; i<number;i++)
        listNbPoint.append(QPointF(i, nbPoint[i]));
    //        ************order descending on y**************
    std::sort(listNbPoint.begin(), listNbPoint.end(), classGeneriquesFonctions::pt2yLessPt1y); 
    return listNbPoint;
}
double class_perforation::calcPerfo(QVector<double> newListClean,double nPixels)
{
    double sumPt=0;
    for (int i = 0 ;i< newListClean.count();i++)
    {
      sumPt+=newListClean.at(i);
    }
    double average=sumPt/newListClean.count();
    if(average>0)
        return nPixels/average;
    return 0.0;


     //    double sumResult=0;
     //    int nb=0;
//0 if not enough point: stamp exampl.bmp

//      for (int i = 0 ;i< newListClean.count();i++)
//     {
//          int j =0;
//          for ( j = i ;j< newListClean.count() ;j++)
//          {
//              sumPt+=newListClean.at(j);
//              if(sumPt>nPixels)
//              {
//                 double delta=((nPixels-(sumPt-newListClean.at(j)))/(newListClean.at(j)));
//                 sumResult+= (j-i)+delta;
//                 nb+=1;
//                 sumPt=0;
//                 break;
//              }
//          }
//          if (j >=newListClean.count())
//              break;
//     }
//      if (nb>0)
//          return sumResult/nb;

//      return 0.0;
}
QList<QPointF> class_perforation::getBasePerforation(QList<QPointF> listStartSortNoDouble,double test)
{
    QList<QPointF> listBasePerforation;
    double memoX=0;
    for (int i = 1 ;i< listStartSortNoDouble.count() - 1;i++)
    {
        if (((listStartSortNoDouble.at(i + 1).y() - listStartSortNoDouble.at(i).y()) < 0) && (listStartSortNoDouble.at(i).x() - memoX > test))
        {
            listBasePerforation.append(QPointF(listStartSortNoDouble.at(i).x()+2, listStartSortNoDouble.at(i).y())); //+2 for debug window
            memoX=listStartSortNoDouble.at(i).x();
        }
    }
    return listBasePerforation;
}

