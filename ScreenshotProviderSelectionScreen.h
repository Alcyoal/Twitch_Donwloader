#pragma once
#include <QThread>
#include <qapplication.h>
#include <memory>
#include <QPixmap>

class ScreenshotProviderSelectionScreen : public QThread
{
	Q_OBJECT

public:
	ScreenshotProviderSelectionScreen( QObject* parent = nullptr);
	void run() override;
	void setInterruptRequest(bool isInterrupt);

Q_SIGNALS:	
	void notifyScreenshot(int64_t indexScreen, const QPixmap& screenshot);

private:
	std::atomic<bool> m_isIntteruptRequested{ false };
};

