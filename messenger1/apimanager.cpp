#include "apimanager.h"
#include "mainwindow.h"
#include<QUrlQuery>
#include "errordialog.h"
#include "qapplication.h"
extern QApplication* a;
extern MainWindow* mainWindow;
extern APIManager apiManager;

ErrorDialog* dialog;

QJsonObject temp_json_object;
QString main_user_chat;
QString where_flag;

APIManager::APIManager(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager,&QNetworkAccessManager::finished,this,&APIManager::onReplyFinished);
}
APIManager::~APIManager(){
    delete timer;
}
QTimer* APIManager::getTimer(){
    return timer;
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
    Delete_All_Files();  //to remove every Files we have saved in our project directory
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

    QJsonDocument jsonDocument(response);
    QByteArray jsonData = jsonDocument.toJson();

    QString userDirectory = QDir::currentPath() + "/USER";
    QDir().mkpath(userDirectory);
    QString filename = dssst+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write the JSON data to the file
        file.write(jsonData);

        // Close the file
        file.close();

        qDebug() << "JSON data saved to file: " << filePath <<"\n";
    } else {
        qDebug() << "Failed to save JSON data to file: " << filename;
    }
//    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QTextStream stream(&file);
//        for(const QString &key : response.keys()){
//            if(key.startsWith("block")){
//                QJsonObject blockObject = response.value(key).toObject();
//                QString src = blockObject.value("src").toString();
//                QString dst = blockObject.value("dst").toString();
//                QString body = blockObject.value("body").toString();

//                stream << src << " -> " <<dst <<" ::: " <<body<<"\n";
//            }
//        }

     //   file.close();
       // qDebug() << "Response written to file: " << filePath <<"\n";
   // }

}
void APIManager::Write_group_floder(const QString &dst, const QJsonObject &response){
    QJsonDocument jsonDocument(response);
    QByteArray jsonData = jsonDocument.toJson();

    QString userDirectory = QDir::currentPath() + "/GROUP";
    QDir().mkpath(userDirectory);
    QString filename = dst+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write the JSON data to the file
        file.write(jsonData);

        // Close the file
        file.close();

        qDebug() << "JSON data saved to file: " << filePath <<"\n";
    } else {
        qDebug() << "Failed to save JSON data to file: " << filename;
    }
//    QString userDirectory = QDir::currentPath() + "/GROUP";
//    QDir().mkpath(userDirectory);
//    QString filename = dst+".txt";
//    // Create the file inside the USER directory
//    QString filePath = userDirectory + "/" + filename;
//    QFile file(filePath);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QTextStream stream(&file);


//        for(const QString &key : response.keys()){
//            if(key.startsWith("block")){
//                QJsonObject blockObject = response.value(key).toObject();
//                QString src = blockObject.value("src").toString();
//                QString body = blockObject.value("body").toString();

//                stream << src <<" ::: " <<body<<"\n";
//            }
//        }

//        file.close();
//        qDebug() << "Response written to file: " << filePath <<"\n";
//    }
}
void APIManager::Write_channel_floder(const QString &dst, const QJsonObject &response){
    QJsonDocument jsonDocument(response);
    QByteArray jsonData = jsonDocument.toJson();

    QString userDirectory = QDir::currentPath() + "/CHANNEL";
    QDir().mkpath(userDirectory);
    QString filename = dst+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write the JSON data to the file
        file.write(jsonData);

        // Close the file
        file.close();

        qDebug() << "JSON data saved to file: " << filePath <<"\n";
    } else {
        qDebug() << "Failed to save JSON data to file: " << filename;
    }

//    QString userDirectory = QDir::currentPath() + "/CHANNEL";
//    QDir().mkpath(userDirectory);
//    QString filename = dst+".txt";
//    // Create the file inside the USER directory
//    QString filePath = userDirectory + "/" + filename;
//    QFile file(filePath);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QTextStream stream(&file);


