#include "mainwindow.h"
#include "QTextCodec"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 以下部分解决中文乱码
    QTextCodec *codec = QTextCodec::codecForName("utf8"); //GBK gbk
//QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
//QTextCodec::setCodecForCStrings(codec);
    // 以上部分解决中文乱码
    MainWindow w;
    w.show();

    return a.exec();
}
