#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>
#include "db.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    Db * db;
    QLabel* labelUsername;
    QLabel* labelPassword;

    QLineEdit* editUsername;
    QLineEdit* editPassword;

    QDialogButtonBox* buttons;

    void setUpGUI();

public:
    explicit LoginDialog(QWidget *parent = 0);

    void setUsername( QString& username );

    void setPassword( QString& password );


signals:
    void acceptLogin( QString& username, QString& password );
    void raiseUserLogged(User user);
public slots:
    void slotAcceptLogin();
};

#endif // LOGINDIALOG_H
