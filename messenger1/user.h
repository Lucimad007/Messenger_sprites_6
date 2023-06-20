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
    QString getToken();

    //seters
    void setUername( QString &given_usernmae);
    void setPassword( QString &given_password);
    void setEmail( QString &given_email);
    void setToken();

private:
    QString Username,Password,Email,token;
};

#endif // USER_H
