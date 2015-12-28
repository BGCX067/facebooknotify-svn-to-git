//	fbNotify: A Facebook notification system.
//	Copyright (C) 2006 fbNotify Team.
//
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along
//	with this program; if not, write to the Free Software Foundation, Inc.,
//	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "FBNConfigurationWindow.h"
#include "../kernel/facebook.messages.h"

FBNConfigurationWindow::FBNConfigurationWindow(FBNResourceManager *rm, FBNLogger *log) : QDesktopWidget()
{
	// Create local pointer to logger and resource manager
	this->logger = log;
	this->resourceManager = rm;

#ifndef QT_NO_DEBUG
	if (log)
		this->logger->writeLine("UI.ConfigurationWindow created");
#endif

	// window stuff
#ifdef Q_OS_WIN32
	this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
#elif Q_OS_MAC
	this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint);
#else
	this->setWindowFlags(Qt::Dialog);
#endif

	this->setWindowTitle(this->resourceManager->getLocalizedString("configwindow_title", "fbNotify | Settings"));
	this->setGeometry((this->screenGeometry().width() - 600) / 2, (this->screenGeometry().height() - 450) / 2, 600, 450);
#ifndef Q_OS_WIN32
	this->setMaximumSize(600, 450);
	this->setMinimumSize(600, 450);
#endif
	QIcon icon((*rm).getAnimatedTrayIcon(0));
	this->setWindowIcon(icon);

#ifndef QT_NO_DEBUG
	if (log)
		this->logger->writeLine("UI.ConfigurationWindow configured");
#endif

	// standard buttons

	this->buttons = new QDialogButtonBox(Qt::Horizontal, this);

	this->okButton = new QPushButton(this->resourceManager->getLocalizedString("configwindow_ok", "OK"), this);
	this->okButton->setDefault(true);

	this->cancelButton = new QPushButton(this->resourceManager->getLocalizedString("configwindow_cancel", "Cancel"), this);
	QObject::connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

	this->restoreDefaultsButton = new QPushButton(this->resourceManager->getLocalizedString("configwindow_reset", "Reset"), this);
	QObject::connect(this->restoreDefaultsButton, SIGNAL(clicked()), this, SLOT(restoreDefaultsButtonClicked()));

	this->buttons->setGeometry(6, this->height() - 28, this->width() - 12, 22);
	
	this->buttons->addButton(okButton, QDialogButtonBox::AcceptRole);
	this->buttons->addButton(cancelButton, QDialogButtonBox::RejectRole);
	this->buttons->addButton(restoreDefaultsButton, QDialogButtonBox::ResetRole);
	
#ifndef QT_NO_DEBUG
	if (log)
		this->logger->writeLine("UI.ConfigurationWindow buttons created");
#endif

	// panelMaster
	this->panelMaster = new FBNConfigurationPanelMaster(this, rm);
	this->panelMaster->setGeometry(0, 0, this->width(), this->buttons->y() - 6);

#ifndef QT_NO_DEBUG
	if (log)
		this->logger->writeLine("UI.ConfigurationWindow.PanelMaster created");
#endif

	this->panel = new FBNConfigurationPanel(rm, this->panelMaster, 3);
	this->panel->setText("My Profile");
	QObject::connect(this->panel, SIGNAL(selectedChanged(bool)), this, SLOT(panelSelectedChanged(bool)));


	// loginPanel
	this->loginPanel = new FBNLoginPanel(rm, this->panelMaster, 2);
	QObject::connect(this->loginPanel, SIGNAL(selectedChanged(bool)), this, SLOT(loginPanelSelectedChanged(bool)));
	QObject::connect(this->loginPanel, SIGNAL(loginClicked()), this, SLOT(loginButtonClicked()));


	// aboutPanel
	this->aboutPanel = new FBNAboutPanel(rm, this->panelMaster, 4);
	QObject::connect(this->aboutPanel, SIGNAL(selectedChanged(bool)), this, SLOT(aboutPanelSelectedChanged(bool)));

	// notificationsPanel
	this->notificationsPanel = new FBNNotificationsPanel(rm, this->panelMaster, 0);
	QObject::connect(this->notificationsPanel, SIGNAL(selectedChanged(bool)), this, SLOT(notificationsPanelSelectedChanged(bool)));
//
//	FBNSettings set;
//	//set.setInt("Dummy", 27);
//this->notificationsPanel->load(set);

	// section heading test

	//this->test = new FBNSectionHeading("My Account", this, this->resourceManager);
	//this->test->setGeometry(210, 100, 300, 18);

	// checkbox test
//	this->testcb = new QCheckBox("&Dummy", this);
//	this->testcb->setGeometry(210, 300, 100, 18);

