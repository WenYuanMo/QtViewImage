/**
带画圆形，矩形，点
**/

#ifndef IMAGEWIDGETSHOW_H
#define IMAGEWIDGETSHOW_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtCore>
#include <QtCore/qnamespace.h>
#include <QLabel>

class imagewidgetshow: public QWidget
{
    Q_OBJECT

public:
    explicit imagewidgetshow(QWidget *parent = nullptr);//构造函数
    void setImage(QImage);//设置当前的图片 默认图片大小为画板大小
    void setImage(QString);//从文件夹中获取图片
    void setBoardSize(qreal width_,qreal height_);//设置画板大小
    void fitWindow();//适应窗口
    void setScale(qreal scale_);//设置缩放
    void setMove(qreal dx_,qreal dy_);//设置移动
    void paintCircle(qreal center_x_,qreal center_y_,qreal r_);//画圆
    void paintRectangle(qreal rightUp_x_,qreal rightUp_y_, qreal width_,qreal height_);//画矩形
    void paintCircleText(QString text_,qreal center_x_,qreal center_y_,qreal r_);//画带文字的圆形
    void paintRectangleText(QString text_,qreal rightUp_x_,qreal rightUp_y_, qreal width_,qreal height_);//画带文字的矩形
    void paintPoint(qreal center_x_,qreal center_y_);//画点
    void clearShapeList();//清空列表
    QImage getImage();//获取当前图片
    QPointF getPointInBoard(QPointF);//获取窗口鼠标坐标在画板中对应坐标
    QPointF getPointInWin(QPointF);//获取画板中坐标在窗口中对应坐标
    qreal _board_width; //画板的宽
    qreal _board_height;  //画板的高
    bool _imageEixt; //图片是否存在

    //信号
signals:
    void positionChanged(int x , int y );//坐标点改变

protected:
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    QPointF _down_point;//鼠标按下的坐标
    QPointF _last_point; //鼠标移动的坐标
    bool _mouse_down;//鼠标按下
    qreal _scale; //缩放
    qreal _scale_multiply;//缩放的倍率
    qreal _dy; //偏移
    qreal _dx;//偏移
    qreal _start_x;//绘制的开始点
    qreal _start_y;  //绘制的开始点
    QImage _image; //当前的图片,默认是画板 
    int _handle; //当前操作shape的点位
    QFont _font;//绘制字体的格式
    QPen _pen; //画笔
    QLabel *_labBoardCoor;//显示板的坐标


};

#endif // IMAGEWIDGETSHOW_H
