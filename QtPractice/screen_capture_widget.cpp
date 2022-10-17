#include "screen_capture_widget.h"

std::vector<QRect> allWindowRect;       //存放窗口矩形
std::vector<HWND> allWindowHwnd;		//存放窗口句柄
std::vector<MyRect> myRectRestlt;

bool CALLBACK MyEnumWindowsProc(HWND _hwnd, LPARAM _lparam);

ScreenCaptureWidget::ScreenCaptureWidget(QWidget* parent)
	: QDialog(parent)
	, mouse_finish_(false)
{
	this->setWindowModality(Qt::WindowModal);
	//this->setWindowFlags(Qt::WindowContextHelpButtonHint);
	this->setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
	//默认鼠标移动进入鼠标移动响应函数
	this->setMouseTracking(true);

	::EnumWindows((WNDENUMPROC)MyEnumWindowsProc, 0);
}

ScreenCaptureWidget::~ScreenCaptureWidget()
{
}

void ScreenCaptureWidget::ScreenCapture()
{
	// qt5.9.1支持
	//show_top_pixmap_ = QScreen::grabWindow(QApplication::desktop()->winId());
	show_top_pixmap_ = QGuiApplication::primaryScreen()->grabWindow();
}

void ScreenCaptureWidget::CalculataRectDistance(QRect rect)
{
	int dis = rect.width() + rect.height();
	MyRect temp_myrect;
	temp_myrect.myRect_ = rect;
	temp_myrect.distance_ = dis;
	myRectRestlt.push_back(temp_myrect);
}

void ScreenCaptureWidget::DrawFruitRectStyle(QPainter* _painter, QPoint& _begion_point, QPoint& _end_point)
{
	int radius_roll = 4;
	int x1 = _begion_point.x();
	int y1 = _begion_point.y();
	int x2 = _end_point.x();
	int y2 = _end_point.y();
	QVector<QPoint> points;
	points.push_back(QPoint(x1, y1));
	points.push_back(QPoint((x1 + x2) / 2, y1));
	points.push_back(QPoint(x2, y1));
	points.push_back(QPoint(x2, (y1 + y2) / 2));
	points.push_back(QPoint(x2, y2));
	points.push_back(QPoint((x1 + x2) / 2, y2));
	points.push_back(QPoint(x1, y2));
	points.push_back(QPoint(x1, (y1 + y2) / 2));
	_painter->setBrush(Qt::blue);
	for (int i = 0; i < 8; i++)
	{
		_painter->drawEllipse(points.at(i), radius_roll, radius_roll);
	}
}

void ScreenCaptureWidget::DrawSlidRect(QPainter* _painter)
{
	//绘制截取区域
	QRect selected_rect = GetRect(mouse_result_begin_point_, mouse_result_end_point_);
	pixmap_ = show_top_pixmap_.copy(selected_rect);
	_painter->drawPixmap(selected_rect.topLeft(), pixmap_);
	if (mouse_finish_)
	{
		DrawFruitRectStyle(_painter, mouse_result_begin_point_, mouse_result_end_point_);
	}
	else
	{
		QPen pen_rect;
		pen_rect.setColor(Qt::yellow);
		pen_rect.setWidth(2);
		_painter->setPen(pen_rect);
		QRect rect(mouse_result_begin_point_, mouse_result_end_point_);
		_painter->drawRect(rect);
	}
	//截取区域大小信息
	QString pixmap_size = QString::number(selected_rect.width()) + " X " + QString::number(selected_rect.height());
	QColor information_color = QColor(0, 0, 0, 150);
	QFontMetrics fm(_painter->font());
	QRect fm_rect = fm.boundingRect(pixmap_size);
	QRect pixmap_size_rect(selected_rect.topLeft().x(), selected_rect.topLeft().y() - 20, fm_rect.width() + 5, 20);
	_painter->fillRect(pixmap_size_rect, information_color);
	_painter->drawText(pixmap_size_rect, Qt::AlignCenter, pixmap_size);
}

QRect ScreenCaptureWidget::GetRect(const QPoint& _begin_Point, const QPoint& _end_Point)
{
	int x, y, width, height;
	width = qAbs(_begin_Point.x() - _end_Point.x());
	height = qAbs(_begin_Point.y() - _end_Point.y());
	x = _begin_Point.x() < _end_Point.x() ? _begin_Point.x() : _end_Point.x();
	y = _begin_Point.y() < _end_Point.y() ? _begin_Point.y() : _end_Point.y();
	QRect selected_rect = QRect(x, y, width, height);									//QRect类代表一个矩形区域
	if (selected_rect.width() == 0)
	{
		selected_rect.setWidth(1);
	}
	if (selected_rect.height() == 0)
	{
		selected_rect.setHeight(1);
	}
	return selected_rect;
}

void ScreenCaptureWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_finish_ = true;
	}
	update();
}

void ScreenCaptureWidget::mouseReleaseEvent(QMouseEvent* event)
{
	QDialog::mouseReleaseEvent(event);
	update();
}

void ScreenCaptureWidget::mouseMoveEvent(QMouseEvent* event)
{
	mouse_now_point_ = event->pos();
	myRectRestlt.clear();
	for (std::vector<QRect>::iterator it = allWindowRect.begin() + 1; it != allWindowRect.end(); it++)
	{
		if (it->contains(mouse_now_point_.x(), mouse_now_point_.y()))
		{
			CalculataRectDistance(*it);
		}
	}
	MyRect temp_myrect;
	for (std::vector<MyRect>::iterator it = myRectRestlt.begin() + 1; it != myRectRestlt.end(); it++)
	{
		if (it->distance_ < temp_myrect.distance_)
		{
			temp_myrect = *it;
		}
		mouse_result_begin_point_ = temp_myrect.myRect_.topLeft();
		mouse_result_end_point_ = temp_myrect.myRect_.bottomRight();
	}
	update();
}

void ScreenCaptureWidget::paintEvent(QPaintEvent* event)
{
	QPainter* painter = new QPainter(this);

	QColor shadowColor = QColor(0, 0, 0, 100);											//阴影色
	painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));					//设置画笔
	painter->drawPixmap(0, 0, show_top_pixmap_);										//将获取的图片画到窗体上
	painter->fillRect(show_top_pixmap_.rect(), shadowColor);							//画影罩效果


	DrawSlidRect(painter);

}


bool CALLBACK MyEnumWindowsProc(HWND _hwnd, LPARAM _lparam)
{
	if (::IsWindow(_hwnd) && ::IsWindowVisible(_hwnd))
	{
		RECT tempRect;
		QRect tempQRect;
		::GetWindowRect(_hwnd, &tempRect);

		tempQRect.setTopLeft(QPoint(tempRect.left, tempRect.top));
		tempQRect.setBottomRight(QPoint(tempRect.right, tempRect.bottom));

		allWindowRect.push_back(tempQRect);
		allWindowHwnd.push_back(_hwnd);

		::EnumChildWindows(_hwnd, (WNDENUMPROC)MyEnumWindowsProc, 0);
	}
	return true;
}