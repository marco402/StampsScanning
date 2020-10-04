
//see https://www.walletfox.com/course/qhelpengineexample.php

#pragma once
#include <QTextBrowser>
#include <QtHelp\QHelpEngine>
#include <QWidget>
class HelpBrowser : public QTextBrowser
{
public:
	HelpBrowser(QHelpEngine* helpEngine, QWidget* parent = 0);
	QVariant loadResource(int type, const QUrl& name);
private:
	QHelpEngine* helpEngine = nullptr;
};
