#ifndef CONTROLLERMAP_H
#define CONTROLLERMAP_H

#include <list>
#include <QString>
#include <QPointF>

class ModelMap
{
private:
    std::list<QPointF*> listOfCommonPlaces;
    std::list<QPointF*> listOfSpecialPlaces;

public:
    ModelMap();
    ModelMap(QString p_path);
    bool LoadPlacesFromFile(QString p_path);
    bool SavePlacesToFile(QString p_path);
    void AddToCommonPlace(QPointF *p_point);
    bool RemoveFromCommonPlace(QPointF *p_point);
    void AddToSpecialPlace(QPointF *p_point);
    bool RemoveFromSpecialPlace(QPointF *p_point);
    std::list<QPointF*>* GetListOfCommonPlaces();
    std::list<QPointF*>* GetListOfSpecialPlaces();
};

#endif // CONTROLLERMAP_H
