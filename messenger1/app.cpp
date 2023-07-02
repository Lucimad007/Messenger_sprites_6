#include <QFileInfo>
#include <QFile>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QSplitter>
#include <QSizePolicy>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QPalette>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QRadioButton>
#include <QCheckBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "apimanager.h"
#include "chatprototypeeventfilter.h"
#include "addcontacteventfilter.h"
#include "app.h"
#include "message.h"
#include "ui_app.h"

extern MainWindow* mainWindow;
extern APIManager apiManager;

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App),
    pendingMessage(mainWindow->getCurrentUser(),"")
{
    ui->setupUi(this);
    //ui->chatPrototypeWidget->setVisible(false);
    this->setWindowTitle("Sprites");
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);     //making window not resizeable
    ui->chatPrototypeScroll->setWidgetResizable(true);
    ui->chatScrollArea->setWidgetResizable(true);
    splitter = new QSplitter(Qt::Vertical);
    chatSplitter = new QSplitter(Qt::Vertical);
    ui->chatPrototypeScroll->setWidget(splitter);
    ui->chatScrollArea->setWidget(chatSplitter);
    AddContactEventFilter* eventFilter = new AddContactEventFilter();
    ui->addContactView->installEventFilter(eventFilter);
    //setting path of default profile picture
    if(load_profile_path() == ""){
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        profilePath = iconInfo.absolutePath() + "/ICons/avatar.ico";
    } else {
        profilePath = load_profile_path();
    }

    //setting scroll bar of chat area always bottom by default
    QScrollBar* verticalScrollBar = ui->chatScrollArea->verticalScrollBar();
    connect(verticalScrollBar, &QScrollBar::rangeChanged, [=](int min, int max) {
        // Set the scrollbar value to the maximum
        verticalScrollBar->setValue(max);});


    //setting primary icons and background
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/Logo/spritesLogo.jpeg";
        QString profileDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
        QString addContactDirectory = iconInfo.absolutePath() + "/ICons/contact-us.ico";
        QString chatBackgroundDirectory = iconInfo.absolutePath() + "/ICons/backgrounds/chat-background.jpg";
        QFile spritesIcon(iconDirectory);
        QFile profileIcon(profileDirectory);
        QFile addContactIcon(addContactDirectory);
        QFile chatBackgroundIcon(chatBackgroundDirectory);
        if(!spritesIcon.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        this->setWindowIcon(*icon);
        if(!profileIcon.exists())
            throw("Icon Not Found.");
        QIcon *profile = new QIcon(profileDirectory);
        QPixmap pixMap = profile->pixmap(ui->profilePicture->width(),ui->profilePicture->height());
        QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixMap);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addItem(pixItem);
        ui->profilePicture->setScene(scene);
        if(!addContactIcon.exists())
            throw("Icon Not Found.");
        QIcon *addContact = new QIcon(addContactDirectory);
        QPixmap pixMapContact = addContact->pixmap(ui->addContactView->width()*2/3,ui->addContactView->height()*2/3);
        QGraphicsPixmapItem* pixItemContact = new QGraphicsPixmapItem(pixMapContact);
        QGraphicsScene* sceneContact = new QGraphicsScene();
        sceneContact->addItem(pixItemContact);
        ui->addContactView->setScene(sceneContact);
        if(!chatBackgroundIcon.exists())
            throw("Icon Not Found.");
        QIcon *chatBackground = new QIcon(chatBackgroundDirectory);
        QPixmap pixMapChatBackground = chatBackground->pixmap(ui->chatBackgroundView->width(),ui->chatBackgroundView->height());
        QGraphicsPixmapItem* pixItemChatBackground = new QGraphicsPixmapItem(pixMapChatBackground);
        QGraphicsScene* sceneChatBackground = new QGraphicsScene();
        sceneChatBackground->addItem(pixItemChatBackground);
        ui->chatBackgroundView->setScene(sceneChatBackground);
        ui->chatBackgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->chatBackgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } catch(char const* error){
        qDebug() << error ;
    }

    //setting primary backgrounds
    try{
        QString backgroundPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo backgroundInfo(backgroundPath);
        QString backgroundDirectory = backgroundInfo.absolutePath() + "/ICons/backgrounds/bg4.jpeg";
        QPixmap chatBackground(backgroundDirectory);
        QPalette palette;
        QBrush brush(chatBackground);
        palette.setBrush(QPalette::Base,brush);
        ui->chatScrollArea->viewport()->setAutoFillBackground(true);
        ui->chatScrollArea->setPalette(palette);
    } catch(char const* error){
        qDebug() << error ;
    }


