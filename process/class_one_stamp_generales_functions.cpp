// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_one_stamp_generales_functions.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include<QPainter>
#include "class_one_stamp_generales_functions.h"
#include "class_geometrie.h"
#include "class_perforation.h"
#include "constantes.h"
#include "common.h"
#include "class_generiques_fonctions.h"
#ifdef DEBUGDISPLAYIMAGE
    structFormStamp classOneStampGeneralesFunctions::processOneStamp(structFormStamp propertyListForm,corners theAngle,QList<QPointF> &listPtDebug,double ratioPerforation, int threshold)
#else
    structFormStamp classOneStampGeneralesFunctions::processOneStamp(structFormStamp propertyListForm,corners theAngle,double ratioPerforation,int threshold)
#endif
{
    structFormStamp f;
    f.index=propertyListForm.index;  //put to 0 if not display
    f.title  =propertyListForm.title;
    f.backColor=propertyListForm.backColor;
    f.border=propertyListForm.border;
    double angleRad = classGeometrie::getRotateAngleRad(theAngle);
    f.oneBmp  = classGeometrie::rotateBitmap(propertyListForm.oneBmp, angleRad, theAngle, propertyListForm.backColor);
    int nbLine=f.oneBmp.height();
    int nbColumn=f.oneBmp.width();
    struct oneMatrix theMatrix;
    theMatrix.pix=reinterpret_cast<bool**>(malloc(static_cast<unsigned long long>(nbColumn)*sizeof(theMatrix.pix)));
    for(int column=0;column<nbColumn;column++)
        theMatrix.pix[column]=reinterpret_cast<bool*>(malloc(static_cast<unsigned long long>(nbLine)*sizeof(theMatrix.pix)));
    classGeneriquesFonctions::bitMapToBinary(&theMatrix,f.oneBmp, threshold);
    //process teeth
#ifdef DEBUGDISPLAYIMAGE
    f.nbTeeth[static_cast<int>(sideStamp::NORTH)] = class_perforation::processPerforation(sideStamp::NORTH, &theMatrix, f.oneBmp,listPtDebug,propertyListForm.border, ratioPerforation);
    f.nbTeeth[static_cast<int>(sideStamp::EAST)] = class_perforation::processPerforation(sideStamp::EAST, &theMatrix, f.oneBmp,listPtDebug,propertyListForm.border, ratioPerforation);
    f.nbTeeth[static_cast<int>(sideStamp::SOUTH)] = class_perforation::processPerforation(sideStamp::SOUTH, &theMatrix, f.oneBmp,listPtDebug,propertyListForm.border, ratioPerforation);
    f.nbTeeth[static_cast<int>(sideStamp::WEST)] = class_perforation::processPerforation(sideStamp::WEST, &theMatrix, f.oneBmp,listPtDebug,propertyListForm.border, ratioPerforation);
#else
    f.nbTeeth[static_cast<int>(sideStamp::NORTH)] = class_perforation::processPerforation(sideStamp::NORTH, &theMatrix, f.oneBmp, ratioPerforation);
    f.nbTeeth[static_cast<int>(sideStamp::EAST)] = class_perforation::processPerforation(sideStamp::EAST, &theMatrix, f.oneBmp, ratioPerforation);
    f.nbTeeth[static_cast<int>(sideStamp::SOUTH)] = class_perforation::processPerforation(sideStamp::SOUTH, &theMatrix, f.oneBmp, ratioPerforation);
    f.nbTeeth[static_cast<int>(sideStamp::WEST)] = class_perforation::processPerforation(sideStamp::WEST, &theMatrix, f.oneBmp, ratioPerforation);

#endif
    //process border
    nbLine=f.oneBmp.height();
    nbColumn=f.oneBmp.width();
    QImage StampWithBorder(nbColumn+2*f.border,nbLine+2*f.border,QImage::Format_ARGB32);
    StampWithBorder.fill(propertyListForm.backColor);
    QPainter painter(&StampWithBorder);
    QRectF target(f.border, f.border,nbColumn,nbLine);
    QRectF source(0.0, 0.0, nbColumn-1, nbLine-1);
    painter.drawImage(target, f.oneBmp, source);
    f.oneBmp=StampWithBorder;
    return f;
}
