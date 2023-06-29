#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include "user.h"

class Message
{
public:
     Message(User user,QString content);
     void setMessage(QString& message);
     QString getMessage();
     QString getSenderName();
private:
     QString content;
     User user;
};

#endif // MESSAGE_H
