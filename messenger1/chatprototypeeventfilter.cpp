#include "chatprototypeeventfilter.h"
#include "mainwindow.h"
#include "apimanager.h"
#include <QLabel>
extern MainWindow* mainWindow;
extern APIManager apiManager;

bool ChatPrototypeEventFilter::eventFilter(QObject* obj, QEvent* event){
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            qDebug() << "Widget clicked!";
            // Perform your action here when the widget is clicked
            QLabel* shownTypeLabel = mainWindow->getApp()->findChild<QLabel*>("shownTypeLabel",Qt::FindChildrenRecursively);
            QLabel* shownNameLabel = mainWindow->getApp()->findChild<QLabel*>("shownNameLabel",Qt::FindChildrenRecursively);
            QLabel* prototypeNameLabel = obj->findChild<QLabel*>("nameLabel",Qt::FindChildrenRecursively);
            QLabel* typeLabel = obj->findChild<QLabel*>("typeLabel",Qt::FindChildrenRecursively);
            shownNameLabel->setText(prototypeNameLabel->text());
            shownTypeLabel->setText(typeLabel->text());
            QString type = typeLabel->text();
            QString dstName = shownNameLabel->text();
            mainWindow->getApp()->clearChatArea();   

            //if connected
            if(apiManager.getIsOnline()){
                if(type == "user"){
                    apiManager.getUsersChat(dstName);
                } else if(type == "channel"){
                    apiManager.getChannelChat(dstName);
                } else if(type == "group"){
                    apiManager.getGroupChat(dstName);
                }
            } else {    //if disconnected
                QJsonObject reply;
                if(type == "user"){
                    reply = apiManager.Read_user_folder(mainWindow->getCurrentUser().getUsername(),dstName);
                    if(reply.isEmpty())
                    reply = apiManager.Read_user_folder(dstName,mainWindow->getCurrentUser().getUsername());
                } else if(type == "channel"){
                    reply = apiManager.Read_channel_folder(dstName);
                } else if(type == "group"){
                    reply = apiManager.Read_group_folder(dstName);
                }
                QString src,dst;
                for (auto it = reply.begin(); it != reply.end(); ++it) {
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
            }
            //loading messages
//            QString dstName = shownNameLabel->text();
//            QJsonObject json = apiManager.getus(mainWindow->getCurrentUser().getUsername(),dstName);
//            qDebug() << json <<  mainWindow->extractNumber(json["message"].toString());
//            for (auto it = json.begin(); it != json.end(); ++it) {
//                    if (it.key().startsWith("block")) {
//                        QJsonObject blockObject = it.value().toObject();
//                        QString body = blockObject.value("body").toString();
//                        QString src = blockObject.value("src").toString();
//                        User user(src,"","");   //it doesnt mather wether it is group or channel or user
//                        Message message(user,body);
//                        mainWindow->getApp()->addMessage(message);
//                        qDebug() << "Body:" << body;
//                    }
//                }
            // You can also access the widget using obj, if needed
            // For example:
            // QWidget* widget = qobject_cast<QWidget*>(obj);
        }
    }

    return QObject::eventFilter(obj, event);
}