//    //testing chatprototype widget
//    User testUser("iutgram","5973","random@gmail.com");
//    Channel channel("iutgram");
//    Group group("iutgram");
//    for(int i=0;i<20;i++){
//        if(i%3==0)
//            addChatPrototype(testUser);
//        else if(i%3 == 1)
//            addChatPrototype(channel);
//        else if(i%3 == 2)
//            addChatPrototype(group);
//    }

//    //testing message widget
//    User user("Ali","1234","ali@gmail.com");
//    Message test(user,"This is a test");
//    for(int i=0;i<20;i++)
//        addMessage(test);
}

QString App::getCurrentType(){
    return ui->shownTypeLabel->text();
}

Group App::getPendingGroup(){
    return pendingGroup;
}

Channel App::getPendingChannel(){
    return pendingChannel;
}

CurrentPending App::getCurrentPending(){
    return currentPending;
}

Message App::getPendingMessage(){
    return pendingMessage;
}

void App::setNumberOfChannels(QString number){
    this->numberOfChannels = number;
}

QString App::getNumberOfChannels(){
    return numberOfChannels;
}
void App::setNumberOfGroups(QString number){
    this->numberOfGroups = number;
}

QString App::getNumberOfGroups(){
    return numberOfGroups;
}

void App::setNumberOfUsers(QString number){
    this->numberOfUsers = number;
}

QString App::getNumberOfUsers(){
    return numberOfUsers;
}

int App::getNumberOfMessages(){
    return chatSplitter->count();
}

QString App::getShownName(){
    return ui->shownNameLabel->text();
}

void App::setShownName(QString name){
    ui->shownNameLabel->setText(name);
}

QString App::getShownType(){
    return ui->shownTypeLabel->text();
}

void App::setShownType(QString name){
    ui->shownTypeLabel->setText(name);
}

void App::addChatPrototype(User& user){
    QGraphicsView* profilePicture;
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/chatprototype.ui";

    QFile file(sourceDirectory);
    try{
        file.open(QFile::ReadOnly);
        if(!file.isOpen())
            throw(file.errorString());

        QWidget *myWidget = loader.load(&file, this);
        ChatPrototypeEventFilter* eventFilter = new ChatPrototypeEventFilter();
        myWidget->installEventFilter(eventFilter);
        myWidget->setFixedSize(myWidget->width(),myWidget->height());
        file.close();

        QLabel* nameLabel = myWidget->findChild<QLabel*>("nameLabel",Qt::FindChildOption::FindChildrenRecursively);
        QLabel* typeLabel = myWidget->findChild<QLabel*>("typeLabel",Qt::FindChildOption::FindChildrenRecursively);
        profilePicture = myWidget->findChild< QGraphicsView*>("profilePicture",Qt::FindChildOption::FindChildrenRecursively);
        if(nameLabel != nullptr)
            nameLabel->setText(user.getUsername());
        else
            return;
        if(typeLabel != nullptr)
            typeLabel->setText("user");
        else
            return;

        splitter->addWidget(myWidget);
    }catch(QString error){
        qDebug() << error;
    }

    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        QPixmap pixMap = icon->pixmap(profilePicture->width(),profilePicture->height());
        QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixMap);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addItem(pixItem);
        profilePicture->setScene(scene);

    } catch(char const* error){
        qDebug() << error ;
    }
}

