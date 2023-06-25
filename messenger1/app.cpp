#include <QFileInfo>
#include <QFile>
#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);
    this->setWindowTitle("Sprites");

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

App::~App()
{
    delete ui;
}
