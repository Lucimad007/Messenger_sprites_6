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
#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);
    this->setWindowTitle("Sprites");
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);     //making window not resizeable
    ui->chatPrototypeScroll->setWidgetResizable(true);
    splitter = new QSplitter(Qt::Vertical);;
    ui->chatPrototypeScroll->setWidget(splitter);


    //setting icon of the app
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/app.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        this->setWindowIcon(*icon);

    } catch(char const* error){
        qDebug() << error ;
    }

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
        myWidget->setFixedSize(myWidget->width(),myWidget->height());
        file.close();

        QLabel* nameLabel = myWidget->findChild<QLabel*>("nameLabel",Qt::FindChildOption::FindChildrenRecursively);
        profilePicture = myWidget->findChild< QGraphicsView*>("profilePicture",Qt::FindChildOption::FindChildrenRecursively);
        if(nameLabel != nullptr)
            nameLabel->setText(user.getUsername());
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

App::~App()
{
    delete ui;
}

void App::on_profileButton_clicked()
{
    if(optionsWidget != nullptr)    //two menus should not be simultaneously
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
            profileWidget->setGeometry(this->width(), 0, profileWidget->width(), profileWidget->height());
            profileWidget->setParent(this);
            profileWidget->setVisible(true);    //it is necessary because default is not visible
            QPropertyAnimation* animation = new QPropertyAnimation(profileWidget, "geometry");
            animation->setDuration(1000);   //duration in milliseconds
            animation->setStartValue(QRect(-profileWidget->width(), 80, 0, this->height()));
            animation->setEndValue(QRect(0, 80, profileWidget->width(), this->height()));
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
        animation->setStartValue(QRect(0, 80, profileWidget->width(), this->height()));
        animation->setEndValue(QRect(-profileWidget->width(), 80, 0, this->height()));
        animation->start();
        profileWidget = nullptr;
    }

}


void App::on_optionsButton_clicked()
{
    if(profileWidget != nullptr)    //two menus should not be simultaneously
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
            optionsWidget->setGeometry(this->width(), 0, optionsWidget->width(), optionsWidget->height());
            optionsWidget->setParent(this);
            optionsWidget->setVisible(true);    //it is necessary because default is not visible
            QPropertyAnimation* animation = new QPropertyAnimation(optionsWidget, "geometry");
            animation->setDuration(1000);   //duration in milliseconds
            animation->setStartValue(QRect(-optionsWidget->width(), 80, 0, this->height()));
            animation->setEndValue(QRect(0, 80, optionsWidget->width(), this->height()));
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
        animation->setStartValue(QRect(0, 80, optionsWidget->width(), this->height()));
        animation->setEndValue(QRect(-optionsWidget->width(), 80, 0, this->height()));
        animation->start();
        optionsWidget = nullptr;
    }
}

