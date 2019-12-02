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





