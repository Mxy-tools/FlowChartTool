#include "slid_screen_capture_widget.h"


SlidScreenCaptureWidget::SlidScreenCaptureWidget(QWidget* parent)
	: mouse_slid_press_flag_(false)
	, mouse_slid_finish_(false)
	, mouse_rect_press_flag_(false)
	, color_is_show_(true)
	, pixel_color_("(0,0,0)")
{
	this->setWindowModality(Qt::WindowModal);
	this->setWindowFlags(Qt::WindowContextHelpButtonHint);
	this->setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
	//默认鼠标移动进入鼠标移动响应函数
	this->setMouseTracking(true);

	InitToolBar();
}

SlidScreenCaptureWidget::~SlidScreenCaptureWidget()
{
}

void SlidScreenCaptureWidget::ScreenCapture()
{
	show_top_pixmap_ = QGuiApplication::primaryScreen()->grabWindow();
}

QRect SlidScreenCaptureWidget::GetRect(const QPoint& _begin_Point, const QPoint& _end_Point)
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

QRgb SlidScreenCaptureWidget::GetPixmapColor(QPixmap _pixmap, QPoint _position)
{
	QImage image_ = _pixmap.toImage();
	QRgb* line_rgb = (QRgb*)image_.scanLine(_position.y());
	return line_rgb[_position.x()];
}

QPoint SlidScreenCaptureWidget::GetOffsetPoint(const QPoint& _begin_Point, const QPoint& _end_Point)
{
	return QPoint(_end_Point.x() - _begin_Point.x(), _end_Point.y() - _begin_Point.y());
}

ArrowType SlidScreenCaptureWidget::PointInRect(QPoint& _point, QRect _rect)
{
	int x1 = _rect.topLeft().x();
	int y1 = _rect.topLeft().y();
	int x2 = _rect.bottomRight().x();
	int y2 = _rect.bottomRight().y();
	int range_size = (_rect.width() ? _rect.height() : _rect.width() > _rect.height()) / 3;

	//全
	if (_point.x() >= x1 + range_size && _point.x() <= x2 - range_size && _point.y() >= y1 + range_size && _point.y() <= y2 - range_size)
		return Size_All_Cursor;
	//水平-左
	if (_point.x() >= x1 - 100 && _point.x() <= x1 + range_size && _point.y() >= y1 + range_size && _point.y() <= y2 - range_size)
		return Size_Hor_Cursor_Left;
	//水平-右
	if (_point.x() >= x2 - range_size && _point.x() <= x2 + 100 && _point.y() >= y1 + range_size && _point.y() <= y2 - range_size)
		return Size_Hor_Cursor_Right;
	//垂直-上
	if (_point.x() >= x1 + range_size && _point.x() <= x2 - range_size && _point.y() >= y1 - 100 && _point.y() <= y1 + range_size)
		return Size_Ver_Cursor_Top;
	//垂直-下
	if (_point.x() >= x1 + range_size && _point.x() <= x2 - range_size && _point.y() >= y2 - range_size && _point.y() <= y2 + 100)
		return Size_Ver_Cursor_Bottom;
	//斜下-上
	if (_point.x() >= x1 - 100 && _point.x() <= x1 + range_size && _point.y() >= y1 - 100 && _point.y() <= y1 + range_size)
		return Size_Fdiag_Cursor_Top;
	//斜下-下
	if (_point.x() >= x2 - range_size && _point.x() <= x2 + 100 && _point.y() >= y2 - range_size && _point.y() <= y2 + 100)
		return Size_Fdiag_Cursor_Bottom;
	//斜上-上
	if (_point.x() >= x2 - range_size && _point.x() <= x2 + 100 && _point.y() >= y1 - 100 && _point.y() <= y1 + range_size)
		return Size_Bdiag_Cursor_Top;
	//斜上-下
	if (_point.x() >= x1 - 100 && _point.x() <= x1 + range_size && _point.y() >= y2 - range_size && _point.y() <= y2 + 100)
		return Size_Bdiag_Cursor_Bottom;
	return Arrow_Cursor;
}


void SlidScreenCaptureWidget::Save()
{
	QString file_name = QFileDialog::getSaveFileName(this, QStringLiteral("截图文件保存"), "picture1.jpg", tr("Images(*.png,*.bmp,*.jpg)"));
	pixmap_.save(file_name);
}

QPixmap SlidScreenCaptureWidget::GetScreenPixmap()
{
	return pixmap_;
}

