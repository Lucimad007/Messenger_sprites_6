#include "mainwindow.h"
#include "ui_Login.h"

#include <QApplication>
#include "apimanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    APIManager apiManager;
    apiManager.signUp("matiiiiiiinTEST", "1234");
    return a.exec();
}
