#include "apimanager.h"
#include<QUrlQuery>

APIManager::APIManager(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager,&QNetworkAccessManager::finished,this,&APIManager::onReplyFinished);
}
void APIManager::signUp(const QString &username ,const QString &password){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/signup";
    // Construct the request URL with query parameters
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("username", username);
    query.addQueryItem("password", password);
    url.setQuery(query);

    // Send the GET request
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::logIn(const QString &username , const QString &password){
    //main apiURL
    QString apiURL ="http://api.barafardayebehtar.ml:8080/login";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("username",username);
    query.addQueryItem("password",password);
    url.setQuery(query);

    //Send the get request to server
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::onReplyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);
        qDebug()<<"Response is : "<<responseString;
    }else{
        qDebug() <<"Error : "<<reply->errorString();
    }
       reply->deleteLater(); //for safely release the memory

}
