#ifndef CONTROLLERMAP_H
#define CONTROLLERMAP_H

#include <list>
#include <QString>
#include <QPointF>
#include <utility>

class ModelMap
{
private:
    std::list<std::pair<QString, QPointF*> *> listOfCommonPlaces;
    std::list<std::pair<QString, QPointF*> *> listOfSpecialPlaces;

public:
    ModelMap();

    bool LoadPlacesFromFile(QString p_path);
    bool SavePlacesToFile(QString p_path);

    void AddToCommonPlace(QString p_name, QPointF *p_point);
    bool RemoveFromCommonPlace(QPointF *p_point);
    std::pair<QString, QPointF*> *CommonPlace(QString p_name);
    std::pair<QString, QPointF*> *CommonPlace(QPointF *p_point);

    void AddToSpecialPlace(QString p_nome, QPointF *p_point);
    bool RemoveFromSpecialPlace(QPointF *p_point);
    std::pair<QString, QPointF*> *SpecialPlace(QString p_name);
    std::pair<QString, QPointF*> *SpecialPlace(QPointF *p_point);

    std::list<std::pair<QString, QPointF*> *>* GetListOfCommonPlaces();
    std::list<std::pair<QString, QPointF*> *>* GetListOfSpecialPlaces();
};

#endif // CONTROLLERMAP_H
