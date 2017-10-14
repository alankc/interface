#include "controllermainwindow.h"
#include "myscene.h"

#include<iostream>

#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QTranslator>
#include <QInputDialog>

bool ControllerMainWindow::_isToAddSpecialPlace     = false;
bool ControllerMainWindow::_isToAddCommonPlace      = false;
bool ControllerMainWindow::_isToRemovePlace         = false;

bool ControllerMainWindow::isToAddTask      = false;
bool ControllerMainWindow::isToRemoveTask   = false;

MainWindow* ControllerMainWindow::view = 0;
ModelMap* ControllerMainWindow::map = 0;


void ControllerMainWindow::LoadMap()
{
    if (map == 0)
    {
        map = new ModelMap();
    }
    else
    {
        delete(map);
        map = new ModelMap();
    }

    QString fileName = QFileDialog::getOpenFileName(view, "Selecione o Mapa", QDir::currentPath(), QObject::tr("PNG (*.png)") );
    if(!fileName.isEmpty())
    {
        QImage *image = new QImage(fileName);

        if(image->isNull())
        {
            QMessageBox::critical(view, "Erro", "Arquivo inadequado!");
            return;
        }

        MyScene* scene = new MyScene();
        view->graphicsView->setScene(scene);

        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
        scene->addItem(item);
    }
}

void ControllerMainWindow::LoadPlaces()
{
    if(map == 0)
    {
        QMessageBox::critical(view, "Erro", "Nenhum mapa carregado!");
        return;
    }
    QString fileName = QFileDialog::getOpenFileName(view, "Selecione o arquivo de locais", QDir::currentPath(), QObject::tr("LOCAIS(*.txt)"));
    if(!fileName.isEmpty())
    {
        if(!map->LoadPlacesFromFile(fileName))
        {
            QMessageBox::critical(view, "Erro", "Falha ao carregar locais");
        }
        else
        {
            ClearPlaces();

            for (auto& item: *(map->GetListOfCommonPlaces()))
            {
                QPoint* point = new QPoint();
                point->setX(item->second->toPoint().rx());
                point->setY(item->second->toPoint().ry());
                AddCommonPlace(point, false);
                AddCommonPlace(item->first);
            }

            for (auto& item: *(map->GetListOfSpecialPlaces()))
            {
                QPoint* point = new QPoint();
                point->setX(item->second->toPoint().rx());
                point->setY(item->second->toPoint().ry());
                AddSpecialPlace(point, false);
                AddSpecialPlace(item->first);
            }
        }
    }
}

void ControllerMainWindow::ClearPlaces()
{
    foreach (QGraphicsItem *item, view->graphicsView->items())
    {
        if (item != view->graphicsView->scene()->items().last())
        {
            view->graphicsView->scene()->removeItem(item);
            delete(item);
        }
    }

    view->listWidgetPlaces->clear();
}

void ControllerMainWindow::SaveMap()
{
    map->SavePlacesToFile("1_teste_alan.txt");
}

void ControllerMainWindow::AddSpecialPlace(QPoint* p_point, bool p_AddToMapList)
{
    if(map != 0)
    {
        QImage *image = new QImage(":/redFlag.png");
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));

        if(p_AddToMapList)
        {
            bool ok;
            QString text = QInputDialog::getText(view, QObject::tr("Nome de Local"), QObject::tr("Informe o nome do local:"), QLineEdit::Normal, "", &ok);

            if (!ok || text.isEmpty())
            {
                delete(image);
                delete(item);
                _isToAddSpecialPlace = false;
                return;
            }

            p_point->setX(p_point->x() - image->size().width() / 2);
            p_point->setY(p_point->y() - image->size().height() / 2);
            QPointF *p = new QPointF(p_point->rx(), p_point->ry());
            map->AddToSpecialPlace(text, p);
            AddSpecialPlace(text);
        }
        item->setPos(*p_point);
        view->graphicsView->scene()->addItem(item);
    }
    _isToAddSpecialPlace = false;
}

void ControllerMainWindow::AddSpecialPlace(QString p_name)
{
    QIcon *icon = new QIcon(":/redFlag.png");
    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setText(p_name);
    newItem->setIcon(*icon);
    int row = view->listWidgetPlaces->row(view->listWidgetPlaces->currentItem());
    view->listWidgetPlaces->insertItem(row, newItem);
}