void SlidScreenCaptureWidget::ShowToolBar(bool _flag)
{
	if (_flag)
	{
		QPoint tool_bar_move(mouse_slid_end_point_.x() - tool_bar_->width(), mouse_slid_end_point_.y() + 10);
		tool_bar_->move(tool_bar_move);
		tool_bar_->show();
	}
	else
	{
		tool_bar_->hide();
	}
	this->update();

}

void SlidScreenCaptureWidget::InitToolBar()
{
	tool_bar_ = new QWidget(this);
	QHBoxLayout* tool_bar_layout = new QHBoxLayout();
	QVector<QPushButton*> tool_bar_buttons;
	tool_bar_buttons.push_back(new QPushButton());
	tool_bar_buttons.push_back(new QPushButton());
	tool_bar_buttons.push_back(new QPushButton());
	tool_bar_buttons.push_back(new QPushButton());
	tool_bar_buttons.push_back(new QPushButton());
	tool_bar_buttons.push_back(new QPushButton());

	for (int i = 0; i < tool_bar_buttons.size(); i++)
	{
		tool_bar_layout->addWidget(tool_bar_buttons.at(i));
		//设置菜单栏箭头样式
		tool_bar_buttons.at(i)->setCursor(Qt::ArrowCursor);
		tool_bar_buttons.at(i)->setFixedSize(40, 40);
	}

	//复制
	connect(tool_bar_buttons.at(0), &QPushButton::clicked, this, [=]() {
		QApplication::clipboard()->setPixmap(pixmap_);
		});
	//取色器
	connect(tool_bar_buttons.at(1), &QPushButton::clicked, this, [=]() {
		color_is_show_ = !color_is_show_;
		});
	//切图
	connect(tool_bar_buttons.at(2), &QPushButton::clicked, this, [=]() {
		mouse_slid_press_flag_ = false;
		mouse_slid_finish_ = false;
		this->setCursor(Qt::ArrowCursor);
		ShowToolBar(false);
		CutGraph* cut_graph = new CutGraph(this);
		cut_graphs_.push_back(cut_graph);
		cut_graph->SetPixmap(pixmap_);
		cut_graph->move(mouse_slid_begin_point_);
		});
	//保存
	connect(tool_bar_buttons.at(3), &QPushButton::clicked, this, [=]() {
		QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("保存图片"), "", tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF"));;//选择路径
		if (filename.isEmpty())
			return;
		else
		{
			if (!(pixmap_.save(filename))) //保存图像
			{

				QMessageBox::information(this, QStringLiteral("图片保存"), QStringLiteral("截屏文件保存失败！"));
				return;
			}
			QMessageBox::information(this, QStringLiteral("图片保存"), QStringLiteral("截屏文件保存成功！"));
		}
		});
	//重置
	connect(tool_bar_buttons.at(4), &QPushButton::clicked, this, [=]() {
		mouse_slid_press_flag_ = false;
		mouse_slid_finish_ = false;
		this->setCursor(Qt::ArrowCursor);
		ShowToolBar(false);
		});
	//关闭
	connect(tool_bar_buttons.at(5), &QPushButton::clicked, this, [=]() {
		close();
		});

	tool_bar_buttons.at(0)->setObjectName("screen_capture_toolbar_copy");
	tool_bar_buttons.at(1)->setObjectName("screen_capture_toolbar_color");
	tool_bar_buttons.at(2)->setObjectName("screen_capture_toolbar_cute");
	tool_bar_buttons.at(3)->setObjectName("screen_capture_toolbar_save");
	tool_bar_buttons.at(4)->setObjectName("screen_capture_toolbar_result");
	tool_bar_buttons.at(5)->setObjectName("screen_capture_toolbar_close");

	tool_bar_buttons.at(0)->setToolTip(QStringLiteral("复制"));
	tool_bar_buttons.at(1)->setToolTip(QStringLiteral("取色器"));
	tool_bar_buttons.at(2)->setToolTip(QStringLiteral("切图"));
	tool_bar_buttons.at(3)->setToolTip(QStringLiteral("保存"));
	tool_bar_buttons.at(4)->setToolTip(QStringLiteral("重置"));
	tool_bar_buttons.at(5)->setToolTip(QStringLiteral("关闭"));

	tool_bar_->setObjectName("screen_capture_toolbar");
	//内边距
	tool_bar_layout->setContentsMargins(0, 0, 0, 0);
	//子控件间距
	tool_bar_layout->setSpacing(0);
	//隐藏标题栏
	tool_bar_->setWindowFlags(Qt::FramelessWindowHint);
	tool_bar_->hide();
	//设置窗口层次
	this->stackUnder(tool_bar_);
	tool_bar_->setLayout(tool_bar_layout);
}

