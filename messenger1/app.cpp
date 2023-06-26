#include <QFileInfo>
#include <QFile>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QSplitter>
#include <QSizePolicy>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);
    this->setWindowTitle("Sprites");
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
