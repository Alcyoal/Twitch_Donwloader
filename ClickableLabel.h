#pragma once
#include <qlabel.h>

class ClickableLabel : public QLabel
{
	Q_OBJECT

public :
	ClickableLabel(QWidget* parent = nullptr);

Q_SIGNALS:
	void notifyClicked();

protected:
	void mousePressEvent(QMouseEvent* event) override;

};

