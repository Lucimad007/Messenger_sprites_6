#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <apimanager.h>
#include <user.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setLoginUI();
    void setRegisterUI();
    ~MainWindow();

private slots:
    void on_loginBtn_clicked();

    void on_signUpBtn_clicked();

    void on_registerBtn_clicked();

    void on_backBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