void App::addChatPrototype(Channel& channel){
    QGraphicsView* profilePicture;
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/chatprototype.ui";

    QFile file(sourceDirectory);
    try{
        file.open(QFile::ReadOnly);
        if(!file.isOpen())
            throw(file.errorString());

        QWidget *myWidget = loader.load(&file, this);
        ChatPrototypeEventFilter* eventFilter = new ChatPrototypeEventFilter();
        myWidget->installEventFilter(eventFilter);
        myWidget->setFixedSize(myWidget->width(),myWidget->height());
        file.close();

        QLabel* nameLabel = myWidget->findChild<QLabel*>("nameLabel",Qt::FindChildOption::FindChildrenRecursively);
        QLabel* typeLabel = myWidget->findChild<QLabel*>("typeLabel",Qt::FindChildOption::FindChildrenRecursively);
        profilePicture = myWidget->findChild< QGraphicsView*>("profilePicture",Qt::FindChildOption::FindChildrenRecursively);
        if(nameLabel != nullptr)
            nameLabel->setText(channel.getName());
        else
            return;
        if(typeLabel != nullptr)
            typeLabel->setText("channel");
        else
            return;

        splitter->addWidget(myWidget);
    }catch(QString error){
        qDebug() << error;
    }

    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        QPixmap pixMap = icon->pixmap(profilePicture->width(),profilePicture->height());
        QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixMap);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addItem(pixItem);
        profilePicture->setScene(scene);

    } catch(char const* error){
        qDebug() << error ;
    }
}

void App::addChatPrototype(Group& group){
    QGraphicsView* profilePicture;
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/chatprototype.ui";

    QFile file(sourceDirectory);
    try{
        file.open(QFile::ReadOnly);
        if(!file.isOpen())
            throw(file.errorString());

        QWidget *myWidget = loader.load(&file, this);
        ChatPrototypeEventFilter* eventFilter = new ChatPrototypeEventFilter();
        myWidget->installEventFilter(eventFilter);
        myWidget->setFixedSize(myWidget->width(),myWidget->height());
        file.close();

        QLabel* nameLabel = myWidget->findChild<QLabel*>("nameLabel",Qt::FindChildOption::FindChildrenRecursively);
        QLabel* typeLabel = myWidget->findChild<QLabel*>("typeLabel",Qt::FindChildOption::FindChildrenRecursively);
        profilePicture = myWidget->findChild< QGraphicsView*>("profilePicture",Qt::FindChildOption::FindChildrenRecursively);
        if(nameLabel != nullptr)
            nameLabel->setText(group.getName());
        else
            return;
        if(typeLabel != nullptr)
            typeLabel->setText("group");
        else
            return;

        splitter->addWidget(myWidget);
    }catch(QString error){
        qDebug() << error;
    }

    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        QPixmap pixMap = icon->pixmap(profilePicture->width(),profilePicture->height());
        QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixMap);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addItem(pixItem);
        profilePicture->setScene(scene);

    } catch(char const* error){
        qDebug() << error ;
    }
}

void App::addMessage(Message& message){
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/message.ui";

    QFile file(sourceDirectory);
    try{
        file.open(QFile::ReadOnly);
        if(!file.isOpen())
            throw(file.errorString());

        QWidget *myWidget = loader.load(&file, this);
        myWidget->setFixedSize(myWidget->width(),myWidget->height());
        file.close();

        QLabel* nameLabel = myWidget->findChild<QLabel*>("nameLabel",Qt::FindChildOption::FindChildrenRecursively);
        QPlainTextEdit* messageText = myWidget->findChild<QPlainTextEdit*>("messageText",Qt::FindChildOption::FindChildrenRecursively);
        if((nameLabel == nullptr) || messageText == nullptr)
            throw("Widgets not found.");
        nameLabel->setText(message.getSenderName());
        messageText->setPlainText(message.getMessage());
        chatSplitter->addWidget(myWidget);
    }catch(QString error){
        qDebug() << error;
    }

}

void App::clearChatArea(){
    chatSplitter->deleteLater();
    chatSplitter = new QSplitter(Qt::Vertical);
    ui->chatScrollArea->setWidget(chatSplitter);
}

