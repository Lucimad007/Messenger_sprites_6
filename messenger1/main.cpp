#include "mainwindow.h"

#include <QApplication>
#include "apimanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    APIManager apiManager;
    //sign up test
//    apiManager.signUp("matiiiiiiinTEST", "1234");

    //login test
    apiManager.logIn("matiiiiiiinTEST","1234");

    return a.exec();
}
