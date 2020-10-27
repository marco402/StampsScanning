// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:partial_form_main_setting.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QSettings>
#include <QFile>
#include "form_main.h"
bool formMain::loadSettings()
{
    m_sSettingsFile = "stampsScanning.ini";
    bool ret=QFileInfo(m_sSettingsFile).exists();
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);
    settings.beginGroup("ParamIde");
    border=settings.value("border", "5").toInt();
    currentPathLoad=settings.value("currentPathLoad","").toString();
    currentPathSave=settings.value("currentPathSave","").toString();
    currentLanguage=settings.value("currentLanguage","en").toString();
    settings.endGroup();
    settings.beginGroup("ParamProcess");
    ratioPerforation=settings.value("ratioPerforation","0.7874").toDouble();    //0.7874=2cm/2.54
	threshold =settings.value("threshold",THRESHOLD).toInt();
	sweepStamp_mm =settings.value("sweepStamp_mm", SWEEPSTAMP_MM).toInt();
	displayDebugContour =settings.value("displayDebugContour", false).toBool();
	calibrationThreshold =settings.value("calibrationThreshold", false).toBool();
    settings.endGroup();
    return ret;
}
void formMain::saveSettings()
{
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);
	settings.beginGroup("ParamIde");
    settings.setValue("border", (cbBorderSize) ? cbBorderSize->currentText() : "5");
    settings.setValue("currentPathLoad", currentPathLoad);
    settings.setValue("currentPathSave", currentPathSave);
    settings.setValue("currentLanguage", currentLanguage);
    settings.endGroup();
    settings.beginGroup("ParamProcess");
    settings.setValue("ratioPerforation", ratioPerforation);
    settings.setValue("threshold", threshold);
	settings.setValue("sweepStamp_mm", sweepStamp_mm);
	settings.setValue("displayDebugContour", displayDebugContour);
	settings.setValue("calibrationThreshold", calibrationThreshold);
	//QFile set = settings.fileName();
	//if(!set.exists())
	//	settings.setValue("displayDebugContour", displayDebugContour);
	//	settings.setValue("calibrationThreshold", calibrationThreshold);
    settings.endGroup();
}


