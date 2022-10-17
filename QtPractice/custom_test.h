#pragma once

#ifndef CUSTOM_TEST_H
#define CUSTOM_TEST_H

#include <QtWidgets/QMainWindow>

class CustomTest : public QMainWindow
{
	Q_OBJECT

public:
	CustomTest(QWidget* parent = 0);
	~CustomTest();

	// 完整组件测试
	void ComponentsTest();

	// 功能代码测试
	void PracticeTest();
};

#endif // CUSTOM_TEST_H


