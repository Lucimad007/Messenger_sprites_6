#include <QFile>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QDir>
#include <QLineEdit>
#include <QPushButton>
#include <QCommandLinkButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setLoginUI();
}

void MainWindow::setLoginUI(){

    ui->setupUi(this);      //this line is very important due to the fact that it prevents our code from having bug
    this->setWindowTitle("Login - Register");

    //loading new UI
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/Login.ui";

    QFile file(sourceDirectory);
    try
    {
        file.open(QFile::ReadOnly);
        if(!file.isOpen())
            throw(file.errorString());

        QWidget *myWidget = loader.load(&file, this);
        file.close();

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(myWidget);
        ui->centralwidget->setLayout(layout);
        QPushButton* loginBtn = myWidget->findChild<QPushButton*>("loginBtn");
        QPushButton* signUpBtn = myWidget->findChild<QPushButton*>("signUpBtn");
        connect(loginBtn, &QPushButton::clicked, this, &MainWindow::on_loginBtn_clicked);   //connecting manually
        connect(signUpBtn,&QCommandLinkButton::clicked,this,&MainWindow::on_signUpBtn_clicked);
    }
    catch(QString error){
        qDebug() << error;
    }

    //setting new icon
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/login.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        this->setWindowIcon(*icon);

    } catch(char const* error){
        qDebug() << error ;
    }
}

void MainWindow::setRegisterUI(){

    ui->setupUi(this);      //this line is very important due to the fact that it prevents our code from having bug
    this->setWindowTitle("Login - Register");

    //loading new UI
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/register.ui";

    QFile file(sourceDirectory);
    try{
        file.open(QFile::ReadOnly);
        if(!file.isOpen())
            throw(file.errorString());

        QWidget *myWidget = loader.load(&file, this);
        file.close();

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(myWidget);
        ui->centralwidget->setLayout(layout);
        QPushButton* registerBtn = myWidget->findChild<QPushButton*>("registerBtn");
        QPushButton* backBtn = myWidget->findChild<QPushButton*>("backBtn");
        connect(registerBtn, &QPushButton::clicked, this, &MainWindow::on_registerBtn_clicked);   //connecting manually
        connect(backBtn, &QPushButton::clicked, this, &MainWindow::on_backBtn_clicked);
    }catch(QString error){
        qDebug() << error;
    }

    //setting new icon
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = iconInfo.absolutePath() + "/ICons/register.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        this->setWindowIcon(*icon);

    } catch(char const* error){
        qDebug() << error ;
    }
}

void MainWindow::on_loginBtn_clicked()
{
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    try
    {
        usernameLineEdit = ui->centralwidget->findChild<QLineEdit*>("usernameLineEdit");
        passwordLineEdit = ui->centralwidget->findChild<QLineEdit*>("passwordLineEdit");
        if((passwordLineEdit == nullptr) || (usernameLineEdit == nullptr))
            throw("The Widget does not exist!");
        passwordLineEdit->setText("");
        usernameLineEdit->setText("");

    }
    catch(const char* error)
    {
        qDebug() << error;
    }

}

void MainWindow::on_signUpBtn_clicked()
{
    setRegisterUI();
}


void MainWindow::on_registerBtn_clicked()
{
    QLineEdit* r_usernameLineEdit;  //r_ stands for register and it helps to prevent code from conflict caused by 2 similar UIs
    QLineEdit* r_passwordLineEdit;
    QLineEdit* r_gmailLineEdit;
    try
    {
        r_usernameLineEdit = ui->centralwidget->findChild<QLineEdit*>("r_usernameLineEdit");
        r_passwordLineEdit = ui->centralwidget->findChild<QLineEdit*>("r_passwordLineEdit");
        r_gmailLineEdit = ui->centralwidget->findChild<QLineEdit*>("r_gmailLineEdit");
       if((r_passwordLineEdit == nullptr) || (r_gmailLineEdit == nullptr) || (r_usernameLineEdit == nullptr))
            throw("The Widget does not exist!");
        r_passwordLineEdit->setText("");
        r_usernameLineEdit->setText("");
        r_gmailLineEdit->setText("");
    }
    catch(const char* error){
        qDebug() << error;
    }
}

void MainWindow::on_backBtn_clicked()
{
    setLoginUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}
