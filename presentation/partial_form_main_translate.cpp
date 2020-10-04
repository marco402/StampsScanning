// **************************************************************************************
//								StampScanning 
// **************************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// Attribution-NonCommercial-ShareAlike 4.0 International License
// http://creativecommons.org/licenses/by-nc-sa/4.0/
//
// File:partial_form_main_translate.cpp
// Written by Marc Prieur (marco40_github@sfr.fr)
//
//History : V1.00 2020-09-01 - First release
//
//
// All text above must be included in any redistribution.
//
// **********************************************************************************

//see wiki.qt.io/How_to_create_a_multi_language_application
//*******************************************************************************
//update language
	//1-modifie program
	//2-from QT creator tools->extern->linguist->lupdate or console 
	//3-from visual studio QT vs tools or start menu windows start QT->linguist
		//load one or more languages
		//modifie them
		//save
	//4-from QT creator tools->extern->linguist->lrelease
    //5-transfert the files stampscanning_*.qm  in the exe(s) and delivery directory + /languages
//********************************************************************************

#include "form_main.h"
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QLayout>
#include <QImageReader>
void formMain::changeEvent(QEvent* event)
{
    if(nullptr != event) {
        switch(event->type()) {
        case QEvent::LanguageChange:
            retranslateUi();
            break;
        case QEvent::LocaleChange:
        {
            QString locale = QLocale::system().name();
            locale.truncate(locale.lastIndexOf('_'));
            loadLanguage(locale);
        }
            break;
        }
 }
 QMainWindow::changeEvent(event);
}
void formMain::slotLanguageChanged(QAction* action)
{
 if(nullptr != action) {
    loadLanguage(action->data().toString());
    setWindowIcon(action->icon());
    currentLanguage=action->data().toString();
    }
}
void formMain::retranslateUi()
{
     openAct->setText(tr("&Open..."));
     rotateAct->setText(tr("&Rotate..."));
     runAct->setText(tr("&Run..."));
     closeAllAct->setText(tr("&CloseAll..."));
     bordureAct->setText(tr("&Border..."));
     stopAct->setText(tr("&Stop..."));
	 helpAct->setText(tr("Help Contents"));
	 aboutAction->setText(tr("&About"));
	 labStatusBar->setText(tr("Open a scan stamp file"));    //
	 //if (formHelp != nullptr)
		// createHelpWindow();
}
void formMain::switchTranslator(QTranslator& translator, const QString& filename)
{
 // remove the old translator
 qApp->removeTranslator(&translator);

 // load the new translator
QString path = QApplication::applicationDirPath();
    path.append("/languages/");

 if(translator.load(path + filename)) //Here Path and Filename has to be entered because the system didn't find the QM Files else
        qApp->installTranslator(&translator);

}
void formMain::loadLanguage(const QString& rLanguage)
{
  if(m_currLang != rLanguage) {
  m_currLang = rLanguage;
  QLocale locale = QLocale(m_currLang);
  QLocale::setDefault(locale);
  QString languageName = QLocale::languageToString(locale.language());
  formMain::switchTranslator(m_translator, QString("stampscanning_%1.qm").arg(rLanguage));
  formMain::switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
  }
}
void formMain::createLanguageMenu()
{
    QActionGroup* langGroup = new QActionGroup(menuLanguage);
    langGroup->setExclusive(true);
    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));
    // format systems language
    QString defaultLocale ="en_EN";  // QLocale::system().name(); put en_EN because text in code is English and my PC langage is french.
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));
    m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/languages");
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("stampscanning_*.qm"));
    for (int i = 0; i < fileNames.size(); ++i) {
          QString locale;
         locale = fileNames[i];
         locale.truncate(locale.lastIndexOf('.'));
         locale.remove(0, locale.indexOf('_') + 1);
        QString lang = QLocale::languageToString(QLocale(locale).language());
        QString pathIcon=QString("%1/%2.png").arg(m_langPath).arg(locale);
        QIcon ico(pathIcon);
        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(locale);
        menuLanguage->addAction(action);
        langGroup->addAction(action);
        if (currentLanguage.isEmpty())
        {
            if (defaultLocale == locale)
            {
                action->setChecked(true);
                currentLanguage= locale;
            }
        }
        else if (currentLanguage == locale)
            action->setChecked(true);
    }
}
