#ifndef ADDCONTACTEVENTFILTER_H
#define ADDCONTACTEVENTFILTER_H

#include <QEvent>
#include <QMouseEvent>
#include <QObject>

class AddContactEventFilter : public QObject
{
    Q_OBJECT

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void on_addButton_clicked();
private:
    QWidget *myWidget = nullptr;
};

#endif // ADDCONTACTEVENTFILTER_H
