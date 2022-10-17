#pragma once

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QApplication>
#include <QStandardPaths>
#include <QKeyEvent>
#include <QMenu>
#include <QClipboard>
#include <QtGui/QWindow>
#include <QDebug>
#include <QtGui/QScreen>
#include <QFileDialog>
#include <Windows.h>
#include <vector>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVector>
#include <QMessageBox>


struct MyRect
{
	QRect myRect_;			//当前矩形
	int distance_;			//点与矩形四边距离和
};

class ScreenCaptureWidget : public QDialog
{
	Q_OBJECT

public:

	ScreenCaptureWidget(QWidget* parent = nullptr);
	~ScreenCaptureWidget();


public:

	void ScreenCapture();

private:

	QPixmap show_top_pixmap_;										//当前桌面显示内容
	QPixmap pixmap_;												//截图对象
	QPoint mouse_now_point_;										//鼠标当前位置
	QPoint mouse_result_begin_point_, mouse_result_end_point_;		//调整结果：图片起始位置
	bool mouse_finish_;												//是否选中

private:

	//用于计算鼠标当前点到各个边的距离之和
	void CalculataRectDistance(QRect rect);
	//绘制结果矩形框--样式
	void DrawFruitRectStyle(QPainter* _painter, QPoint& _begion_point, QPoint& _end_point);
	//绘制矩形框
	void DrawSlidRect(QPainter* _painter);
	//获取要绘制的矩形
	QRect GetRect(const QPoint& _begin_Point, const QPoint& _end_Point);

protected:

	virtual void mousePressEvent(QMouseEvent* event) override;


	virtual void mouseReleaseEvent(QMouseEvent* event) override;


	virtual void mouseMoveEvent(QMouseEvent* event) override;


	virtual void paintEvent(QPaintEvent* event) override;

};
