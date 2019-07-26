#include <QMessageBox>
#include "utilities.h"

void ShowStylizedErrorMessage(const QString& error) {
    QMessageBox messageBox;
    messageBox.setWindowIcon(QPixmap(":/Resources/error_icon.png"));
    messageBox.setWindowTitle("Ошибка");
    messageBox.setText(error);
    messageBox.setFixedSize(500,200);
    messageBox.setModal(true);
    messageBox.exec();
}