void App::clearChatPrototypes(){
    splitter->deleteLater();
    splitter = new QSplitter(Qt::Vertical);
    ui->chatPrototypeScroll->setWidget(splitter);
}

App::~App()
{
    delete chatSplitter;
    delete splitter;
    delete createjoinWidget;
    delete profileWidget;
    delete optionsWidget;
    delete ui;
}

void App::on_profileButton_clicked()
{
    if((optionsWidget != nullptr) || (createjoinWidget != nullptr))    //two menus should not be simultaneously available
        return;

    if(profileWidget == nullptr){
        ui->profileButton->setText("Close");
        QUiLoader loader;
        QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
        QFileInfo fileInfo(filePath);
        QString sourceDirectory = fileInfo.absolutePath() + "/profile.ui";

        QFile file(sourceDirectory);
        try{
            file.open(QFile::ReadOnly);
            if(!file.isOpen())
                throw(file.errorString());


            profileWidget = loader.load(&file,this);
            file.close();

            //loading profile picture
            QGraphicsView* profilePicture = profileWidget->findChild<QGraphicsView*>("profilePicture",Qt::FindChildrenRecursively);
            profilePicture->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            profilePicture->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            QLabel* channelNumber = profileWidget->findChild<QLabel*>("numberOfChannels",Qt::FindChildrenRecursively);
            channelNumber->setText(numberOfChannels);
            QLabel* groupNumber = profileWidget->findChild<QLabel*>("numberOfGroups",Qt::FindChildrenRecursively);
            groupNumber->setText(numberOfGroups);
            QLabel* username = profileWidget->findChild<QLabel*>("username",Qt::FindChildrenRecursively);
            username->setText(mainWindow->getCurrentUser().getUsername());
            QCheckBox* internetCheckBox = profileWidget->findChild<QCheckBox*>("internetCheckBox",Qt::FindChildrenRecursively);
            connect(internetCheckBox, &QCheckBox::stateChanged, [=](int state) {
                if (state == Qt::Checked)
                    on_internetCheckBox_checked();
                 else
                    on_internetCheckBox_unchecked();
            });
            QPushButton* logoutButton = profileWidget->findChild<QPushButton*>("logoutButton",Qt::FindChildrenRecursively);
            connect(logoutButton,&QRadioButton::clicked,this,&App::on_logoutButton_clicked);
            try{
                if(!profilePicture->isWidgetType())
                    throw("Error while finding widget");
                QString iconDirectory = profilePath;
                QFile temp(iconDirectory);
                if(!temp.exists())
                    throw("Icon Not Found.");
                QIcon *icon = new QIcon(iconDirectory);
                QPixmap pixMap = icon->pixmap(profilePicture->width(),profilePicture->height());
                QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixMap);
                QGraphicsScene* scene = new QGraphicsScene();
                scene->addItem(pixItem);
                profilePicture->setScene(scene);

            } catch(char const* error){
                qDebug() << error ;
            }

            //animation
            profileWidget->setGeometry(this->width(), 0, profileWidget->width(), profileWidget->height());
            profileWidget->setParent(this);
            profileWidget->setVisible(true);    //it is necessary because default is not visible
            QPropertyAnimation* animation = new QPropertyAnimation(profileWidget, "geometry");
            animation->setDuration(1000);   //duration in milliseconds
            animation->setStartValue(QRect(-profileWidget->width(), 110, 0, this->height()));
            animation->setEndValue(QRect(0, 110, profileWidget->width(), this->height()));
            animation->start();
        }catch(QString error){
            qDebug() << error;
        }
    }  else if(profileWidget != nullptr){
        ui->profileButton->setText("Profile");
        profileWidget->setGeometry(this->width(), 0, profileWidget->width(), profileWidget->height());
        profileWidget->setParent(this);
        profileWidget->setVisible(true);    //it is necessary because default is not visible
        QPropertyAnimation* animation = new QPropertyAnimation(profileWidget, "geometry");
        animation->setDuration(1000);   //duration in milliseconds
        animation->setStartValue(QRect(0, 110, profileWidget->width(), this->height()));
        animation->setEndValue(QRect(-profileWidget->width(), 110, 0, this->height()));
        animation->start();
        profileWidget = nullptr;
    }


    //set User Information here...
    // . . .

}