//        for(const QString &key : response.keys()){
//            if(key.startsWith("block")){
//                QJsonObject blockObject = response.value(key).toObject();
//                QString src = blockObject.value("src").toString();
//                QString body = blockObject.value("body").toString();

//                stream << src <<" ::: " <<body<<"\n";
//            }
//        }

//        file.close();
//        qDebug() << "Response written to file: " << filePath<<"\n";
//    }
}
void APIManager::get_list_of(const QString type, const QJsonObject &response){
    QJsonDocument jsonDocument(response);
    QByteArray jsonData = jsonDocument.toJson();

    QString userDirectory = QDir::currentPath() + "/LIST";
    QDir().mkpath(userDirectory);
    QString filename = type+".txt";
    // Create the file inside the USER directory
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write the JSON data to the file
        file.write(jsonData);

        // Close the file
        file.close();

        qDebug() << "JSON data saved to file: " << filePath <<"\n";
    } else {
        qDebug() << "Failed to save JSON data to file: " << filename;
    }
}
QJsonObject APIManager::get_list_of_channels(){

    QString userDirectory = QDir::currentPath() + "/LIST";
    QDir().mkpath(userDirectory);
    QString filename = "channels.txt";
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filename;
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error while parsing JSON: " << parseError.errorString();
        return QJsonObject(); // Return an empty JSON object
    }


    if (!jsonDocument.isObject()) {
        qDebug() << "JSON data is not an object.";
        return QJsonObject(); // Return an empty JSON object if parsing results in a non-object
    }
    qDebug()<<jsonDocument.object();
    return jsonDocument.object();
}
QJsonObject APIManager::get_list_of_group(){
    QString userDirectory = QDir::currentPath() + "/LIST";
    QDir().mkpath(userDirectory);
    QString filename = "groups.txt";
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filename;
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error while parsing JSON: " << parseError.errorString();
        return QJsonObject(); // Return an empty JSON object
    }


    if (!jsonDocument.isObject()) {
        qDebug() << "JSON data is not an object.";
        return QJsonObject(); // Return an empty JSON object if parsing results in a non-object
    }
    qDebug()<<jsonDocument.object();
    return jsonDocument.object();
}
QJsonObject APIManager::get_list_of_users(){
    QString userDirectory = QDir::currentPath() + "/LIST";
    QDir().mkpath(userDirectory);
    QString filename = "users.txt";
    QString filePath = userDirectory + "/" + filename;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filename;
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error while parsing JSON: " << parseError.errorString();
        return QJsonObject(); // Return an empty JSON object
    }


    if (!jsonDocument.isObject()) {
        qDebug() << "JSON data is not an object.";
        return QJsonObject(); // Return an empty JSON object if parsing results in a non-object
    }
    qDebug()<<jsonDocument.object();
    return jsonDocument.object();
}
QJsonObject APIManager::Read_group_folder(const QString &dst){
    QString filename = "GROUP/" + dst + ".txt";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filename;
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error while parsing JSON: " << parseError.errorString();
        return QJsonObject(); // Return an empty JSON object
    }


    if (!jsonDocument.isObject()) {
        qDebug() << "JSON data is not an object.";
        return QJsonObject(); // Return an empty JSON object if parsing results in a non-object
    }
    //qDebug()<<jsonDocument.object();
    return jsonDocument.object();
}
QJsonObject APIManager::Read_channel_folder(const QString &dst){
    QString filename = "CHANNEL/" + dst + ".txt";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filename;
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error while parsing JSON: " << parseError.errorString();
        return QJsonObject(); // Return an empty JSON object
    }


    if (!jsonDocument.isObject()) {
        qDebug() << "JSON data is not an object.";
        return QJsonObject(); // Return an empty JSON object if parsing results in a non-object
    }
    //qDebug()<<jsonDocument.object();
    return jsonDocument.object();
}
QJsonObject APIManager::Read_user_folder(const QString &src, const QString &dst){
    QString filename = "USER/" + src+"_to_"+dst + ".txt";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filename;
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error while parsing JSON: " << parseError.errorString();
        return QJsonObject(); // Return an empty JSON object
    }


    if (!jsonDocument.isObject()) {
        qDebug() << "JSON data is not an object.";
        return QJsonObject(); // Return an empty JSON object if parsing results in a non-object
    }
    //qDebug()<<jsonDocument.object();
    return jsonDocument.object();
}
void APIManager::Delete_All_Files(){
    QString baseDirectory = QDir::currentPath(); // this will give us where we are in the project


    QString usersDirectory = baseDirectory + "/USER";
    QString channelDirectory = baseDirectory + "/CHANNEL";
    QString listDirectory = baseDirectory + "/LIST";
    QString groupDirectory = baseDirectory + "/GROUP";        
    QDir(usersDirectory).removeRecursively();
    QDir(channelDirectory).removeRecursively();
    QDir(listDirectory).removeRecursively();
    QDir(groupDirectory).removeRecursively();
    qDebug() <<"Removed all files "<<"\n";
}
bool APIManager::getIsOnline(){
    return isOnline;
}
void APIManager::setIsOnline(bool online){
    isOnline = online;
}
void APIManager::Thread_task(){
//        getUsersList();
//        getChannelList();
//        getGroupList();
//        // Sleep for 3 second
//        QThread::msleep(3000);

}
void APIManager::check_response_code(const QString& response_code, const QString& server_message)
{
    if (response_code == "200" && server_message == "Logged in Successfully") {
        qDebug() << "Task has been done code 200"; // for test

//        //using thread Instead of QTimer
//        QThread *thread = new QThread;
//        moveToThread(thread);
//        connect(thread,&QThread::started,this,&APIManager::Thread_task);
//        thread->start();

//            //working with QTimer
                timer = new QTimer(this);
                timer->setInterval(3000); // equal to 3 seconds

                connect(timer, &QTimer::timeout, this, [&]() {
                    QString type = mainWindow->getApp()->getCurrentType();
                    QString dst = mainWindow->getApp()->getShownName();
                    if(type == "user")
                        getUsersChat(dst);
                    else if(type == "channel")
                        getChannelChat(dst);
                    else if(type == "group")
                        getGroupChat(dst);
                    getUsersList();
                    getChannelList();
                    getGroupList();

                });

                timer->start();
    }
    else if (response_code == "401") {
        qDebug() << "code is 401 retry"; // for test
    }
    else if (response_code == "404") {
        qDebug() << "code is 404!!!"; // for test
    }
}

