#include "visualcryptpicturewidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <algorithm>
#include <QDebug>

VisualCryptPictureWidget::VisualCryptPictureWidget(QWidget *parent)
    : QWidget(parent)
{
}

VisualCryptPictureWidget::~VisualCryptPictureWidget()
{

}

void VisualCryptPictureWidget::setPicture(XBild *picture)
{
    m_picture = picture;
    this->update();
}

int VisualCryptPictureWidget::calcCellSize()
{
    int myWidth = this->geometry().width();
    int myHeight = this->geometry().height();
    int pictureHeight = m_picture->get_y_size();
    int pictureWidth = m_picture->get_x_size();
    int input_height = (myHeight / pictureHeight);
    int input_width = (myWidth / pictureWidth);
    if (input_height == 0 || input_width == 0) {
        qDebug() << "picture width or height bigger than widget width/height";
        qDebug() << myWidth << myHeight << pictureWidth << pictureHeight;
    }
    int cellsize = std::min(input_height, input_width);
    return cellsize;
}

void VisualCryptPictureWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (m_picture == 0) {
        return;
    }

    // use m_matrix to draw a grid/table

    QPainter painter(this);
    // can draw the cells by using painter function
    int cellsize = calcCellSize();

    for (int j = 0; j < m_picture->get_y_size(); ++j) {
        for (int i = 0; i < m_picture->get_x_size(); ++i){
            int xi = cellsize * i;
            int yj = cellsize * j;
            if ((*m_picture)[j][i] == true){
                painter.setPen(Qt::blue);

            }
            else{
                painter.setPen(Qt::white);
            }
//            qDebug() << xi << yj << cellsize;
            painter.drawPoint(xi, yj);
        }


    }

}