void App::on_optionsButton_clicked()
{
    if((createjoinWidget != nullptr) || (profileWidget != nullptr))    //two menus should not be simultaneously available
        return;

    if(optionsWidget == nullptr){
        ui->optionsButton->setText("Close");
        QUiLoader loader;
        QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
        QFileInfo fileInfo(filePath);
        QString sourceDirectory = fileInfo.absolutePath() + "/options.ui";

        QFile file(sourceDirectory);
        try{
            file.open(QFile::ReadOnly);
            if(!file.isOpen())
                throw(file.errorString());


            optionsWidget = loader.load(&file,this);
            file.close();

            //loading Logo of sprites
            QGraphicsView* logo = optionsWidget->findChild<QGraphicsView*>("logo",Qt::FindChildrenRecursively);
            QGraphicsView* profilePictureView = optionsWidget->findChild<QGraphicsView*>("profilePictureView",Qt::FindChildrenRecursively);
            QPushButton* changeProfilePictureButton = optionsWidget->findChild<QPushButton*>("changeProfilePictureButton",Qt::FindChildrenRecursively);
            connect(changeProfilePictureButton,&QPushButton::clicked,this,&App::on_changeProfilePictureButton_clicked);
            QPushButton* clearLocalFilesButton = optionsWidget->findChild<QPushButton*>("clearLocalFilesButton",Qt::FindChildrenRecursively);
            connect(clearLocalFilesButton,&QPushButton::clicked,this,&App::on_clearLocalFilesButton_clicked);
            QRadioButton* defaultThemeButton = optionsWidget->findChild<QRadioButton*>("defaultThemeButton",Qt::FindChildrenRecursively);
            connect(defaultThemeButton,&QRadioButton::clicked,this,&App::on_defaultThemeButton_clicked);
            QRadioButton* darkThemeButton = optionsWidget->findChild<QRadioButton*>("darkThemeButton",Qt::FindChildrenRecursively);
            connect(darkThemeButton,&QRadioButton::clicked,this,&App::on_darkThemeButton_clicked);
            QRadioButton* lightThemeButton = optionsWidget->findChild<QRadioButton*>("lightThemeButton",Qt::FindChildrenRecursively);
            connect(lightThemeButton,&QRadioButton::clicked,this,&App::on_lightThemeButton_clicked);
            try{
                if(!(logo->isWidgetType()) || !(profilePictureView->isWidgetType()))
                    throw("Error while finding widget");
                QString iconPath = QString::fromLocal8Bit(__FILE__);
                QFileInfo iconInfo(iconPath);
                QString iconDirectory = iconInfo.absolutePath() + "/ICons/Logo/spritesLogo.jpeg";
                QString avatarDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
                QFile iconFile(iconDirectory);
                QFile profileFile(avatarDirectory);

                if(!iconFile.exists())
                    throw("Icon Not Found.");
                QIcon *icon = new QIcon(iconDirectory);
                QPixmap pixMap = icon->pixmap(logo->width()/2,logo->height()/2);
                QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixMap);
                QGraphicsScene* scene = new QGraphicsScene();
                scene->addItem(pixItem);
                logo->setScene(scene);

                if(!profileFile.exists())
                    throw("Profile Not Found.");
                QIcon *profile = new QIcon(avatarDirectory);
                QPixmap pixMapProfile = profile->pixmap(profilePictureView->width(),profilePictureView->height());
                QGraphicsPixmapItem* pixItemProfile = new QGraphicsPixmapItem(pixMapProfile);
                QGraphicsScene* sceneProfile = new QGraphicsScene();
                sceneProfile->addItem(pixItemProfile);
                profilePictureView->setScene(sceneProfile);

            } catch(char const* error){
                qDebug() << error ;
            }


            //animation
            optionsWidget->setGeometry(this->width(), 0, optionsWidget->width(), optionsWidget->height());
            optionsWidget->setParent(this);
            optionsWidget->setVisible(true);    //it is necessary because default is not visible
            QPropertyAnimation* animation = new QPropertyAnimation(optionsWidget, "geometry");
            animation->setDuration(1000);   //duration in milliseconds
            animation->setStartValue(QRect(-optionsWidget->width(), 110, 0, this->height()));
            animation->setEndValue(QRect(0, 110, optionsWidget->width(), this->height()));
            animation->start();
        }catch(QString error){
            qDebug() << error;
        }
    }  else if(optionsWidget != nullptr){
        ui->optionsButton->setText("Options");
        optionsWidget->setGeometry(this->width(), 0, optionsWidget->width(), optionsWidget->height());
        optionsWidget->setParent(this);
        optionsWidget->setVisible(true);    //it is necessary because default is not visible
        QPropertyAnimation* animation = new QPropertyAnimation(optionsWidget, "geometry");
        animation->setDuration(1000);   //duration in milliseconds
        animation->setStartValue(QRect(0, 110, optionsWidget->width(), this->height()));
        animation->setEndValue(QRect(-optionsWidget->width(), 110, 0, this->height()));
        animation->start();
        optionsWidget = nullptr;
    }
}

