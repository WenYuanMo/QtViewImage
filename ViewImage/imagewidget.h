/**
图品缩放控件
*/
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtCore>
#include <QtCore/qnamespace.h>
#include <QLabel>

 class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    void setImage(QImage);
    void setImage(QString);
    void setBoardSize(qreal width_,qreal height_);
    void fitWindow();
    void setScale(qreal scale_);
    void setMove(qreal dx_,qreal dy_);
    QPointF getPointInBoard(QPointF);
    QPointF getPointInWin(QPointF);
    qreal _board_width; //画板的宽
    qreal _board_height; //画板的高
    QPointF _down_point; //鼠标按下的坐标
    QPointF _last_point;  //鼠标移动的坐标
    bool _mouse_down;//鼠标按下
    bool _imageEixt;//图片是否存在
    qreal _scale; //缩放
    qreal _dy; //偏移
    qreal _dx; //偏移

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

    qreal _start_x;  //绘制的开始点
    qreal _start_y;//绘制的开始点
    QImage _image;//当前的图片
    QFont _font; //绘制字体的格式
    QPen _pen;//画笔
    QLabel *_labBoardCoor;//显示板的坐标
};

#endif // IMAGEWIDGET_H
