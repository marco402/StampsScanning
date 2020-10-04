// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_sep_stamps_thread.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QMutexLocker>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <QPainter>
#include "constantes.h"
#include "class_sep_stamps_thread.h"
#include "class_generiques_fonctions.h"
#include "class_one_stamp_generales_functions.h"
void MyThread::run()
{
        terminate=false;
        propertyListForm.clear();
         while(isRunning() && !terminate)
        {
        int cptForm=1;  //start to one, zero not display
        foreach( corners OneAngles, theAngle )
        {
            if(terminate==true) break;
            emit sendProgress(cptForm, theAngle.count());
            structFormStamp f;
            f.oneBmp=image;
            f.index=cptForm;  //put to 0 if not display
            f.title  = tr("stamp ") +QString::number(cptForm) + " ";
            f.backColor=backColor;
            f.border=border;
            QList <QPointF> listPtDebug;
#ifdef DEBUGDISPLAYIMAGE
            propertyListForm.append(classOneStampGeneralesFunctions::processOneStamp( f, OneAngles, listPtDebug, ratioPerforation, threshold));
            int nbLine=propertyListForm.last().oneBmp.height();
            int nbColumn=propertyListForm.last().oneBmp.width();
            QImage  newImage(nbColumn-1,nbLine-1,QImage::Format_ARGB32);
            QPainter painter(&newImage);
            QRectF target(0.0, 0.0,nbColumn-1,nbLine-1);
            painter.drawImage(target, propertyListForm.last().oneBmp, target);
            painter.setPen( (Qt::red));
            foreach(QPointF pt,listPtDebug)
                painter.drawPoint(pt);
            emit sendImageDebug(newImage);
#else
            propertyListForm.append(classOneStampGeneralesFunctions::processOneStamp( f, OneAngles, ratioPerforation, threshold));
#endif
            cptForm+=1;
        }
    terminate=true;
    sleep(1);
    }
    emit sendFinished(); 
}
void MyThread::receiveTerminate()
{
    terminate=true;
}
void MyThread::setImage(QImage theImage)
{
    image=theImage.copy();
}
void MyThread::setBorder(int border)
{
    this->border=border;
}
void MyThread::setRatioPerforation(double ratioPerforation)
{
    this->ratioPerforation= ratioPerforation;
}
void MyThread::setBackColor(QColor backColor)
{
    this->backColor=backColor;
}
void MyThread::setAngles(QList<corners> theAngle)
{
    this->theAngle=theAngle;
}
QList<structFormStamp> MyThread::getStamps(void)
{
    return propertyListForm;
}
void MyThread::setThreshold(int threshold)
{
    this->threshold= threshold;
}
