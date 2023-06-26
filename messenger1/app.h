#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include "user.h"

namespace Ui {
class App;
}

class App : public QMainWindow
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);
    void addChatPrototype(User& user);
    ~App();

private:
    Ui::App *ui;
    QSplitter* splitter;
};

#endif // APP_H
