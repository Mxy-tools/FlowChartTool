/*
	* 滑动截取屏幕
	*
*/
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

enum ArrowType
{
	Arrow_Cursor,
	Size_Ver_Cursor_Top,
	Size_Ver_Cursor_Bottom,
	Size_Hor_Cursor_Left,
	Size_Hor_Cursor_Right,
	Size_All_Cursor,
	Size_Bdiag_Cursor_Top,
	Size_Bdiag_Cursor_Bottom,
	Size_Fdiag_Cursor_Top,
	Size_Fdiag_Cursor_Bottom
};


class CutGraph;
class SlidScreenCaptureWidget
	:public QDialog
{
	Q_OBJECT
public:
	SlidScreenCaptureWidget(QWidget* parent = Q_NULLPTR);
	~SlidScreenCaptureWidget();


public:

	void ScreenCapture();

private:

	QPixmap show_top_pixmap_;										//当前桌面显示内容
	QPixmap pixmap_;												//当前图片
	QString pixel_color_;											//当前像素颜色
	QPoint mouse_slid_begin_point_, mouse_slid_end_point_;			//截取图片：滑动鼠标起始位置
	QPoint mouse_now_point_;										//鼠标当前位置
	bool mouse_slid_press_flag_;									//截取图片：鼠标是否按下
	bool mouse_slid_finish_;										//截取图片：截屏区域是否选择完毕
	QPoint mouse_rect_begin_point_, mouse_rect_end_point_;			//调整截屏区域：滑动鼠标起始位置
	bool mouse_rect_press_flag_;									//调整截屏区域：鼠标是否按下
	QPoint mouse_result_begin_point_, mouse_result_end_point_;		//调整结果：图片起始位置

	QWidget* tool_bar_;												//工具栏
	bool color_is_show_;											//取色器是否显示
	QVector<CutGraph*> cut_graphs_;									//存放切图

private:
	/*******************画笔绘制相关********************/
	//绘制整体背景图片
	void DrawBackgroundPixmap(QPainter* _painter);
	//绘制滑动矩形框
	void DrawSlidRect(QPainter* _painter);
	//绘制辅助线
	void DrawBoostLine(QPainter* _painter);
	//绘制信息框
	void DrawInformationRect(QPainter* _painter);
	//绘制结果矩形框--大小重绘
	void DrawFruitRect(QPainter* _painter);
	//绘制结果矩形框--样式
	void DrawFruitRectStyle(QPainter* _painter, QPoint& _begion_point, QPoint& _end_point);
	//绘制结果矩形框相关判断显示
	void DrawFruitRectIsShow(QPainter* _painter);

	//获取要绘制的矩形
	QRect GetRect(const QPoint& _begin_Point, const QPoint& _end_Point);
	//获取图片固定位置颜色
	QRgb GetPixmapColor(QPixmap _pixmap, QPoint _position);
	//获取起始点的偏移
	QPoint GetOffsetPoint(const QPoint& _begin_Point, const QPoint& _end_Point);
	//判断点是否在该矩形内
	ArrowType PointInRect(QPoint& _point, QRect _rect);
	//保存图片
	void Save();
	//返回当前截图对象
	QPixmap GetScreenPixmap();
	//显示菜单栏
	void ShowToolBar(bool _flag);
	//初始化菜单栏
	void InitToolBar();

protected:
	virtual void mousePressEvent(QMouseEvent* event);


	virtual void mouseReleaseEvent(QMouseEvent* event);


	virtual void mouseMoveEvent(QMouseEvent* event);


	virtual void paintEvent(QPaintEvent* event);


	virtual void keyReleaseEvent(QKeyEvent* event);


	virtual void closeEvent(QCloseEvent* event) override;

};


class CutGraph
	:public QDialog
{
	Q_OBJECT
public:
	CutGraph(QWidget* parent = Q_NULLPTR);
	~CutGraph();

public:

	//设置贴图对象
	void SetPixmap(QPixmap _pimmap);

private:

	//初始化菜单
	void InitMenu();

private slots:

	void CheckedCopyAction();										//复制

	void CheckedCloseAction();										//关闭

	void CheckedSaveAction();										//保存

private:

	QPixmap pixmap_;												//当前图片
	QPoint move_point_;												//贴图拖动相关
	QMenu* menu_;													//右键菜单
	QVector<QAction*> menu_action_;									//右键菜单事件

protected:

	virtual void mousePressEvent(QMouseEvent*) override;


	virtual void mouseMoveEvent(QMouseEvent*) override;


	virtual void paintEvent(QPaintEvent*) override;

};