void ControllerMainWindow::AddCommonPlace(QPoint* p_point, bool p_AddToMapList)
{
    if(map != 0)
    {
        QImage *image = new QImage(":/greenFlag.png");
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));

        if(p_AddToMapList)
        {
            bool ok;
            QString text = QInputDialog::getText(view, QObject::tr("Nome de Local"), QObject::tr("Informe o nome do local:"), QLineEdit::Normal, "", &ok);

            if (!ok || text.isEmpty())
            {
                delete(image);
                delete(item);
                _isToAddCommonPlace = false;
                return;
            }

            p_point->setX(p_point->x() - image->size().width() / 2);
            p_point->setY(p_point->y() - image->size().height() / 2);

            QPointF *p = new QPointF(p_point->rx(), p_point->ry());
            map->AddToCommonPlace(text, p);
            AddCommonPlace(text);
        }
        item->setPos(*p_point);
        view->graphicsView->scene()->addItem(item);
    }
    _isToAddCommonPlace = false;
}

void ControllerMainWindow::AddCommonPlace(QString p_name)
{
    QIcon *icon = new QIcon(":/greenFlag.png");
    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setText(p_name);
    newItem->setIcon(*icon);
    int row = view->listWidgetPlaces->row(view->listWidgetPlaces->currentItem());
    view->listWidgetPlaces->insertItem(row, newItem);
}

void ControllerMainWindow::RemovePlace(QPoint* p_point)
{
    _isToRemovePlace = false;
    QGraphicsItem* item = view->graphicsView->scene()->itemAt(*p_point);

    if (item != view->graphicsView->scene()->items().last())
    {
        QPointF *p = new QPointF(item->pos().rx(), item->pos().ry());

        auto itemSpecial = map->SpecialPlace(p);
        auto itemCommom = map->CommonPlace(p);

        if ((itemSpecial == NULL) && (itemCommom == NULL))
        {
            QMessageBox::critical(view, "Item não encontrado", "Falha ao remover item!");
            return;
        }
        else if ((itemSpecial == NULL) && (itemCommom != NULL))
        {
            for (auto itemList: view->listWidgetPlaces->findItems(itemCommom->first, Qt::MatchWildcard))
            {
                view->listWidgetPlaces->removeItemWidget(itemList);
                delete(itemList);
                break;
            }
            map->GetListOfCommonPlaces()->remove(itemCommom);
        }
        else if ((itemSpecial != NULL) && (itemCommom == NULL))
        {
            for (auto itemList: view->listWidgetPlaces->findItems(itemSpecial->first, Qt::MatchWildcard))
            {
                view->listWidgetPlaces->removeItemWidget(itemList);
                delete(itemList);
                break;
            }
            map->GetListOfSpecialPlaces()->remove(itemSpecial);
        }
        else
        {
            QMessageBox::critical(view, "Itens Duplicados", "Falha ao remover item!");
            return;
        }

        view->graphicsView->scene()->removeItem(item);
        delete(item);
    }
    else
    {
        QMessageBox::critical(view, "Erro", "Nenhum item para ser removido!");
    }
}

void ControllerMainWindow::RemovePlace(int index)
{
    _isToRemovePlace = false;
    QGraphicsItem* GraphicsItem;

    if (index >= 0)
    {
        auto item = view->listWidgetPlaces->item(index);

        auto itemSpecial = map->SpecialPlace(item->text());
        auto itemCommom = map->CommonPlace(item->text());

        if ((itemSpecial == NULL) && (itemCommom == NULL))
        {
            QMessageBox::critical(view, "Item Faltante", "Falha ao remover item!");
            return;
        }
        else if ((itemSpecial == NULL) && (itemCommom != NULL))
        {
            view->listWidgetPlaces->removeItemWidget(item);
            delete(item);

            for (auto itemList : view->graphicsView->items())
            {
                if ((itemList->pos().rx() == itemCommom->second->rx()) && (itemList->pos().ry() == itemCommom->second->ry()))
                {
                    GraphicsItem = itemList;
                    break;
                }
            }

            map->GetListOfCommonPlaces()->remove(itemCommom);
            delete(itemCommom);
        }
        else if ((itemSpecial != NULL) && (itemCommom == NULL))
        {
            view->listWidgetPlaces->removeItemWidget(item);
            delete(item);

            for (auto itemList : view->graphicsView->items())
            {
                if ((itemList->pos().rx() == itemSpecial->second->rx()) && (itemList->pos().ry() == itemSpecial->second->ry()))
                {
                    GraphicsItem = itemList;
                    break;
                }
            }

            map->GetListOfSpecialPlaces()->remove(itemSpecial);
            delete(itemSpecial);
        }
        else
        {
            QMessageBox::critical(view, "Itens Duplicados", "Falha ao remover item!");
            return;
        }

        view->graphicsView->scene()->removeItem(GraphicsItem);
        delete(GraphicsItem);
    }
}
