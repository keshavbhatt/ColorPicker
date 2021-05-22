#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QColor>
#include <QColorDialog>
#include <QEvent>
#include <QMouseEvent>
#include <QObject>

class ColorDialog : public QColorDialog
{
    Q_OBJECT
  public:
    ColorDialog(QWidget *parent = nullptr, const QColor &color = QColor{"red"});

  protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // COLORDIALOG_H
