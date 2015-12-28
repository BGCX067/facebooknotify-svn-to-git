#include "FBNotifyCore.h"

FBNotifyCore::FBNotifyCore(FBNotificationManager * m, QApplication * a, Logger * log)
{
	log->enter("FBNotifyCore::FBNotifyCore()");

	this->log = log;

	this->app = a;
	this->manager = m;
	this->thread = new FBNotificationThread(this->log);
	this->startNotificationThread();

	log->leave("FBNotifyCore::FBNotifyCore()");
}

FBNotifyCore::~FBNotifyCore(void)
{
	log->enter("FBNotifyCore::~FBNotifyCore()");
	log->leave("FBNotifyCore::~FBNotifyCore()");

}


void FBNotifyCore::startNotificationThread()
{
	log->enter("FBNotifyCore::startNotificationThread()");
	
	this->thread->start();

	this->thread->active = true;

	log->leave("FBNotifyCore::startNotificationThread()");

}
	

void FBNotifyCore::stopNotificationThread()
{
	log->enter("FBNotifyCore::stopNotificationThread()");

	this->thread->active = false;

	log->leave("FBNotifyCore::stopNotificationThread()");

}


void FBNotifyCore::shutDown()
{
	log->enter("FBNotifyCore::shutDown()");


	this->thread->active = false;
	this->thread->terminate();

	log->leave("FBNotifyCore::shutDown()");

	this->app->quit();


}