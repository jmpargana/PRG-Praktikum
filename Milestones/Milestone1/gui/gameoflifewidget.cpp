#include "gameoflifewidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <algorithm>

GameOfLifeWidget::GameOfLifeWidget(QWidget *parent)
    : QWidget(parent)
{
}

GameOfLifeWidget::~GameOfLifeWidget()
{

}

void GameOfLifeWidget::setMatrix(CellularAutomaton *matrix)
{
    m_matrix = matrix;
    this->update();
}

int GameOfLifeWidget::calcCellSize()
{
    int myWidth = this->geometry().width();
    int myHeight = this->geometry().height();
    int input_height = (myHeight / m_matrix->get_rows());
    int input_width = (myWidth / m_matrix->get_cols());
    int cellsize = std::min(input_height, input_width);
    return cellsize;
}

void GameOfLifeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (m_matrix == 0) {
        return;
    }

    // use m_matrix to draw a grid/table

    QPainter painter(this);
    // can draw the cells by using painter function
    int cellsize = calcCellSize();

    for (int j = 0; j < m_matrix->get_rows(); ++j) {
        for (int i = 0; i < m_matrix->get_cols(); ++i){
            int xi = cellsize * i;
            int yj = cellsize * j;
            if ((*m_matrix)[j][i] == true){
                painter.setBrush(Qt::blue);

            }
            else{
                painter.setBrush(Qt::white);
            }
            painter.setPen(Qt::black);
            painter.drawRect(QRect{xi, yj, cellsize, cellsize});
        }


    }

}

void GameOfLifeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_matrix == 0) {
        return;
    }
    QPoint pos = event->pos(); // <- pos.x() and pos.y() which coordinates where clicked


    int cellsize = calcCellSize();
    int i = floor(pos.x() / cellsize);
    int j = floor(pos.y() / cellsize);
   // update the data
    if((*m_matrix)[j][i] == true){
        (*m_matrix)[j][i] = false;
    }
    else {
        (*m_matrix)[j][i] = true;
    }

    this->update(); // this repaints GameOfLifeWidget
}

