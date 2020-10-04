// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:form_help.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************

//see https://flylib.com/books/en/2.18.1/using_qtextbrowser_as_a_simple_help_engine.html
//see https://www.walletfox.com/course/qhelpengineexample.php
//*******************************************************************************************
//for modification help file:
	//1-edit help file with open office writer   help_" + currentLanguage + ".html"
	//2-for each language in a console
        //...\StampsScanning\help > your Path QT \bin\qhelpgenerator.exe stampsScanning_
															//+ currentLanguage + .qhcp
		//	Reading collection config file...
		//	Generating help for stampsScanning_fr.qhp...
		//	Building up file structure...
		//	Insert custom filters...
		//	Insert help data for filter section(1 of 1)...
		//	Insert files...
		//	Insert contents...
		//	Insert indices...
		//	Documentation successfully generated.
		//	Creating collection file...
    //3-transfert the files *.qhc et *.qch in the exe and delivery directory + /help
//***********************************************************************************************
#include "form_help.h"
#include <QtHelp\QHelpEngine>
#include <QTextBrowser>
#include <QSplitter>
#include "helpBrowser.h"
#include <QVBoxLayout>
#include <QDockWidget>
formHelp::formHelp(QString currentLanguage) {
	//if (formHelp != nullptr)
	//	helpWindow->close();
	this->setWindowTitle(tr("help")+ " StampsScanning");
	QString pathHelp = QApplication::applicationDirPath() + "/help";

	QHelpEngine *helpEngine = new QHelpEngine(pathHelp + "/StampsScanning_" + currentLanguage + ".qhc");
	helpEngine->setupData();

	//QTabWidget* tWidget = new QTabWidget;
	//tWidget->setMaximumWidth(200);
	////tWidget->addTab((QWidget*)helpEngine->contentWidget(), "Contents");
	//tWidget->addTab((QWidget*)helpEngine->indexWidget(), "Contents");

	HelpBrowser *textViewer = new HelpBrowser(helpEngine);
	//qthelp= name.scheme in helpBrowser.cpp;stampsScanning=namespace and help=virtualFolder in StampsScanning_xx.qhp
	textViewer->setSource(QUrl("qthelp://stampsScanning/help/help_" + currentLanguage + ".html"));

	//connect((QWidget*)helpEngine->indexWidget(), SIGNAL(linkActivated(QUrl, QString)), textViewer, SLOT(setSource(QUrl)));

	QSplitter *horizSplitter = new QSplitter(Qt::Horizontal);
	//horizSplitter->insertWidget(0, tWidget);
	horizSplitter->insertWidget(0, textViewer);
	horizSplitter->resize(500, 400);
	horizSplitter->show();
	
	//formHelp = new QDockWidget(tr("Help"), this);
	//formHelp->setWidget(horizSplitter);
	//formHelp->show();
	//addDockWidget(Qt::BottomDockWidgetArea, formHelp);
}

