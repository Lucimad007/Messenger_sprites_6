#include "errordialog.h"
#include "ui_errordialog.h"
#include <QString>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QDir>

ErrorDialog::ErrorDialog(QWidget *parent, QString code, QString message) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Error code " + code);
    this->code = code;
    this->message = message;
    this->setWindowModality(Qt::ApplicationModal);    //makes other windows disabled
    loadSymbol();
    ui->messageLabel->setText(message);
}

void ErrorDialog::loadSymbol(){
    try{
        QFileInfo iconInfo(QDir::currentPath());
        QString iconDirectory;
        if(code == "404")
            iconDirectory = iconInfo.dir().path() + "/messenger1/ICons/error.png";
        if(code == "401")
            iconDirectory = iconInfo.dir().path() + "/messenger1/ICons/error2.png";
        if(code == "204")
            iconDirectory = iconInfo.dir().path() + "/messenger1/ICons/info.png";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");

        QIcon icon(iconDirectory);
        this->setWindowIcon(icon);
    } catch(char const* error){
        qDebug() << error ;
    }
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::on_okButton_clicked()
{
    this->~ErrorDialog();
}