void SlidScreenCaptureWidget::mousePressEvent(QMouseEvent* event)
{
	//滑动获取截屏区域
	if (event->button() == Qt::LeftButton && !mouse_slid_finish_)
	{
		mouse_slid_press_flag_ = true;
		mouse_slid_begin_point_ = event->pos();
	}
	//拖动截屏区域
	if (event->button() == Qt::LeftButton && !mouse_rect_press_flag_ && mouse_slid_finish_ && PointInRect(mouse_now_point_, GetRect(mouse_slid_begin_point_, mouse_slid_end_point_)) != Arrow_Cursor)
	{
		mouse_rect_press_flag_ = true;
		mouse_rect_begin_point_ = event->pos();
		mouse_rect_end_point_ = event->pos();
		/*QRect rect_f = GetRect(mouse_slid_begin_point_, mouse_slid_end_point_);
		mouse_result_begin_point_ = rect_f.topLeft();
		mouse_result_end_point_ = rect_f.bottomRight();*/
		mouse_result_begin_point_ = mouse_slid_begin_point_;
		mouse_result_end_point_ = mouse_slid_end_point_;
	}
	update();
	return QWidget::mousePressEvent(event);
}

void SlidScreenCaptureWidget::mouseReleaseEvent(QMouseEvent* event)
{
	//滑动获取截屏区域
	if (mouse_slid_press_flag_)
	{
		mouse_slid_end_point_ = event->pos();
		mouse_slid_press_flag_ = false;
		mouse_slid_finish_ = true;
		mouse_result_begin_point_ = mouse_slid_begin_point_;
		mouse_result_end_point_ = mouse_slid_end_point_;
	}
	//拖动截屏区域
	if (mouse_rect_press_flag_)
	{
		mouse_rect_end_point_ = event->pos();
		mouse_rect_press_flag_ = false;
		mouse_slid_begin_point_ = mouse_result_begin_point_;
		mouse_slid_end_point_ = mouse_result_end_point_;
	}
	update();
	return QWidget::mouseReleaseEvent(event);
}

void SlidScreenCaptureWidget::mouseMoveEvent(QMouseEvent* event)
{
	mouse_now_point_ = event->pos();
	//滑动获取截屏区域
	if (mouse_slid_press_flag_)
	{
		mouse_slid_end_point_ = event->pos();
	}
	//拖动截屏区域
	if (mouse_rect_press_flag_)
	{
		mouse_rect_end_point_ = event->pos();
	}

	//调用该函数时会调用paintEvent函数
	update();
	return QWidget::mouseMoveEvent(event);
}

void SlidScreenCaptureWidget::keyReleaseEvent(QKeyEvent* event)
{
	//退出
	if (event->key() == Qt::Key_Escape)
	{
		close();
	}
	//保存颜色
	if (event->key() == Qt::Key_C)
	{
		QApplication::clipboard()->setText(pixel_color_);
	}
	//复制内容到剪切板
	if (event->matches(QKeySequence::Copy))
	{
		QApplication::clipboard()->setPixmap(pixmap_);
	}
	if (event->matches(QKeySequence::Save))
	{
		Save();
		mouse_slid_press_flag_ = false;
		mouse_slid_finish_ = false;
	}
	this->update();
}

void SlidScreenCaptureWidget::closeEvent(QCloseEvent* event)
{
	//关闭切图窗口
	for (int i = 0; i < cut_graphs_.size(); i++)
	{
		cut_graphs_.at(i)->close();
	}
	QDialog::closeEvent(event);
}

void SlidScreenCaptureWidget::DrawBackgroundPixmap(QPainter* _painter)
{
	QColor shadowColor = QColor(0, 0, 0, 100);											//阴影色
	_painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));					//设置画笔
	_painter->drawPixmap(0, 0, show_top_pixmap_);										//将获取的图片画到窗体上
	_painter->fillRect(show_top_pixmap_.rect(), shadowColor);							//画影罩效果
}

