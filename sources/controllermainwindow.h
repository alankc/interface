#ifndef CONTROLLERMAINWINDOW_H
#define CONTROLLERMAINWINDOW_H

#include "mainwindow.h"
#include "modelmainwindow.h"
#include "myscene.h"
#include "modelmap.h"

class ControllerMainWindow
{
private:
    static MainWindow *view;
    static ModelMap *map;
    static bool _isToAddSpecialPlace;
    static bool _isToAddCommonPlace;
    static bool _isToRemovePlace;

    static bool _isToAddTask;
    static bool _isToRemoveTask;

public:
    static void SetView(MainWindow *p_view) {view = p_view;}

    static void LoadMap();
    static void SaveMap();
    static void LoadPlaces();
    static void ClearPlaces();

    static void SetToAddSpecialPlace() {if (map != NULL) _isToAddSpecialPlace = true;}
    static bool IsToAddSpecialPlace() {return _isToAddSpecialPlace;}
    static void AddSpecialPlace(QPoint* p_point, bool pAddToMapList);
    static void AddSpecialPlace(QString p_name);

    static void SetToAddCommonPlace() {if (map != NULL) _isToAddCommonPlace = true;}
    static bool IsToAddCommonPlace() {return _isToAddCommonPlace;}
    static void AddCommonPlace(QPoint* p_point, bool p_AddToMapList);
    static void AddCommonPlace(QString p_name);

    static void SetToRemovePlace() {if (map != NULL) _isToRemovePlace = true;}
    static bool IsToRemovePlace() {return _isToRemovePlace;}
    static void RemovePlace(QPoint* p_point);
    static void RemovePlace(int index);

    static void SetToAddTask() {if (map != NULL) _isToAddTask = true;}
    static bool IsToAddTask() {return _isToAddTask;}
    static void SetToRemoveTask(){if (map != NULL) _isToRemoveTask = true;}
    static bool IsToRemoveTask() {return _isToRemoveTask;}
    static void AddTask(int index);
    static void RemoveTask(int index);

    static void SendToRobot();


};

#endif // CONTROLLERMAINWINDOW_H
