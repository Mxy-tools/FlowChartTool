#pragma once

#include <QGraphicsView>
#include "flowchart_graphics_item.h"
#include "flowchar_graphics_link.h"
#include <QObject>
#include "flowchart_global.h"
#include <QMenu>

class FlowchartView : public QGraphicsView
{
	Q_OBJECT

public:
	FlowchartView(QGraphicsScene *parent = nullptr);
	~FlowchartView();
	
	void RegistryMenu(ItemType _menu_type, QMenu * _menu);

	void SetMouseModel(FlowchartCursor _type);

protected:
	virtual void mousePressEvent(QMouseEvent *event);

	virtual void mouseReleaseEvent(QMouseEvent *event);

	virtual void mouseMoveEvent(QMouseEvent *event);

	virtual void contextMenuEvent(QContextMenuEvent *event);

	virtual void wheelEvent(QWheelEvent* event);

private:


private:
	QCursor						hand_cursor_;
	QPoint						mouse_press_point_;
	QPoint						mouse_move_point_;
	bool						is_move_ = false;
	bool						right_press_ = false;
	QMap<ItemType, QMenu*>		menus_;
	double						view_scale_;
};