void App::on_createJoinButton_clicked()
{
    if((optionsWidget != nullptr) || (profileWidget != nullptr))    //two menus should not be simultaneously available
        return;

    if(createjoinWidget == nullptr){
        ui->createJoinButton->setText("Close");
        QUiLoader loader;
        QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
        QFileInfo fileInfo(filePath);
        QString sourceDirectory = fileInfo.absolutePath() + "/createjoin.ui";

        QFile file(sourceDirectory);
        try{
            file.open(QFile::ReadOnly);
            if(!file.isOpen())
                throw(file.errorString());


            createjoinWidget = loader.load(&file,this);
            file.close();

            QPushButton* createGroupButton = createjoinWidget->findChild<QPushButton*>("createGroupButton",Qt::FindChildrenRecursively);
            connect(createGroupButton,&QPushButton::clicked,this,&App::on_createGroupButton_clicked);
            QPushButton* createChannelButton = createjoinWidget->findChild<QPushButton*>("createChannelButton",Qt::FindChildrenRecursively);
            connect(createChannelButton,&QPushButton::clicked,this,&App::on_createChannelButton_clicked);
            QPushButton* joinGroupButton = createjoinWidget->findChild<QPushButton*>("joinGroupButton",Qt::FindChildrenRecursively);
            connect(joinGroupButton,&QPushButton::clicked,this,&App::on_joinGroupButton_clicked);
            QPushButton* joinChannelButton = createjoinWidget->findChild<QPushButton*>("joinChannelButton",Qt::FindChildrenRecursively);
            connect(joinChannelButton,&QPushButton::clicked,this,&App::on_joinChannelButton_clicked);
            //animation
            createjoinWidget->setGeometry(this->width(), 0, createjoinWidget->width(), createjoinWidget->height());
            createjoinWidget->setParent(this);
            createjoinWidget->setVisible(true);    //it is necessary because default is not visible
            QPropertyAnimation* animation = new QPropertyAnimation(createjoinWidget, "geometry");
            animation->setDuration(1000);   //duration in milliseconds
            animation->setStartValue(QRect(-createjoinWidget->width(), 110, 0, this->height()));
            animation->setEndValue(QRect(0, 110, createjoinWidget->width(), this->height()));
            animation->start();
        }catch(QString error){
            qDebug() << error;
        }
    }  else if(createjoinWidget != nullptr){
        ui->createJoinButton->setText("Create / Join");
        createjoinWidget->setGeometry(this->width(), 0, createjoinWidget->width(), createjoinWidget->height());
        createjoinWidget->setParent(this);
        createjoinWidget->setVisible(true);    //it is necessary because default is not visible
        QPropertyAnimation* animation = new QPropertyAnimation(createjoinWidget, "geometry");
        animation->setDuration(1000);   //duration in milliseconds
        animation->setStartValue(QRect(0, 110, createjoinWidget->width(), this->height()));
        animation->setEndValue(QRect(-createjoinWidget->width(), 110, 0, this->height()));
        animation->start();
        createjoinWidget = nullptr;
    }
}



