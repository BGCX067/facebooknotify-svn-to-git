#ifndef FBNOTIFYKERNEL_H
#define FBNOTIFYKERNEL_H

#include <qobject.h>
#include <qhttp.h>
#include <qsemaphore.h>
#include <qbuffer.h>
#include <qtextedit.h>
#include <qfile.h>
#include "md5.h"
#include <QDomDocument>
#include "Logger.h"
#include "include/curl/curl.h"

class FBNotifyKernel: public QObject
{
	Q_OBJECT   
public:
	FBNotifyKernel(Logger * log);
	~FBNotifyKernel(void);
	
public:

	void md5(QString, QString & );

	void initCall();

	bool get(const char * url, QString & output);
	bool post(const char * url, QString& data, QString & output);
	static bool postHTTPS(const char * url, QString & data, QString & output);
	static size_t handleCurlWrite(void *ptr, size_t size, size_t nmemb, void *userp);
	bool auth_createToken(QString , QString,  QString& );
	bool auth_getSession(QString , QString, QString , QString & , QString & , QString & );

	
private slots:
	
	void handleRequest(int, bool);
	

	

signals:
	
	void unreadMessages(int);
	void totalMessages(int);
	void wallCount(int);
	void pokeCount(int);


protected:

	QHttp *http;
    QSemaphore semaphore;
	QBuffer *buffer;
	QDomDocument xml;
	int current;
	bool success;
	int errorCode;

	QString baseURL;


	Logger * log;

	static QSemaphore static_semaphore;
	static CURL * curl;
	static CURLcode res;



};

#endif