#include "login_dialog.h"
#include "db.h"
#include "utilities.h"
#include "mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{

    db = new Db();

    setUpGUI();
    setWindowTitle( tr("Распоряжения 1.0 | Авторизация") );
    setModal( true );
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowIcon(QPixmap(":/Resources/lock_icon.png"));
    resize(270, 120);
}

void LoginDialog::setUpGUI(){
    // set up the layout
    QGridLayout* formGridLayout = new QGridLayout( this );

    editUsername = new QLineEdit( this );
    editPassword = new QLineEdit( this );
    editPassword->setEchoMode( QLineEdit::Password );

    labelUsername = new QLabel( this );
    labelPassword = new QLabel( this );
    labelUsername->setText( tr( "Логин" ) );
    labelUsername->setBuddy( editUsername );
    labelPassword->setText( tr( "Пароль" ) );
    labelPassword->setBuddy( editPassword );

    buttons = new QDialogButtonBox( this );
    buttons->addButton( QDialogButtonBox::Ok );
    buttons->addButton( QDialogButtonBox::Cancel );
    buttons->button( QDialogButtonBox::Ok )->setText( tr("Войти") );
    buttons->button( QDialogButtonBox::Cancel )->setText( tr("Отмена") );

    connect( buttons->button( QDialogButtonBox::Cancel ),
             SIGNAL (clicked()),
             this,
             SLOT (close())
             );

    connect( buttons->button( QDialogButtonBox::Ok ),
             SIGNAL (clicked()),
             this,
             SLOT (slotAcceptLogin()) );

    formGridLayout->addWidget( labelUsername, 0, 0 );
    formGridLayout->addWidget( editUsername, 0, 1 );
    formGridLayout->addWidget( labelPassword, 1, 0 );
    formGridLayout->addWidget( editPassword, 1, 1 );
    formGridLayout->addWidget( buttons, 2, 0, 1, 2 );

    setLayout( formGridLayout );

}

void LoginDialog::setUsername(QString &username) {
    editUsername->setText( username );
}

void LoginDialog::setPassword(QString &password){
    editPassword->setText( password );
}

void LoginDialog::slotAcceptLogin(){
    QString username = editUsername->text();
    QString password = editPassword->text();

    if (username.isEmpty()) {
        ShowStylizedErrorMessage(tr("Поле логина не может быть пустым"));
        return;
    }
    else if (password.isEmpty()) {
        ShowStylizedErrorMessage(tr("Поле пароля не может быть пустым"));
        return;
    }

    if (!db->connect()) {
        ShowStylizedErrorMessage(tr("Не удалось соединиться с базой данных. Текст ошибки: ") + db->lastError());
        return;
    }

    if (!db->tryLogin(username, password)) {
        ShowStylizedErrorMessage(tr("Неверные логин или пароль. Попробуйте еще раз."));
        return;
    }
    else {
        close();
        new MainWindow(db);
    }
}

