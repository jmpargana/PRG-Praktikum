#ifndef VisualCryptPictureWidget_H
#define VisualCryptPictureWidget_H

#include <vector>

#include <QWidget>

#include "../code/include/vis_crypt.h"

class VisualCryptPictureWidget : public QWidget
{
    Q_OBJECT

public:
    VisualCryptPictureWidget(QWidget *parent = 0);
    ~VisualCryptPictureWidget();

    void setPicture(XBild* pictur);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int calcCellSize();

    XBild *m_picture = 0;
};

#endif // VisualCryptPictureWidget_H
