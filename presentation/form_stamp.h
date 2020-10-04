// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:form_stamp.h
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include "class_functions_windows.h"
#include "common.h"
#include "constantes.h"

class formStamp : public QMainWindow {
    Q_OBJECT
public:
    formStamp();
    formStamp(structFormStamp frm,QString * currentPathSave,double * ratioPerforation);   //
    void retranslateUi();
public:

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
#ifdef DEBUGTOOLTIP
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
#endif
private:
    void initResize();
    void loadWidgets(structFormStamp frm);
    void displayPath();
private slots:
    void save();
    void rotate();
    void calibrationPerf();
    void changePath();
private:
    QToolBar *toolbar = nullptr;
    QImage *image = nullptr;
    QLabel  *labelPicture = nullptr;
    QLabel *labStatusBar = nullptr;
    QPixmap *myPixmap = nullptr;
    QComboBox *cbNbPerforations = nullptr;
	QLineEdit *editYearStamp = nullptr;
    QLineEdit *editRefStamp = nullptr;
    QLineEdit *editNamePictureFile = nullptr;
    QAction* saveAct = nullptr;
    QAction* rotateAct = nullptr;
    QAction* calibrationPerfAct = nullptr;
    QAction* changePathAct = nullptr;
    int newWidthWindow=0;
    int newHeightWindow=0;
    int angle=90;
    double nbPerforation[4];
    bool noResizeByUser=false;
    int cor=0;
    QString *currentPathSave = nullptr;
    double *ratioPerforation = nullptr;
};
