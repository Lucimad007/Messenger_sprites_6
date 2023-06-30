#include "apimanager.h"
#include<QUrlQuery>
QJsonObject temp_json_object;
QString main_user_chat;
APIManager::APIManager(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager,&QNetworkAccessManager::finished,this,&APIManager::onReplyFinished);
}
QString chat_history_filename ="";
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
void APIManager::creatGroup(QString &group_name, QString &group_title){
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
void APIManager::creatChannel( QString &channel_name,  QString &channel_title){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/createchannel";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("channel_name",channel_name);
    query.addQueryItem("channel_title",channel_title);
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getUsersList(){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getuserlist";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getGroupList(){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getgrouplist";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}

void APIManager::getChannelList(){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getchannellist";
    QUrl url(apiURL);
    QUrlQuery query;

    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    url.setQuery(query);

    //send
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getUsersChat(QString &dst){
    main_user_chat = dst;
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getuserchats";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("dst",dst);
    url.setQuery(query);



    QNetworkRequest request(url);
    m_networkManager.get(request);


}
void APIManager::getGroupChat(QString &dst){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getgroupchats";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("dst",dst);
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::getChannelChat(QString &dst){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/getchannelchats";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("dst",dst);
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::joinGroup(QString &group_name){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/joingroup";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("group_name",group_name);
    url.setQuery(query);

    //sending
    QNetworkRequest request(url);
    m_networkManager.get(request);

}
void APIManager::joinChannel(QString &channel_name){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/joinchannel";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("channel_name",channel_name);
    url.setQuery(query);

    //sending
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::sendMessageUser(QString &dst, QString &body){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/sendmessageuser";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("dst",dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    //sending api
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::sendMessageGroup(QString &dst, QString &body){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/sendmessagegroup";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
    query.addQueryItem("dst",dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    //sending api
    QNetworkRequest request(url);
    m_networkManager.get(request);
}
void APIManager::sendMessageChannel(QString &dst, QString &body){
    QString apiURL = "http://api.barafardayebehtar.ml:8080/sendmessagechannel";
    QUrl url(apiURL);
    QUrlQuery query;
    QString main_token = readTokenFromFile();
    query.addQueryItem("token",main_token);
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
void APIManager::saveCodeToFile(const QString &code){
    QFile file("ResponseCode.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << code;
        file.close();
    } else {
        qDebug() << "Failed to open the ResponseCode file for writing.";
    }
}
QString APIManager::readCodeFromFile(){
    QFile file("ResponseCode.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString code = in.readAll();
        file.close();
        return code;
    } else {
        qDebug() << "Failed to open the ResponseCode file for reading the code";
        return QString();
    }
}
void APIManager::RemoveCode(){
    QFile file("ResponseCode.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.remove();
    }
}

bool flag =true;
void APIManager::check_response_code(const QString &response_code,const QString &server_message){

    if(response_code == "200" && server_message == "Logged in Successfully"){

        while(flag){
            flag=false;
            getUsersList();

        }

        qDebug() <<"Task has been done code 200"; //for test

    }else if(response_code == "401"){

        qDebug() <<" code is 401 retry"; //for test

    } else if(response_code == "404"){

        qDebug() <<" code is 404!!!"; //for test
    }
}

void APIManager::Write_chat_folder(const QString &target_user, const QJsonObject &response){
    QString filename = target_user +".txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        // Extract src, dst, and body from the response
        QString src = response.value("block").toObject().value("src").toString();
        QString dst = response.value("block").toObject().value("dst").toString();
        QString body = response.value("block").toObject().value("body").toString();

        // Write the extracted values to the file
        stream << src <<" -> "<<dst <<":::"<<body<<"\n";

        file.close();
        qDebug() << "Response written to file: " << filename;
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
        //          -------------------------------------------------------------
        //        Matins edit please dont do anything with this my friend

        for (const QString& key : jsonObject.keys()) {
            if (key.startsWith("block")) {
                QJsonObject blockObject = jsonObject.value(key).toObject();
                if (!(blockObject.contains("dst")) && blockObject.contains("src") && !(blockObject.contains("body"))) {
                    QString src = blockObject.value("src").toString();

                    getUsersChat(src);

                }
                if ((blockObject.contains("dst")) && blockObject.contains("src") && (blockObject.contains("body"))) {
                    QString dst = blockObject.value("dst").toString();
                    QString src = blockObject.value("src").toString();
                    QString final = src+"_to_"+dst;
                    temp_json_object = jsonObject;
                    Write_chat_folder(final,temp_json_object);

                    break;
                }
            }
        }

        //          -------------------------------------------------------------
        if (jsonObject.contains("token")) {
            // Extract the token value
            QString extractedToken = jsonObject["token"].toString();
            saveTokenToFile(extractedToken);
            // qDebug() << "Token is: " << extractedToken;
        }


        //           Check if the response contains a "code"


        if (jsonObject.contains("code")) {
            // Extract the code and message values
            QString extractedCode = jsonObject["code"].toString();
            QString extractedMessage = jsonObject["message"].toString();
            saveCodeToFile(extractedCode);
            // Checking code
            check_response_code(extractedCode, extractedMessage);
            RemoveCode();
            // qDebug() << "ResponseCode is: " << extractedCode;
        }

    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater(); // Safely release the memory
}
