#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QObject>
#include <QWidget>
#include <QTextBrowser>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QWheelEvent>

class Previewer : public QTextBrowser
{
    Q_OBJECT
public:
    Previewer(QWidget *parent = nullptr);
public slots:
    void setBackground(QColor color);
    QString getParaText();
protected slots:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

    virtual void wheelEvent(QWheelEvent *event)
      {
        if(event->modifiers() & Qt::ControlModifier)
           event->ignore();
        else
          QTextBrowser::wheelEvent(event);
      }
 };

#endif // PREVIEWER_H
