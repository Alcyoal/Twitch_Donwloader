#pragma once
#include <QObject>
#include "ScreenshotProviderSelectionScreen.h"
#include <QLabel>
#include <QThread>
#include <QPixmap>
#include "ClickableLabel.h"

class DofusHelperManager : public QObject 
{
	Q_OBJECT

public : 
	DofusHelperManager(QObject* parent = nullptr);

public Q_SLOTS:
	void receiveScreenshot(int64_t indexScreen, const QPixmap& screnshot);
	void startApplication();
	void receiveLabelClicked();

private:
	QVector<ClickableLabel*> m_screensDisplaySections;
};

