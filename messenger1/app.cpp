#include <QFileInfo>
#include <QFile>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QSplitter>
#include <QSizePolicy>
#include <QLabel>
#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);
    this->setWindowTitle("Sprites");

    splitter = new QSplitter(Qt::Vertical, this);
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(splitter);

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

      //testing add function
//    User test1("Ali","","");
//    User test2("Mohammad","","");
//    User test3("Zahra","","");
//    addChatPrototype(test1);
//    addChatPrototype(test2);
//    addChatPrototype(test3);

}

void App::addChatPrototype(User& user){
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
        if(nameLabel != nullptr)
            nameLabel->setText(user.getUsername());
        else
            return;

        splitter->addWidget(myWidget);
        ui->centralwidget->setLayout(layout);
    }catch(QString error){
        qDebug() << error;
    }
}

App::~App()
{
    delete ui;
}
