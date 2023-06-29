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
#include "chatprototypeeventfilter.h"
#include "app.h"
#include "message.h"
#include "ui_app.h"

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App)
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

    //setting scroll bar of chat area always bottom by default
    QScrollBar* verticalScrollBar = ui->chatScrollArea->verticalScrollBar();
    connect(verticalScrollBar, &QScrollBar::rangeChanged, [=](int min, int max) {
        // Set the scrollbar value to the maximum
        verticalScrollBar->setValue(max);});


    //setting primary icons
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/Logo/spritesLogo.jpeg";
        QString profileDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
        QFile spritesIcon(iconDirectory);
        QFile profileIcon(profileDirectory);
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


    //testing chatprototype widget
    User testUser("No one","5973","random@gmail.com");
    Channel channel("warehouse");
    Group group("groove");
    for(int i=0;i<20;i++){
        if(i%3==0)
            addChatPrototype(testUser);
        else if(i%3 == 1)
            addChatPrototype(channel);
        else if(i%3 == 2)
            addChatPrototype(group);
    }

    //testing message widget
    User user("Ali","1234","ali@gmail.com");
    Message test(user,"This is a test");
    for(int i=0;i<20;i++)
        addMessage(test);
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

App::~App()
{
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
    User tempUser("Mohammad","12351","zone@gmail.com");
    QString text = ui->messageLineEdit->text();
    Message message(tempUser,text);
    addMessage(message);
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
    //log out the user
}
/// //////////////////////////////////////////////////

//////////////////////////////////////////////////////
//slots for options.ui

void App::on_changeProfilePictureButton_clicked(){
    //change the profle here
}

void App::on_clearLocalFilesButton_clicked(){
    //delete local files of user
}

void App::on_defaultThemeButton_clicked(){
    //change theme to default
}

void App::on_darkThemeButton_clicked(){
    //change theme to dark
}

void App::on_lightThemeButton_clicked(){
    //change thene to light
}
//////////////////////////////////////////////////////
//slots for createjoin.ui

void App::on_createGroupButton_clicked(){
    //create group here
}

void App::on_createChannelButton_clicked(){
    //create channel here
}

void App::on_joinGroupButton_clicked(){
    //join group here
}

void App::on_joinChannelButton_clicked(){
    //join channel here
}
//////////////////////////////////////////////////////
