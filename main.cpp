// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:main.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************

#include <QApplication>
#include <QWindow>
#include "common.h"
#include "presentation\form_main.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    const QIcon Q=QIcon(":/icons/icon_app.png");
    app.setWindowIcon(Q);
    formMain window;
    window.show();
    app.exec();
}
