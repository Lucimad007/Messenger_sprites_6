#include "mainwindow.h"
#include "user.h"
#include <QApplication>
#include <QDir>
#include "apimanager.h"
#include "app.h"
QApplication* application;
MainWindow* mainWindow;
APIManager apiManager;

int main(int argc, char *argv[])
{
    application = new QApplication(argc, argv);
    mainWindow = new MainWindow;
    mainWindow->show();
//    QFileInfo info = QFileInfo(QDir::currentPath());
//    qDebug() << info.dir().path() ;
//    return 0;

    User farhad("ASGHAR", "9876", "asgharFarhadi@gmail.com");
    User salar("Salar", "3221", "salarmanam@gmail.com");

    // User matin("matiiiiiiinTEST", "1234", "matin@gmail.com");
    // User maxv("max", "1111", "Maxmaz");

    // apiManager.logIn(maxv);
    // apiManager.signUp(maxv);
    // apiManager.logOut(farhad);
     //apiManager.logIn(farhad);
    //apiManager.getUsersList();
    // apiManager.getGroupList();
    // apiManager.getChannelList();

    //apiManager.logOut(farhad);
   // apiManager.logIn(farhad);

   //QString temp= "farhadg2";
   //apiManager.Read_group_folder(temp);


    //QString src ="ASGHAR";
    //QString dst = "max";
    //apiManager.Read_user_folder(src,dst);


    //apiManager.get_list_of_users();
    return application->exec();
}
