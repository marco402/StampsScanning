// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_one_stamp_generales_functions.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef CLASS_ONE_STAMP_GENERALES_FUNCTIONS_H
#define CLASS_ONE_STAMP_GENERALES_FUNCTIONS_H
#include<QList>
#include "common.h"
#include "constantes.h"
class classOneStampGeneralesFunctions
{
public:
#ifdef DEBUGDISPLAYIMAGE
    static structFormStamp processOneStamp(structFormStamp propertyListForm,corners theAngle,QList<QPointF> &listPtDebug,double ratioPerforation, int threshold);
#else
    static structFormStamp processOneStamp(structFormStamp propertyListForm,corners theAngle,double ratioPerforation, int threshold);
#endif
};
#endif // CLASS_ONE_STAMP_GENERALES_FUNCTIONS_H
