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

private slots:
    void on_profileButton_clicked();

private:
    Ui::App *ui;
    QSplitter* splitter;
    QWidget* profileWidget;
};

#endif // APP_H
