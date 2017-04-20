#include "WorkerThread.h"
#include <QtMath>
#include <QTime>

WorkerThread::WorkerThread(QString id, QObject *parent /*= 0*/)
	: QThread(parent) 
	,ThreadID(id)
{
	qsrand(QTime::currentTime().msecsSinceStartOfDay());
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::ThreadsNeedExit()
{
	NeedExit = true;
}

void WorkerThread::run()
{
	int count = 0;
	while (!NeedExit)
	{
		QThread::sleep(qrand()%5);

		++count;

		emit resultReady(tr("%1:%2").arg(ThreadID).arg(count));
	}

	emit resultReady(tr("%1 is over!").arg(ThreadID));
}

bool WorkerThread::NeedExit = false;
