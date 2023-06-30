#ifndef CHANNEL_H
#define CHANNEL_H
#include <QString>

class Channel
{
public:
    Channel(QString name = "");
    void setName(QString name);
    QString getName();
private:
    QString name;
};

#endif // CHANNEL_H
