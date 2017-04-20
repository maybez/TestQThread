#include "MainWindow.h"
#include "WorkerThread.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonStart, &QPushButton::clicked, this, &MainWindow::OnStartThread);
	connect(ui.pushButtonStop, &QPushButton::clicked, this, &MainWindow::OnStopThread);

}

MainWindow::~MainWindow()
{
	WorkerThread::ThreadsNeedExit();

	QThread::sleep(10);
}

void MainWindow::OnStartThread()
{
	static int ThreadIndex = 0;
	++ThreadIndex;
	
	WorkerThread* workerThread = new WorkerThread(tr("Thread%1").arg(ThreadIndex),this);
	connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::OnThreadResult,Qt::QueuedConnection);      // 此函数的最后一个参数非常重要哦~~
	connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
	workerThread->start();
}

void MainWindow::OnStopThread()
{
	WorkerThread::ThreadsNeedExit();
}

void MainWindow::OnThreadResult(QString ThreadResult)
{
	ui.textBrowserLog->append(ThreadResult);
}
