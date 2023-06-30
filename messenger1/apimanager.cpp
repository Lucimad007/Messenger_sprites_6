#include "apimanager.h"
#include<QUrlQuery>
#include "errordialog.h"

ErrorDialog* dialog;

QJsonObject temp_json_object;
QString main_user_chat;
QString where_flag;

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
    where_flag = "user";
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
    where_flag="group";
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
    where_flag ="channel";
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
void APIManager::Write_chat_folder(const QString &dssst, const QJsonObject &response){

    QString userDirectory = QDir::currentPath() + "/USER";
    QDir().mkpath(userDirectory);
    QString filename = dssst+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        for(const QString &key : response.keys()){
            if(key.startsWith("block")){
                QJsonObject blockObject = response.value(key).toObject();
                QString src = blockObject.value("src").toString();
                QString dst = blockObject.value("dst").toString();
                QString body = blockObject.value("body").toString();

                stream << src << " -> " <<dst <<" ::: " <<body<<"\n";
            }
        }

        file.close();
        qDebug() << "Response written to file: " << filePath <<"\n";
    }

}
void APIManager::Write_group_floder(const QString &dst, const QJsonObject &response){
    QString userDirectory = QDir::currentPath() + "/GROUP";
    QDir().mkpath(userDirectory);
    QString filename = dst+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);


        for(const QString &key : response.keys()){
            if(key.startsWith("block")){
                QJsonObject blockObject = response.value(key).toObject();
                QString src = blockObject.value("src").toString();
                QString body = blockObject.value("body").toString();

                stream << src <<" ::: " <<body<<"\n";
            }
        }

        file.close();
        qDebug() << "Response written to file: " << filePath <<"\n";
    }
}
void APIManager::Write_channel_floder(const QString &dst, const QJsonObject &response){
    QString userDirectory = QDir::currentPath() + "/CHANNEL";
    QDir().mkpath(userDirectory);
    QString filename = dst+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);


        for(const QString &key : response.keys()){
            if(key.startsWith("block")){
                QJsonObject blockObject = response.value(key).toObject();
                QString src = blockObject.value("src").toString();
                QString body = blockObject.value("body").toString();

                stream << src <<" ::: " <<body<<"\n";
            }
        }

        file.close();
        qDebug() << "Response written to file: " << filePath<<"\n";
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
void APIManager::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);
        qDebug() << "Response is: " << responseString;

        // Parse the JSON response
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
//-----------------------------------------------------------------------------------------------------
        // Matins edit

        for (const QString& key : jsonObject.keys()) {
            if (key.startsWith("block")) {
                QJsonObject blockObject = jsonObject.value(key).toObject();

                if ((blockObject.contains("dst")) && blockObject.contains("src") && (blockObject.contains("body"))) {
                    QString dst = blockObject.value("dst").toString();
                    QString src = blockObject.value("src").toString();
                    QString final = src + "_to_" + dst;
                    temp_json_object = jsonObject;

                    if (where_flag == "user") {
                        Write_chat_folder(final, temp_json_object);
                    }
                    else if (where_flag == "group") {
                        Write_group_floder(dst, temp_json_object);
                    }
                    else if (where_flag == "channel") {
                        Write_channel_floder(dst, temp_json_object);
                    }

                    break;
                }
                if (!(blockObject.contains("dst")) && blockObject.contains("src") && !(blockObject.contains("body"))) {
                    QString src = blockObject.value("src").toString();
                    getUsersChat(src);
                }
                if (blockObject.contains("group_name") && !(blockObject.contains("dst"))) {
                    QString group_name = blockObject.value("group_name").toString();
                    getGroupChat(group_name);
                }
                if (blockObject.contains("channel_name") && !(blockObject.contains("dst"))) {
                    QString channel_name = blockObject.value("channel_name").toString();
                    getChannelChat(channel_name);
                }
            }
        }
//-----------------------------------------------------------------------------------------------------
        if (jsonObject.contains("token")) {
            QString extractedToken = jsonObject["token"].toString();
            saveTokenToFile(extractedToken);
        }

        if (jsonObject.contains("code")) {
            QString extractedCode = jsonObject["code"].toString();
            QString extractedMessage = jsonObject["message"].toString();
            saveCodeToFile(extractedCode);
            check_response_code(extractedCode, extractedMessage);
            RemoveCode();
        }


        ///////////////////////////////////////////////////////////////
        //graphical content
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        QJsonObject replyJson = jsonDocument.object();

        if(replyJson["code"].toString() == "200"){
            if(replyJson["message"].toString() == "Signed Up Successfully"){

            } else if(replyJson["message"].toString() == "Logged in Successfully"){

            }

            } else if(replyJson["message"].toString() == "Logged Out Successfully"){

            } else if(replyJson["message"].toString() == "Group Created Successfully"){

            } else if(replyJson["message"].toString() == "Channel Created Successfully"){

            } else if(replyJson["message"].toString() == "Successfully Joined"){  //for both channel and group

            } else if(replyJson["message"].toString().contains("You Are in") && replyJson["message"].toString().contains("Group")){

            } else if(replyJson["message"].toString().contains("You Are in") && replyJson["message"].toString().contains("Channel")){

            } else if(replyJson["message"].toString().contains("You Chat With") && replyJson["message"].toString().contains("User")){

            } else if(replyJson["message"].toString() == "Message Sent Successfully"){    //for user/channel/group

            } else if(replyJson["message"].toString().contains("There Are") && replyJson["message"].toString().contains("Message")){   //for user/channel/group

            } else {
            dialog = new ErrorDialog(nullptr,replyJson["code"].toString(),replyJson["message"].toString());
            dialog->show();
        }

        //qDebug() << "test : " << replyJson["code"].toString();

       ///////////////////////////////////////////////////////////////

    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater(); // Safely release the memory
}
