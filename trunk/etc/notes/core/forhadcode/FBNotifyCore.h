#ifndef FBNOTIFYCORE_H
#define FBNOTIFYCORE_H

#include <qobject.h>
#include "FBNotificationThread.h"
#include "FBNotificationManager.h"
#include <vector>
#include <qapplication.h>
#include "Logger.h"


class FBNotifyCore: public QObject
{
	Q_OBJECT 
public:

	FBNotifyCore(FBNotificationManager * m, QApplication * a, Logger * log);
	~FBNotifyCore(void);



public slots:

	void startNotificationThread();
	void stopNotificationThread();
	void shutDown();


signals:

	void newMessageNotification(int);
	void newPokeNotification(int);
	void newWallNotification(int);





protected:


	FBNotificationManager * manager;
	FBNotificationThread * thread;

	QApplication * app;
	Logger * log;
};

#endif