void APIManager::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        isOnline = true;
        if(mainWindow->getApp() != nullptr){
            if(mainWindow->getApp()->getConnectionLabel() != nullptr)
                mainWindow->getApp()->getConnectionLabel()->setText("connected");
            if(mainWindow->getApp()->getConnectionCheckBox() != nullptr){
                mainWindow->getApp()->getConnectionCheckBox()->setChecked(true);
            }
        }
            this->currentUser = mainWindow->getCurrentUser();   //pairing two users
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);
        qDebug() << "Response is: " << responseString;

        // Parse the JSON response
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
//-----------------------------------------------------------------------------------------------------
        // working with file for offline mode

//        for (const QString& key : jsonObject.keys()) {
//            if (key.startsWith("block")) {
//                QJsonObject blockObject = jsonObject.value(key).toObject();

//                if ((blockObject.contains("dst")) && blockObject.contains("src") && (blockObject.contains("body"))) {
//                    QString dst = blockObject.value("dst").toString();
//                    QString src = blockObject.value("src").toString();
//                    QString final = src + "_to_" + dst;
//                    temp_json_object = jsonObject;

//                    if (where_flag == "user") {
//                        Write_chat_folder(final, temp_json_object);
//                    }
//                    else if (where_flag == "group") {
//                        Write_group_floder(dst, temp_json_object);
//                    }
//                    else if (where_flag == "channel") {
//                        Write_channel_floder(dst, temp_json_object);
//                    }

