// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:form_stamp.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QPushButton>
#include <QAction>
#include <QToolBar>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QToolTip>
#include <QImageReader>
#include <QImageWriter>
#include <QStatusBar>
#include <QLineEdit>
#include <QResizeEvent>

#include "form_stamp.h"

formStamp::formStamp(structFormStamp frm)
{
    memmove ( nbPerforation, frm.nbTeeth, 4*sizeof(double) ) ;
    setWindowTitle(frm.title );   //+ QString::number(frm.index)
    move(frm.left,frm.top);
    loadWidgets(frm);
    initResize();
    //displayPath();
}
formStamp::formStamp(structFormStamp frm,QString * currentPathSave,double * ratioPerforation)
{
    this->currentPathSave=currentPathSave;
    this->ratioPerforation=ratioPerforation;
    memmove ( nbPerforation, frm.nbTeeth, 4*sizeof(double) ) ;
    setWindowTitle(frm.title );   //+ QString::number(frm.index)
    move(frm.left,frm.top);
    loadWidgets(frm);
    initResize();
    displayPath();
}
void formStamp::initResize()
{
    int widthScreen = static_cast<int>((QApplication::desktop()->width())*PROPORTIONWINDOWSMAX);
    int heighScreen = static_cast<int>((QApplication::desktop()->height())*PROPORTIONWINDOWSMAX); 
	setMinimumSize(WIDTHWINDOWSTAMPMIN,HEIGHTWINDOWMIN);	
    setMaximumSize(widthScreen,heighScreen);
	
	//part==initResize formMain
	int newWidthPicture=image->width();
	int newHeightPicture=image->height();
	toolbar->setFixedHeight(34);				//the size is not fixed here (30)
	statusBar()->setFixedHeight(20);			//the size is not fixed here (30)
	cor=(toolbar->height()+statusBar()->height());
    functionsWindows::calcNewSizeIfImageTooBig(&newWidthPicture,&newHeightPicture,cor, WIDTHWINDOWSTAMPMIN, HEIGHTWINDOWMIN);
    myPixmap->convertFromImage(*image,Qt::DiffuseDither);
    *myPixmap =myPixmap->scaled(newWidthPicture, newHeightPicture,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    labelPicture->setPixmap(*myPixmap);
    noResizeByUser=true;
    this->resize(newWidthPicture, newHeightPicture +cor);
    newWidthWindow=width();
    newHeightWindow=height();
}
void formStamp::loadWidgets(structFormStamp frm)
{

    editRefStamp = new QLineEdit;
    editRefStamp->setToolTip(tr("Ref of stamp."));
	editNamePictureFile =new QLineEdit;
    editNamePictureFile->setToolTip(tr("Name if you want it.."));
    editYearStamp = new QLineEdit;
    editYearStamp->setText(frm.yearStamp);
    editYearStamp->setToolTip(tr("Year if you want it."));
    cbNbPerforations = new QComboBox;
    cbNbPerforations->setEditable(false);
    average=(frm.nbTeeth[static_cast<int>(sideStamp::NORTH)]+frm.nbTeeth[static_cast<int>(sideStamp::SOUTH)]+frm.nbTeeth[static_cast<int>(sideStamp::EAST)]+frm.nbTeeth[static_cast<int>(sideStamp::WEST)])/4;
    cbNbPerforations->addItem(QString::number(average,'f',1));

    cbNbPerforations->addItem(tr("North:  ")+QString::number(frm.nbTeeth[static_cast<int>(sideStamp::NORTH)],'f',1));
    cbNbPerforations->addItem(tr("South:   ")+QString::number(frm.nbTeeth[static_cast<int>(sideStamp::SOUTH)],'f',1));
    cbNbPerforations->addItem(tr("East:   ")+QString::number(frm.nbTeeth[static_cast<int>(sideStamp::EAST)],'f',1));
    cbNbPerforations->addItem(tr("West: ")+QString::number(frm.nbTeeth[static_cast<int>(sideStamp::WEST)],'f',1));

     saveAct = new QAction(QIcon(":/icons/save.png") , tr("&Save..."), this);
     changePathAct= new QAction(QIcon(":/icons/open.png") , tr("&Change path to save..."), this);
     rotateAct = new QAction(QIcon(":/icons/rotateright.png") , tr("&Rotate..."), this);
     calibrationPerfAct = new QAction(QIcon(":/icons/calibration.png") , tr("&Calibration perforation..."), this);
     connect(saveAct, &QAction::triggered, this, &formStamp::save);
     connect(rotateAct, &QAction::triggered, this, &formStamp::rotate);
     connect(calibrationPerfAct, &QAction::triggered, this, &formStamp::calibrationPerf);
     connect(changePathAct, &QAction::triggered, this, &formStamp::changePath);
     toolbar = addToolBar("main toolbar");
     toolbar->addWidget(editRefStamp);
     toolbar->addWidget(editNamePictureFile);
	 toolbar->addWidget(editYearStamp);
	 toolbar->addAction(saveAct);
     toolbar->addAction(rotateAct);
     toolbar->addWidget(cbNbPerforations);
     toolbar->addAction(changePathAct);
     toolbar->addAction(calibrationPerfAct);
     labStatusBar=new QLabel;
     statusBar()->addWidget(labStatusBar);
     labelPicture = new QLabel(this);
     setCentralWidget(labelPicture);
     labelPicture->setScaledContents(true);
     setMinimumSize(50,50);
     image=new QImage(frm.oneBmp);
     myPixmap=new QPixmap;

#ifdef DEBUGTOOLTIP
     labelPicture->setMouseTracking(true);  //event without click
     labelPicture->installEventFilter(this);
#endif
}
void formStamp::rotate()
{
    int newWidthPicture=myPixmap->width();
    int newHeightPicture=myPixmap->height();
	newWidthWindow = width();
	newHeightWindow = height();
    functionsWindows::rotate( angle,cor,image,myPixmap,labelPicture,&newWidthPicture,&newHeightPicture,&newWidthWindow,&newHeightWindow, WIDTHWINDOWSTAMPMIN, HEIGHTWINDOWMIN);
    noResizeByUser=true;
    this->resize(newWidthWindow,newHeightWindow);
    double temp=nbPerforation[ static_cast<int>(sideStamp::NORTH)];
    nbPerforation[static_cast<int>(sideStamp::NORTH)]=nbPerforation[static_cast<int>(sideStamp::WEST)];
    nbPerforation[static_cast<int>(sideStamp::WEST)]=nbPerforation[static_cast<int>(sideStamp::SOUTH)];
    nbPerforation[static_cast<int>(sideStamp::SOUTH)]=nbPerforation[static_cast<int>(sideStamp::EAST)];
    nbPerforation[static_cast<int>(sideStamp::EAST)]=temp;
    cbNbPerforations->clear();
    cbNbPerforations->addItem(QString::number(average,'f',1));
    cbNbPerforations->addItem(tr("North:  ") + QString::number(nbPerforation[static_cast<int>(sideStamp::NORTH)],'f',1));
    cbNbPerforations->addItem(tr("South:   ") +  QString::number(nbPerforation[static_cast<int>(sideStamp::SOUTH)],'f',1));
    cbNbPerforations->addItem(tr("East:   ") +  QString::number(nbPerforation[static_cast<int>(sideStamp::EAST)],'f',1));
    cbNbPerforations->addItem(tr("West: ") +  QString::number(nbPerforation[static_cast<int>(sideStamp::WEST)],'f',1));
}
void formStamp::calibrationPerf()
{
    double averagePerf=0.0;
    for(int i=0;i<4;i++)
        averagePerf+=nbPerforation[i];
    averagePerf/=4;
    bool ok;
    QMessageBox msgBox;
        QString text = QInputDialog::getText(this, tr("calibration"),
              tr("enter the number of teeth"), QLineEdit::Normal,
              QString::number(averagePerf), &ok);
        if (ok && !text.isEmpty())
        {
          double nbTeeth=text.toDouble();
          if(nbTeeth==0.0) {
              msgBox.setText(tr("error: your text is not a number."));
              msgBox.setDefaultButton(QMessageBox::Cancel);
              msgBox.exec();
              return;
          }
          *ratioPerforation=*ratioPerforation/averagePerf*nbTeeth;
          msgBox.setText(tr("new calibration ok."));
          msgBox.setDefaultButton(QMessageBox::Cancel);
          msgBox.exec();
        }
}

void formStamp::changePath()
{
	*currentPathSave = QFileDialog::getExistingDirectory(this, tr("Select a directory"));
	displayPath();
}
void formStamp::displayPath()
{
    const QString message = tr("Save path:") + *currentPathSave;
    labStatusBar->setText(message);
}

void formStamp::save()
{

if (*currentPathSave=="")
        changePath();
    QMessageBox msgBox;
    if (editRefStamp->text().isEmpty())
    {
        msgBox.setText(tr("Type a reference for this stamp."));
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
        return;
    }
    QString imagePath =*currentPathSave+"/"+ editRefStamp->text();

    if (!editNamePictureFile->text().isEmpty())
        imagePath+=("_" + editNamePictureFile->text() );

     if (!editYearStamp->text().isEmpty())
         imagePath += "_" + editYearStamp->text() ;      //if bmp or png ok,only change extension
#ifdef __DEBUG__
     imagePath += ".bmp";
#else
     imagePath += ".jpg";
#endif
    if(QFile::exists(imagePath))
    {
        msgBox.setText(tr("This file exist,do you want replace it?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret=msgBox.exec();
        if (ret==QMessageBox::Cancel)
            return;
    }


	QImageWriter writer(imagePath);
	bool ret=writer.write(*image);
    if(ret)
    {
    const QString message = (tr("Saved") + "\"%1\", %2x%3") .arg(imagePath).arg(image->width()).arg(image->height());
	labStatusBar->setToolTip(message);
      labStatusBar->setText(message);
	  QPalette palette;
	  palette.setColor(QPalette::Base, QColor(Qt::green));
      editRefStamp->setPalette(palette);
	  editNamePictureFile->setPalette(palette);
      editYearStamp->setPalette(palette);

    }
    else
    {
         labStatusBar->setText(tr("no save file."));
         msgBox.setText(writer.errorString());
         msgBox.setDefaultButton(QMessageBox::Cancel);
         msgBox.exec();
         return;
    }
}
void formStamp::retranslateUi()
{
     saveAct->setText(tr("&Save..."));
     rotateAct->setText(tr("&Rotate..."));
}
//resizeEvent for resize window by user with mouse
void  formStamp::resizeEvent(QResizeEvent* event)
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
        functionsWindows::calcNewSizeIfWindowTooBig(width(),height(),cor,image,&newWidthWindow,&newHeightWindow, WIDTHWINDOWSTAMPMIN,HEIGHTWINDOWMIN);
        this->resize(newWidthWindow,newHeightWindow);
        newWidthWindow=width();
        newHeightWindow= height()-cor;
    }
    noResizeByUser=false;
}
#ifdef DEBUGTOOLTIP
bool formStamp::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == labelPicture) {
        if(event->type() == QEvent::MouseMove)
        {
			int cursorScreenY = cursor().pos().y();
			int topWindowStamp = this->geometry().y();
			int cursorInWindowStampY = cursorScreenY - topWindowStamp;
			int zeroImageY = cursorInWindowStampY - toolbar->height();
			int restForImageY = height() - toolbar->height() - statusBar()->height();//height() is without title barre
															//toolbar->height()->34
															//statusBar()->height()->20
			int cursorScreenX = cursor().pos().x();
			int leftWindowStamp = this->geometry().x();
			int cursorInWindowStampX = cursorScreenX - leftWindowStamp;
			int zeroImageX = cursorInWindowStampX;
			QToolTip::showText(cursor().pos(),
				QString::number(((zeroImageX*image->width()) / width())) +
				", " +
				QString::number(((zeroImageY*image->height()) / restForImageY)) +
				", " +
				QString::number(zeroImageX) +
				", " +
				QString::number(zeroImageY)
				,this, rect());
            return true;
        }
        else
            return false;
    }
    else
        return formStamp::eventFilter(obj, event);
}
#endif

