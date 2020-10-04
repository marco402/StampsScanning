// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:form_main.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QSlider>
#include <QStatusBar>
#include <QTextEdit>
#include <QComboBox>
#include <QToolTip>
#include <QLabel>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QLayout>
#include <QCloseEvent>
#include <QProgressBar>
#include <QImageReader>
#include "form_main.h"
#include "constantes.h"
#include "form_help.h"
#include "..\process\class_sep_stamps_thread.h"


formMain::formMain() {

    loadSettings();
     threadProcess = new MyThread();
     connect(threadProcess, SIGNAL(sendProgress(int, int)), this, SLOT(receiveProgress(int, int)));
#ifdef DEBUGDISPLAYIMAGE
     connect(threadProcess, SIGNAL(sendImageDebug(QImage)), this, SLOT(receiveImageDebug(QImage)));
#endif
     connect(threadProcess, SIGNAL(sendFinished()), this, SLOT(receiveFinished()));  //
     connect(this, SIGNAL(sendTerminate()), threadProcess, SLOT(receiveTerminate()));
    labelPicture=new QLabel(this);
    setWindowTitle("stampsScanning V1.0");
    move(10,10);

    loadWidgets();
    layout()->setSizeConstraint (QLayout::SetNoConstraint);  //sinon pas de rétrécissement sur image > contraintes QT 2/3
    image=new QImage;
    myPixmap=new QPixmap;
    setCentralWidget(labelPicture);
    labelPicture->setScaledContents(true);
    //int widthScreen = static_cast<int>((QApplication::desktop()->width())*PROPORTIONWINDOWSMAX);
    //int heighScreen = static_cast<int>((QApplication::desktop()->height())*PROPORTIONWINDOWSMAX);

    //setMinimumSize(WIDTHWINDOWMAINMIN,HEIGHTWINDOWMIN);
    //setMaximumSize(widthScreen,heighScreen);
    cbBorderSize->setCurrentText(QString::number(border));
    runAct->setEnabled(false);
    rotateAct->setEnabled(false);
	
#ifdef LOADWHENSTART
//**************if load to open window**********************
    QString fileName = QApplication::applicationDirPath() + "../../stamps_test/1timbre.bmp";   //le petit prince pb.bmpT11.bmpcarre_penche_droite.bmp35timbres.bmp 3timbres.jpg45degres200ppm.bmp  "C:/marc/developpement/T11.bmp" "C:/marc/developpement/dossiers/Nouveau dossier (2)/capture1.jpg"  ;   //"C:/marc/developpement/StampsScanning/StampsScanning/35timbres.jpg";

    if(loadFile(fileName))
    {
		valideLoadFile(fileName);
    }
    else {
        setGeometry(0,0,500,300);
    }

//****************************************************************
#else
    setGeometry(0,0,600,300);
#endif
}
formMain::~formMain()
{
}
//without closeEvent, destructor only when all windows are closed
void formMain::closeEvent(QCloseEvent *event)
{
	stop();
    event->accept();
    closeAll();
	qApp->closeAllWindows();
	while (threadProcess->isRunning()); 
	threadProcess->quit();
	saveSettings();
	exit(0);
}
void formMain::loadWidgets()
{
    //actions
    openAct = new QAction(QIcon(":/icons/open.png") , tr("&Open..."), this);
    rotateAct = new QAction(QIcon(":/icons/rotateright.png") , tr("&Rotate..."), this);
    runAct = new QAction(QIcon(":/icons/right-32.png") , tr("&Run..."), this);
    closeAllAct = new QAction(QIcon(":/icons/topbar_button_close.png") , tr("&CloseAll..."), this);
    bordureAct = new QAction(QIcon(":/icons/square.png") , tr("&Border..."), this);
    stopAct = new QAction(QIcon(":/icons/stop-32.png") , tr("&Stop..."), this);
    connect(openAct, &QAction::triggered, this, &formMain::open);
    connect(runAct, &QAction::triggered, this, &formMain::run);
    connect(rotateAct, &QAction::triggered, this, &formMain::rotate);
    connect(closeAllAct, &QAction::triggered, this, &formMain::closeAll);
    connect(stopAct, &QAction::triggered, this, &formMain::stop);
	helpAct = new QAction(tr("Help Contents"), this);
	helpAct->setShortcut(QKeySequence::HelpContents);
	connect(helpAct, SIGNAL(triggered()), this, SLOT(createHelpWindow()));
	aboutAction = new QAction(tr("&About"), this);
	connect(aboutAction, SIGNAL(triggered()),this, SLOT(about()));
    //combo border
    cbBorderSize = new QComboBox;
    for (int j=1;j<11;j++)
    {
        cbBorderSize->addItem(QString::number(j));
        if(j==5)
           cbBorderSize->setItemData(j-1, QColor(Qt::darkGreen), Qt::BackgroundRole);
        else
           cbBorderSize->setItemData(j-1, QColor(Qt::green), Qt::BackgroundRole);

           cbBorderSize->setItemData(j-1, QColor(Qt::white), Qt::ForegroundRole);
    }
    cbBorderSize->setToolTip(tr("proposed 5 for standard"));
	//combo year
    cbYear = new QComboBox;
	cbYear->addItem("");
    for (int j=1840;j<2040;j++)
		cbYear->addItem(QString::number(j));
	cbYear->setToolTip(tr("Choose the year if you want it add to the name of the stamp file."));

    //language
    menuLanguage=new QMenu(this);
    createLanguageMenu();
    setContextMenuPolicy(Qt::NoContextMenu);
    if(!currentLanguage.isEmpty())
        loadLanguage(currentLanguage);

    //toolbar
    toolbar = addToolBar("main toolbar");
    toolbar->addAction(openAct);
    toolbar->addSeparator();
    toolbar->addAction(runAct);
    toolbar->addSeparator();
    toolbar->addAction(rotateAct);
    toolbar->addAction(bordureAct);
    toolbar->addWidget(cbBorderSize);
	toolbar->addWidget(cbYear);
    toolbar->addAction(closeAllAct);
    toolbar->addSeparator();
    toolbar->addAction(stopAct);
	//help
	helpMenu = new QMenu(tr("&Help"), this);
//#ifdef HELP
	helpMenu->addAction(helpAct);
//#endif
	helpMenu->addAction(aboutAction);
	toolbar->addWidget(helpMenu);

   toolbar->addSeparator();
    toolbar->addWidget(menuLanguage);
  toolbar->addSeparator();

#ifdef CALIBRATIONTHRESHOLD
	if (calibrationThreshold)
	{
		sliderCalibration = new QSlider(Qt::Horizontal);
		sliderCalibration->setTracking(false);
		sliderCalibration->setEnabled(false);
		sliderCalibration->setToolTip(QString::number(sliderCalibration->sliderPosition()));
		sliderCalibration->setRange(0, 255);
		sliderCalibration->setValue(threshold);
		sliderCalibration->setToolTip(QString::number(threshold));
		toolbar->addSeparator();
		toolbar->addWidget(sliderCalibration);
	}
#endif
    //status bar
    labStatusBar=new QLabel;
    statusBar()->addWidget(labStatusBar);
    //progress  bar
    progressBarProcess = new QProgressBar();
    progressBarProcess->setAlignment(Qt::AlignRight);
    progressBarProcess->setMaximumSize(180, 19);
    statusBar()->addWidget(progressBarProcess);
    progressBarProcess->hide();
#ifdef DEBUGTOOLTIP
     labelPicture->setMouseTracking(true);  //event without click
     labelPicture->installEventFilter(this);
#endif
}

