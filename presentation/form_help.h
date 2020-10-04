// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:form_help.h
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
#include <QTextBrowser>
class formHelp : public QMainWindow {
	Q_OBJECT
public:
	formHelp(QString currentLanguage);
public:

protected:

private slots:

private:
	QTextBrowser *textBrowser = nullptr;
};
