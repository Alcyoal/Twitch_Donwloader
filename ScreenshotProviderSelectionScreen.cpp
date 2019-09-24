#include "ScreenshotProviderSelectionScreen.h"
#include <iostream>
#include <QScreen>
#include <opencv2/opencv.hpp>

ScreenshotProviderSelectionScreen::ScreenshotProviderSelectionScreen(QObject* parent)
	: QThread(parent)
{
}

void ScreenshotProviderSelectionScreen::run()
{
	while (!m_isIntteruptRequested)
	{
		int64_t index_screen{ -1 };
		for (const auto screen : qApp->screens())
		{
			++index_screen;
			if (screen == nullptr) continue;
			QThread::msleep(25);
			Q_EMIT notifyScreenshot(index_screen, screen->grabWindow(0));
		}
	}
}

void ScreenshotProviderSelectionScreen::setInterruptRequest(bool isInterrupt)
{
	m_isIntteruptRequested = isInterrupt;
}