void App::on_sendButton_clicked()
{
    //replace it by correct current user later
    QString text = ui->messageLineEdit->text();
    pendingMessage = Message(mainWindow->getCurrentUser(),text);
    QLabel* shownNameLabel = mainWindow->getApp()->findChild<QLabel*>("shownNameLabel",Qt::FindChildrenRecursively);
    QLabel* shownTypeLabel = mainWindow->getApp()->findChild<QLabel*>("shownTypeLabel",Qt::FindChildrenRecursively);
    QString dstName = shownNameLabel->text();
    if(shownTypeLabel->text() == "user"){
        apiManager.sendMessageUser(dstName,text);
    } else if(shownTypeLabel->text() == "channel"){
        apiManager.sendMessageChannel(dstName,text);
    } else if(shownTypeLabel->text() == "group"){
        apiManager.sendMessageGroup(dstName,text);
    }
    ui->messageLineEdit->setText("");
}

//////////////////////////////////////////////////////
//slots for profile.

void App::on_internetCheckBox_checked(){
    //change connection here
}

void App::on_internetCheckBox_unchecked(){
    //change connection here
}

void App::on_logoutButton_clicked(){
    User user = mainWindow->getCurrentUser();
    apiManager.getTimer()->stop();
    apiManager.logOut(user);
    this->close();
    mainWindow->show();
}
/// //////////////////////////////////////////////////

//////////////////////////////////////////////////////
//slots for options.ui

void App::on_changeProfilePictureButton_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this,"open file",QDir::homePath(),"All Files (*.*)");
    if(!fileName.isEmpty()){
        profilePath = fileName;
        save_profile_path(profilePath);
    } else {
        qDebug() << "Invalid file path.";
    }
}

void App::on_clearLocalFilesButton_clicked(){
    apiManager.Delete_All_Files();
    QString iconPath = QString::fromLocal8Bit(__FILE__);
    QFileInfo iconInfo(iconPath);
    profilePath = iconInfo.absolutePath() + "/ICons/avatar.ico";
    QString empty = "";
    save_profile_path(empty);
}

void App::on_defaultThemeButton_clicked(){
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString chatBackgroundDirectory = iconInfo.absolutePath() + "/ICons/backgrounds/chat-background.jpg";
        QFile chatBackgroundIcon(chatBackgroundDirectory);
        if(!chatBackgroundIcon.exists())
            throw("Icon Not Found.");
        QIcon *chatBackground = new QIcon(chatBackgroundDirectory);
        QPixmap pixMapChatBackground = chatBackground->pixmap(ui->chatBackgroundView->width(),ui->chatBackgroundView->height());
        QGraphicsPixmapItem* pixItemChatBackground = new QGraphicsPixmapItem(pixMapChatBackground);
        QGraphicsScene* sceneChatBackground = new QGraphicsScene();
        sceneChatBackground->addItem(pixItemChatBackground);
        ui->chatBackgroundView->setScene(sceneChatBackground);
        ui->chatBackgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->chatBackgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } catch(const char* error) {
        qDebug() << error;
    }
}
void App::on_darkThemeButton_clicked(){
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString chatBackgroundDirectory = iconInfo.absolutePath() + "/ICons/backgrounds/dark-chat-background.jpg";
        QFile chatBackgroundIcon(chatBackgroundDirectory);
        if(!chatBackgroundIcon.exists())
            throw("Icon Not Found.");
        QIcon *chatBackground = new QIcon(chatBackgroundDirectory);
        QPixmap pixMapChatBackground = chatBackground->pixmap(ui->chatBackgroundView->width(),ui->chatBackgroundView->height());
        QGraphicsPixmapItem* pixItemChatBackground = new QGraphicsPixmapItem(pixMapChatBackground);
        QGraphicsScene* sceneChatBackground = new QGraphicsScene();
        sceneChatBackground->addItem(pixItemChatBackground);
        ui->chatBackgroundView->setScene(sceneChatBackground);
        ui->chatBackgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->chatBackgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } catch(const char* error) {
        qDebug() << error;
    }
}

