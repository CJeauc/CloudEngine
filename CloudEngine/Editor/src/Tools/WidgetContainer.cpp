#include "WidgetContainer.h"
#include <QApplication>

TContainer::TContainer(QWidget* parent, QPoint p, QSize p_size, QWidget* cWidget)
	: QWidget(parent), m_mode(NONE), m_chilWidget(cWidget)
{
	setAttribute(Qt::WA_DeleteOnClose);
	this->QWidget::setVisible(true);
	setAutoFillBackground(false);
	setMouseTracking(true);
	setFocusPolicy(Qt::ClickFocus);
	setFocus();
	move(p);

	m_vLayout = new QVBoxLayout(this);
	if(cWidget != 0 )
	{
		cWidget->setParent(this);
		cWidget->releaseMouse();
		cWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		m_vLayout->addWidget(cWidget);
		m_vLayout->setContentsMargins(0, 0, 0, 0);
	}
	resize(p_size);
	setLayout(m_vLayout);
	m_inFocus = true;
	m_showMenu = false;
	m_isEditing = true;
	installEventFilter(parent);
}

TContainer::~TContainer()
{
	delete m_vLayout;
}

void TContainer::setChildWidget(QWidget* cWidget)
{
	if(cWidget != 0)
	{
		m_chilWidget = cWidget;
		m_chilWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		m_chilWidget->setParent(this);
		m_vLayout->addWidget(cWidget);
		m_vLayout->setContentsMargins(0, 0, 0, 0);
	}
}

void TContainer::popupShow(const QPoint& pt)
{
	if (m_menu->isEmpty())
		return;
	QPoint global = this->mapToGlobal(pt);
	m_showMenu = true;
	m_menu->exec(global);
	m_showMenu = false;
}

void TContainer::focusInEvent(QFocusEvent*)
{
	m_inFocus = true;
	parentWidget()->installEventFilter(this);
	parentWidget()->repaint();
	emit inFocus(true);
}

void TContainer::focusOutEvent(QFocusEvent*)
{
	if (!m_isEditing) return;
	if (m_showMenu) return;
	m_mode = NONE;
	emit outFocus(false);
	m_inFocus = false;
}
bool TContainer::eventFilter(QObject *p_obj, QEvent *p_event)
{
	if(m_inFocus)
	{
		QWidget *widget = this->parentWidget();
		if(widget == p_obj &&p_event->type() == QEvent::Paint)
		{
			QPainter painter(widget);
			QPoint p = this->mapTo(widget, QPoint(-3, -3));
			QPoint LT = widget->mapFrom(widget, p);
			QPoint LB = widget->mapFrom(widget, QPoint(p.x(), p.y() + this->height()));
			QPoint RB = widget->mapFrom(widget, QPoint(p.x() + this->width(), p.y() + this->height()));
			QPoint RT = widget->mapFrom(widget, QPoint(p.x() + this->width(), p.y()));

			painter.fillRect(LT.x(), LT.y(), 4, 4, QColor("black"));
			painter.fillRect(RB.x(), RB.y(), 4, 4, QColor("black"));
		
			return QWidget::eventFilter(p_obj, p_event); 
		}
	}
	return QWidget::eventFilter(p_obj, p_event);	
}

void TContainer::mousePressEvent(QMouseEvent *p_event)
{
	m_position = QPoint(p_event->globalX() - geometry().x(), p_event->globalY() - geometry().y());
	if (!m_isEditing) 
		return;
	
	if (!m_inFocus)
		return;
	if(!p_event->buttons() && Qt::LeftButton)
	{
		setCursorShape(p_event->pos());
		return;
	}
	if (!p_event->buttons() && Qt::RightButton)
	{
		popupShow(p_event->pos());
		p_event->accept();
	}
}

void TContainer::keyPressEvent(QKeyEvent *p_event)
{
	if (!m_isEditing)
		return;
	if(p_event->key() == Qt::Key_Delete)
		this->deleteLater();

	if(QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		QPoint newPos(this->x(), this->y());
		if (p_event->key() == Qt::Key_Up)
			newPos.setY(newPos.y() - 1);
		if (p_event->key() == Qt::Key_Down)
			newPos.setY(newPos.y() + 1);
		if (p_event->key() == Qt::Key_Left)
			newPos.setX(newPos.x() - 1);
		if (p_event->key() == Qt::Key_Right)
			newPos.setX(newPos.x() + 1);
	}
	if (QApplication::keyboardModifiers() == Qt::ShiftModifier)
	{
		if (p_event->key() == Qt::Key_Up)
			resize(width(), height() - 1);
		if (p_event->key() == Qt::Key_Down)
			resize(width(), height() + 1);
		if (p_event->key() == Qt::Key_Left)
			resize(width() - 1, height());
		if (p_event->key() == Qt::Key_Right)
			resize(width() + 1, height());
	}
	emit newGeometry(this->geometry());
}

