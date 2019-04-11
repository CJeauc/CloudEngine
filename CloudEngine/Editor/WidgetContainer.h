#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QtGui>
#include <QVBoxLayout>
#include <QMenu>

enum modes
{
	NONE		= 0,
	MOVE		= 1,
	RESIZETL	= 2,
	RESIZET		= 3,
	RESIZETR	= 4,
	RESIZER		= 5,
	RESIZEBR	= 6,
	RESIZEB		= 7,
	RESIZEBL	= 8,
	RESIZEL		= 9
};

class TContainer : public QWidget
{
	Q_OBJECT

public:
	TContainer(QWidget *parent, QPoint p, QSize p_size, QWidget* cWidget = 0);
	~TContainer();

	void setChildWidget(QWidget *cWidget);
protected:
	void setCursorShape(const QPoint &e_pos);
	void keyPressEvent(QKeyEvent* event) override;
	void focusInEvent(QFocusEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void popupShow(const QPoint &pt);
	QWidget* clone();

	bool eventFilter(QObject *p_obj, QEvent *p_event);

signals:
	void inFocus(bool p_mode);
	void outFocus(bool p_mode);
	void newGeometry(QRect rect);

protected:
	int m_mode;
	QPoint m_position;
	QVBoxLayout *m_vLayout;
	bool m_inFocus;
	bool m_showMenu;
	bool m_isEditing;
	
public:
	QWidget *m_chilWidget;
	QMenu *m_menu;
};