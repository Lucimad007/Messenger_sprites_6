#include "message.h"

Message::Message(User user,QString content)
{
    this->user = user;
    this->content = content;
}

void Message::setMessage(QString& message){
    this->content = message;
}

QString Message::getMessage(){
    return this->content;
}

QString Message::getSenderName(){
    return this->user.getUsername();
}
