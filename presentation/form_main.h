// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:form_main.h
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
#include <QLabel>
#include <QComboBox>
#include <QTranslator>
#include <QProgressBar>
#include <QFileInfo>
#include "common.h"
#include "constantes.h"
#include "class_functions_windows.h"
#include "process\class_sep_stamps_thread.h"
#include "form_stamp.h"
#include "form_help.h"
class formMain : public QMainWindow {
    Q_OBJECT
public:
    formMain();
    ~formMain()override;
public:
    QString currentPathSave;

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void changeEvent(QEvent*) override;
    virtual void closeEvent(QCloseEvent *bar) override;

#ifdef DEBUGTOOLTIP
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
#endif
protected slots:
    void open();
    void run();
    void rotate();
    void closeAll();
    void stop();
    void slotLanguageChanged(QAction* action);
    void receiveFinished();
    void receiveProgress(int value,int maximum);
#ifdef CALIBRATIONTHRESHOLD
	void valueSliderCalibrationChanged(int position);
	void sliderCalibrationMove(int position);
#endif
#ifdef DEBUGDISPLAYIMAGE
    void receiveImageDebug(QImage image);
#endif
signals:
    void sendTerminate();
private:
    void loadWidgets();
    //****setting************
    bool loadSettings(void);
    void saveSettings(void);
    void resizePicture();
    bool loadFile(const QFileInfo &fileName);
    void initResize();
    //language
    void createLanguageMenu();
    void loadLanguage(const QString& rLanguage);
    void retranslateUi();
	void switchTranslator(QTranslator& translator, const QString& filename);
    QList<corners> getListStampWithDetection(struct oneMatrix *theMatrix,QImage image);
private:
    QString m_sSettingsFile;
    QString VERSION="V 1.0.1";
    //***********************
    QImage *image = nullptr;
    QLabel  *labelPicture = nullptr;
    QPixmap *myPixmap = nullptr;
    QToolBar *toolbar = nullptr;
    QComboBox *cbBorderSize = nullptr;
    QComboBox *cbYear = nullptr;
    QList<formStamp*> listFormStamp;
	void valideLoadFile(QString fileName);
#ifdef CALIBRATIONTHRESHOLD
	void traiteSliderCalibration();
	QSlider *sliderCalibration = nullptr;
#endif
    //****languages***********
    QMenu *menuLanguage = nullptr;
    QTranslator m_translator;
    QTranslator m_translatorQt;
    QString m_currLang;
    QString m_langPath;
    //************************
    QAction* openAct = nullptr;
    QAction* rotateAct = nullptr;
    QAction* runAct = nullptr;
    QAction* closeAllAct = nullptr;
    QAction* bordureAct = nullptr;
    QAction* stopAct = nullptr;
    QLabel *labStatusBar = nullptr;
	QAction *aboutAction = nullptr;
	QMenu *helpMenu = nullptr;
	QAction *helpAct;
private slots:
	void about();
	void createHelpWindow();
private:
    int newWidthPicture=0;
    int newHeightPicture=0;
    int newWidthWindow=0;
    int newHeightWindow=0;
    int angle=90;
    double nbPerforation[4];
    bool noResizeByUser=false;
    int cor=0;
    int border=5;
    double ratioPerforation;
	int threshold = THRESHOLD;
	int sweepStamp_mm = 15;
	bool displayDebugContour = true;
	bool calibrationThreshold = false;
private:
    void displayStamp(QList<structFormStamp> propertyListForm);
    MyThread * threadProcess = nullptr;
    QVector<structFormStamp> allStamp;
    QColor backColor;
    QProgressBar *progressBarProcess = nullptr;
    QString currentPathLoad;
    QString currentLanguage;
};
