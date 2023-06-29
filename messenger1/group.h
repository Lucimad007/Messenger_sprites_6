#ifndef GROUP_H
#define GROUP_H
#include <QString>

class Group
{
public:
    Group(QString name = "");
    void setName(QString name);
    QString getName();
private:
    QString name;
};

#endif // GROUP_H
