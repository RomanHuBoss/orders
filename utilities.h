#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPixmap>
#include <QString>
#include <QMessageBox>
#include <QIcon>

void ShowStylizedErrorMessage(const QString& error) {
    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка", error);
    messageBox.setWindowIcon(QIcon(QPixmap(":/Resources/error_icon.png")));
    messageBox.setFixedSize(500,200);
}

#endif // UTILITIES_H
