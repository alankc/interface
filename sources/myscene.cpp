#include "myscene.h"
#include "controllermainwindow.h"

#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint *point =  new QPoint();
    point->setX(event->scenePos().x());
    point->setY(event->scenePos().y());

    if (ControllerMainWindow::IsToRemovePlace() == true)
        ControllerMainWindow::RemovePlace(point);
    else if (ControllerMainWindow::IsToAddSpecialPlace() == true)
        ControllerMainWindow::AddSpecialPlace(point, true);
    else if (ControllerMainWindow::IsToAddCommonPlace() == true)
        ControllerMainWindow::AddCommonPlace(point, true);
}

