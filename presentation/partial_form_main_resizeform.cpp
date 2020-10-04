// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:partial_form_main_resizeform.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QMessageBox>
#include <QFileDialog>
#include<QImageIOHandler>
#include <QStatusBar>
#include <QToolBar>
#include <QDesktopWidget>
#include <QResizeEvent>
#include<QImageIOHandler>
#include<QFileInfo>
#include "form_main.h"
#include "constantes.h"
//resize cases: you can verified their size with DEBUGTOOLTIP(constantes.h)->tooltip position
    //load image 1 stamp + rotate
    //reload image 8 stamp + rotate
    //reload image 1 stamp
    //rotate
    //load width image>max
    //load width image<min
    //load height image>max
    //load height image<min
    //resize by user with mouse
    //rotate after resize with mouse
//on load new image
				//put DEBUGTOOLTIP 
//my screen 1600pix/900-->1.77
//          383mm:216---->1.77
//        4.177pix/mm  4.166pix/mm  moy 4.171
//0.239mm/pix  0.24mm/pix
//stamp bonnes vacances 
//image--->325pix/214---->1.519
	//load
		//formMain         325/214--->1.519
						// 400/263--->1.52
		//formStamp        325/214--->1.519
						// 325/214--->1.519
						// 78mm/52--->1.5
//78mm/52
	//resize max
		//formMain         325/214--->1.519-->ok   1111/732-->1.517-->ok
		//formStamp        325/214--->1.519-->ok   1148/756-->1.518-->ok
	//rotate
		//formMain	   after resize max
			//+90°    732/482-->1.518-->ok  
			//+90°    732/482-->1.518-->ok  
			//+90°    732/482-->1.518-->ok    
			//+90°    732/482-->1.518-->ok    
		//formStamp			
			//+90°    756/497-->1.52-->ok    
			//+90°    756/497-->1.52-->ok  
			//+90°    756/497-->1.52-->ok  
			//+90°    756/497-->1.52-->ok  



void formMain::initResize()
{
	newWidthPicture = image->width();
	newHeightPicture = image->height();
	cor = (toolbar->height() + statusBar()->height());
	functionsWindows::calcNewSizeIfImageTooBig(&newWidthPicture, &newHeightPicture, cor, WIDTHWINDOWMAINMIN, HEIGHTWINDOWMIN);
	myPixmap->convertFromImage(*image, Qt::DiffuseDither);
	*myPixmap = myPixmap->scaled(newWidthPicture, newHeightPicture, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	labelPicture->setPixmap(*myPixmap);
	noResizeByUser = true;
	this->resize(newWidthPicture, newHeightPicture + cor);
	newWidthWindow = width();
	newHeightWindow = height();
}
//resizeEvent for resize window by user with mouse
void  formMain::resizeEvent(QResizeEvent* event)
{
    if(noResizeByUser)
    {
        noResizeByUser=false;
        return;
    }
    if(image->width()>0)
    {
        event->accept();
        cor=(toolbar->height()+statusBar()->height());
        functionsWindows::calcNewSizeIfWindowTooBig(width(),height(),cor,image,&newWidthWindow,&newHeightWindow, WIDTHWINDOWMAINMIN, HEIGHTWINDOWMIN);
        this->resize(newWidthWindow,newHeightWindow);
        newWidthPicture=width();
        newHeightPicture= height()-cor;
    }
    noResizeByUser=false;
}





