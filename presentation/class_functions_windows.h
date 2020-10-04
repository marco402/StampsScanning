// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_functions_windows.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef FUNCTIONSWINDOWS_H
#define FUNCTIONSWINDOWS_H

#include <QApplication>
#include <QLabel>
class functionsWindows
{
public:
    static void calcNewSizeIfImageTooBig(int *newWidthPicture,    int  *newHeightPicture,int cor, int widthWindowMin, int heightWindowMin);
    static void calcNewSizeIfWindowTooBig(int widthWindow,int heightWindow,int cor,QImage *image,int *newWidthWindow,int  *newHeightWindow, int widthWindowMin, int heightWindowMin);
    static void rotate(int angle,int cor,QImage *image,QPixmap *myPixmap,QLabel  *labelPicture,int *newWidthPicture,    int  *newHeightPicture,int *newWidthWindow,    int  *newHeightWindow, int widthWindowMin, int heightWindowMin);
private:
};

#endif // FUNCTIONSWINDOWS_H
