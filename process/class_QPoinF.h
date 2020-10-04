// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_QPointF.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#pragma once
#include <qpoint.h>
class myQPoinF
{
public:
	myQPoinF();
	~myQPoinF();
	static double sommePtX(QList<QPointF>listPt);
	static double sommePtY(QList <QPointF>listPt);
	static double averagePtX(QList<QPointF>listPt);
	static double averagePtY(QList <QPointF>listPt);
	static void dispayListPointF(QList <QPointF>listPt);
};

