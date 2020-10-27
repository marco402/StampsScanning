// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_geometrie.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "class_geometrie.h"
#include "class_generiques_fonctions.h"
#include "qglobal.h"
#include <QDebug>
#include <QtMath>
#include <QPointF>
#include <QList>
#include "class_QPoinF.h"
//rotate n points in polygon with delta.
QPolygonF classGeometrie::rotatePoint(QPolygonF original,QPointF center,double angleDeg , double deltaX , double deltaY)
{
    QTransform transform;
    transform.translate(center.x()- deltaX, center.y()- deltaY);
    transform.rotate(angleDeg);
    transform.translate(-center.x() ,- center.y() );
    QPolygonF rotated = transform.map(original);
    return rotated;
}
//rotate 1 point in polygon with delta.
QPointF classGeometrie::rotatePoint(QPointF lePoint,QPointF center,double angleDeg, double deltaX , double deltaY )
{
    QPolygonF newPol=QPolygonF() << lePoint;
    newPol = rotatePoint(newPol, center, angleDeg, deltaX, deltaY);
    return newPol[0];
}
//rotate image with delta and back color
QImage classGeometrie::rotateImage(QImage bitmapIn,double angleDeg,QPointF &deltaBound,QColor backColor)
{
    QPolygonF rotationPoints=QPolygonF() << QPointF(0, 0) << QPointF(bitmapIn.width(), 0) <<
                                            QPointF(0, bitmapIn.height())<<QPointF(bitmapIn.width(), bitmapIn.height());
    QPointF center =QPointF(bitmapIn.width()/2.0,bitmapIn.height()/2.0);
    QPolygonF newRotationPoints = rotatePoint(rotationPoints,center, angleDeg);
    QRectF bounds =newRotationPoints.boundingRect();
    QImage leBitmapOut = QImage(  static_cast<int>(bounds.width()), static_cast<int>(bounds.height()),bitmapIn.format());
    deltaBound=QPointF(bounds.left(),bounds.top());
    leBitmapOut.fill(backColor);
    leBitmapOut = leBitmapOut.transformed(QTransform().translate(center.x(),center.y()),Qt::SmoothTransformation);
    leBitmapOut = bitmapIn.transformed(QTransform().rotate(angleDeg),Qt::SmoothTransformation);
    leBitmapOut = leBitmapOut.transformed(QTransform().translate(-deltaBound.x(),- deltaBound.y()),Qt::SmoothTransformation);
    return leBitmapOut;
}
//average of angles for rotate
double classGeometrie::getRotateAngleRad(corners listeSideStampAtAxesLevel)
{
    double a[]={
    (qAtan2(qAbs(listeSideStampAtAxesLevel.NORTH_WEST.y() - listeSideStampAtAxesLevel.NORTH_EAST.y()),
                   qAbs(listeSideStampAtAxesLevel.NORTH_EAST.x() - listeSideStampAtAxesLevel.NORTH_WEST.x()))),
    (qAtan2(qAbs(listeSideStampAtAxesLevel.NORTH_WEST.x() - listeSideStampAtAxesLevel.SOUTH_WEST.x()),
                   qAbs(listeSideStampAtAxesLevel.NORTH_WEST.y() - listeSideStampAtAxesLevel.SOUTH_WEST.y()))),
    (qAtan2(qAbs(listeSideStampAtAxesLevel.SOUTH_WEST.y() - listeSideStampAtAxesLevel.SOUTH_EAST.y()),
                   qAbs(listeSideStampAtAxesLevel.SOUTH_EAST.x() - listeSideStampAtAxesLevel.SOUTH_WEST.x()))),
    (qAtan2(qAbs(listeSideStampAtAxesLevel.NORTH_EAST.x() - listeSideStampAtAxesLevel.SOUTH_EAST.x()),
                   qAbs(listeSideStampAtAxesLevel.NORTH_EAST.y() - listeSideStampAtAxesLevel.SOUTH_EAST.y()))) };
    if( listeSideStampAtAxesLevel.NORTH_WEST.y() > listeSideStampAtAxesLevel.NORTH_EAST.y() )
        return (a[0] + a[1] + a[2] + a[3]) / 4;
    else
        return -(a[0] + a[1] + a[2] + a[3]) / 4;
}
//calculation of the equation of the line 
bool classGeometrie::getLineAveragePoints(QList<QPointF> data , double &Ai, double &Bi)
{
    double averageDebut_X = 0;
    double averageDebut_Y = 0;
    double averageFin_X = 0;
    double averageFin_Y = 0;
    int nbd = 0;
    int nbf = 0;
    foreach( QPointF Data, data ) {
        if (data.indexOf(Data) < (data.count() / 2))
        {
            averageDebut_X += Data.x();
            averageDebut_Y += Data.y();
            nbd += 1;
        }
        else
        {
            averageFin_X += Data.x();
            averageFin_Y += Data.y();
            nbf += 1;
        }
    }
    averageDebut_X /= nbd;
    averageDebut_Y /= nbd;
    averageFin_X /= nbf;
    averageFin_Y /= nbf;

    Ai = (averageFin_Y - averageDebut_Y) / (averageFin_X - averageDebut_X);

    if (std::isinf(Ai))
        Bi = averageFin_X;
    else
        Bi = averageDebut_Y - (Ai * averageDebut_X);
    return true;
}
corners classGeometrie::getCrossLines(double tabAi[],double tabBi[], bool &indicOK)
{
    corners theAngles;
    theAngles.NORTH_EAST = getCross2Lines(tabAi[static_cast<int>(sideStamp::NORTH)], tabBi[static_cast<int>(sideStamp::NORTH)],
		tabAi[static_cast<int>(sideStamp::EAST)], tabBi[static_cast<int>(sideStamp::EAST)], indicOK);
    theAngles.NORTH_WEST = getCross2Lines(tabAi[static_cast<int>(sideStamp::NORTH)], tabBi[static_cast<int>(sideStamp::NORTH)],
		tabAi[static_cast<int>(sideStamp::WEST)], tabBi[static_cast<int>(sideStamp::WEST)], indicOK);
    theAngles.SOUTH_EAST = getCross2Lines(tabAi[static_cast<int>(sideStamp::SOUTH)], tabBi[static_cast<int>(sideStamp::SOUTH)],
		tabAi[static_cast<int>(sideStamp::EAST)], tabBi[static_cast<int>(sideStamp::EAST)], indicOK);
    theAngles.SOUTH_WEST = getCross2Lines(tabAi[static_cast<int>(sideStamp::SOUTH)], tabBi[static_cast<int>(sideStamp::SOUTH)],
		tabAi[static_cast<int>(sideStamp::WEST)], tabBi[static_cast<int>(sideStamp::WEST)], indicOK);
    return theAngles;
}
QPointF classGeometrie::getCross2Lines(double Ai1,double Bi1,double Ai2,double Bi2, bool &indicOK)
{
    QPointF thePt;
	if (Ai1 == Ai2)
	{
		indicOK = false;
        //qDebug("Parallel lines");
    }
    else if (std::isinf((Ai1)))
	{
        thePt = QPointF(Bi1, (Ai2 * Bi1) + Bi2);
		//qDebug("1 parallel to axis y");
    }
    else if (std::isinf((Ai2)))
	{
        thePt =QPointF (Bi2,Ai1 * Bi2 + Bi1);
		//qDebug("2 parallel to axis y");
	}
    else
    {
        double x=qMax(0.0, (Bi2 - Bi1) / (Ai1 - Ai2));
        thePt =QPointF (x,(qMax(0.0, (Ai1 * x) + Bi1)));
		if (thePt.x()==0.0)
		{
			//qDebug("thePt.x==0.0");
			//qDebug("x=%f", (Bi2 - Bi1) / (Ai1 - Ai2));
			//qDebug("y=%f", (Ai1 * x) + Bi1);
			indicOK = false;
        }
    }
    return thePt;
}
QImage classGeometrie::rotateBitmap(QImage &bm_in,double angleRad,corners stampCorners,QColor backColor)
{
    double angleDeg= (angleRad / M_PI * 180);
    QPointF deltaBound;
    QImage fullStampRectified  = rotateImage(bm_in, angleDeg,deltaBound , backColor);
    QPointF centerRot =  QPointF((bm_in.width() / 2.0), (bm_in.height() / 2.0));
    corners newStampCorners;
    newStampCorners.NORTH_EAST = rotatePoint(  stampCorners.NORTH_EAST, centerRot, angleDeg, deltaBound.x(), deltaBound.y());
    newStampCorners.NORTH_WEST = rotatePoint(stampCorners.NORTH_WEST, centerRot, angleDeg, deltaBound.x(), deltaBound.y());
    newStampCorners.SOUTH_EAST = rotatePoint(stampCorners.SOUTH_EAST, centerRot, angleDeg, deltaBound.x(), deltaBound.y());
    newStampCorners.SOUTH_WEST = rotatePoint(stampCorners.SOUTH_WEST, centerRot, angleDeg, deltaBound.x(), deltaBound.y());
    double  dx = (qMin(newStampCorners.NORTH_WEST.x(), newStampCorners.SOUTH_WEST.x()));
    double  dy = (qMin(newStampCorners.NORTH_WEST.y(), newStampCorners.NORTH_EAST.y()));
    int width=static_cast<int>(round(qMax(newStampCorners.NORTH_EAST.x(), newStampCorners.SOUTH_EAST.x()) 
		- qMin(newStampCorners.NORTH_WEST.x(), newStampCorners.SOUTH_WEST.x()) + 1));
    int height=static_cast<int>(round(qMax(newStampCorners.SOUTH_WEST.y(), newStampCorners.SOUTH_EAST.y()) 
		- qMin(newStampCorners.NORTH_WEST.y(), newStampCorners.NORTH_EAST.y()) + 1));
    if (((width > 0) && (height > 0)))
        return fullStampRectified.copy(static_cast<int>(dx), static_cast<int>(dy), width, height);
    else
        return fullStampRectified;
}
corners classGeometrie::processAngles( QList<QList<QPointF>> theData, bool &indicOK ,double aiDebug[] ,double biDebug[])
{
	QList<QPointF> listCleanN = classGeneriquesFonctions::rejectAberrantsPoints(theData[static_cast<int>(sideStamp::NORTH)], oppositeSide::NORTHSOUTH);
    getLineAveragePoints( listCleanN, aiDebug[static_cast<int>(sideStamp::NORTH)], biDebug[static_cast<int>(sideStamp::NORTH)]);
    QList<QPointF> listCleanS  = classGeneriquesFonctions::rejectAberrantsPoints(theData[static_cast<int>(sideStamp::SOUTH)], oppositeSide::NORTHSOUTH);
    getLineAveragePoints( listCleanS, aiDebug[static_cast<int>(sideStamp::SOUTH)], biDebug[static_cast<int>(sideStamp::SOUTH)]);
    QList<QPointF> listCleanE  = classGeneriquesFonctions::rejectAberrantsPoints(theData[static_cast<int>(sideStamp::EAST)], oppositeSide::EASTWEST);
    getLineAveragePoints( listCleanE, aiDebug[static_cast<int>(sideStamp::EAST)], biDebug[static_cast<int>(sideStamp::EAST)]);
    QList<QPointF> listCleanO  = classGeneriquesFonctions::rejectAberrantsPoints(theData[static_cast<int>(sideStamp::WEST)], oppositeSide::EASTWEST);
    getLineAveragePoints( listCleanO, aiDebug[static_cast<int>(sideStamp::WEST)], biDebug[static_cast<int>(sideStamp::WEST)]);
    for (int i=0;i<4;i++){
        if (!std::isinf(aiDebug[i]) || !std::isnan(aiDebug[i]))
            indicOK += 1;
    }
    return getCrossLines(aiDebug, biDebug, indicOK);
}
bool classGeometrie::isInside(QPointF pt[],QPointF ref)
{
    bool a  = ((pt[1].y() - pt[0].y()) * ref.x() - (pt[1].x() - pt[0].x()) *
		ref.y() - pt[0].x() * pt[1].y() + pt[1].x() * pt[0].y()) > 0;
    bool  b  = ((pt[1].y() - pt[0].y()) * pt[2].x() - (pt[1].x() - pt[0].x()) *
		pt[2].y() - pt[0].x() * pt[1].y() + pt[1].x() * pt[0].y()) > 0;
    if (a != b) return false;
    a  = ((pt[2].y() - pt[1].y()) * ref.x() - (pt[2].x() - pt[1].x()) *
		ref.y() - pt[1].x() * pt[2].y() + pt[2].x() * pt[1].y()) > 0;
    b  = ((pt[2].y() - pt[1].y()) * pt[3].x() - (pt[2].x() - pt[1].x()) *
		pt[3].y() - pt[1].x() * pt[2].y() + pt[2].x() * pt[1].y()) > 0;
    if( a != b) return false;
    a  = ((pt[3].y() - pt[2].y()) * ref.x() - (pt[3].x() - pt[2].x()) *
		ref.y() - pt[2].x() * pt[3].y() + pt[3].x() * pt[2].y()) > 0;
    b  = ((pt[3].y() - pt[2].y()) * pt[0].x() - (pt[3].x() - pt[2].x()) *
		pt[0].y() - pt[2].x() * pt[3].y() + pt[3].x() * pt[2].y()) > 0;
    if (a != b) return false;
    a = ((pt[0].y() - pt[3].y()) * ref.x() - (pt[0].x() - pt[3].x()) *
		ref.y() - pt[3].x() * pt[0].y() + pt[0].x() * pt[3].y()) > 0;
    b  = ((pt[0].y() - pt[3].y()) * pt[1].x() - (pt[0].x() - pt[3].x()) *
		pt[1].y() - pt[3].x() * pt[0].y() + pt[0].x() * pt[3].y()) > 0;
    if (a != b) return false;
    return true;
}
