#include "draw_to_decide.h"
#include <QDebug>
DrawToDecide::DrawToDecide(QWidget* parent)
	: QWidget(parent)
	, mouse_pressed_(false)
	, draw_style_(DRAW_Line)
{
	this->setFixedSize(600, 600);

	QVector<QPushButton*> btn_draw;
	btn_draw.push_back(new QPushButton(QStringLiteral("线")));
	btn_draw.push_back(new QPushButton(QStringLiteral("矩形")));
	btn_draw.push_back(new QPushButton(QStringLiteral("圆形")));
	btn_draw.push_back(new QPushButton(QStringLiteral("箭头")));
	btn_draw.push_back(new QPushButton(QStringLiteral("文本")));
	btn_draw.push_back(new QPushButton(QStringLiteral("马赛克")));
	btn_draw.push_back(new QPushButton(QStringLiteral("马克笔")));

	com_style_ = new QComboBox();
	com_style_->setCursor(Qt::ArrowCursor);
	QStringList list_style;
	list_style << QStringLiteral("SolidLine") << QStringLiteral("DotLine") << QStringLiteral("DashDotLine") << QStringLiteral("DashLine") << QStringLiteral("DashDotDotLine");
	com_style_->addItems(list_style);
	com_style_->setItemData(0, (int)Qt::SolidLine);
	com_style_->setItemData(1, (int)Qt::DotLine);
	com_style_->setItemData(2, (int)Qt::DashDotLine);
	com_style_->setItemData(3, (int)Qt::DashLine);
	com_style_->setItemData(4, (int)Qt::DashDotDotLine);

	com_color_ = new QComboBox();
	com_color_->setCursor(Qt::ArrowCursor);
	QStringList list_color;
	list_color << QStringLiteral("黑") << QStringLiteral("红") << QStringLiteral("绿") << QStringLiteral("蓝");
	com_color_->addItems(list_color);
	com_color_->setItemData(0, QColor(0, 0, 0));
	com_color_->setItemData(1, QColor(255, 0, 0));
	com_color_->setItemData(2, QColor(0, 255, 0));
	com_color_->setItemData(3, QColor(0, 0, 255));

	com_width_ = new QComboBox();
	com_width_->setCursor(Qt::ArrowCursor);
	QStringList list_width;
	list_width << QStringLiteral("1") << QStringLiteral("2") << QStringLiteral("3") << QStringLiteral("4") << QStringLiteral("5") << QStringLiteral("6");
	com_width_->addItems(list_width);
	com_width_->setItemData(0, 1);
	com_width_->setItemData(1, 2);
	com_width_->setItemData(2, 3);
	com_width_->setItemData(3, 4);
	com_width_->setItemData(4, 5);
	com_width_->setItemData(5, 6);

	QVBoxLayout* main_layout = new QVBoxLayout();
	QHBoxLayout* top_button_layout = new QHBoxLayout();
	QHBoxLayout* top_com_layout = new QHBoxLayout();
	for (int i = 0; i < btn_draw.size(); i++)
	{
		top_button_layout->addWidget(btn_draw.at(i));
		btn_draw.at(i)->setCursor(Qt::ArrowCursor);
	}
	top_com_layout->addWidget(com_style_);
	top_com_layout->addWidget(com_color_);
	top_com_layout->addWidget(com_width_);
	main_layout->addLayout(top_button_layout);
	main_layout->addLayout(top_com_layout);
	main_layout->addStretch();

	connect(btn_draw.at(0), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Line;
		});
	connect(btn_draw.at(1), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Rectangle;
		});
	connect(btn_draw.at(2), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Circul;
		});
	connect(btn_draw.at(3), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Arrow;
		});
	connect(btn_draw.at(4), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Text;
		});
	connect(btn_draw.at(5), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Mosaic;
		});
	connect(btn_draw.at(6), &QPushButton::clicked, this, [=]() {
		draw_style_ = DRAW_Marker_Pen;
		});
	this->setLayout(main_layout);
	QCursor cursor(QPixmap(":/PracticeOne/Resources/pen.png"));
	this->setCursor(cursor);

	line_eidit_ = new QLineEdit();
	line_eidit_->setObjectName("custom_draw_text_input");
	//设置透明色生效
	line_eidit_->window()->setAttribute(Qt::WA_TranslucentBackground, true);
	line_eidit_->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	connect(line_eidit_, &QLineEdit::editingFinished, this, &DrawToDecide::LineEditFinishText);
}

DrawToDecide::~DrawToDecide()
{
}


void DrawToDecide::DrawShape(QPainter& _painter, LineStyle* _line_style)
{
	QTextOption toption(Qt::AlignCenter);
	toption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
	switch (_line_style->draw_style_)
	{
	case DRAW_Line:
		_painter.drawPolyline(QPolygon(_line_style->points_));
		break;
	case DRAW_Rectangle:
		_painter.drawRect(QRect(_line_style->points_.at(0), _line_style->points_.at(1)));
		break;
	case DRAW_Circul:
		_painter.drawEllipse(QRect(_line_style->points_.at(0), _line_style->points_.at(1)));
		break;
	case DRAW_Arrow:
		_painter.setBrush(_line_style->color_);
		_painter.drawPolygon(QPolygon(GetArrowShape(_line_style->points_.at(0), _line_style->points_.at(1))));
		_painter.setBrush(Qt::NoBrush);
		break;
	case DRAW_Text:

		_painter.drawText(QRect(_line_style->points_.at(0), _line_style->points_.at(1)), _line_style->content_, toption);
		break;
	default:
		break;
	}

}