void TContainer::setCursorShape(const QPoint& e_pos)
{
	const int diff = 5;
	if(	
		((e_pos.y() > y() + height() - diff) && (e_pos.x() < x() + diff)) ||

		((e_pos.y() > y() + height() - diff) && (e_pos.x() > x() + width() - diff)) ||
		
		((e_pos.y() < y() + diff) && (e_pos.x() < x() + diff)) ||

		((e_pos.y() < y() + diff) && (e_pos.x() > x() + width() - diff))
		)

	{
		if(	(e_pos.y() > y() + height() - diff) &&
			(e_pos.x() < x() + diff))
		{
			m_mode = RESIZEBL;
			setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		if ((e_pos.y() > y() + height() - diff) &&
			(e_pos.x() > x() + width() - diff))
		{
			m_mode = RESIZEBR;
			setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		if ((e_pos.y() < y() + diff) &&
			(e_pos.x() < x() + diff))
		{
			m_mode = RESIZETL;
			setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		if ((e_pos.y() < y() + diff) &&
			(e_pos.x() > x() + width() - diff))
		{
			m_mode = RESIZETR;
			setCursor(QCursor(Qt::SizeBDiagCursor));
		}
	}
	else if ((e_pos.x() < x() + diff) ||
			((e_pos.x() > x() + width() - diff)))
	{
		if(e_pos.x() < x() +diff)
		{
			setCursor(QCursor(Qt::SizeHorCursor));
			m_mode = RESIZEL;
		}
		else
		{
			setCursor(QCursor(Qt::SizeHorCursor));
			m_mode = RESIZER;	
		}
	}
	else if (((e_pos.y() > y() + height() - diff)) ||
		(e_pos.y() < y() + diff))
	{
		if (e_pos.y() < y() + diff)
		{
			setCursor(QCursor(Qt::SizeVerCursor));
			m_mode = RESIZET;
		}
		else
		{
			setCursor(QCursor(Qt::SizeVerCursor));
			m_mode = RESIZEB;
		}
	}
	else
	{
		setCursor(QCursor(Qt::ArrowCursor));
		m_mode = MOVE;
	}
}

void TContainer::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
}

void TContainer::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
	if (!m_isEditing) 
		return;
	if (!m_inFocus)
		return; 
	if(!event->buttons() && Qt::LeftButton)
	{
		QPoint p = QPoint(event->x() + geometry().x(), event->y() + geometry().y());
		setCursorShape(p);
		return;
	}
	if((m_mode == MOVE || m_mode == NONE) && event->buttons() && Qt::LeftButton)
	{
		QPoint toMove = event->globalPos() - m_position;
		if (toMove.x() < 0) return;
		if (toMove.y() < 0) return;
		if (toMove.x() > this->parentWidget()->width() - this->width()) return;

		move(toMove);
		emit newGeometry(this->geometry());
		this->parentWidget()->repaint();
		return;
	}
	if((m_mode != MOVE) && event->buttons() && Qt::LeftButton)
	{
		switch(m_mode)
		{
		case RESIZETL:
			{
			int newWidth = event->globalX() - m_position.x() - geometry().x();
			int newHeight = event->globalY() - m_position.y() - geometry().y();
			QPoint toMove = event->globalPos() - m_position;
			resize(this->geometry().width() - newWidth, this->geometry().height() - newHeight);
			move(toMove.x(), toMove.y());
			break;
			}
		case RESIZETR:
		{
			int newHeight = event->globalY() - m_position.y() - geometry().y();
			QPoint toMove = event->globalPos() - m_position;
			resize(event->x(), this->geometry().height() - newHeight);
			move(this->x(), toMove.y());
			break;
		}
		case RESIZEBL:
			{
			int newWidth = event->globalX() - m_position.x() - geometry().x();
			QPoint toMove = event->globalPos() - m_position;
			resize(this->geometry().width() - newWidth, event->y());
			move(toMove.x(), this->y());
			break;
			}
		case RESIZEB:
			{				
			resize(width(), event->y());
			break;
			}
		case RESIZEL:
			{
			int newWidth = event->globalX() - m_position.x() - geometry().x();
			QPoint toMove = event->globalPos() - m_position;
			resize(this->geometry().width() - newWidth, height());
			move(toMove.x(), this->y());
			break;
			}
		case RESIZET :
			{
			int newHeight = event->globalY() - m_position.y() - geometry().y();
			QPoint toMove = event->globalPos() - m_position;
			resize(width(), this->geometry().height() - newHeight);
			move(this->x(), toMove.y());
			break;
			}
		case RESIZER:
			{
			resize(event->x(), height());
			break;
			}
		case RESIZEBR:
			{
			resize(event->x(), event->y());
			break;
			}
		}
		this->parentWidget()->repaint();
	}
	emit newGeometry(this->geometry());
}











