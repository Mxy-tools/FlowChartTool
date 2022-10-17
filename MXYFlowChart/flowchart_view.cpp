#include "flowchart_view.h"
#include <QApplication>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QLabel>
FlowchartView::FlowchartView(QGraphicsScene *parent)
	: QGraphicsView(parent)
	, view_scale_(1.0)
{
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	setRenderHint(QPainter::TextAntialiasing);
	setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
	setDragMode(QGraphicsView::RubberBandDrag);
	//setRenderHint(QPainter::Antialiasing);
	//setOptimizationFlag(QGraphicsView::DontSavePainterState);

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//设置记录光标信息
	this->setMouseTracking(true);
}

FlowchartView::~FlowchartView()
{
}

void FlowchartView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton) {
		// ! [1] 鼠标拖动相关
		SetMouseModel(FlowchartCursor::OpenHandCursor);
		right_press_ = true;
		mouse_press_point_ = event->pos();
	}

	QGraphicsView::mousePressEvent(event);
}

void FlowchartView::mouseReleaseEvent(QMouseEvent *event)
{
	QApplication::restoreOverrideCursor();
	// 设置鼠标拖动模式
	/*	三种拖拽模式：
	1、NoDrag（没有任何反应，鼠标事件将被忽略）
	2、ScrollHandDrag(光标变为指向手，然后拖动鼠标将滚动滚动条，此模式在交互和非交互模式下均有效)
	3、RubberBandDrag(将出现矩形块，拖动鼠标将设置矩形的大小，并选中矩形覆盖的所有项目，非交互视图禁用此模式)*/
	setDragMode(QGraphicsView::RubberBandDrag);
	right_press_ = false;
	QGraphicsView::mouseReleaseEvent(event);
}

void FlowchartView::mouseMoveEvent(QMouseEvent *event)
{
	QApplication::restoreOverrideCursor();
	if (right_press_) {
		is_move_ = true;
		setDragMode(QGraphicsView::NoDrag);
		SetMouseModel(FlowchartCursor::ClosedHandCursor);

		QPointF disPointF = event->pos() - mouse_press_point_;
		mouse_press_point_ = event->pos();
		this->scene()->setSceneRect(scene()->sceneRect().x() - disPointF.x(), scene()->sceneRect().y() - disPointF.y(),
			scene()->sceneRect().width(), scene()->sceneRect().height());
		this->scene()->update();
		/*QPoint move_pos = event->pos();
		QPointF dis = mapToScene(move_pos) - mapToScene(mouse_press_point_);
		QGraphicsView::translate(dis.x(), dis.y());*/
	}
	mouse_move_point_ = event->pos();
	QGraphicsView::mouseMoveEvent(event);
}

void FlowchartView::contextMenuEvent(QContextMenuEvent *event)
{
	if (is_move_) {
		is_move_ = false;
		return;
	}

	// ! [1] 根据不同的选择 显示不同的菜单
	auto * item = itemAt(event->pos());

	auto menu_exec = [=](ItemType _menu_type) {
		if (nullptr != menus_.value(_menu_type))
			menus_.value(_menu_type)->popup(event->globalPos() + QPoint(2, 2));
	};
	auto * d_item = qgraphicsitem_cast<FlowchartGraphicsRectItem*>(item);

	if (nullptr == d_item)
		menu_exec(ItemType::Nomal);
	else
	{
		switch (d_item->GetItemType()) {

		case ItemType::Rect:
		{
			menu_exec(ItemType::Rect);
			break;
		}
		case ItemType::Link:
		{
			menu_exec(ItemType::Link);
			break;
		}
		default:;
		}
	}

	QGraphicsView::contextMenuEvent(event);
}

void FlowchartView::wheelEvent(QWheelEvent* event)
{
	// ! [1] 获取当前的鼠标所在的view坐标;
	QPoint prev_viewPos = mouse_move_point_;
	// ! [2] 获取当前鼠标相对于scene的位置;
	QPointF prev_scenePos = mapToScene(prev_viewPos);
	// ! [3] 计算缩放比例 缩放界面
	scale(1 / view_scale_, 1 / view_scale_);
	if (event->angleDelta().y() > 0) {
		if (view_scale_ < 10)
			view_scale_ += 0.2;
		else
			view_scale_ = 10;
	}
	else {
		if (view_scale_ > 0.2)
			view_scale_ -= 0.2;
		else
			view_scale_ = 0.2;
	}
	//缩放
	scale(view_scale_, view_scale_);  
	//调整scene，使得scene和view一致，主要是为了排除掉scroll
	scene()->setSceneRect(mapToScene(this->rect()).boundingRect());  
	//获取缩放后的scene坐标
	QPointF scenePos = mapToScene(prev_viewPos);
	//获取缩放前后的坐标差值，即为需要进行move的位移
	QPointF disPointF = scenePos - prev_scenePos;
	//调整位置
	scene()->setSceneRect(scene()->sceneRect().x() - disPointF.x(), scene()->sceneRect().y() - disPointF.y(),
		scene()->sceneRect().width(), scene()->sceneRect().height());
	scene()->update();

}

void FlowchartView::RegistryMenu(ItemType _menu_type, QMenu * _menu)
{
	menus_.insert(_menu_type, _menu);
}

void FlowchartView::SetMouseModel(FlowchartCursor _type)
{
	QCursor cursor;
	if (_type == FlowchartCursor::ArrowCursor)
	{
		cursor = QCursor(Qt::ArrowCursor);
	}
	else if (_type == FlowchartCursor::DrawLinkCursor)
	{
		cursor = QCursor(Qt::CrossCursor);
	}
	else if (_type == FlowchartCursor::SizeAllCurSor)
	{
		cursor = QCursor(Qt::SizeAllCursor);
	}
	else if (_type == FlowchartCursor::OpenHandCursor)
	{
		cursor = QCursor(Qt::OpenHandCursor);
	}
	else if (_type == FlowchartCursor::ClosedHandCursor)
	{
		cursor = QCursor(Qt::ClosedHandCursor);
	}
	viewport()->setCursor(cursor);
}
