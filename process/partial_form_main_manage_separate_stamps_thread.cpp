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
#include <QTimer>
#include <QRect>
#include <QApplication>
#include <QStatusBar>
#include <QImage>
#include <QColor>
#include <QList>
#include <QDesktopWidget>
#include <QPainter>
#include <iostream>
#include <QFileDialog>
#include "presentation\form_main.h"
#include "class_sep_stamps_generales_functions.h"
#include "class_sep_stamps_thread.h"
#include "constantes.h"
#include "class_one_stamp_generales_functions.h"
#include "class_generiques_fonctions.h"
#include "class_geometrie.h"

#ifdef DEBUGDISPLAYIMAGE
void formMain::receiveImageDebug(QImage imageDebug)
{
    structFormStamp frm;
    frm.title=QString("imageDebug ");
    frm.oneBmp=imageDebug;
    frm.index=9999;
    frm.top=100;
    frm.left=100;
    formStamp *w = new formStamp(frm,&currentPathSave,&ratioPerforation);
    w->retranslateUi();
    w->show();
}
#endif
void formMain::receiveProgress(int value,int maximum)
{
    progressBarProcess->setMaximum(maximum);
    progressBarProcess->setValue(value);
}
void formMain::receiveFinished()
{
	QList<structFormStamp> propertyListForm=threadProcess->getStamps();
	displayStamp(propertyListForm);
#ifdef CALIBRATIONTHRESHOLD
	if (calibrationThreshold)
		sliderCalibration->setEnabled(true);
#endif
}
void formMain::run()
{
    closeAll();
    listFormStamp.clear();
    allStamp.clear();
    backColor = classGeneriquesFonctions::getBackColor(*image);
    int nbLine=image->height();
    int nbColumn=image->width();
    struct oneMatrix theMatrix;
    theMatrix.pix=reinterpret_cast<bool**>(malloc(static_cast<unsigned long long>(nbColumn)*sizeof(theMatrix.pix)));
    for(int column=0;column<nbColumn;column++)
        theMatrix.pix[column]=reinterpret_cast<bool*>(malloc(static_cast<unsigned long long>(nbLine)*sizeof(theMatrix.pix)));
#ifdef DEBUGCLEAN
    QImage  debugImage = image->copy();
    QImage *ptrDebugImage=&debugImage;
    debugImage=image->copy();
    classGeneriquesFonctions::bitMapToBinary(&theMatrix,image, threshold,ptrDebugImage);
#else
    classGeneriquesFonctions::bitMapToBinary(&theMatrix,image, threshold);
#endif

#ifdef DEBUGCLEAN
    structFormStamp f;
    f.left = 200;
    f.top = 100;
    f.oneBmp = *ptrDebugImage;
    f.title = ("clean ");
    f.backColor = Qt::black;
    f.border = 0;
    formStamp *w = new formStamp(f);
    w->retranslateUi();
    w->show();
#endif
    QList<float> angleRad;
    QList<corners> theAngle;
#ifdef CALIBRATIONTHRESHOLD
	if(calibrationThreshold)
		sliderCalibration->setEnabled(false);
#endif  
    progressBarProcess->setFormat("%p%" + tr("scan"));
    theAngle = getListStampWithDetection(&theMatrix, *image);
    if (theAngle.count()==0) return;
	if (displayDebugContour)
	{
		QImage  newImage(nbColumn - 1, nbLine - 1, QImage::Format_ARGB32);
		QPainter painter(&newImage);
		QRectF target(0.0, 0.0, nbColumn - 1, nbLine - 1);
		painter.drawImage(target, *image, target);
		QPen pen;
		pen.setColor(Qt::red);
		pen.setWidth(2);
		painter.setPen(pen);
		foreach(corners pt, theAngle)
		{
			painter.drawLine(pt.NORTH_WEST, pt.NORTH_EAST);
			painter.drawLine(pt.NORTH_EAST, pt.SOUTH_EAST);
			painter.drawLine(pt.SOUTH_EAST, pt.SOUTH_WEST);
			painter.drawLine(pt.SOUTH_WEST, pt.NORTH_WEST);
			painter.drawLine(pt.NORTH_WEST, pt.NORTH_EAST);
			painter.drawLine(pt.NORTH_EAST, pt.SOUTH_EAST);
			painter.drawLine(pt.SOUTH_EAST, pt.SOUTH_WEST);
			painter.drawLine(pt.SOUTH_WEST, pt.NORTH_WEST);
		}
		structFormStamp frm;
		frm.title = QString("imageDebugContour4Lines ");
		frm.oneBmp = newImage;
		frm.index = 9999;
		frm.top = 100;
		frm.left = 100;
		formStamp *w = new formStamp(frm, &currentPathSave, &ratioPerforation);
		w->retranslateUi();
		w->show();
	}
    progressBarProcess->setFormat("%v/%m" + tr("stamps"));
    progressBarProcess->setMaximum(theAngle.count());
    progressBarProcess->setValue(0);
    threadProcess->setAngles(theAngle);
    threadProcess->setImage(*image);
    threadProcess->setBackColor(backColor);
    threadProcess->setBorder(cbBorderSize->itemText(cbBorderSize->currentIndex()).toInt());
	threadProcess->setThreshold(threshold);
    threadProcess->setRatioPerforation(ratioPerforation);
    threadProcess->start(QThread::LowPriority);//HighPriority
}
void formMain::displayStamp(QList<structFormStamp> propertyListForm)
{
    progressBarProcess->setFormat("%v/%m" + tr("stamps ok"));
    progressBarProcess->setMaximum(propertyListForm.count());
    int widthScreen = (QApplication::desktop()->width());
    int heighScreen = (QApplication::desktop()->height());
    int left=x()+width();
    int top=0;
    int cpt=1;
    if(currentPathSave.isEmpty())
        currentPathSave = QFileDialog::getExistingDirectory(this, tr("Select a directory for save your stamps"),currentPathLoad);
    foreach(  structFormStamp frm, propertyListForm )
    {
        if (frm.index>0)
        {
            progressBarProcess->setValue(cpt);
            frm.left=left;
            frm.top=top;
            frm.currentPathSave=currentPathSave;
			frm.yearStamp = cbYear->itemText(cbYear->currentIndex());
            formStamp *w = new formStamp(frm,&currentPathSave,&ratioPerforation);  //
            listFormStamp.append(w);
            w->retranslateUi();
            w->show();

            left+=20;
            if ((left+20)>widthScreen)
            {
                left=x()+width();
                top+=20;
            }
            if (top>heighScreen)
            {
                left=x()+width();
                top=0;
            }
            cpt+=1;
        }
    }
}
QList<corners> formMain::getListStampWithDetection(struct oneMatrix *theMatrix,QImage image)
{
    int nbLine=image.height();
    int nbColumn=image.width();
    int   NbPixForSweep= static_cast<int> (image.physicalDpiX() / INCH * (sweepStamp_mm/10));
    progressBarProcess->show();
    progressBarProcess->setMaximum(nbLine);
    progressBarProcess->setValue(0);
    QList<QList<QPointF>> sidesPoints;
    QList<corners> theAngles;
    for (int y= NbPixForSweep;y< nbLine;y+= NbPixForSweep)
    {
        progressBarProcess->setValue(y);
        int testx=-1;
        for (int x=0;x< nbColumn-1;x++)
        {
            if (theMatrix->pix[x][y] ) //it's a stamp
            {
                bool itsAStamp=true;
                while (true)
                {
                    int finX=qMin(x + 5, nbColumn);
                    for (int i=x;i<finX;i++)
                    {
                        if (!theMatrix->pix[x][y] )
                        {
                            x = i;
                            itsAStamp=false;
                        }
                    }
                    if(!itsAStamp)break;   //out while()
                    QPointF memoX;

                    bool notInside=true;
                    while (true)
                    {
                        QPointF memoXH;
                        QPointF memoXT;
                        int cpt  = 0;
                        //****is the stamp already in the list?****
                        foreach( corners ang, theAngles ) {
                            QPointF   thePts[] = { QPointF(ang.NORTH_EAST.x(), ang.NORTH_EAST.y()),  QPointF(ang.SOUTH_EAST.x(), ang.SOUTH_EAST.y()),  QPointF(ang.SOUTH_WEST.x(), ang.SOUTH_WEST.y()),  QPointF(ang.NORTH_WEST.x(), ang.NORTH_WEST.y())};
                            if (classGeometrie::isInside(thePts, QPointF(x, y)))
                            {
                                //look for the output x
                                QPointF ptCurrent=  QPointF(x, y);

                                QList<QPointF>::iterator i;
                                for (i = sidesPoints[cpt].begin(); i != sidesPoints[cpt].end(); ++i)
                                    if(*i==ptCurrent)
                                    {
                                        memoX = *i;
                                        break;
                                    }
                                if( memoX.x() == 0.0)
                                    memoX=QPointF(x + 1,y);
                                notInside=false;
                            }
                            cpt += 1;
                        }
                        if (!notInside)break;
                        //*****************************************
#ifdef __DEBUG__
						if (theAngles.count() == 35)  //debug
							cpt = cpt;					  //debug
						qDebug("%d=", theAngles.count());
#endif
                        QList<QList<QPointF>> tempClockwise;
                        QList<QList<QPointF>> tempTrigo;
                        tempClockwise = sepStampFunctions::processAroundAndCornersStampClockwise(theMatrix,  QPointF(x, y), memoXH,image);
#ifdef DEBUGDISPLAYCONTOURIMAGE
                        int nbLine=image.height();
                        int nbColumn=image.width();
                        QImage  newImage(nbColumn-1,nbLine-1,QImage::Format_ARGB32);
                        QPainter painter(&newImage);
                        QRectF target(0.0, 0.0,nbColumn-1,nbLine-1);
                        painter.drawImage(target, image, target);
						QPen pen;
						pen.setColor(Qt::red);
						pen.setWidth(2);
						painter.setPen(pen);
                        foreach(QList<QPointF> list,tempClockwise)
                            foreach(QPointF pt,list)
                                 painter.drawPoint(pt);
                        structFormStamp frm;
                        frm.title=QString("imageDebugContourClockwise ");
                        frm.oneBmp=newImage;
                        frm.index= theAngles.count();
                        frm.top=100;
                        frm.left=100;
                        formStamp *w = new formStamp(frm,&currentPathSave,&ratioPerforation);
                        w->retranslateUi();
                        w->show();

#endif
                        bool IndicClockwiseOK  = false;
                        if (tempClockwise.count() > 0)
                            IndicClockwiseOK = tempClockwise[0].count() > NBPOINTMINIXX && tempClockwise[1].count() > NBPOINTMINIXX && tempClockwise[2].count() > NBPOINTMINIXX && tempClockwise[3].count() > NBPOINTMINIXX;
                        tempTrigo = sepStampFunctions::processAroundAndCornersStampTrigo(theMatrix,  QPointF(x, y), memoXT,image);
#ifdef DEBUGDISPLAYCONTOURIMAGE
                        QImage  newImageT(nbColumn-1,nbLine-1,QImage::Format_ARGB32);
                        QPainter painterT(&newImageT);
                        QRectF targetT(0.0, 0.0,nbColumn-1,nbLine-1);
                        painterT.drawImage(targetT, image, targetT);
                        painterT.setPen(pen);
                        foreach(QList<QPointF> list,tempTrigo)
                            foreach(QPointF pt,list)
                                 painterT.drawPoint(pt);


                        frm.title=QString("imageDebugContourTrigo");
                        frm.oneBmp=newImageT;
                        frm.index= theAngles.count();
                        frm.top=100;
                        frm.left=100;
                        formStamp *w1 = new formStamp(frm,&currentPathSave,&ratioPerforation);
                        w1->retranslateUi();
                        w1->show();
#endif
                        bool IndicTrigoOK  = false;
                        if (tempTrigo.count() > 0)
                            IndicTrigoOK = tempTrigo[0].count() > NBPOINTMINIXX && tempTrigo[1].count() > NBPOINTMINIXX && tempTrigo[2].count() > NBPOINTMINIXX && tempTrigo[3].count() > NBPOINTMINIXX;
                        double aiClockwise[4] ;
                        double biClockwise[4];
        //                int indicAiOKClockwise = 0;
                        corners cornerClockwise;
                        if (IndicClockwiseOK)
                            cornerClockwise = classGeometrie::processAngles(tempClockwise, IndicClockwiseOK, aiClockwise, biClockwise);
                        double aiTrigo[4] ;
                        double biTrigo[4];
        //                int indicAiOKHTrigo  = 0;
                        corners cornerTrigo ;
                        if (IndicTrigoOK)
                            cornerTrigo = classGeometrie::processAngles(tempTrigo, IndicTrigoOK, aiTrigo, biTrigo);
                        if (!IndicClockwiseOK && !IndicTrigoOK)
                        {
                            memoX=QPointF(x+1,y) ;
                            break;
                        }
                        else if (!IndicTrigoOK)
                            theAngles= sepStampFunctions::processClockwiseOrTrigo(cornerClockwise, theAngles, sidesPoints, memoX, tempClockwise,memoXH );
                        else if (!IndicClockwiseOK)
                            theAngles= sepStampFunctions::processClockwiseOrTrigo(cornerTrigo, theAngles, sidesPoints, memoX, tempTrigo,memoXT);
                        else
                        {
                            if (qAbs(aiClockwise[0] - aiTrigo[0]) < qAbs(aiClockwise[0] - aiTrigo[1]))
                            {
                                if (qAbs(aiClockwise[0] - aiClockwise[2]) < qAbs(aiTrigo[0] - aiTrigo[2]))
                                    theAngles= sepStampFunctions::processClockwiseOrTrigo(cornerClockwise, theAngles, sidesPoints, memoX, tempClockwise, memoXH );
                                else
                                    theAngles= sepStampFunctions::processClockwiseOrTrigo(cornerTrigo, theAngles, sidesPoints, memoX, tempTrigo,memoXT);
                            }
                            else
                            {
                                if (qAbs(aiClockwise[0] - aiClockwise[2]) < qAbs(aiTrigo[1] - aiTrigo[3]))
                                    theAngles= sepStampFunctions::processClockwiseOrTrigo(cornerClockwise, theAngles, sidesPoints, memoX, tempClockwise, memoXH );
                                else
                                    theAngles= sepStampFunctions::processClockwiseOrTrigo(cornerTrigo, theAngles, sidesPoints, memoX, tempTrigo,memoXT);
                            }
                        }
                        break;
                    }   //while (notInside)
                    x = static_cast<int>(  memoX.x());

                    break;
                }  //while (itsAStamp)
            }    //it's a stamp
            if(x<=testx)
                x=testx+1;     //abnormal case due to obliteration(35timbres.jpg with THRESHOLD  = 130)
            testx=x;
            if(x>=nbColumn)
                break;  //exit for
        }    // for x
    }     //for y
    QList<corners> listCorner;
    foreach( corners angl, theAngles )
        listCorner.append(classGeneriquesFonctions::removeFrame(angl, DXY_BORDER / 2));
    return listCorner;
}
void formMain::stop()
{
	emit sendTerminate();
}
