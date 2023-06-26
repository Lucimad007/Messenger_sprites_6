#include "apimanager.h"
#include<QUrlQuery>
extern User farhad;
APIManager::APIManager(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager,&QNetworkAccessManager::finished,this,&APIManager::onReplyFinished);
}

void APIManager::signUp(User &given_user){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/signup";
    //  ruct the request URL with query parameters
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("username", given_user.getUsername());
    query.addQueryItem("password", given_user.getPassword());
    url.setQuery(query);

    // Send the GET request
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::logIn(User &given_user){
    //main apiURL
    QString apiURL ="http://api.barafardayebehtar.ml:8080/login";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("username",given_user.getUsername());
    query.addQueryItem("password",given_user.getPassword());
    url.setQuery(query);

    //Send the get request to server
    QNetworkRequest request(url);
    m_networkManager.get(request);
}

void APIManager::logOut(User &given_user){
    //work with main api
    QString apiURL = "http://api.barafardayebehtar.ml:8080/logout";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("username",given_user.getUsername());
    query.addQueryItem("password",given_user.getPassword());
    url.setQuery(query);

    //send Get
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::creatGroup(User &given_user, QString &group_name, QString &group_title){
    QString apiURL="http://api.barafardayebehtar.ml:8080/creategroup";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("group_name",group_name);
    query.addQueryItem("group_title",group_title);
    url.setQuery(query);

    //send get
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::creatChannel( User &given_user, QString &channel_name,  QString &channel_title){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/createchannel";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("channel_name",channel_name);
    query.addQueryItem("channel_title",channel_title);
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getUsersList( User &given_user){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getuserlist";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getGroupList( User &given_user){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getgrouplist";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}

void APIManager::getChannelList( User &given_user){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getchannellist";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getUsersChat( User &given_user,QString &dst){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getuserchats";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("dst",dst);
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getGroupChat( User &given_user,QString &dst){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getgroupchats";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("dst",dst);
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getChannelChat( User &given_user, QString &dst){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getchannelchats";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("dst",dst);
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::joinGroup(User &given_user, QString &group_name){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/joingroup";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("group_name",group_name);
    url.setQuery(query);

    //sending
    QNetworkRequest request(url);
    m_networkManager.get(request);

}
void APIManager::joinChannel(User &given_user, QString &channel_name){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/joinchannel";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("channel_name",channel_name);
    url.setQuery(query);

    //sending
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::sendMessageUser(User &given_user, QString &dst, QString &body){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/sendmessageuser";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("dst",dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    //sending api
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::sendMessageGroup(User &given_user, QString &dst, QString &body){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/sendmessagegroup";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("dst",dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    //sending api
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::sendMessageChannel(User &given_user, QString &dst, QString &body){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/sendmessagechannel";
    QUrl url(apiURL);
    QUrlQuery query;
    query.addQueryItem("token",given_user.getToken());
    query.addQueryItem("dst",dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    //sending api
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::saveTokenToFile(const QString& token) {
    QFile file("token.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << token;
        file.close();
    } else {
        qDebug() << "Failed to open the token file for writing.";
    }
}
QString APIManager::readTokenFromFile() {
    QFile file("token.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString token = in.readAll();
        file.close();
        return token;
    } else {
        qDebug() << "Failed to open the token file for reading.";
        return QString(); // Return an empty token if reading fails
    }
}

void APIManager::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);
        qDebug() << "Response is: " << responseString;

        // Parse the JSON response
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();

        // Check if the response contains a "token" field
        if (jsonObject.contains("token")) {
            // Extract the token value
            QString extractedToken = jsonObject["token"].toString();
            saveTokenToFile(extractedToken);
        } else {
            // Handle the case where the response does not contain a token field
            // qDebug() << "Response does not contain a token.";
        }
    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater(); // Safely release the memory
}
