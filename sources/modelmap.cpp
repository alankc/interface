#include "modelmap.h"
#include "pointfile.h"

#include <fstream>
#include <iostream>
#include <string>

ModelMap::ModelMap()
{

}

ModelMap::ModelMap(QString p_path)
{

}

bool ModelMap::LoadPlacesFromFile(QString p_path)
{
    std::string path = p_path.toStdString();
    std::ifstream in(path.c_str(), std::ios_base::in);

    if (!in.is_open())
        return false;

    for (auto& item: this->listOfCommonPlaces)
        this->listOfCommonPlaces.remove(item);

    for (auto& item: this->listOfSpecialPlaces)
        this->listOfSpecialPlaces.remove(item);

    size_t sizeOfCommonList, sizeOfSpecialList;
    in.read((char*)&sizeOfCommonList, sizeof(sizeOfCommonList));
    in.read((char*)&sizeOfSpecialList, sizeof(sizeOfSpecialList));

    for (uint i = 0; i < sizeOfCommonList; i++)
    {
        PointFile pf;
        in.read((char*)&pf, sizeof(pf));

        std::pair<QString, QPointF*>* pair = new std::pair<QString, QPointF*>();
        pair->first = QString(pf.name);
        pair->second = new QPointF(pf.x, pf.y);

        this->listOfCommonPlaces.push_back(pair);
    }

    for (uint i = 0; i < sizeOfSpecialList; i++)
    {
        PointFile pf;
        in.read((char*)&pf, sizeof(pf));

        std::pair<QString, QPointF*>* pair = new std::pair<QString, QPointF*>();
        pair->first = QString(pf.name);
        pair->second = new QPointF(pf.x, pf.y);

        this->listOfSpecialPlaces.push_back(pair);
    }

    in.close();
    return true;
}

bool ModelMap::SavePlacesToFile(QString p_path)
{
    std::string path = p_path.toStdString();
    std::ofstream out(path.c_str(), std::ios_base::out | std::ios_base::trunc);

    if (!out.is_open())
        return false;

    size_t sizeOfCommonList = this->listOfCommonPlaces.size();
    out.write((char*)&sizeOfCommonList, sizeof(sizeOfCommonList));
    size_t sizeOfSpecialList = this->listOfSpecialPlaces.size();
    out.write((char*)&sizeOfSpecialList, sizeof(sizeOfSpecialList));

    for (auto& item: listOfCommonPlaces)
    {
        PointFile pf;
        const char* name_temp = ((QString)item->first).toStdString().c_str();

        for (uint8_t i = 0; name_temp[i] != '\0' && i < NAME_SIZE - 1; i++)
            pf.name[i] = name_temp[i];

        pf.x = item->second->rx();
        pf.y = item->second->ry();

        out.write((char*)&pf, sizeof(PointFile));
    }

    for (auto& item: listOfSpecialPlaces)
    {
        PointFile pf;

        const char* name_temp = ((QString)item->first).toStdString().c_str();

        for (uint8_t i = 0; name_temp[i] != '\0' && i < NAME_SIZE - 1; i++)
            pf.name[i] = name_temp[i];

        pf.x = item->second->rx();
        pf.y = item->second->ry();

        out.write((char*)&pf, sizeof(PointFile));
    }

    out.close();

    return true;
}

void ModelMap::AddToCommonPlace(QString p_name, QPointF *p_point)
{
    std::pair<QString, QPointF*> *pair = new std::pair<QString, QPointF*>();
    pair->first = p_name;
    pair->second = p_point;
    this->listOfCommonPlaces.push_back(pair);
}
bool ModelMap::RemoveFromCommonPlace(QPointF *p_point)
{
    for(auto& pair: this->listOfCommonPlaces)
    {

        QPointF* point = pair->second;
        if ((point->rx() == p_point->rx()) && (point->ry() == p_point->ry()))
        {
            this->listOfCommonPlaces.remove(pair);
            delete(pair);
            delete(point);
            return true;
        }
    }
    return false;
}

void ModelMap::AddToSpecialPlace(QString p_name, QPointF *p_point)
{
    std::pair<QString, QPointF*> *pair = new std::pair<QString, QPointF*>();
    pair->first = p_name;
    pair->second = p_point;
    this->listOfSpecialPlaces.push_back(pair);
}

bool ModelMap::RemoveFromSpecialPlace(QPointF *p_point)
{
    for(auto& pair: this->listOfSpecialPlaces)
    {
        QPointF* point = pair->second;
        if ((point->rx() == p_point->rx()) && (point->ry() == p_point->ry()))
        {
            this->listOfSpecialPlaces.remove(pair);
            delete(pair);
            delete(point);
            return true;
        }
    }
    return false;
}

std::list<std::pair<QString, QPointF*>*>* ModelMap::GetListOfCommonPlaces()
{
    return &(this->listOfCommonPlaces);
}

std::list<std::pair<QString, QPointF*>*>* ModelMap::GetListOfSpecialPlaces()
{
    return &(this->listOfSpecialPlaces);
}
