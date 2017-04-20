#pragma once

#include <QThread>

class WorkerThread : public QThread
{
	Q_OBJECT

public:
	WorkerThread(QString id,QObject *parent = 0);
	~WorkerThread();

	static void ThreadsNeedExit();

protected:
	void run() Q_DECL_OVERRIDE;

private:
	static bool NeedExit;
	QString ThreadID;

signals:
	void resultReady(const QString &s);
};


