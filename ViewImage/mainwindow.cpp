#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置大小
    resize(800, 600);

    centralwidget = new QWidget(this);
    centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0)"));

    gridLayout =new QGridLayout(centralwidget);
    verticalLayout =new QVBoxLayout(centralwidget);
    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    loadImageButton=new QPushButton(centralwidget);
    loadImageButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"
                                                     "color: rgb(255, 255, 255);"
                                                     "border-style:outset;"
                                                     "border-width: 2px;"
                                                     "border-color: rgb(200, 200, 200);"));

    loadImageButton->setMinimumSize(QSize(150,50));
    loadImageButton->setMaximumHeight(50);
    loadImageButton->setText(QString("LoadImage"));
    verticalLayout->addWidget(loadImageButton);

    imageWidget =new ImageWidget(centralwidget);
    imageWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

    verticalLayout->addWidget(imageWidget);

    this->setCentralWidget(centralwidget);
    connect(loadImageButton,SIGNAL(clicked()), this, SLOT(LoadImage()));
}

void MainWindow::LoadImage()
{
    QString curPath=QDir::currentPath();//获取系统当前目录

    //QString dlgTitle=QString::fromLocal8Bit("选择一个文件");  中文会编译不过
    //QString filter=QString::fromLocal8Bit("图片文件(*.jpg *.gif *.png *.bmp)"); //文件过滤器

    QString dlgTitle="choice one image";
    QString filter="image(*.jpg *.gif *.png *.bmp)"; //文件过滤器

    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,"",filter);

    if(aFileName!="")
    {
        imageWidget->setImage(aFileName);
        imageWidget->fitWindow();
    }
}

MainWindow::~MainWindow()
{
}