void SlidScreenCaptureWidget::DrawSlidRect(QPainter* _painter)
{
	//绘制截取区域
	QRect selected_rect = GetRect(mouse_slid_begin_point_, mouse_slid_end_point_);
	pixmap_ = show_top_pixmap_.copy(selected_rect);
	_painter->drawPixmap(selected_rect.topLeft(), pixmap_);
	DrawFruitRectStyle(_painter, mouse_slid_begin_point_, mouse_slid_end_point_);

	//截取区域大小信息
	QString pixmap_size = QString::number(selected_rect.width()) + " X " + QString::number(selected_rect.height());
	QColor information_color = QColor(0, 0, 0, 150);
	QFontMetrics fm(_painter->font());
	QRect fm_rect = fm.boundingRect(pixmap_size);
	QRect pixmap_size_rect(selected_rect.topLeft().x(), selected_rect.topLeft().y() - 20, fm_rect.width() + 5, 20);
	_painter->fillRect(pixmap_size_rect, information_color);
	_painter->drawText(pixmap_size_rect, Qt::AlignCenter, pixmap_size);
}

void SlidScreenCaptureWidget::DrawBoostLine(QPainter* _painter)
{
	//绘制辅助线
	QLine line_boost_x(QPoint(0, mouse_slid_end_point_.y()), QPoint(show_top_pixmap_.width(), mouse_slid_end_point_.y()));
	QLine line_boost_y(QPoint(mouse_slid_end_point_.x(), 0), QPoint(mouse_slid_end_point_.x(), show_top_pixmap_.height()));
	_painter->drawLine(line_boost_x);
	_painter->drawLine(line_boost_y);
}

void SlidScreenCaptureWidget::DrawInformationRect(QPainter* _painter)
{
	if (!color_is_show_)
	{
		return;
	}
	//绘制辅助信息框位置
	int information_x = mouse_now_point_.x() + 50;
	int information_y = mouse_now_point_.y() + 50;

	//*******************信息框--整体****************
	QRect rect_infomation(information_x, information_y, 170, 170);
	//整体颜色基调
	QColor information_color = QColor(0, 0, 0, 150);
	_painter->fillRect(rect_infomation, information_color);
	//*******************信息框--文本内容****************
	//文本：位置信息
	QRect rect_infomation_position(information_x, information_y + 110, 170, 20);
	QString text_information_position = "(" + QString::number(mouse_now_point_.x()) + "," + QString::number(mouse_now_point_.y()) + ")";
	_painter->drawText(rect_infomation_position, Qt::AlignCenter, text_information_position);

	//文本：颜色信息
	QRect rect_infomation_color(information_x, information_y + 130, 170, 20);
	//颜色显示小框
	QRect rect_infomation_color_f(information_x + 5, information_y + 135, 10, 10);
	QRgb rgb_color = GetPixmapColor(show_top_pixmap_, mouse_now_point_);
	QString text_information_color = "(" + QString::number(qRed(rgb_color)) + "  ," + QString::number(qGreen(rgb_color)) + "  ," + QString::number(qBlue(rgb_color)) + ")";
	pixel_color_ = text_information_color;
	_painter->drawText(rect_infomation_color, Qt::AlignCenter, text_information_color);
	_painter->setBrush(QColor(rgb_color));
	_painter->drawRect(rect_infomation_color_f);
	_painter->setBrush(Qt::NoBrush);

	//文本：提示信息
	QRect rect_infomation_text(information_x, information_y + 150, 170, 20);
	QString text_information_text = QStringLiteral("按C复制颜色值");
	_painter->drawText(rect_infomation_text, Qt::AlignCenter, text_information_text);

	//*******************信息框--图片区****************
	//图片框
	QRect rect_infomation_pixmap_rect(information_x, information_y, 170, 110);
	//放大图片
	QRect rect_information_pixmap(mouse_now_point_.x() - 8, mouse_now_point_.y() - 5, 17, 11);
	QPixmap information_pixmap_ = show_top_pixmap_.copy(rect_information_pixmap).scaled(170, 110, Qt::KeepAspectRatioByExpanding);
	_painter->drawPixmap(rect_infomation_pixmap_rect.topLeft(), information_pixmap_);
	//中央辅助线
	QColor information_pixmap_color = QColor(0, 0, 255, 150);
	QRect information_pixmap_x(information_x, information_y + 50, 170, 10);
	QRect information_pixmap_y(information_x + 80, information_y, 10, 110);
	_painter->fillRect(information_pixmap_x, information_pixmap_color);
	_painter->fillRect(information_pixmap_y, information_pixmap_color);
	QRect information_pixmap_f(information_x + 80, information_y + 50, 10, 10);
	_painter->setBrush(QColor(rgb_color));
	_painter->drawRect(information_pixmap_f);
	_painter->setBrush(Qt::NoBrush);
	_painter->drawRect(rect_infomation_pixmap_rect);
}


