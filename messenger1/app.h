#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include "user.h"
#include "message.h"

namespace Ui {
class App;
}

class App : public QMainWindow
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);
    void addChatPrototype(User& user);
    void addMessage(Message& message);
    ~App();

private slots:
    void on_profileButton_clicked();

    void on_optionsButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::App *ui;
    QSplitter* splitter;
    QSplitter* chatSplitter;
    QWidget* profileWidget = nullptr;   //initializing it as nullptr prevents app from unexpected crashes
    QWidget* optionsWidget = nullptr;   //initializing it as nullptr prevents app from unexpected crashes
};

#endif // APP_H
