#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User
{
public:
    User(const QString &username , const QString &password, const QString &email);
    //geters

    QString getUsername();
    QString getPassword();
    QString getEmail();

    //seters
    void setUername( QString &given_usernmae);
    void setPassword( QString &given_password);
    void setEmail( QString &given_email);

private:
    QString Username,Password,Email;
};

#endif // USER_H