//test text edit
	this->testtext = new QTextBrowser(this->panel);
	this->testtext->setFrameShape(QFrame::NoFrame);
	this->testtext->setGeometry(0, 0, 300, 300);
	//this->testtext->setCurrentFont(this->resourceManager->getSmallFBNormalFont());
	//this->testtext->setTextColor(this->resourceManager->getFBDarkBlueColor());
	this->testtext->insertHtml("You have &copy;");
	//this->testtext->setFontWeight(QFont::Bold);
	//this->testtext->textCursor().insertText(" 100 ");
	//this->testtext->setFontWeight(QFont::Normal);
	//this->testtext->textCursor().insertText("new");
	//this->testtext->setFontWeight(QFont::Bold);
	//this->testtext->textCursor().insertText(" wall posts");
	//this->testtext->setFontWeight(QFont::Normal);
	//this->testtext->textCursor().insertText(".");
	// panel dummy

	this->testwarning = new FBNWarningBox("Dummy", this->panel, this->resourceManager);
	this->testwarning->setGeometry(210, 100, 300, 18);

	// test of xml
	//try
	//{

	//	facebook::Messages abc("<?xml version=\"1.0\" encoding=\"UTF-8\"?><result method=\"facebook.messages.getCount\"><unread>27</unread><total>182</total></result>");
	//	QString lol;
	//		QMessageBox::question(this, "messages", lol.setNum(abc.getUnread()), QMessageBox::Yes, QMessageBox::No);

	//}
	//catch (const QString &val) {
	//QMessageBox::question(this, "messages", val, QMessageBox::Yes, QMessageBox::No);
	//
	//}

}
FBNConfigurationWindow::~FBNConfigurationWindow(void)
{
	delete this->testwarning;
	delete this->testtext;

	delete this->okButton;
	delete this->cancelButton;
	delete this->restoreDefaultsButton;
	delete this->buttons;

	delete this->aboutPanel;
	delete this->loginPanel;
	delete this->panel;
	delete this->notificationsPanel;
	delete this->panelMaster;



//	delete this->test;


//	delete this->testcb;

#ifndef QT_NO_DEBUG
	if (this->logger)
		this->logger->writeLine("UI.ConfigurationWindow destroyed");
#endif
}

void FBNConfigurationWindow::show()
{
	QDesktopWidget::show();
	this->notificationsPanel->setSelected(true);	
	this->activateWindow();
}
void FBNConfigurationWindow::showThenLogin()
{
	this->show();
	this->loginPanel->setSelected(true);
	this->activateWindow();
}

void FBNConfigurationWindow::showThenAbout()
{
	this->show();
	this->aboutPanel->setSelected(true);
	this->activateWindow();
}

void FBNConfigurationWindow::restoreDefaultsButtonClicked()
{
		if (QMessageBox::question(this, 
			this->resourceManager->getLocalizedString("configwindow_resetbox_title", "fbNotify | Reset Settings"),
			this->resourceManager->getLocalizedString("configwindow_resetbox_message", "Are you sure you want to reset the default settings for fbNotify?"),
			QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
		{
			this->notificationsPanel->loadDefault();
		}
}

void FBNConfigurationWindow::cancelButtonClicked()
{
	this->hide();
}
void FBNConfigurationWindow::aboutPanelSelectedChanged(bool selected)
{
	if (selected)
	{
		this->panel->setSelected(false);
		this->loginPanel->setSelected(false);

		this->notificationsPanel->setSelected(false);
	}
}
void FBNConfigurationWindow::loginPanelSelectedChanged(bool selected)
{
	if (selected)
	{
		this->aboutPanel->setSelected(false);
		this->panel->setSelected(false);

		this->notificationsPanel->setSelected(false);
	}
}

void FBNConfigurationWindow::panelSelectedChanged(bool selected)
{
	if (selected)
	{
		this->aboutPanel->setSelected(false);
		this->loginPanel->setSelected(false);

		this->notificationsPanel->setSelected(false);
	}
}
void FBNConfigurationWindow::notificationsPanelSelectedChanged(bool selected)
{
	if (selected)
	{
		this->aboutPanel->setSelected(false);
		this->panel->setSelected(false);
		this->loginPanel->setSelected(false);

	}
}
void FBNConfigurationWindow::keyPressEvent(QKeyEvent * e)
{
#ifdef Q_OS_WIN32
	if (e->key() == Qt::Key_Escape)
		this->cancelButtonClicked();
#endif
}
void FBNConfigurationWindow::loginButtonClicked()
{
	emit loginClicked();
}
void FBNConfigurationWindow::setLoginPanelEnabled(bool val)
{
	if (this->loginPanel->selected() && !val)
		this->notificationsPanel->setSelected(true);

	this->loginPanel->setEnabled(val);
}