void SlidScreenCaptureWidget::DrawFruitRect(QPainter* _painter)
{
	//绘制结果矩形框
	//计算偏移
	if (mouse_rect_press_flag_)
	{
		QRect rect_f = GetRect(mouse_slid_begin_point_, mouse_slid_begin_point_);
		QPoint rect_f_begin = rect_f.topLeft();
		QPoint rect_f_end = rect_f.bottomRight();
		ArrowType flag = PointInRect(mouse_now_point_, GetRect(mouse_result_begin_point_, mouse_result_end_point_));
		int offset_x = GetOffsetPoint(mouse_rect_begin_point_, mouse_rect_end_point_).x();
		int offset_y = GetOffsetPoint(mouse_rect_begin_point_, mouse_rect_end_point_).y();
		switch (flag)
		{
		case Arrow_Cursor:
			break;
		case Size_Ver_Cursor_Top:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x(), mouse_slid_begin_point_.y() + offset_y);
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x(), mouse_slid_end_point_.y());
			break;
		case Size_Ver_Cursor_Bottom:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x(), mouse_slid_begin_point_.y());
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x(), mouse_slid_end_point_.y() + offset_y);
			break;
		case Size_Hor_Cursor_Left:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x() + offset_x, mouse_slid_begin_point_.y());
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x(), mouse_slid_end_point_.y() + offset_y);
			break;
		case Size_Hor_Cursor_Right:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x(), mouse_slid_begin_point_.y());
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x() + offset_x, mouse_slid_end_point_.y());
			break;
		case Size_All_Cursor:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x() + offset_x, mouse_slid_begin_point_.y() + offset_y);
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x() + offset_x, mouse_slid_end_point_.y() + offset_y);
			break;
		case Size_Bdiag_Cursor_Top:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x(), mouse_slid_begin_point_.y() + offset_y);
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x() + offset_x, mouse_slid_end_point_.y());
			break;
		case Size_Bdiag_Cursor_Bottom:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x() + offset_x, mouse_slid_begin_point_.y());
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x(), mouse_slid_end_point_.y() + offset_y);
			break;
		case Size_Fdiag_Cursor_Top:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x() + offset_x, mouse_slid_begin_point_.y() + offset_y);
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x(), mouse_slid_end_point_.y());
			break;
		case Size_Fdiag_Cursor_Bottom:
			mouse_result_begin_point_ = QPoint(mouse_slid_begin_point_.x(), mouse_slid_begin_point_.y());
			mouse_result_end_point_ = QPoint(mouse_slid_end_point_.x() + offset_x, mouse_slid_end_point_.y() + offset_y);
			break;
		default:
			break;
		}

	}

	//绘制截取区域
	QRect selected_rect = GetRect(mouse_result_begin_point_, mouse_result_end_point_);
	pixmap_ = show_top_pixmap_.copy(selected_rect);
	_painter->drawPixmap(selected_rect.topLeft(), pixmap_);
	DrawFruitRectStyle(_painter, mouse_result_begin_point_, mouse_result_end_point_);

	//截取区域大小信息
	QString pixmap_size = QString::number(selected_rect.width()) + " X " + QString::number(selected_rect.height());
	QColor information_color = QColor(0, 0, 0, 150);
	QFontMetrics fm(_painter->font());
	QRect fm_rect = fm.boundingRect(pixmap_size);
	QRect pixmap_size_rect(selected_rect.topLeft().x(), selected_rect.topLeft().y() - 20, fm_rect.width() + 5, 20);
	_painter->fillRect(pixmap_size_rect, information_color);
	_painter->drawText(pixmap_size_rect, Qt::AlignCenter, pixmap_size);

}

void SlidScreenCaptureWidget::DrawFruitRectStyle(QPainter* _painter, QPoint& _begion_point, QPoint& _end_point)
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

