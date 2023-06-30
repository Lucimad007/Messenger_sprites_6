#include "mainwindow.h"
#include "user.h"
#include <QApplication>
#include "apimanager.h"
#include "app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    APIManager apiManager;
    User farhad("ASGHAR", "9876", "asgharFarhadi@gmail.com");
    User salar("Salar", "3221", "salarmanam@gmail.com");

    // User matin("matiiiiiiinTEST", "1234", "matin@gmail.com");
    // User maxv("max", "1111", "Maxmaz");

    // apiManager.logIn(maxv);
    // apiManager.signUp(maxv);
    // apiManager.logOut(farhad);
    // apiManager.logIn(farhad);
    // apiManager.getUsersList();
    // apiManager.getGroupList();
    // apiManager.getChannelList();

    return a.exec();
}
