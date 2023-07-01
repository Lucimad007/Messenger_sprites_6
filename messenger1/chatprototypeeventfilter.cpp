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
            mainWindow->getApp()->clearChatArea();
            // You can also access the widget using obj, if needed
            // For example:
            // QWidget* widget = qobject_cast<QWidget*>(obj);
        }
    }

    return QObject::eventFilter(obj, event);
}
