#include "group.h"

Group::Group(QString name)
{
    this->name = name;
}

void Group::setName(QString name){
    this->name = name;
}

QString Group::getName(){
    return name;
}
