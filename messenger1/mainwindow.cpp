#include <QFile>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QDir>
#include <QLineEdit>
#include <QPushButton>
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
    this->setWindowTitle("Login - Register");

    //loading new UI
    QUiLoader loader;
    QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
    QFileInfo fileInfo(filePath);
    QString sourceDirectory = fileInfo.absolutePath() + "/Login.ui";

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
        QPushButton* myButton = myWidget->findChild<QPushButton*>("loginBtn");
        connect(myButton, &QPushButton::clicked, this, &MainWindow::on_loginBtn_clicked);   //connecting manually
    }catch(QString error){
        qDebug() << error;
    }

    //setting new icon
    try{
        QString iconPath = QString::fromLocal8Bit(__FILE__);
        QFileInfo iconInfo(iconPath);
        QString iconDirectory = fileInfo.absolutePath() + "/ICons/login.ico";
        QFile temp(iconDirectory);
        if(!temp.exists())
            throw("Icon Not Found.");
        QIcon *icon = new QIcon(iconDirectory);
        this->setWindowIcon(*icon);

    } catch(char const* error){
        qDebug() << error ;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_loginBtn_clicked()
{
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    try{
        usernameLineEdit = ui->centralwidget->findChild<QLineEdit*>(QString::fromStdString("usernameLineEdit"));
        passwordLineEdit = ui->centralwidget->findChild<QLineEdit*>(QString::fromStdString("passwordLineEdit"));
       if(passwordLineEdit == nullptr)
            throw("The Widget do not exist!");
        passwordLineEdit->setText("");
        usernameLineEdit->setText("");

    } catch(const char* error){
        qDebug() << error;
    }
}
