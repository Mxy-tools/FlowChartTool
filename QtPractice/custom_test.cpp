#include <QHBoxLayout>

#include "custom_test.h"
#include "screen_capture_widget.h"
#include "slid_screen_capture_widget.h"
#include "draw_to_decide.h"
#include "multi_select_combobox.h"
#include "custom_table_widget.h"

#define TestModel 1

CustomTest::CustomTest(QWidget* parent)
	: QMainWindow(parent)
{
#if TestModel
	ComponentsTest();
#else
	PracticeTest();
#endif

}

CustomTest::~CustomTest()
{

}

void CustomTest::ComponentsTest()
{

#if 0
	/*截图测试*/
	ScreenCaptureWidget* test = new ScreenCaptureWidget(this);
	test->ScreenCapture();
	test->show();
#endif

#if 0
	/*滑动截图测试*/
	SlidScreenCaptureWidget* test = new SlidScreenCaptureWidget(this);
	test->ScreenCapture();
	test->show();
#endif

#if 1
	/*鼠标想定绘制*/
	DrawToDecide* custom_draw = new DrawToDecide();
	custom_draw->show();
#endif

#if 0
	/*下拉复选框测试*/
	MultiSelectComboBox* test = new MultiSelectComboBox(this);
	QStringList data_list;
	for (int i = 0; i < 10; i++)
	{
		data_list << QStringLiteral("足球%1").arg(QString::number(i));
		data_list << QStringLiteral("乒乓球%1").arg(QString::number(i));
		data_list << QStringLiteral("网球%1").arg(QString::number(i));
		data_list << QStringLiteral("羽毛球%1").arg(QString::number(i));
		data_list << QStringLiteral("篮球%1").arg(QString::number(i));
		data_list << QStringLiteral("橄榄球%1").arg(QString::number(i));
	}
	test->setObjectName("multiselect_combobox");
	test->addItems(data_list);
	test->SetSearchBarPlaceHolderText(QStringLiteral("搜索球类运动.........."));
	test->setFixedSize(250, 40);
	test->clear();
	test->addItems(data_list);
	QHBoxLayout* layout_ = new QHBoxLayout();
	this->setLayout(layout_);
	this->show();
#endif


#if 0
	/*自定义表格测试*/
	CustomtableWidget* test = new CustomtableWidget();
	test->resize(1000, 600);
	test->show();
#endif
}

void CustomTest::PracticeTest()
{

}
