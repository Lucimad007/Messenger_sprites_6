#include "errordialog.h"
#include "ui_errordialog.h"
#include <QString>
#include <QGraphicsPixmapItem>
#include <QFileInfo>

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
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory;
        if(code == "404")
            iconDirectory = iconInfo.absolutePath() + "/ICons/error.png";
        if(code == "401")
            iconDirectory = iconInfo.absolutePath() + "/ICons/error2.png";
        if(code == "204")
            iconDirectory = iconInfo.absolutePath() + "/ICons/info.png";
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

