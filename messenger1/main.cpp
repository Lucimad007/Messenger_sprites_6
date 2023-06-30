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
      User farhad = User("ASGHAR","9876","asgharFarhadi@gmail.com");
       User salar = User("Salar","3221","salarmanam@gmail.com");
    //    User matin = User("matiiiiiiinTEST","1234","matin@gmail.com");

//       User maxv = User("max","1111","Maxmaz");
//        apiManager.logIn(maxv);
//        apiManager.signUp(maxv);

    //apiManager.logOut(farhad);
    //apiManager.logIn(farhad);


   QString group1 = "farhadg";
//       QString body1 ="hello to this new group";
//              QString body2 ="hello to this new group2";
//                     QString body3 ="hello to this new group3";

//              QString group2 ="farhadg2";
//    apiManager.sendMessageGroup(group2,body1);
//    apiManager.sendMessageGroup(group2,body2);
//    apiManager.sendMessageGroup(group2,body3);
//       apiManager.getGroupList();
//apiManager.getUsersList();
apiManager.getGroupList();
//apiManager.getChannelList();

 //--------------------------------------------------

    return a.exec();
}
