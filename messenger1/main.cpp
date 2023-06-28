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
    //   User farhad = User("ASGHAR","9876","asgharFarhadi@gmail.com");
    //    User salar = User("Salar","3221","salarmanam@gmail.com");
    //    User matin = User("matiiiiiiinTEST","1234","matin@gmail.com");

//       User maxv = User("max","1111","Maxmaz");
//        apiManager.logIn(maxv);
//        apiManager.signUp(maxv);


 //--------------------------------------------------

    //I have to note that every time we want to creat group or channel or ... we have to pass the const
    //so I declared the //      QString title = "farhadg"; as an example


//      apiManager.logOut(farhad);
//      apiManager.logIn(farhad);
//      QString title = "farhadg";
//      QString topic = "chess";
//      apiManager.creatGroup(farhad,title,topic);


//         QString title = "farhadg2";
//         QString topic = "chess2";
//         apiManager.creatGroup(farhad,title,topic);

//         QString title2 = "farhadg22";
//         QString topic2 = "chess22";
//         apiManager.creatGroup(farhad,title2,topic2);

//             QString title_chan = "farhadchan";
//             QString topic_chan = "math";
//             apiManager.creatChannel(farhad,title_chan,topic_chan);

//             QString title_group = "farhadgr";
//             QString topic_group = "Fun";
//            apiManager.creatGroup(farhad,title_group,topic_group);

 //--------------------------------------------------

    //sign up test

    //apiManager.signUp(farhad);
    //apiManager.signUp(salar);

    //login test
//    apiManager.logIn(matin);
//    apiManager.logIn(farhad);
//    apiManager.logIn(salar);

    //Logout test
//    apiManager.logOut(matin);

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
