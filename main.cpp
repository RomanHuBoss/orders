#include <QApplication>
#include "login_dialog.h"
#include "db.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont font;
    font.setFamily(font.defaultFamily());
    app.setFont(font);

    LoginDialog login;
    login.show();



    return app.exec();
}
