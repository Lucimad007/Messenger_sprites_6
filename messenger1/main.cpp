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
       QString user = "Salar";
       QString user2 = "max";
       QString user3 = "matiiiiiiinTEST";
       QString body = "Salam salar jan";
       QString body2 = "Salam max jan";
       QString body3 = "Salam matin jan";

//       apiManager.sendMessageUser(user2,body2);
//       apiManager.sendMessageUser(user3,body3);
//       apiManager.sendMessageUser(user2,body2);
//       apiManager.sendMessageUser(user3,body3);
//       apiManager.sendMessageUser(user2,body2);
//       apiManager.sendMessageUser(user3,body3);
//       apiManager.sendMessageUser(user2,body2);
//       apiManager.sendMessageUser(user3,body3);
//       apiManager.sendMessageUser(user2,body2);
//       apiManager.sendMessageUser(user3,body3);
//       apiManager.sendMessageUser(user2,body2);
//       apiManager.sendMessageUser(user3,body3);
 //  apiManager.logIn(farhad);
//apiManager.logOut(farhad);
                     //apiManager.getUsersChat(user2);
                   //  apiManager.getUsersList();
       apiManager.logOut(farhad);
 //--------------------------------------------------

    return a.exec();
}
