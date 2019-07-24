#include <QApplication>
#include "login_dialog.h"
#include "db.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginDialog login;
    login.show();



    return app.exec();
}
