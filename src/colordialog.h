#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QObject>
#include <QColorDialog>
#include <QColor>
#include <QMouseEvent>
#include <QEvent>

class ColorDialog : public QColorDialog
{
    Q_OBJECT
public:
    ColorDialog(QWidget *parent =nullptr, const QColor &color =QColor("red"));
protected slots:
    void keyPressEvent(QKeyEvent *e);
};

#endif // COLORDIALOG_H
