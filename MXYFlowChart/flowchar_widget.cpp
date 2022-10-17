#include "flowchar_widget.h"
FlowCharWidget::FlowCharWidget(QWidget *parent)
	: QMainWindow(parent)
{
	InitWindow();
	DataTest();
	
}

FlowchartInforBases FlowCharWidget::GetFlowCharData()
{
	FlowchartInforBases datas;
	if (scene_ == nullptr)
		return datas;
	datas = scene_->FlowChart2Data();
	return datas;
}

void FlowCharWidget::SetFlowChartData(FlowchartInforBases _datas)
{

}

void FlowCharWidget::InitWindow()
{
	// 流程图编辑界面
	scene_ = new FlowchartScene();
	this->setCentralWidget(scene_->GetFlowcharView());
	// 左侧形状菜单
	tool_side_bar_ = new FlowCharToolSideBar(this);
	this->addDockWidget(Qt::LeftDockWidgetArea, tool_side_bar_);
	// 顶层工具栏
	tool_button_bar_ = new FlowCharToolButtonBar(this);
	tool_button_bar_->SetFlowchartScene(scene_);
	tool_button_bar_->SetToolSideBar(tool_side_bar_);
	this->addToolBar(tool_button_bar_);


	QWidget *main_widget = new QWidget();
	QHBoxLayout *main_layout = new QHBoxLayout();
	main_widget->setLayout(main_layout);

	this->resize(1400, 800);
}

void FlowCharWidget::DataTest()
{
}

//*******************************工具栏************************************
FlowCharToolButtonBar::FlowCharToolButtonBar(QWidget *parent /*= Q_NULLPTR*/)
	: QToolBar(parent)
{
	InitWidget();
}

FlowCharToolButtonBar::~FlowCharToolButtonBar()
{

}

void FlowCharToolButtonBar::SetFlowchartScene(FlowchartScene* _scene)
{
	scene_ = _scene;
}

void FlowCharToolButtonBar::SetToolSideBar(FlowCharToolSideBar* _side_bar)
{
	side_bar_ = _side_bar;
}

void FlowCharToolButtonBar::InitWidget()
{
	// 设置浮动
	setFloatable(false);
	setMovable(false);
	setAllowedAreas(Qt::TopToolBarArea | Qt::RightToolBarArea);
	this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	
	file_save_ = new QAction(QPixmap(":/new/prefix1/Resources/FileSave.png"), QStringLiteral("保存"));
	file_read_ = new QAction(QPixmap(":/new/prefix1/Resources/FileOpen.png"), QStringLiteral("打开"));
	item_type_ = new QAction(QPixmap(":/new/prefix1/Resources/Shape.png"), QStringLiteral("形状"));
	mouse_status_nomal_ = new QAction(QPixmap(":/new/prefix1/Resources/ArrowCursor.png"), QStringLiteral("指针工具"));
	mouse_status_link_ = new QAction(QPixmap(":/new/prefix1/Resources/DrawLinkCursor.png"),QStringLiteral("连接线"));

	addAction(file_save_);
	addAction(file_read_);
	addAction(item_type_);
	addAction(mouse_status_nomal_);
	addAction(mouse_status_link_);

	connect(file_save_, SIGNAL(triggered()), this, SLOT(FlowActionSlot()));
	connect(file_read_, SIGNAL(triggered()), this, SLOT(FlowActionSlot()));
	connect(item_type_, SIGNAL(triggered()), this, SLOT(FlowActionSlot()));
	connect(mouse_status_nomal_, SIGNAL(triggered()), this, SLOT(FlowActionSlot()));
	connect(mouse_status_link_, SIGNAL(triggered()), this, SLOT(FlowActionSlot()));
}

void FlowCharToolButtonBar::FileSave()
{
	if (scene_ == nullptr)
		return;
	datas = scene_->FlowChart2Data();
	for (auto data_one : datas)
	{
	}
}

void FlowCharToolButtonBar::FileRead()
{
	if (scene_ == nullptr)
		return;
	scene_->Data2FlowChart(datas);
}

void FlowCharToolButtonBar::FlowActionSlot()
{
	QAction *signal_action = (QAction*)sender();
	if (signal_action == mouse_status_nomal_){
		if (scene_ == nullptr)
			return;
		scene_->SetSceneMode(SceneMode::MoveItem);
	}
	else if (signal_action == mouse_status_link_){
		if (scene_ == nullptr)
			return;
		scene_->SetSceneMode(SceneMode::DrawLineItem);
	}
	else if (signal_action == item_type_){
		if (side_bar_ == nullptr)
			return;
		side_bar_->show();
	}
	else if (signal_action == file_save_) {
		FileSave();
	}
	else if (signal_action == file_read_) {
		FileRead();
	}
	return;
}

//*******************************左侧工具栏************************************
FlowCharToolSideBar::FlowCharToolSideBar(QWidget *parent /*= Q_NULLPTR*/)
	: QDockWidget(parent)
{
	InitWidget();
}

FlowCharToolSideBar::~FlowCharToolSideBar()
{

}

void FlowCharToolSideBar::SetFlowchartScene(FlowchartScene* _scene)
{
	scene_ = _scene;
}

void FlowCharToolSideBar::InitWidget()
{
	setAllowedAreas(Qt::LeftDockWidgetArea);
	setWindowTitle(QStringLiteral("形状"));
	setMinimumWidth(270);

	QWidget *main_widget = new QWidget();
	QVBoxLayout *main_layout = new QVBoxLayout();
	main_widget->setLayout(main_layout);
	this->setWidget(main_widget);

	vec_btn_.insert("流程", new QPushButton(QStringLiteral("流程")));
	vec_btn_.insert("判定", new QPushButton(QStringLiteral("判定")));
	vec_btn_.insert("自循环", new QPushButton(QStringLiteral("自循环"))); 
	for (QMap<std::string, QPushButton*>::iterator iter = vec_btn_.begin(); iter != vec_btn_.end(); iter++){
		main_layout->addWidget(iter.value());
		connect(iter.value(), SIGNAL(pressed()), this, SLOT(FlowButtonSlot()));
	}
	main_layout->addStretch();
	/*main_layout->addWidget(new QAction(""));*/
}

void FlowCharToolSideBar::InitData()
{

}

void FlowCharToolSideBar::FlowButtonSlot()
{
	QDrag *drag = new QDrag(this);
	QMimeData *data = new QMimeData();
	data->clear();
	QPushButton *clicked_btn = (QPushButton*)sender();
	if (clicked_btn == vec_btn_["流程"]){
		data->setText(QStringLiteral("流程"));
	}
	else if (clicked_btn == vec_btn_["判定"]){
		data->setText(QStringLiteral("判定"));
	}
	else if (clicked_btn == vec_btn_["自循环"]){
		data->setText(QStringLiteral("自循环"));
	}
	drag->setMimeData(data);
	drag->exec(Qt::MoveAction);
}
