#pragma once
#include <QUuid>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <string>
#include <memory>
using namespace std;

#ifndef M_PI
#define  M_PI  3.14159265358979323846
#endif

enum class ItemType
{
	Null = 0,		// 空
	Nomal,			// 代表全局常态
	Link,			// 连接线
	Rect,			// 流程
	Condition,		// 判定
	Circulation,	// 自循环
};

struct FlowchartItemType
{
	ItemType	type = ItemType::Null;
};

enum class  FlowchartCursor
{
	ArrowCursor = 0,
	DrawLinkCursor,
	SizeAllCurSor,
	OpenHandCursor,
	ClosedHandCursor,
};

// 图元样式信息
struct FlowchartStyleBase
{
	QPen							pen_;					// 基本画笔样式--背景相关
	QBrush							brush_;					// 基本画刷样式--背景相关
	QPen							text_pen_;				// 文本画笔样式
	QFont							font_;					// 字体样式
	FlowchartStyleBase()
	{
		pen_ = QPen();
		pen_.setColor(QColor(65, 113, 156));
		pen_.setWidth(1);

		brush_ = QBrush(QColor(89, 152, 209));

		text_pen_ = QPen();;
		text_pen_.setColor(QColor(254, 255, 255));
		text_pen_.setWidth(1);

		font_ = QFont("Microsoft YaHei", 12, 2);
	}
};

// 图元数据信息
struct FlowchartContentBase
{
	QString							id_;										// 图元id
	QString							content_;									// 图元内容
	QString							tooltip_;									// 图元提示信息

	FlowchartContentBase()
	{
		id_ = QUuid::createUuid().toString();
		content_ = "Text";
		tooltip_ = "Tooltip";
	}
};

// 图元父子结构关系信息
struct FlowchartStructuralData
{
	FlowchartStructuralData()
	{

	}
	QVector<QString>				father_ids_;					// 父节点id集合
	QVector<QString>				children_ids_;					// 子节点id集合
};

// 图元结构体基类
struct FlowchartInforBase
{
	double							position_x_, position_y_, width_, height_;
	FlowchartStyleBase				item_style_;
	FlowchartContentBase			item_content_;
	FlowchartItemType				item_type_;
	FlowchartStructuralData			item_structural_;

	FlowchartInforBase()
	{
		position_x_ = 0.0;
		position_y_ = 0.0;
		width_ = 160.0;
		height_ = 40.0;
		item_style_ = FlowchartStyleBase();
		item_content_ = FlowchartContentBase();
		item_structural_ = FlowchartStructuralData();
	};
	FlowchartInforBase(double _x, double _y, double _width = 160.0, double _height = 40.0)
	{
		position_x_ = _x;
		position_y_ = _y;
		width_ = _width;
		height_ = _height;
		item_style_ = FlowchartStyleBase();
		item_content_ = FlowchartContentBase();
		item_structural_ = FlowchartStructuralData();
	};
};
typedef std::vector<FlowchartInforBase*>	FlowchartInforBases;