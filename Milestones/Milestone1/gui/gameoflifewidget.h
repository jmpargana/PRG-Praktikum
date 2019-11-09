#ifndef GameOfLifeWidget_H
#define GameOfLifeWidget_H

#include <vector>

#include <QWidget>

#include "../code/include/cellular_automaton.hpp"

class GameOfLifeWidget : public QWidget
{
    Q_OBJECT

public:
    GameOfLifeWidget(QWidget *parent = 0);
    ~GameOfLifeWidget();

    void setMatrix(CellularAutomaton* matrix);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int calcCellSize();

    CellularAutomaton *m_matrix = 0;
};

#endif // GameOfLifeWidget_H
