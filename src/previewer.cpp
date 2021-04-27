#include "previewer.h"
#include <QDebug>


Previewer::Previewer(QWidget *parent)
{
    setParent(parent);
    setAcceptDrops(true);
}

void Previewer::setBackground(QColor color){
    this->setStyleSheet("background-color:"+color.name());
}

void Previewer::dropEvent(QDropEvent *event)
{
    setBackground(QColor(event->mimeData()->colorData().toString()).name());
    event->acceptProposedAction();
}

void Previewer::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-color")){
         event->acceptProposedAction();
    }
}

void Previewer::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-color"))
        event->acceptProposedAction();
}

QString Previewer::getParaText(){
    return QString("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.");
}




