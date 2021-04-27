#include "colordialog.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

ColorDialog::ColorDialog(QWidget *parent,QColor color) :
    QColorDialog(color,parent)
{
    setWindowFlags(Qt::Widget);
    setOptions(QColorDialog::NoButtons | QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel );
}

void ColorDialog::keyPressEvent(QKeyEvent *e)
{
    //prevent esc key close the ColorDialog widget
    if(e->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(e);
}




