#pragma warning( push )
#pragma warning( disable : 26439)
#pragma warning( disable : 26495 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26498 )
#include <QtWidgets/QApplication>
#include <utility>
#include <string>
#include <QQmlEngine>
#include <QQmlContext>
#include <opencv2/opencv.hpp>
#include "DofusHelperManager.h"
#pragma warning( pop )


int main(int argc, char *argv[])
{ 
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);

	DofusHelperManager dofus_manager;
	dofus_manager.startApplication();
	/*HostWindowQML container;

	container.engine()->rootContext()->setContextProperty("ui_injectedSignaler", &signaler);
	container.engine()->rootContext()->setContextProperty("ui_hostWindow", &container);
	 
	container.setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | container.windowFlags());
	container.setWindowModality(Qt::NonModal);
	container.setResizeMode(QQuickWidget::SizeRootObjectToView);
	container.setGeometry(0, 0, 290, 500);
	container.setSource(QUrl::fromLocalFile("MasterView.qml"));
	container.show();*/

	return a.exec();
}
