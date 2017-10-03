#include "modelmap.h"
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

    size_t sizeOfCommonList;
    in.read((char*)&sizeOfCommonList, sizeof(sizeOfCommonList));
    size_t sizeOfSpecialList;
    in.read((char*)&sizeOfSpecialList, sizeof(sizeOfSpecialList));

    foreach (QPointF* point, this->listOfCommonPlaces)
    {
        this->listOfCommonPlaces.remove(point);
        delete(point);
    }
    for(uint i = 0; i < sizeOfCommonList; i++)
    {
        double x, y;
        in.read((char*)&x, sizeof(x));
        in.read((char*)&y, sizeof(y));
        this->listOfCommonPlaces.push_back(new QPointF(x, y));
    }

    foreach (QPointF* point, this->listOfSpecialPlaces)
    {
        this->listOfSpecialPlaces.remove(point);
        delete(point);
    }

    for(uint i = 0; i < sizeOfSpecialList; i++)
    {
        double x, y;
        in.read((char*)&x, sizeof(x));
        in.read((char*)&y, sizeof(y));
        this->listOfSpecialPlaces.push_back(new QPointF(x, y));
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

    foreach (QPointF* item, listOfCommonPlaces) {
        double value = item->rx();
        out.write((char*)&value, sizeof(value));
        value = item->ry();
        out.write((char*)&value, sizeof(value));
    }

    foreach (QPointF* item, listOfSpecialPlaces) {
        double value = item->rx();
        out.write((char*)&value, sizeof(value));
        value = item->ry();
        out.write((char*)&value, sizeof(value));
    }

    out.close();

    return true;
}

void ModelMap::AddToCommonPlace(QPointF *p_point)
{
    this->listOfCommonPlaces.push_back(p_point);
}

bool ModelMap::RemoveFromCommonPlace(QPointF *p_point)
{
    foreach (QPointF* point, this->listOfCommonPlaces) {
        if ((point->rx() == p_point->rx()) && (point->ry() == p_point->ry()))
        {
            this->listOfCommonPlaces.remove(point);
            delete(point);
            return true;
        }
    }
    return false;
}

void ModelMap::AddToSpecialPlace(QPointF *p_point)
{
    this->listOfSpecialPlaces.push_back(p_point);
}

bool ModelMap::RemoveFromSpecialPlace(QPointF *p_point)
{
    foreach (QPointF* point, this->listOfSpecialPlaces) {
        if ((point->rx() == p_point->rx()) && (point->ry() == p_point->ry()))
        {
            this->listOfSpecialPlaces.remove(point);
            delete(point);
            return true;
        }
    }
    return false;
}

std::list<QPointF*>* ModelMap::GetListOfCommonPlaces()
{
    return &(this->listOfCommonPlaces);
}

std::list<QPointF*>* ModelMap::GetListOfSpecialPlaces()
{
    return &(this->listOfSpecialPlaces);
}