void SlidScreenCaptureWidget::DrawFruitRectIsShow(QPainter* _painter)
{
	ArrowType flag = PointInRect(mouse_now_point_, GetRect(mouse_result_begin_point_, mouse_result_end_point_));
	switch (flag)
	{
	case Arrow_Cursor:
		this->setCursor(Qt::ArrowCursor);
		break;
	case Size_Ver_Cursor_Top:
		this->setCursor(Qt::SizeVerCursor);
		break;
	case Size_Ver_Cursor_Bottom:
		this->setCursor(Qt::SizeVerCursor);
		break;
	case Size_Hor_Cursor_Left:
		this->setCursor(Qt::SizeHorCursor);
		break;
	case Size_Hor_Cursor_Right:
		this->setCursor(Qt::SizeHorCursor);
		break;
	case Size_All_Cursor:
		this->setCursor(Qt::SizeAllCursor);
		break;
	case Size_Bdiag_Cursor_Top:
		this->setCursor(Qt::SizeBDiagCursor);
		break;
	case Size_Bdiag_Cursor_Bottom:
		this->setCursor(Qt::SizeBDiagCursor);
		break;
	case Size_Fdiag_Cursor_Top:
		this->setCursor(Qt::SizeFDiagCursor);
		break;
	case Size_Fdiag_Cursor_Bottom:
		this->setCursor(Qt::SizeFDiagCursor);
		break;
	default:
		break;
	}
	if (flag && !mouse_rect_press_flag_)
	{
		DrawInformationRect(_painter);					//绘制信息框
		ShowToolBar(true);
	}
	else
	{
		ShowToolBar(false);
	}
}

void SlidScreenCaptureWidget::paintEvent(QPaintEvent* event)
{
	QPainter* painter = new QPainter(this);
	painter->save();
	DrawBackgroundPixmap(painter);							//绘制整体背景图片
	//滑动截取图片
	if (mouse_slid_press_flag_)
	{
		DrawBoostLine(painter);								//绘制辅助线
		DrawSlidRect(painter);								//绘制滑动矩形框
		DrawInformationRect(painter);						//绘制信息框
	}
	//截取图片二次处理
	if (mouse_slid_finish_)
	{
		DrawFruitRect(painter);								//绘制结果矩形框--大小重绘
		DrawFruitRectIsShow(painter);						//绘制结果矩形框相关判断显示
		if (mouse_rect_press_flag_)
			ShowToolBar(false);
		else
			ShowToolBar(true);

	}
	painter->restore();
}






CutGraph::CutGraph(QWidget* parent /*= Q_NULLPTR*/)
{
	InitMenu();
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->show();
}

CutGraph::~CutGraph()
{

}

void CutGraph::SetPixmap(QPixmap _pimmap)
{
	pixmap_ = _pimmap;
}

void CutGraph::InitMenu()
{
	menu_action_.push_back(new QAction(QStringLiteral("复制"), this));
	menu_action_.push_back(new QAction(QStringLiteral("另存为"), this));
	menu_action_.push_back(new QAction(QStringLiteral("关闭"), this));

	menu_ = new QMenu(this);
	menu_->setWindowFlags(Qt::Popup);
	for (auto menu_one : menu_action_)
		menu_->addAction(menu_one);

	connect(menu_action_.at(0), SIGNAL(triggered()), this, SLOT(CheckedCopyAction()));
	connect(menu_action_.at(1), SIGNAL(triggered()), this, SLOT(CheckedSaveAction()));
	connect(menu_action_.at(2), SIGNAL(triggered()), this, SLOT(CheckedCloseAction()));
}

void CutGraph::CheckedCopyAction()
{
	QApplication::clipboard()->setPixmap(pixmap_);
}

void CutGraph::CheckedCloseAction()
{
	close();
}

void CutGraph::CheckedSaveAction()
{
	QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("保存图片"), "", tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF"));;//选择路径
	if (filename.isEmpty())
		return;
	else
	{
		if (!(pixmap_.save(filename))) //保存图像
		{

			QMessageBox::information(this, QStringLiteral("图片保存"), QStringLiteral("截屏文件保存失败！"));
			return;
		}
		QMessageBox::information(this, QStringLiteral("图片保存"), QStringLiteral("截屏文件保存成功！"));
	}
}

void CutGraph::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		move_point_ = this->pos() - event->globalPos();
	}
	if (event->button() == Qt::RightButton)
	{
		delete menu_;
		menu_ = new QMenu(this);
		menu_->setWindowFlags(Qt::Popup);
		for (auto menu_one : menu_action_)
			menu_->addAction(menu_one);
		menu_->move(event->globalPos());
		menu_->show();
	}
}

void CutGraph::mouseMoveEvent(QMouseEvent* event)
{
	this->move(event->globalPos() + move_point_);
}

void CutGraph::paintEvent(QPaintEvent* event)
{
	this->setFixedSize(pixmap_.size());
	QPainter* painter = new QPainter(this);
	painter->save();
	painter->drawPixmap(0, 0, pixmap_);										//将获取的图片画到窗体上
	painter->restore();
}

