// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_generiques_fonctions.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "class_generiques_fonctions.h"
#include <QtMath>
#include <QPointF>
#include <QList>
#include "class_geometrie.h"
#include "constantes.h"
#include "class_QPoinF.h"
#include <QPainter>
#include "../presentation/form_stamp.h"
void classGeneriquesFonctions::bitMapToBinary(struct oneMatrix *theMatrix,QImage *image, int treshold,QImage *ptrDebugImage)
 {
    int nbLine=image->height();
    int nbColumn=image->width();
	for (int line=0;line<nbLine;line++)
    {
        for (int column=0;column<nbColumn;column++)
        {
            if (qMax(qMax(qRed(image->pixel(column,line)), qGreen(image->pixel(column,line))), qBlue(image->pixel(column,line))) > treshold)
                theMatrix->pix[column][line]= true;
			else
				theMatrix->pix[column][line] = false;
        }
     }
    if(ptrDebugImage)
        cleanMatrix(theMatrix,ptrDebugImage,true);
    else
        cleanMatrix(theMatrix,image,false);
}
void classGeneriquesFonctions::cleanMatrix(struct oneMatrix *theMatrix,QImage *image,bool flagDebug)
{
	const int NBPIX = 1;
	const int SEUILNBPIX = (NBPIX *8)-(NBPIX);
    int nbLine=image->height();
    int nbColumn=image->width();

#ifdef DEBUGCLEAN
    QPainter painter(image);
    if(flagDebug)
    {
    QRectF target(0.0, 0.0, nbColumn - 1, nbLine - 1);
    painter.fillRect(target, Qt::white);
    painter.setPen(Qt::red);
    }
#endif
    for (int line=0;line<nbLine;line++)
    {
        for (int column=0;column<nbColumn;column++)
        {
            int nbBlack=0;
            if (theMatrix->pix[column][line]==true)  //light point: verify if around is also light
            {
                 int debutX=column- NBPIX;
                 int debutY=line- NBPIX;
                 int finX=column+ NBPIX;
                 int finY=line+ NBPIX;
                 if (debutX<0) debutX=0;
                 if (debutY<0) debutY=0;
                 if (finX>nbColumn-1) finX=nbColumn-1;
                 if (finY>nbLine-1) finY=nbLine-1;
//test a square around spot

                 for (int C=debutX;C<finX;C++)
                 {
                    if (theMatrix->pix[C][debutY]==false)
                            nbBlack+=1;
                 }
                 for (int C=debutX;C<finX;C++)
                 {
                    if (theMatrix->pix[C][finY]==false)
                            nbBlack+=1;
                 }
                 for (int L=debutY;L<finY;L++)
                 {
                     if (theMatrix->pix[debutX][L]==false)
                             nbBlack+=1;
                 }
                 for (int L=debutY;L<finY;L++)
                 {
                     if (theMatrix->pix[finX][L]==false)
                             nbBlack+=1;
                 }
            }
            if (nbBlack> SEUILNBPIX)
            {
                theMatrix->pix[column][line]=false;
#ifdef DEBUGCLEAN
                if(flagDebug)
                {
                painter.drawPoint(column,line);
                }
#endif
            }
        }
     }
}

