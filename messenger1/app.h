#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include "user.h"
#include "channel.h"
#include "group.h"
#include "message.h"

enum CurrentPending {GROUP, CHANNEL};       //for joining/creating channel/group

namespace Ui {
class App;
}

class App : public QMainWindow
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);
    Group getPendingGroup();
    Channel getPendingChannel();
    CurrentPending getCurrentPending();
    Message getPendingMessage();
    void addChatPrototype(User& user);
    void addChatPrototype(Channel& channel);
    void addChatPrototype(Group& group);
    void addMessage(Message& message);
    void clearChatArea();
    ~App();

private slots:
    void on_profileButton_clicked();

    void on_optionsButton_clicked();

    void on_sendButton_clicked();

    void on_changeProfilePictureButton_clicked();

    void on_clearLocalFilesButton_clicked();

    void on_defaultThemeButton_clicked();

    void on_darkThemeButton_clicked();

    void on_lightThemeButton_clicked();

    void on_internetCheckBox_checked();

    void on_internetCheckBox_unchecked();

    void on_logoutButton_clicked();

    void on_createJoinButton_clicked();

    void on_createGroupButton_clicked();

    void on_createChannelButton_clicked();

    void on_joinGroupButton_clicked();

    void on_joinChannelButton_clicked();

private:
    Ui::App *ui;
    QSplitter* splitter;
    QSplitter* chatSplitter;
    QWidget* profileWidget = nullptr;   //initializing it as nullptr prevents app from unexpected crashes
    QWidget* optionsWidget = nullptr;   //initializing it as nullptr prevents app from unexpected crashes
    QWidget* createjoinWidget = nullptr;//initializing it as nullptr prevents app from unexpected crashes
    CurrentPending currentPending;   //for joining/creating channel/group
    Group pendingGroup;
    Channel pendingChannel;
    Message pendingMessage;
};

#endif // APP_H
