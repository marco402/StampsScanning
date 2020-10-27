// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:partial_form_main_command.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include <QAction>
#include <QFileDialog>
#include <QLayout>
#include <QCloseEvent>
#include <QProgressBar>
#include <QImageReader>
#include <QPainter>
#include <QMessageBox>
#include "form_main.h"
#include "constantes.h"
#include "process/class_generiques_fonctions.h"
void formMain::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a scan stamp file"),currentPathLoad,tr("Files scan (*.bmp);;Other possible files scan (*.png *.jpg)"));
    QFileInfo fileinfo(fileName);
    if (fileinfo.exists())
    {
        if(  loadFile(fileinfo))
			valideLoadFile(fileName);
    }
}
void formMain::valideLoadFile(QString fileName)
{
           const QString message = (tr("Opened") + "\"%1\", %2x%3")
                    .arg(QDir::toNativeSeparators(fileName)).arg(image->width()).arg(image->height());
           labStatusBar->setText(message);
           runAct->setEnabled(true);
           rotateAct->setEnabled(true);
#ifdef CALIBRATIONTHRESHOLD
		   if(calibrationThreshold)
		   {
		   sliderCalibration->setEnabled(true);
		   connect(sliderCalibration, SIGNAL(valueChanged(int)), this, SLOT(valueSliderCalibrationChanged(int)));
		   connect(sliderCalibration, SIGNAL(sliderMoved(int)), this, SLOT(sliderCalibrationMove(int)));
			}
#endif
}
void formMain::closeAll()
{
               foreach (formStamp *w, listFormStamp)
               {
                   w->close();
               }
               listFormStamp.clear();
}
bool formMain::loadFile(const QFileInfo &fileName)
{
    QImageReader reader(fileName.absoluteFilePath());
    reader.setAutoTransform(true);
    if (reader.read(image))
    {
        currentPathLoad=fileName.absolutePath();
        initResize();
        return true;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("do not found file.") + " : " + fileName.filePath());
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
        return false;
    }
}
void formMain::rotate()
{
    newWidthWindow=width();
    newHeightWindow=height();
    functionsWindows::rotate( angle,cor,image,myPixmap,labelPicture,&newWidthPicture,&newHeightPicture,&newWidthWindow,&newHeightWindow, WIDTHWINDOWMAINMIN, HEIGHTWINDOWMIN);
    noResizeByUser=true;
    this->resize(newWidthWindow,newHeightWindow);
}
#ifdef CALIBRATIONTHRESHOLD
void formMain::traiteSliderCalibration()
{
	int	nbLine = image->height();
	if (nbLine == 0)return;
	progressBarProcess->setMaximum(4);
	progressBarProcess->setValue(1);
	progressBarProcess->show();
	int nbColumn = image->width();
	struct oneMatrix theMatrix;
	theMatrix.pix = reinterpret_cast<bool**>(malloc(static_cast<unsigned long long>(nbColumn) * sizeof(theMatrix.pix)));
	for (int column = 0; column < nbColumn; column++)
		theMatrix.pix[column] = reinterpret_cast<bool*>(malloc(static_cast<unsigned long long>(nbLine) * sizeof(theMatrix.pix)));
    classGeneriquesFonctions::bitMapToBinary(&theMatrix, image, threshold);
	QImage  newImage(nbColumn - 1, nbLine - 1, QImage::Format_ARGB32);
	QPainter painter(&newImage);
	QRectF target(0.0, 0.0, nbColumn - 1, nbLine - 1);
	painter.fillRect(target, Qt::black);
	painter.setPen(Qt::white);
	progressBarProcess->setValue(2);
	for (int x = 0; x < nbColumn; x++)
	{
		for (int y = 0; y < nbLine; y++)
		{
			if (theMatrix.pix[x][y])
				painter.drawPoint(x,y);
		}
	}
	progressBarProcess->setValue(3);
	structFormStamp f;
	f.left = 200;
	f.top = 100;
	f.currentPathSave = currentPathSave;
	f.oneBmp = newImage;
	f.index = threshold;  //put to 0 if not display
	f.title = tr("stamp ");
	f.backColor = Qt::black;
	f.border = 0;
	formStamp *w = new formStamp(f, &currentPathSave, &ratioPerforation); 
	w->retranslateUi();
	w->show();
	progressBarProcess->setValue(4);
}
#endif