void App::on_lightThemeButton_clicked(){
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString chatBackgroundDirectory = iconInfo.absolutePath() + "/ICons/backgrounds/light-chat-background.jpg";
        QFile chatBackgroundIcon(chatBackgroundDirectory);
        if(!chatBackgroundIcon.exists())
            throw("Icon Not Found.");
        QIcon *chatBackground = new QIcon(chatBackgroundDirectory);
        QPixmap pixMapChatBackground = chatBackground->pixmap(ui->chatBackgroundView->width(),ui->chatBackgroundView->height());
        QGraphicsPixmapItem* pixItemChatBackground = new QGraphicsPixmapItem(pixMapChatBackground);
        QGraphicsScene* sceneChatBackground = new QGraphicsScene();
        sceneChatBackground->addItem(pixItemChatBackground);
        ui->chatBackgroundView->setScene(sceneChatBackground);
        ui->chatBackgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->chatBackgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } catch(const char* error) {
        qDebug() << error;
    }
}
//////////////////////////////////////////////////////
//slots for createjoin.ui

void App::on_createGroupButton_clicked(){
    currentPending = GROUP;
    QLineEdit* nameLineEdit = createjoinWidget->findChild<QLineEdit*>("createGroupLineEdit",Qt::FindChildrenRecursively);
    QString name = nameLineEdit->text();
    Group group(name);
    pendingGroup = group;
    apiManager.creatGroup(name,name);
    nameLineEdit->setText("");
}

void App::on_createChannelButton_clicked(){
    currentPending = CHANNEL;
    QLineEdit* nameLineEdit = createjoinWidget->findChild<QLineEdit*>("createChannelLineEdit",Qt::FindChildrenRecursively);
    QString name = nameLineEdit->text();
    Channel channel(name);
    pendingChannel = channel;
    apiManager.creatChannel(name,name);
    nameLineEdit->setText("");
}

void App::on_joinGroupButton_clicked(){
    currentPending = GROUP;
    QLineEdit* nameLineEdit = createjoinWidget->findChild<QLineEdit*>("joinGroupLineEdit",Qt::FindChildrenRecursively);
    QString name = nameLineEdit->text();
    Group group(name);
    pendingGroup = group;
    apiManager.joinGroup(name);
    nameLineEdit->setText("");
}

void App::on_joinChannelButton_clicked(){
    currentPending = CHANNEL;
    QLineEdit* nameLineEdit = createjoinWidget->findChild<QLineEdit*>("joinChannelLineEdit",Qt::FindChildrenRecursively);
    QString name = nameLineEdit->text();
    Channel channel(name);
    pendingChannel = channel;
    apiManager.joinChannel(name);
    nameLineEdit->setText("");
}
//////////////////////////////////////////////////////
void App::save_profile_path(QString &path){
    // Open the "PROFILE" folder
    QString filename = "profile";
    QString profileFolderPath = QDir::currentPath() + "/PROFILE";
    QDir profileDir(profileFolderPath);

    if (!profileDir.exists()) {
        // Create the "PROFILE" folder if it doesn't exist
        profileDir.mkpath(".");
    }
    QString filePath = profileFolderPath + "/"+ filename+ ".txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream out(&file);
        out << path;
        file.close();
        qDebug() << "Path saved in file:" << filePath;
    }
}
QString App::load_profile_path(){
    QString profileFolderPath = QDir::currentPath() + "/PROFILE";
    QString filePath = profileFolderPath + "/profile.txt";

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();
        return content;
    } else {
        qDebug() << "Failed to open profile.txt";
        return QString();
    }
}
void App::delete_profile(){
    QString baseDirectory = QDir::currentPath(); // this will give us where we are in the project
     QString profileDirectory = baseDirectory + "/PROFILE";
     QDir(profileDirectory).removeRecursively();
     qDebug() <<"Profile has been Removed"<<"\n";

}
//////////////////////////////////////////////////////
