#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

#include <QJsonDocument>
#include <QJsonObject>

#include <QFile>
#include <QTextStream>


#include "user.h"

class APIManager : public QObject
{

    Q_OBJECT

public:
    explicit APIManager(QObject *parent = nullptr);

public slots:
    void logIn(User &given_user);
    void signUp( User &given_user);
    void logOut( User &given_user);
    void creatGroup( User &given_user,  QString &group_name, QString &group_title);
    void creatChannel( User &given_user , QString &channel_name ,  QString &channel_title);
    void getUsersList( User &given_user);
    void getGroupList( User &given_user);
    void getChannelList( User &given_user);
    void getUsersChat( User &given_user , QString &dst);
    void getGroupChat( User &given_user , QString &dst);
    void getChannelChat( User &given_user ,QString &dst);
    void joinGroup( User &given_user ,QString &group_name);
    void joinChannel( User &given_user ,QString &channel_name);
    void sendMessageUser( User &given_user ,QString &dst , QString &body);
    void sendMessageGroup( User &given_user ,QString &dst , QString &body);
    void sendMessageChannel( User &given_user ,QString &dst , QString &body);
    //    //void getUsersChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    //    //void getGroupChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    //    //void getChannelChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    void saveTokenToFile(const QString &token);
    QString readTokenFromFile();
    void saveCodeToFile(const QString &code);
    QString readCodeFromFile();
private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};

#endif // APIMANAGER_H
