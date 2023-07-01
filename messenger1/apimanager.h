#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QTextStream>
#include <QDir>

#include <QTimer>
#include <QThread>

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
    void creatGroup(QString &group_name, QString &group_title);
    void creatChannel(QString &channel_name ,  QString &channel_title);
    void getUsersList();
    void getGroupList();
    void getChannelList();
    void getUsersChat( QString &dst);
    void getGroupChat( QString &dst);
    void getChannelChat(QString &dst);
    void joinGroup(QString &group_name);
    void joinChannel(QString &channel_name);
    void sendMessageUser(QString &dst , QString &body);
    void sendMessageGroup(QString &dst , QString &body);
    void sendMessageChannel(QString &dst , QString &body);
    //    //void getUsersChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    //    //void getGroupChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    //    //void getChannelChat(const QString &token ,const QString &dst,const QString &date); //it will overload soon
    void saveTokenToFile(const QString &token);
    QString readTokenFromFile();
    void saveCodeToFile(const QString &code);
    QString readCodeFromFile();
    void RemoveCode();
    void check_response_code(const QString &code ,const QString &server_message);

    void Write_chat_folder(const QString &target_user, const QJsonObject &temp_jobj);
    void Write_group_floder(const QString &dst , const QJsonObject &temp_obj);
    void Write_channel_floder(const QString &dst , const QJsonObject &temp_obj);

    QJsonObject Read_group_folder(const QString &dst);
    QJsonObject Read_channel_folder(const QString &dst);
    QJsonObject Read_user_folder(const QString &src,const QString &dst);

    void get_list_of(const QString type,const QJsonObject &response); //the functin that stores list of USERS GROUPS and CHANNELS

    QJsonObject get_list_of_users();
    QJsonObject get_list_of_channels();
    QJsonObject get_list_of_group();

    void Delete_All_Files();

private slots:
    void Thread_task();
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
    User currentUser;
};

#endif // APIMANAGER_H
