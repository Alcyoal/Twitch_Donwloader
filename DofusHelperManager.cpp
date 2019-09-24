#include "DofusHelperManager.h"
#include <QDialog>
#include <QGridLayout>

DofusHelperManager::DofusHelperManager(QObject* parent)
	: QObject(parent)
{
	qRegisterMetaType<std::shared_ptr<QPixmap>>("std::shared_ptr<QPixmap>");
	qRegisterMetaType<int64_t>("int64_t");
	qRegisterMetaType<QPixmap>("QPixmap");

}

void DofusHelperManager::startApplication()
{
	QDialog dlg_selection_screens;
	dlg_selection_screens.setMinimumHeight(600);
	dlg_selection_screens.setMinimumWidth(600);
	QGridLayout* grid_layout = new QGridLayout();
	m_screensDisplaySections.clear();
	ScreenshotProviderSelectionScreen screenshotProvider;

	for (size_t index{ 0 }; index < qApp->screens().size(); ++index)
	{
		m_screensDisplaySections.push_back(new ClickableLabel());
		m_screensDisplaySections.last()->setScaledContents(true);
		m_screensDisplaySections.last()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		m_screensDisplaySections.last()->setStyleSheet("border: 5px solid white");
		QObject::connect(m_screensDisplaySections.last(), &ClickableLabel::notifyClicked, this, &DofusHelperManager::receiveLabelClicked);
		grid_layout->addWidget(m_screensDisplaySections.last(), index%2, index/2);
	}

	dlg_selection_screens.setLayout(grid_layout);
	QObject::connect(&screenshotProvider, &ScreenshotProviderSelectionScreen::notifyScreenshot, this, &DofusHelperManager::receiveScreenshot);
	screenshotProvider.start();
	dlg_selection_screens.exec();
	m_screensDisplaySections.clear();
	QObject::disconnect(&screenshotProvider, &ScreenshotProviderSelectionScreen::notifyScreenshot, this, &DofusHelperManager::receiveScreenshot);
	screenshotProvider.setInterruptRequest(true);
	screenshotProvider.wait();
}

void DofusHelperManager::receiveLabelClicked()
{
	ClickableLabel* senderLabel = static_cast<ClickableLabel*>(sender());
	for (ClickableLabel* currentLabel : m_screensDisplaySections)
	{
		if (currentLabel == senderLabel)
		{
			currentLabel->setStyleSheet("border: 5px solid blue");
			// Set property screen selected
		}
		else
		{
			currentLabel->setStyleSheet("border: 5px solid white");
		}
	}
}

void DofusHelperManager::receiveScreenshot(int64_t indexScreen, const QPixmap& screenshot)
{
	if (indexScreen >= m_screensDisplaySections.size()) return;
	m_screensDisplaySections[indexScreen]->setPixmap(screenshot);
}
