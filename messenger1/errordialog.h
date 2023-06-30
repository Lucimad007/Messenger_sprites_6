#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = nullptr, QString code = "", QString message = "");
    void loadSymbol();
    ~ErrorDialog();

private slots:
    void on_okButton_clicked();

private:
    Ui::ErrorDialog *ui;
    QString code;
    QString message;
};

#endif // ERRORDIALOG_H
