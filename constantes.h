// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:constantes.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef CONSTANTES_H
#define CONSTANTES_H

#ifdef __DEBUG__  //put or delete NO_
	#define NO_DEBUGDISPLAYCONTOURIMAGE
	#define NO_DEBUGDISPLAYIMAGE					//this option need modified code...
	#define NO_LOADWHENSTART
	#define DEBUGTOOLTIP
#endif
#define CALIBRATIONTHRESHOLD     //see setting true or false for display

//ok for unused variable(QT Creator only)but error on MYTHREAD in formMain.h
//#include "presentation/class_functions_windows.h"
//#include "presentation/form_main.h"

//presentation
int const WIDTHWINDOWMAINMIN = 400;
int const WIDTHWINDOWSTAMPMIN=300;
int const HEIGHTWINDOWMIN=200;
double const PROPORTIONWINDOWSMAX=0.8;


//process
int const   REJECT_OUTLIERS  = 20;  //rejection of outliers 
int const   THRESHOLD  = 110;  //detection threshold stamp borders       130 for 8timbres  100 for 16 of 35timbres, 130  de 130 a 120 for rommy
int const   D_SWEEP_OUT  = 5;           //past of 9 to 6 minimum number of pixels on the borders makes it possible to consider that one is on a border
int const   D_SWEEP_IN  = 20;        //past of 5 to 20 ,pb if cancellation 2° stamp de 8timbres.jpg
double const   INCH  = 2.54;
int const   DXY_BORDER = 10; //border add to stamp contour    put 10 for stamp an2000 of 35 timbres  pb à 5 .
int const   NBPOINTMINIXX  = 10 ;
int const   SWEEPSTAMP_MM  = 15 ; 
#endif // CONSTANTES_H
