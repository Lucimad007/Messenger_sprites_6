#include "chatprototypeeventfilter.h"

bool ChatPrototypeEventFilter::eventFilter(QObject* obj, QEvent* event){
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            qDebug() << "Widget clicked!";
            // Perform your action here when the widget is clicked

            // You can also access the widget using obj, if needed
            // For example:
            // QWidget* widget = qobject_cast<QWidget*>(obj);
        }
    }

    return QObject::eventFilter(obj, event);
}
