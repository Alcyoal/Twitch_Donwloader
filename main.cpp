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
#include <opencv2/opencv.hpp>
#include <qfile.h>
#include <qstring.h>
#include <algorithm>
#include <qtextstream.h>
#pragma warning( pop )


int main(int argc, char *argv[])
{ 
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);

	DofusHelperManager dofus_manager;
	//dofus_manager.startApplication();

	
	QFile file = QFile("C:/Users/DELL/Documents/Twitch_chat_downloader/output/484915883.txt");
	QString content;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
	{
		content = file.readAll();
	}
	QStringList splittedContent = content.split("\n", QString::SkipEmptyParts);
	std::vector<uint32_t> collectionSecondsMessages;
	collectionSecondsMessages.reserve(splittedContent.size());
	for (QString& current : splittedContent)
	{
		current.replace("[", "&");
		current.replace("]", "&");
		QStringList cuttedPieces = current.split("&", QString::SkipEmptyParts);
		if (cuttedPieces.size() == 0) {
			continue;
		}
		QStringList timingPieces = cuttedPieces[0].split(":", QString::SkipEmptyParts);
		if (timingPieces.size() != 3){
			continue;
		}
		uint32_t seconds = timingPieces[0].toUInt() * 60 * 60;
		seconds += timingPieces[1].toUInt() * 60 ;
		seconds += timingPieces[2].toUInt();
		collectionSecondsMessages.push_back(seconds);
	}
	
	int max_element = *std::max_element(collectionSecondsMessages.cbegin(), collectionSecondsMessages.cend());
	std::vector<uint32_t> distributionValues;
	distributionValues.resize((max_element / 15) + 1);
	std::fill(distributionValues.begin(), distributionValues.end(), 0);
	for (const uint32_t& currentValue : collectionSecondsMessages)
	{
		distributionValues[currentValue / 15]++;
	}

	cv::Mat image = cv::Mat(100, distributionValues.size(), CV_8UC1);
	for (int j = 0; j < image.rows; j++)
	{
		for (int i = 0; i < image.cols; i++)
		{
			image.at<uchar>(j, i) = distributionValues[i]; //white
		}
	}
	
	cv::Mat sobelx;
	cv::Sobel(image, sobelx, CV_64F, 1, 0, 3, 0.3);
	cv::convertScaleAbs(sobelx, sobelx);
	
	for (int j = 0; j < sobelx.rows; j++)
	{
		for (int i = 0; i < sobelx.cols; i++)
		{
			sobelx.at<uchar>(j, i) = sobelx.at<uchar>(j, i) > 100 ? 255 : 0;
		}
	}
	
	cv::Mat labels;
	cv::Mat stats;
	cv::Mat centroids;
	cv::connectedComponentsWithStats(sobelx, labels, stats, centroids);
	std::vector<int> positions_x;
	for (int i = 0; i < stats.rows; i++)
	{
		positions_x.push_back(stats.at<int>(cv::Point(0, i)));
	}
	const QString template_string = "concat_win.exe -vod=\"484915883\" -start=\"%1 %2 %3\" -end=\"%4 %5 %6\" -max-concurrent-downloads 5 -download-path=\"C:/Users/DELL/Documents/Twitch_chat_downloader/output2/%7\"";
	QStringList scriptSplitted;
	for (int current : positions_x)
	{
		int seconds = current * 15;
		int start_seconds = std::max(seconds - 60, 0);
		int start_hour = start_seconds / 3600;
		start_seconds = start_seconds % 3600;
		int start_min = start_seconds / 60;
		start_seconds = start_seconds % 60;
		
		int stop_seconds = std::min(seconds + 60, max_element);
		int stop_hour = stop_seconds / 3600;
		stop_seconds = stop_seconds % 3600;
		int stop_min = stop_seconds / 60;
		stop_seconds = stop_seconds % 60;

		QString parsed = template_string.arg(start_hour).arg(start_min).arg(start_seconds).arg(stop_hour)
			.arg(stop_min).arg(stop_seconds).arg("Video_" + QString::number(scriptSplitted.size()));
		scriptSplitted.push_back(parsed);
	}
	QString scriptString = scriptSplitted.join("\n");
	QString filename = "Data_doublelift.txt";
	QFile file2(filename);
	if (file2.open(QIODevice::ReadWrite)) {
		QTextStream stream(&file2);
		stream << scriptString;
	}
	cv::imwrite("doublelift_gradient.bmp", sobelx);

	return a.exec();
}
