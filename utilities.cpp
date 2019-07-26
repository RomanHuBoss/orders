#include <QMessageBox>
#include "utilities.h"

void ShowStylizedErrorMessage(const QString& error) {
    QMessageBox messageBox;
    messageBox.critical(nullptr, "Ошибка", error);
    messageBox.setModal(true);
}

void ShowStylizedInfoMessage(const QString &info)
{
    QMessageBox messageBox;
    messageBox.information(nullptr, "Уведомление", info);
    messageBox.setModal(true);
}
