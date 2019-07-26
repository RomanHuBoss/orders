#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPixmap>
#include <QString>
#include <QMessageBox>
#include <QIcon>

void ShowStylizedErrorMessage(const QString& error) {
    QMessageBox messageBox;
    messageBox.setWindowIcon(QPixmap(":/Resources/error_icon.png"));
    messageBox.setWindowTitle("Ошибка");
    messageBox.setText(error);
    messageBox.setFixedSize(500,200);
    messageBox.setModal(true);
    messageBox.exec();
}

#endif // UTILITIES_H
