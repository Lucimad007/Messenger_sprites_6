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

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;

};

#endif // APIMANAGER_H