void formMain::about()
{
	QMessageBox::about(this, tr("About StampsScanning"),
        tr("V1.0 proposed by Marc Prieur\n 09/2020.")+"\n email:marco40_github@sfr.fr");
}

void formMain::createHelpWindow()
{
	 new formHelp(currentLanguage);   //formHelp *frmHelp =
}


#ifdef CALIBRATIONTHRESHOLD

void formMain::sliderCalibrationMove(int position)
{
	labStatusBar->setText(tr("threshold:")+ QString::number(position));
}

void formMain::valueSliderCalibrationChanged(int position)
{
	static int memoPosition = 0;
	if (memoPosition!=position)
	{
		runAct->setEnabled(false);
		rotateAct->setEnabled(false);
		memoPosition = position;
		threshold = position;
		qDebug("%d", position);
		traiteSliderCalibration();
		runAct->setEnabled(true);
		rotateAct->setEnabled(true);
    }
}
#endif


#ifdef DEBUGTOOLTIP
bool formMain::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == labelPicture) {
        if(event->type() == QEvent::MouseMove)
        {
             int cursorScreenY=cursor().pos().y();
             int topWindowStamp=this->geometry().y();
             int cursorInWindowStampY=cursorScreenY-topWindowStamp;
             int zeroImageY=cursorInWindowStampY-toolbar->height();
             int restForImageY=height()-toolbar->height()-statusBar()->height();
             int cursorScreenX=cursor().pos().x();
             int leftWindowStamp=this->geometry().x();
             int cursorInWindowStampX=cursorScreenX-leftWindowStamp;
             int zeroImageX=cursorInWindowStampX;
             QToolTip::showText(cursor().pos(),
                  QString::number(((zeroImageX*image->width()) /width()))+
				 ", " +
                  QString::number(((zeroImageY*image->height()) /restForImageY)) +
				 ", " + 
				 QString::number(zeroImageX) +
				 ", " + 
				 QString::number(zeroImageY),
				 this,
				 rect() );
            return true;
        }
        else
            return false;
    }
    else
        return formMain::eventFilter(obj, event);
}
#endif

//#endif

