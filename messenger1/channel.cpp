#include "channel.h"

Channel::Channel(QString name)
{
    this->name = name;
}

void Channel::setName(QString name){
    this->name = name;
}

QString Channel::getName(){
    return name;
}
