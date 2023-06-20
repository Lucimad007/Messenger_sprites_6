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
private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};

#endif // APIMANAGER_H
