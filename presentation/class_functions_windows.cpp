// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:class_functions_windows.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "class_functions_windows.h"
#include <QDesktopWidget>
#include <QWidget>
#include "common.h"
#include "constantes.h"
void functionsWindows::calcNewSizeIfWindowTooBig(int widthWindow,int heightWindow,int cor,QImage *image,int *newWidthWindow,int  *newHeightWindow, int widthWindowMin, int heightWindowMin)
{
        int widthScreenMax = static_cast<int>((QApplication::desktop()->width())*PROPORTIONWINDOWSMAX);
        int heighScreenMax = static_cast<int>((QApplication::desktop()->height())*PROPORTIONWINDOWSMAX);
        if (newWidthWindow)
        {
            if(widthWindow!=*newWidthWindow)
            {
                if(widthWindow>widthScreenMax)
                    widthWindow=widthScreenMax;
                else if(widthWindow< widthWindowMin)
                    widthWindow= widthWindowMin;
                heightWindow=((widthWindow * image->height())/image->width())+cor;
                if(heightWindow>heighScreenMax)
                {
                    heightWindow=heighScreenMax;
                    widthWindow=((heightWindow-cor)*image->width())/image->height();
                 }
                else if(heightWindow< heightWindowMin)
                {
                    heightWindow=heightWindowMin ;
                    widthWindow=((heightWindow-cor)*image->width())/image->height();
                }
            }
            else
            {
                 if(heightWindow>heighScreenMax)
                    heightWindow=heighScreenMax;
                else if(heightWindow< heightWindowMin)
                    heightWindow= heightWindowMin;
                widthWindow=((heightWindow-cor)*image->width())/image->height();
                if(widthWindow>widthScreenMax)
                {
                    widthWindow=widthScreenMax;
                    heightWindow=((widthWindow*image->height())/image->width())+cor;
                }
                else if(widthWindow< widthWindowMin)
                {
                    widthWindow= widthWindowMin;
                    heightWindow=((widthWindow*image->height())/image->width())+cor;
                 }
				if (heightWindow > heighScreenMax)
				{
					heightWindow = heighScreenMax;
					widthWindow = ((heightWindow - cor)*image->width()) / image->height();
				}
				else if (heightWindow < heightWindowMin)
				{
					heightWindow = heightWindowMin;
					widthWindow = ((heightWindow - cor)*image->width()) / image->height();
				}
            }
            *newWidthWindow=widthWindow;
            *newHeightWindow=heightWindow;
        }
}
void functionsWindows::calcNewSizeIfImageTooBig(int *newWidthPicture,int  *newHeightPicture,int cor,int widthWindowMin,int heightWindowMin)
{
    int widthScreenMax =  static_cast<int>((QApplication::desktop()->width())*PROPORTIONWINDOWSMAX);
    int heighScreenMax =  static_cast<int>((QApplication::desktop()->height())*PROPORTIONWINDOWSMAX);
    int widthPicture =*newWidthPicture;
    int heightPicture =*newHeightPicture;
    if(widthPicture> widthScreenMax)
        *newWidthPicture= widthScreenMax;
    else if(widthPicture< widthWindowMin)
        *newWidthPicture= widthWindowMin;
    *newHeightPicture=(*newWidthPicture*heightPicture)/widthPicture;

    if(*newHeightPicture> (heighScreenMax - cor))
    {
        *newHeightPicture= heighScreenMax - cor;
        *newWidthPicture=(*newHeightPicture*widthPicture)/heightPicture;
    }
    else if(*newHeightPicture< (heightWindowMin-cor))
    {
        *newHeightPicture= heightWindowMin-cor;
        *newWidthPicture=(*newHeightPicture*widthPicture)/heightPicture;
    }
}
void functionsWindows::rotate(int angle,int cor,QImage *image,QPixmap *myPixmap,QLabel *labelPicture,int *newWidthPicture,int *newHeightPicture,int *newWidthWindow,int *newHeightWindow, int widthWindowMin, int heightWindowMin)
{
    *newWidthPicture=*newHeightWindow-cor;
    *newHeightPicture=*newWidthWindow;   //+cor
    QTransform transform;
    transform.rotate(angle);
    *image = image->transformed(transform,Qt::SmoothTransformation);
    myPixmap->convertFromImage(*image,Qt::DiffuseDither);
    *myPixmap =myPixmap->scaled(*newWidthPicture,*newHeightPicture,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    labelPicture->setPixmap(*myPixmap);
    calcNewSizeIfImageTooBig(newWidthPicture,newHeightPicture,cor, widthWindowMin, heightWindowMin);
    *newWidthWindow=*newWidthPicture;
    *newHeightWindow=*newHeightPicture+cor;   //
}
