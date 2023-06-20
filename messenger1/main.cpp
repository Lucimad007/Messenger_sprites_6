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
    //apiManager.logIn("matiiiiiiinTEST","1234");


    //Logout test
    //apiManager.logOut("matiiiiiiinTEST","1234");

    //Creat_group test
    apiManager.creatGroup("107beb12166aa8961be46848a7bc19c3","First_Matin_Group","Chess");
    return a.exec();
}
