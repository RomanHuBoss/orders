#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPixmap>
#include <QString>
#include <QMessageBox>
#include <QIcon>
#include <QMap>
#include <QVariant>

typedef QMap<QString, QVariant> RowData;
typedef QVector<RowData> Rows;

void ShowStylizedErrorMessage(const QString& error);

#endif // UTILITIES_H
