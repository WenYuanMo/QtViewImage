#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    _scale=1;
    _dy=0;
    _dx=0;
    _start_x=0;
    _start_y=0;
    _mouse_down=false;
    _imageEixt=false;
    _board_width=this->width();
    _board_height=this->height();

    _font.setFamily("Microsoft YaHei");
    _font.setPointSize(60);
    _font.setBold(true);
    _font.setLetterSpacing(QFont::AbsoluteSpacing, 60);

    _pen.setBrush(Qt::red);
    _pen.setWidth(5);

    this->setMouseTracking(true);
    _labBoardCoor=new QLabel(this);
    _labBoardCoor->setGeometry(10,0,100,20);
    _labBoardCoor->setText("0,0");
}

void ImageWidget::wheelEvent(QWheelEvent *event)
{

    QPointF win_point1_=event->pos();//获取鼠标窗口坐标
    qreal original_x_=(win_point1_.x()-this->_start_x-this->_dx)/_scale;//鼠标点在画板中没有缩放的坐标
    qreal original_y_=(win_point1_.y()-this->_start_y-this->_dy)/_scale;

    if(event->delta()>0)//缩放
    {
        _scale*=1.2;
    }
    else
    {
        _scale*=0.8;
    }

    QPointF win_point2_;

    win_point2_.setX(original_x_*_scale+this->_start_x+this->_dx);//缩放后鼠标原来画板中的坐标对应窗口坐标
    win_point2_.setY(original_y_*_scale+this->_start_y+this->_dy);

    _start_x=_start_x+((win_point1_.x()-win_point2_.x()));//更新开始坐标
    _start_y=_start_y+((win_point1_.y()-win_point2_.y()));

    this->update();
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect blackboard_=event->rect();
    painter.fillRect(blackboard_,Qt::white);

    if(_imageEixt==false)
    {
        return;
        painter.end();
    }
    qreal moveX_=this->_start_x+this->_dx;
    qreal moveY_=this->_start_y+this->_dy;
    painter.translate(moveX_,moveY_);
    painter.scale(_scale,_scale);
    painter.drawImage(0,0,_image);
    painter.setFont(_font);
    painter.setPen(_pen);


    painter.end();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(_mouse_down==true)
    {
        _last_point=event->pos();
        _dx+=_last_point.x()-_down_point.x();
        _dy+=_last_point.y()-_down_point.y();
        _down_point=_last_point;

        this->update();
    }
    else
    {
        QPointF point_=event->pos();
        qreal x_=(point_.x()-this->_start_x-this->_dx)/_scale;
        qreal y_=(point_.y()-this->_start_y-this->_dy)/_scale;

        if(x_<0||x_>_board_width)
        {
            x_=0;
        }

        if(y_<0||y_>_board_height)
        {
            y_=0;
        }

        _labBoardCoor->setText(QString::number(x_)+QString::fromStdString(",")+QString::number(y_));
        QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&ImageWidget::positionChanged);
        if (this->isSignalConnected(valueChangedSignal))
        {
            emit positionChanged(x_,y_);
        }
    }
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )//判断鼠标是不是左键是的话返回
    {
        _down_point=event->pos();
        _last_point=event->pos();
        _mouse_down=true;

    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    _mouse_down=false;
}

void ImageWidget::setImage(QImage img_)
{
    _image=img_;
    _imageEixt=true;
    _board_width=img_.width();
    _board_height=img_.height();
    this->update();
}

void ImageWidget::setImage(QString path_)
{
    _image.load(path_);
    _imageEixt=true;
    _board_width=_image.width();
    _board_height=_image.height();
    this->update();
}

void ImageWidget::fitWindow()
{
    qreal win_width_=this->width();
    qreal win_height_=this->height();

    qreal width_scale_=win_width_/_board_width;
    qreal height_scale_=win_height_/_board_height;

    if(width_scale_<height_scale_)
    {
        _scale=width_scale_;
    }
    else
    {
        _scale=height_scale_;
    }

    _dx=0;
    _dy=0;

    qreal fitWidth_=_board_width*_scale;
    qreal fitHeight_=_board_height*_scale;

    _start_x=(win_width_-fitWidth_)/2;
    _start_y=(win_height_-fitHeight_)/2;

    this->update();
}

void ImageWidget::setScale(qreal scale_)
{
    _scale*=scale_;
    this->update();
}

void ImageWidget::setMove(qreal dx_, qreal dy_)
{
    _dx=dx_;
    _dy=dy_;
    update();
}

void ImageWidget::setBoardSize(qreal width_, qreal height_)
{
    _board_width=width_;
    _board_height=height_;
}

QPointF ImageWidget::getPointInBoard(QPointF point_)
{
    QPointF po_=point_;
    po_.setX((point_.x()-this->_start_x-this->_dx)/_scale);
    po_.setY((point_.y()-this->_start_y-this->_dy)/_scale);
    return  po_;
}

QPointF  ImageWidget::getPointInWin(QPointF point_)
{
    QPointF po_=point_;
    po_.setX(point_.x()*_scale+this->_start_x+this->_dx);
    po_.setY(point_.y()*_scale+this->_start_y+this->_dy);
    return  po_;
}


