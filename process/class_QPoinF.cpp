// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_QPoinF.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "class_QPoinF.h"
#include <QList>
double myQPoinF::sommePtX(QList<QPointF> listPt)
{
	double somme=0.0;
	foreach(QPointF pt, listPt)
	{
		somme+=pt.x();
	}
	return somme;
}
double myQPoinF::sommePtY(QList<QPointF> listPt)
{
	double somme = 0.0;
	foreach(QPointF pt, listPt)
	{
		somme += pt.y();
	}
	return somme;
}
double myQPoinF::averagePtX(QList<QPointF> listPt)
{
	return sommePtX(listPt) / listPt.count();
}
double myQPoinF::averagePtY(QList<QPointF> listPt)
{
	return sommePtY(listPt) / listPt.count();
}
void  myQPoinF::dispayListPointF(QList <QPointF>listPt)
{
	foreach(QPointF pt, listPt)
	{
		qDebug("%f\t%f", pt.x(), pt.y());
	}
}