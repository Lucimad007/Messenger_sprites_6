#include "addcontacteventfilter.h"
#include "mainwindow.h"
#include "apimanager.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QUiLoader>
#include <QFile>
#include <QFileInfo>
extern MainWindow* mainWindow;
extern APIManager apiManager;
bool AddContactEventFilter::eventFilter(QObject* obj, QEvent* event){
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            qDebug() << "Widget clicked!";
            // Perform your action here when the widget is clicked

            //loading addcontact.ui
            QUiLoader loader;
            QFileInfo fileInfo(QDir::currentPath());
            QString sourceDirectory = fileInfo.dir().path() + "/messenger1/addcontact.ui";

            QFile file(sourceDirectory);
            try{
                file.open(QFile::ReadOnly);
                if(!file.isOpen())
                    throw(file.errorString());

                myWidget = loader.load(&file);
                myWidget->setWindowTitle("Add");
                myWidget->show();
                myWidget->setFixedSize(myWidget->width(),myWidget->height());
                file.close();

                QPushButton* findButton = myWidget->findChild<QPushButton*>("findButton",Qt::FindChildOption::FindChildrenRecursively);
                connect(findButton,&QPushButton::clicked,this,&AddContactEventFilter::on_findButton_clicked);
            }catch(QString error){
                qDebug() << error;
            }

            //setting icon for widget
            try{
                QFileInfo iconInfo(QDir::currentPath());
                QString iconDirectory = iconInfo.absolutePath() + "/messenger1/ICons/avatar.ico";
                QFile temp(iconDirectory);
                if(!temp.exists())
                    throw("Icon Not Found.");
                QIcon *icon = new QIcon(iconDirectory);
                myWidget->setWindowIcon(*icon);
            } catch(char const* error){
                qDebug() << error;
            }
            // You can also access the widget using obj, if needed
            // For example:
            // QWidget* widget = qobject_cast<QWidget*>(obj);
        }
    }

    return QObject::eventFilter(obj, event);
}

void AddContactEventFilter::on_findButton_clicked(){
    //get the name here and manipulate it
    QLineEdit* nameLineEdit = myWidget->findChild<QLineEdit*>("nameLineEdit",Qt::FindChildOption::FindChildrenRecursively);
    QString name = nameLineEdit->text();
    apiManager.getUsersChat(name);
    User user(name,"","");
    mainWindow->getApp()->setShownName(name);
    mainWindow->getApp()->setShownType("user");
    mainWindow->getApp()->clearChatArea();
    nameLineEdit->setText("");
    myWidget->close();
}
