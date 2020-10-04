// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_sep_stamps_thread.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef MANAGETH_H
#define MANAGETH_H
#include "constantes.h"
#include <QObject>
#include <QThread>
#include <QMutex>
#include "common.h"

class MyThread : public QThread {
        Q_OBJECT
public slots:
    void receiveTerminate();
signals:
    void sendProgress(int value,int maximum);
    void sendFinished();
#ifdef DEBUGDISPLAYIMAGE
    void sendImageDebug(QImage fullStampRectified);
#endif
public:
    void setImage(QImage theImage);
    void setBorder(int border);
	void setThreshold(int threshold);
    void setBackColor(QColor backColor);
    void setAngles(QList<corners> theAngle);
    void setRatioPerforation(double ratioPerforation);
    QList<structFormStamp> getStamps();
private:
        void run() override;
        QImage image;
private:
        bool terminate=false;
        QList<structFormStamp> propertyListForm;
        QVector<structFormStamp> *allStamp;
        int border;
        double ratioPerforation;
        QColor backColor;
        QList<corners> theAngle;
		int threshold=THRESHOLD;
};

#endif // MANAGETH_H