//                    break;
//                }
//                if (!(blockObject.contains("dst")) && blockObject.contains("src") && !(blockObject.contains("body"))) {
//                    QString type = "users";
//                    get_list_of(type,jsonObject);
//                    QString src = blockObject.value("src").toString();
//                    getUsersChat(src);
//                }
//                if (blockObject.contains("group_name") && !(blockObject.contains("dst"))) {
//                    QString type = "groups";
//                    get_list_of(type,jsonObject);
//                    QString group_name = blockObject.value("group_name").toString();
//                    getGroupChat(group_name);
//                }
//                if (blockObject.contains("channel_name") && !(blockObject.contains("dst"))) {
//                    QString type = "channels";
//                    get_list_of(type,jsonObject);
//                    QString channel_name = blockObject.value("channel_name").toString();
//                    getChannelChat(channel_name);
//                }
//            }
//        }
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
                mainWindow->setLoginUI();
            } else if(replyJson["message"].toString() == "Logged in Successfully"){
                mainWindow->startApp();
                getUsersList();
                getGroupList();
                getChannelList();
            } else if(replyJson["message"].toString() == "You are already logged in!"){
                this->logOut(currentUser);
                this->logIn(currentUser);
            } else if(replyJson["message"].toString() == "Logged Out Successfully"){
                QString token = "";
                currentUser.setToken(token);   //token is no longer available
            } else if(replyJson["message"].toString() == "Group Created Successfully"){
                Group group = mainWindow->getApp()->getPendingGroup();
                mainWindow->getApp()->addChatPrototype(group);
            } else if(replyJson["message"].toString() == "Channel Created Successfully"){
                Channel channel = mainWindow->getApp()->getPendingChannel();
                mainWindow->getApp()->addChatPrototype(channel);
            } else if(replyJson["message"].toString() == "Successfully Joined"){  //for both channel and group
                if(mainWindow->getApp()->getCurrentPending() == CHANNEL){
                    Channel channel = mainWindow->getApp()->getPendingChannel();
                    mainWindow->getApp()->addChatPrototype(channel);
                } else if(mainWindow->getApp()->getCurrentPending() == GROUP){
                    Group group = mainWindow->getApp()->getPendingGroup();
                    mainWindow->getApp()->addChatPrototype(group);
                }
            } else if(replyJson["message"].toString().contains("You Are in") && replyJson["message"].toString().contains("Group")){
                QJsonObject json = get_list_of_group();
                int diffrenece = mainWindow->extractNumber(replyJson["message"].toString()).toInt() - mainWindow->getApp()->getNumberOfGroups().toInt() + 2;
                QString type = "groups";
                get_list_of(type,jsonObject);
                qDebug() << replyJson <<  mainWindow->extractNumber(replyJson["message"].toString());
                for (auto it = replyJson.end() - diffrenece; it != replyJson.end(); ++it) {
                        if (it.key().startsWith("block")) {
                            QJsonObject blockObject = it.value().toObject();
                            QString src = blockObject.value("group_name").toString();
                            Group group(src);
                            mainWindow->getApp()->addChatPrototype(group);
                            qDebug() << "Body:" << src;
                        }
                    }
                mainWindow->getApp()->setNumberOfGroups(mainWindow->extractNumber(replyJson["message"].toString()));
            } else if(replyJson["message"].toString().contains("You Are in") && replyJson["message"].toString().contains("Channel")){
                QJsonObject json = get_list_of_channels();
                int diffrenece = mainWindow->extractNumber(replyJson["message"].toString()).toInt() - mainWindow->getApp()->getNumberOfChannels().toInt() + 2;
                QString type = "channels";
                get_list_of(type,jsonObject);
                qDebug() << replyJson <<  mainWindow->extractNumber(replyJson["message"].toString());
                for (auto it = replyJson.end() - diffrenece; it != replyJson.end(); ++it) {
                        if (it.key().startsWith("block")) {
                            QJsonObject blockObject = it.value().toObject();
                            QString src = blockObject.value("channel_name").toString();
                            Channel channel(src);
                            mainWindow->getApp()->addChatPrototype(channel);
                            qDebug() << "Body:" << src;
                        }
                    }
                mainWindow->getApp()->setNumberOfChannels(mainWindow->extractNumber(replyJson["message"].toString()));
            } else if(replyJson["message"].toString().contains("You Have Chat") && replyJson["message"].toString().contains("User")){
                QJsonObject json = get_list_of_users();
                int diffrenece = mainWindow->extractNumber(replyJson["message"].toString()).toInt() - mainWindow->getApp()->getNumberOfUsers().toInt() + 2;
                QString type = "users";
                get_list_of(type,jsonObject);
                qDebug() << replyJson <<  mainWindow->extractNumber(replyJson["message"].toString());
                for (auto it = replyJson.end() - diffrenece; it != replyJson.end(); ++it) {
                        if (it.key().startsWith("block")) {
                            QJsonObject blockObject = it.value().toObject();
                            QString src = blockObject.value("src").toString();
                            QString dst = blockObject.value("dst").toString();
                            User user(src,"","");
                            mainWindow->getApp()->addChatPrototype(user);
                            qDebug() << "Body:" << src;
                        }
                    }
               mainWindow->getApp()->setNumberOfUsers(mainWindow->extractNumber(replyJson["message"].toString()));
            } else if(replyJson["message"].toString() == "Message Sent Successfully"){    //for user/group
                Message message = mainWindow->getApp()->getPendingMessage();
                mainWindow->getApp()->addMessage(message);
            } else if(replyJson["message"].toString() == "Message Successfully Sent") {     //for channel
                Message message = mainWindow->getApp()->getPendingMessage();
                mainWindow->getApp()->addMessage(message);
            } else if(replyJson["message"].toString().contains("There Are") && replyJson["message"].toString().contains("Message")){   //for user/channel/group
                qDebug() << replyJson <<  mainWindow->extractNumber(replyJson["message"].toString());
                int diffrenece = mainWindow->extractNumber(replyJson["message"].toString()).toInt() - mainWindow->getApp()->getNumberOfMessages() + 2;
                QString src,dst;
                for (auto it = replyJson.end() - diffrenece; it != replyJson.end(); ++it) {
                        if (it.key().startsWith("block")) {
                            QJsonObject blockObject = it.value().toObject();
                            QString body = blockObject.value("body").toString();
                            src = blockObject.value("src").toString();
                            dst = blockObject.value("dst").toString();
                            User user(src,"","");   //it doesnt mather wether it is group or channel or user
                            Message message(user,body);
                            mainWindow->getApp()->addMessage(message);
                            qDebug() << "Body:" << body;
                        }
                    }

                QString final = src + "_to_" + dst;
                if(where_flag == "channel")
                     Write_channel_floder(dst,replyJson);
                else if(where_flag == "user")
                    Write_chat_folder(final,replyJson);
                else if(where_flag == "group")
                    Write_group_floder(dst,replyJson);
                }
            } else {
            dialog = new ErrorDialog(nullptr,replyJson["code"].toString(),replyJson["message"].toString());
            dialog->show();

        }

        //qDebug() << "test : " << replyJson["code"].toString();

       ///////////////////////////////////////////////////////////////

    } else {
        if(mainWindow->getApp() != nullptr){
            if(mainWindow->getApp()->getConnectionLabel() != nullptr)
                mainWindow->getApp()->getConnectionLabel()->setText("disconnected");
            if(mainWindow->getApp()->getConnectionCheckBox() != nullptr){
                mainWindow->getApp()->getConnectionCheckBox()->setChecked(false);
            }
        }
        qDebug() << "Error: " << reply->errorString();
        qDebug()<<"this is a test";
        isOnline = false;
    }

    reply->deleteLater(); // Safely release the memory
}
