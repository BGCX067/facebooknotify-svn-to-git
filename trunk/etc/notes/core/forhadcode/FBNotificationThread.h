#ifndef FBNOTIFICATIONTHREAD_H
#define FBNOTIFICATIONTHREAD_H

#include <qthread.h>
#include "FBNotifyKernel.h"
#include <qstring.h>
#include <qprocess.h>
#include "Logger.h"

class FBNotificationThread : public QThread
{
public:
	FBNotificationThread(Logger * log);
	~FBNotificationThread(void);


public:

	QString api_key;
	QString secret;
	QString auth_token;
	QString session_key;
	QString uid;
	QString session_secret;

	bool active;

	bool notifyWallPosts;
	bool notifyMessages;
	bool notifyPokes;
	bool notifyPhotoComments;

public:

	bool login();
	void browserLogin(QString, QString);
	void run();
	void pollPause();

protected:

	Logger * log;

	FBNotifyKernel * kernel;
	int maxGetSessionAttempts;
	int getSessionSleep;



};

#endif
