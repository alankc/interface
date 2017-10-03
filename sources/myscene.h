#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>

class MyScene : public QGraphicsScene
{
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYSCENE_H
