#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QObject>
#include <QTextBrowser>
#include <QWheelEvent>
#include <QWidget>

class Previewer : public QTextBrowser
{
    Q_OBJECT
  public:
    Previewer(QWidget *parent = nullptr);

  public slots:
    void setBackground(QColor color);

    QString getParaText();

  protected:
    void dropEvent(QDropEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    
    void dragMoveEvent(QDragMoveEvent *event) override;

    void wheelEvent(QWheelEvent *event) override
    {
        if (event->modifiers() & Qt::ControlModifier)
            event->ignore();
        else
            QTextBrowser::wheelEvent(event);
    }
};

#endif // PREVIEWER_H
