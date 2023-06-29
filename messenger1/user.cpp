#include "user.h"


User::User(){
    this->Username = "";
    this->Password = "";
    this->Email = "";
    this->token = "";
}

User::User(const QString& username, const QString& password, const QString& email)
    : Username(username), Password(password), Email(email)
{
}

QString User::getUsername()
{
    return this->Username;
}

void User::setUername(QString& username)
{
    this->Username = username;
}

QString User::getPassword()
{
    return this->Password;
}

void User::setPassword( QString& password)
{
    this->Password = password;
}

QString User::getEmail()
{
    return this->Email;
}

void User::setEmail( QString& email)
{
    this->Email = email;
}
QString User::getToken(){
    return this->token;
}
void User::setToken(QString &given_token){
    //After Logout we should set token NULL
    this->token = given_token;
}
