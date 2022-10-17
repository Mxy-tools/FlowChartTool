#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QComboBox>
#include <QPixmap>
#include <QCursor>
#include <QLineEdit>

enum DrawStyle
{
	DRAW_Line = 0,								//线
	DRAW_Rectangle,								//矩形
	DRAW_Circul,								//圆形
	DRAW_Arrow,									//箭头
	DRAW_Text,									//文本
	DRAW_Mosaic,								//马赛克
	DRAW_Marker_Pen								//马克笔
};

struct LineStyle
{
	QVector<QPoint> points_;					//绘制图形点集
	QColor color_;								//线颜色
	int width_;									//线宽度
	Qt::PenStyle pen_style_;					//线样式
	DrawStyle draw_style_;						//绘制图形样式
	QString content_;							//文本内容
	QFont font_;								//文本样式--暂不设置
};

class DrawToDecide : public QWidget
{
	Q_OBJECT

public:

	DrawToDecide(QWidget* parent = nullptr);
	~DrawToDecide();

private:

	void DrawShape(QPainter& _painter, LineStyle* _line_style);

	//获取箭头图形点集
	QVector<QPoint> GetArrowShape(QPoint _start_point, QPoint _end_point);

private slots:

	void LineEditFinishText();

protected:

	virtual void mouseMoveEvent(QMouseEvent* event) override;


	virtual void paintEvent(QPaintEvent* event) override;


	virtual void mousePressEvent(QMouseEvent* event) override;


	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:

	QVector<LineStyle*> lines_;
	QVector<QPoint> points_;
	bool mouse_pressed_;
	int lines_count_;
	DrawStyle draw_style_;
	QComboBox* com_style_;
	QComboBox* com_color_;
	QComboBox* com_width_;
	QLineEdit* line_eidit_;

};
