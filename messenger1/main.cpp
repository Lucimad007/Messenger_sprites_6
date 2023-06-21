#include "mainwindow.h"
#include "user.h"
#include <QApplication>
#include "apimanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    APIManager apiManager;
    User farhad = User("ASGHAR","9876","asgharFarhadi@gmail.com");
    User salar = User("Salar","3221","salarmanam@gmail.com");
    User matin = User("matiiiiiiinTEST","1234");
    //sign up test

//    apiManager.signUp(farhad);
//    apiManager.signUp(salar);

    //login test
    //apiManager.logIn("matiiiiiiinTEST","1234");


    //Logout test
    //apiManager.logOut("matiiiiiiinTEST","1234");

    //Creat_group test
    //apiManager.creatGroup("107beb12166aa8961be46848a7bc19c3","First_Matin_Group","Chess");

    //Creat_Channel test
    //apiManager.creatChannel("107beb12166aa8961be46848a7bc19c3","First_matin_channel","Math");

    //getUsersList test ?????
    //getGroupList test ????
    //get ChannelList test???


    //Remmeber to overload this funcs with data !!!
    //getUsers Chat test?
    //apiManager.getUsersChat();

    //getGroup Chat test?
    //apiManager.getUsersChat();
    //apiManager.getChannelChat();

    //join tests
    //apiManager.joinGroup();
    //apiManager.joinChannel();

    //sending message test
    //apiManager.sendMessageUser();
    //apiManager.sendMessageGroup();
    //apiManager.sendMessageChannel();

    return a.exec();
}
