#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")


#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include <QObject>
#include <QDir>
#include <QFileDialog>
#include <imagewidget.h>
#include <QGridLayout>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    /**
@brief 主要的控件
*/
    QWidget *centralwidget;

/**
@brief 网格布局
*/
    QGridLayout *gridLayout;

    /**
@brief 主要的垂直布局
*/
    QVBoxLayout *verticalLayout;

    /**
@brief 加载图片按钮
*/
    QPushButton *loadImageButton;

    /**
@brief 图片显示控件
*/
   ImageWidget  *imageWidget;

public slots:
    /**
@brief 加载一张图片
*/
    void LoadImage();

};
#endif // MAINWINDOW_H
