#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

class APIManager : public QObject
{

    Q_OBJECT

public:
    explicit APIManager(QObject *parent = nullptr);

public slots:
    void signUp(const QString &username, const QString &password);
    void logIn(const QString &username, const QString &password);
    void logOut(const QString &username, const QString &password);
    void creatGroup(const QString &token, const QString &group_name,const QString &group_title);
    void creatChannel(const QString &token, const QString &channel_name , const QString &channel_title);
    void getUsersList(const QString &token);
    void getGroupList(const QString &token);
    void getChannelList(const QString &token);
    void getUsersChat(const QString &token , QString &dst);
    //void getUsersChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    void getGroupChat(const QString &token , QString &dst);
    //void getGroupChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    void getChannelChat(const QString &token ,const QString &dst);
    //void getChannelChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    void joinGroup(const QString &token , const QString &group_name);
    void joinChannel(const QString &token , const QString &channel_name);
private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};

#endif // APIMANAGER_H
