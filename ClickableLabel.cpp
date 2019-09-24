#include "ClickableLabel.h"
#include <QMouseEvent>


ClickableLabel::ClickableLabel(QWidget* parent)
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
	if (event->type() == Qt::RightButton)
	{
		Q_EMIT notifyClicked();
	}
}