corners classGeneriquesFonctions::addFrame(corners fourCorner,int width)
{
	corners unAngleOut;
    double angleRad = classGeometrie::getRotateAngleRad(fourCorner);
    double tau= ((M_PI / 2) + static_cast<double>(angleRad));
    double gamma = (tau + M_PI / 4);
    double dx1 = (width * qSqrt(2) * qCos(gamma));
    double dy1 = (width * qSqrt(2) * qSin(gamma));
    QList<QPointF> l ;
    l.append(fourCorner.NORTH_EAST);
    l.append(fourCorner.NORTH_WEST);
    l.append(fourCorner.SOUTH_EAST);
    l.append(fourCorner.SOUTH_WEST);
    std::sort(l.begin(), l.end(), pt1yLessPt2y);
            unAngleOut.NORTH_EAST = {fourCorner.NORTH_EAST.x() + dy1, fourCorner.NORTH_EAST.y() + dx1};
            unAngleOut.SOUTH_EAST = {fourCorner.SOUTH_EAST.x() - dx1, fourCorner.SOUTH_EAST.y() + dy1};
            unAngleOut.NORTH_WEST = {fourCorner.NORTH_WEST.x() + dx1,fourCorner.NORTH_WEST.y()-dy1};
            unAngleOut.SOUTH_WEST = {fourCorner.SOUTH_WEST.x() - dy1, fourCorner.SOUTH_WEST.y() - dx1};
return unAngleOut;
}
bool classGeneriquesFonctions::pt1yLessPt2y(const QPointF &pt1, const QPointF &pt2)
{
    if(pt1.y() < pt2.y())
        return true;
    return false;
}
bool classGeneriquesFonctions::pt2yLessPt1y(const QPointF &pt1, const QPointF &pt2)
{
    if(pt1.y() > pt2.y())
        return true;
    return false;
}
bool classGeneriquesFonctions::pt1xLessPt2x(const QPointF &pt1, const QPointF &pt2)
{
    return pt1.x() < pt2.x();
}
bool classGeneriquesFonctions::pt1YComparePt2Y(const QPointF &pt1, const QPointF &pt2)
{
    if (qAbs(pt1.y() - pt2.y()) <= DBL_EPSILON)
        return true;
    return false;
}
bool classGeneriquesFonctions::floatCompare(double f1, double f2)
{
    if (qAbs(f1 - f2) <= DBL_EPSILON)
        return true;
    return false;
}
corners  classGeneriquesFonctions::removeFrame(corners fourCorner ,int width)
{
    corners unAngleOut;
    double dx1 = 0.0;
    double dy1  = 0.0;
    double angleRad  = classGeometrie::getRotateAngleRad(fourCorner);
    double tau  = ((M_PI / 2) + angleRad);
    double gamma  = (tau + (M_PI / 4));
    dx1 = (width * qSqrt(2) * qCos(gamma));
    dy1 = (width * qSqrt(2) * qSin(gamma));
    QList<QPointF> l;
    l.append(fourCorner.NORTH_EAST);
    l.append(fourCorner.NORTH_WEST);
    l.append(fourCorner.SOUTH_EAST);
    l.append(fourCorner.SOUTH_WEST);
    std::sort(l.begin(), l.end(), pt1yLessPt2y);
            unAngleOut.NORTH_EAST = {(fourCorner.NORTH_EAST.x() - dy1)<0.0?0.0:(fourCorner.NORTH_EAST.x() - dy1),(fourCorner.NORTH_EAST.y() - dx1)<0.0?0.0:(fourCorner.NORTH_EAST.y() - dx1)};
            unAngleOut.SOUTH_EAST = {(fourCorner.SOUTH_EAST.x() + dx1)<0.0?0.0:(fourCorner.SOUTH_EAST.x() + dx1),(fourCorner.SOUTH_EAST.y() - dy1)<0.0?0.0:(fourCorner.SOUTH_EAST.y() - dy1)};
            unAngleOut.NORTH_WEST = {(fourCorner.NORTH_WEST.x() - dx1)<0.0?0.0:(fourCorner.NORTH_WEST.x() - dx1),(fourCorner.NORTH_WEST.y() + dy1)<0.0?0.0:(fourCorner.NORTH_WEST.y() + dy1)};
            unAngleOut.SOUTH_WEST = {(fourCorner.SOUTH_WEST.x() + dy1)<0.0?0.0:(fourCorner.SOUTH_WEST.x() + dy1),(fourCorner.SOUTH_WEST.y() + dx1)<0.0?0.0:(fourCorner.SOUTH_WEST.y() + dx1)};
    return unAngleOut;
}
QList<QPointF>  classGeneriquesFonctions::rejectAberrantsPoints(xOrY param,QList<int> start)
{
    QList<QPointF> debutYTrie;
    if( start.count() == 0 ) return debutYTrie;

    double average = 0;
    double sum=0;
	
	for(int i=0;i<start.count();i++)
		sum+=start[i];
	average=sum/start.count();

    for(int i=0;i<start.count();i++)
    {
        if (qAbs(start[i] - average) < REJECT_OUTLIERS && i > 0 && start[i] > 0)
            {
            if (param== xOrY::X)
                debutYTrie.append(QPointF(i , start[i])); 
            else
                debutYTrie.append(QPointF(start[i], i ));
            }
    }
    return debutYTrie;
}
QVector<double> classGeneriquesFonctions::rejectAberrantsPoints(QVector<double> thePts , int delta )
{
    if (thePts.count() == 0) return thePts;
    QVector<double>  result;
    double sum = 0.0;
        foreach( double pt, thePts )
            sum += pt;
         double average = sum / thePts.count();
        sum = 0;
        foreach( double pt, thePts )
            sum += qAbs(pt - average);
        double averageDelta = sum / thePts.count()  ; 
        foreach( double pt, thePts ) {
            if ((qAbs(pt - average)) <= (averageDelta + delta))
                 result.append(pt);
         }
    return result;
}
QList<QPointF> classGeneriquesFonctions::rejectAberrantsPoints(QList<QPointF> thePts , oppositeSide sideNorthOrSouth , int delta )
{
    if (thePts.count() == 0) return thePts;
    QList<QPointF>  result;
    double sum = 0.0;
    if (sideNorthOrSouth==oppositeSide::NORTHSOUTH) {
        foreach( QPointF pt, thePts )
            sum += pt.y();
         double average = sum / thePts.count();
         sum = 0;
        foreach( QPointF pt, thePts )
            sum += qAbs(pt.y() - average);
         double averageDelta = sum / thePts.count() * 2 ; 
         foreach( QPointF pt, thePts ) {
            if ((qAbs(pt.y()) - average) <= (averageDelta + delta))
                result.append(QPointF(pt.x(), pt.y()));
        }
    }
    else 
   {
        foreach( QPointF pt, thePts )
            sum += pt.x();
        double average  = sum / thePts.count();
        sum = 0;
        foreach( QPointF pt, thePts )
            sum += qAbs(pt.x() - average);
        double averageDelta= sum / thePts.count() * 2;
        foreach( QPointF pt, thePts ){
            if (qAbs(pt.x() - average) <= averageDelta + delta)
                result.append(QPointF(pt.x(), pt.y()));
        }
   }
    return result;
}
    QList<QPointF> classGeneriquesFonctions::averageEqualY(QList<QPointF> startSorted)
    {
        QList<QPointF> StartSortNoDouble;
        int cpt1  = 0;
         for (int i  = 0 ;i< startSorted.count() - 1;i++)
        {
            if (startSorted.at(i).y() - startSorted.at(i + 1).y() < DBL_EPSILON)
                cpt1 += 1;
            else
            {
                StartSortNoDouble.append(QPointF((startSorted.at(i).x() - (cpt1 / 2)), startSorted.at(i).y()));
                cpt1 = 0;
            }
        }
        return StartSortNoDouble;
    }
    QColor classGeneriquesFonctions::getBackColor(QImage startBitmap)
    {
        int x  = 0;
        int y = 0;
        int a = 0 ;
        int r = 0;
        int g = 0;
        int b = 0;
        for (x = 0;x< startBitmap.width() ;x++)
            processColor(startBitmap,a,r,g,b,x, y);
        y = startBitmap.height() - 1;
        for (x = 0;x< startBitmap.width() ;x++)
            processColor(startBitmap,a,r,g,b,x, y);
        x = 0;
        for (y = 0;y< startBitmap.height() ;y++)
            processColor(startBitmap,a,r,g,b,x, y);
        x = startBitmap.width() - 1;
        for (y = 0;y< startBitmap.height() ;y++)
            processColor(startBitmap,a,r,g,b,x, y);
        int nb  = (startBitmap.width() + startBitmap.height()) * 2;
        a /= nb;
        r /= nb;
        g /= nb;
        b /= nb;
        return QColor(r,g,b,a);
    }
    void classGeneriquesFonctions::processColor(QImage startBitmap,int &a,int &r,int &g,int &b,int x,int y)
    {
        a += qAlpha(startBitmap.pixel(x, y));
        r += qRed(startBitmap.pixel(x, y));
        g += qGreen(startBitmap.pixel(x, y));
        b += qBlue(startBitmap.pixel(x, y));
    }
