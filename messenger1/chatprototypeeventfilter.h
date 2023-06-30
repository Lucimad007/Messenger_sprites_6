#ifndef CHATPROTOTYPEEVENTFILTER_H
#define CHATPROTOTYPEEVENTFILTER_H
#include <QEvent>
#include <QMouseEvent>
#include <QObject>

class ChatPrototypeEventFilter : public QObject
{
    Q_OBJECT

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

};

#endif // CHATPROTOTYPEEVENTFILTER_H