QVector<QPoint> DrawToDecide::GetArrowShape(QPoint _start_point, QPoint _end_point)
{
	QVector<QPoint> arrow_points;
	float x1 = _start_point.x();
	float y1 = _start_point.y();
	float x2 = _end_point.x();
	float y2 = _end_point.y();

	double angle = atan2(y2 - y1, x2 - x1);				//计算线段的夹角
	float arrow_length_long = 20;						//箭头边的长度--长
	float arrow_angle_long = 0.6;						//箭头与线段的夹角--长
	float arrow_length_short = 12;						//箭头边的长度--短
	float arrow_angle_short = 0.3;						//箭头与线段的夹角--短

	float point_long_x1 = x2 - arrow_length_long * cos(angle - arrow_angle_long);
	float point_long_y1 = y2 - arrow_length_long * sin(angle - arrow_angle_long);
	float point_long_x2 = x2 - arrow_length_long * cos(angle + arrow_angle_long);
	float point_long_y2 = y2 - arrow_length_long * sin(angle + arrow_angle_long);
	float point_short_x1 = x2 - arrow_length_short * cos(angle - arrow_angle_short);
	float point_short_y1 = y2 - arrow_length_short * sin(angle - arrow_angle_short);
	float point_short_x2 = x2 - arrow_length_short * cos(angle + arrow_angle_short);
	float point_short_y2 = y2 - arrow_length_short * sin(angle + arrow_angle_short);

	arrow_points.append(_start_point);
	arrow_points.append(QPoint(point_short_x1, point_short_y1));
	arrow_points.append(QPoint(point_long_x1, point_long_y1));
	arrow_points.append(_end_point);
	arrow_points.append(QPoint(point_long_x2, point_long_y2));
	arrow_points.append(QPoint(point_short_x2, point_short_y2));
	arrow_points.append(_start_point);

	return arrow_points;
}

void DrawToDecide::LineEditFinishText()
{
	QString lineedit_text = line_eidit_->text();
	line_eidit_->clear();
	line_eidit_->close();
	lines_.at(lines_count_)->content_ = lineedit_text;
	qDebug() << lineedit_text;
}

void DrawToDecide::mouseMoveEvent(QMouseEvent* event)
{
	if (mouse_pressed_)
	{
		switch (draw_style_)
		{
		case DRAW_Line:
			points_.append(event->pos());
			lines_.at(lines_count_)->points_ = points_;
			break;
		case DRAW_Rectangle:
			lines_.at(lines_count_)->points_[1] = event->pos();
			break;
		case DRAW_Circul:
			lines_.at(lines_count_)->points_[1] = event->pos();
			break;
		case DRAW_Arrow:
			lines_.at(lines_count_)->points_[1] = event->pos();
			break;
		case DRAW_Text:
			lines_.at(lines_count_)->points_[1] = event->pos();
			break;
		case DRAW_Mosaic:
			break;
		case DRAW_Marker_Pen:
			break;
		default:
			break;
		}

	}
	update();
}

void DrawToDecide::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	for (int i = 0; i < lines_.size(); i++)
	{
		LineStyle* line_style = lines_.at(i);
		QPen pen;
		pen.setWidth(line_style->width_);
		pen.setColor(line_style->color_);
		pen.setStyle(line_style->pen_style_);
		painter.setPen(pen);
		DrawShape(painter, line_style);
	}
}

void DrawToDecide::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_pressed_ = true;

		LineStyle* line_style = new LineStyle();
		line_style->color_ = com_color_->currentData().value<QColor>();
		line_style->width_ = com_width_->currentData().toInt();
		line_style->draw_style_ = draw_style_;
		line_style->pen_style_ = (Qt::PenStyle)com_style_->currentData().toInt();
		lines_.push_back(line_style);
		lines_count_ = lines_.count() - 1;
		points_.clear();
		switch (draw_style_)
		{
		case DRAW_Line:
			break;
		case DRAW_Rectangle:
			lines_.at(lines_count_)->points_.append(event->pos());
			lines_.at(lines_count_)->points_.append(event->pos());
			break;
		case DRAW_Circul:
			lines_.at(lines_count_)->points_.append(event->pos());
			lines_.at(lines_count_)->points_.append(event->pos());
			break;
		case DRAW_Arrow:
			lines_.at(lines_count_)->points_.append(event->pos());
			lines_.at(lines_count_)->points_.append(event->pos());
			break;
		case DRAW_Text:
			lines_.at(lines_count_)->points_.append(event->pos());
			lines_.at(lines_count_)->points_.append(event->pos());
			break;
		case DRAW_Mosaic:
			break;
		case DRAW_Marker_Pen:
			break;
		default:
			break;
		}
	}
	update();
}

void DrawToDecide::mouseReleaseEvent(QMouseEvent* event)
{
	mouse_pressed_ = false;
	switch (draw_style_)
	{
	case DRAW_Line:
		break;
	case DRAW_Rectangle:
		lines_.at(lines_count_)->points_[1] = event->pos();
		break;
	case DRAW_Circul:
		lines_.at(lines_count_)->points_[1] = event->pos();
		break;
	case DRAW_Arrow:
		lines_.at(lines_count_)->points_[1] = event->pos();
		break;
	case DRAW_Text:
		lines_.at(lines_count_)->points_[1] = event->pos();
		//输入框位置大小处理
		line_eidit_->move(event->globalPos() - (lines_.at(lines_count_)->points_[1] - lines_.at(lines_count_)->points_[0]));
		line_eidit_->setFixedSize((lines_.at(lines_count_)->points_[1] - lines_.at(lines_count_)->points_[0]).x(), (lines_.at(lines_count_)->points_[1] - lines_.at(lines_count_)->points_[0]).y());
		line_eidit_->show();
		break;
	case DRAW_Mosaic:
		break;
	case DRAW_Marker_Pen:
		break;
	default:
		break;
	}
	update();
}
