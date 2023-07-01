#include "chatprototypeeventfilter.h"
#include "mainwindow.h"
#include "apimanager.h"
#include <QLabel>
extern MainWindow* mainWindow;
extern APIManager apiManager;
QString extractNumber(const QString& inputString)
{
    qDebug() << inputString;
    QRegularExpression re("-\\d+-");
    QRegularExpressionMatch match = re.match(inputString);

    if (match.hasMatch()) {
        QString matchedString = match.captured(0);
        // Remove the hyphens from the matched string
        matchedString.remove('-');
        return matchedString;
    }

    // Return an empty string if no match is found
    return QString();
}
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
            mainWindow->getApp()->clearChatArea();

            //loading messages
            QString dstName = shownNameLabel->text();
            QJsonObject json = apiManager.Read_user_folder(mainWindow->getCurrentUser().getUsername(),dstName);
            qDebug() << json <<  extractNumber(json["message"].toString());
            for (auto it = json.begin(); it != json.end(); ++it) {
                    if (it.key().startsWith("block")) {
                        QJsonObject blockObject = it.value().toObject();
                        QString body = blockObject.value("body").toString();
                        QString src = blockObject.value("src").toString();
                        User user(src,"","");   //it doesnt mather wether it is group or channel or user
                        Message message(user,body);
                        mainWindow->getApp()->addMessage(message);
                        qDebug() << "Body:" << body;
                    }
                }
            // You can also access the widget using obj, if needed
            // For example:
            // QWidget* widget = qobject_cast<QWidget*>(obj);
        }
    }

    return QObject::eventFilter(obj, event);
}
