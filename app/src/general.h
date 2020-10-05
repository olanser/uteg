#ifndef GENERAL_H
#define GENERAL_H

#include <QVector>
#include <QMap>
#include <QPair>
#include "file.h"
#include "mainwindow.h"
#include <QTableWidget>

class General
{
public:
    General(QTableWidget *newTable = nullptr, QTextBrowser *newTextBrowser = nullptr);
    void setPath(const QString& path);
    void setErrorArgv(void);
    bool ifEditTable(void);
    void addNewChenge(int idFile, int idTeg, int row, const QString &newValue);
    void saveChange(void);
    void cancel(void);
    void update(void);
private:
    QVector<File> files;
    QMap<QPair<int, int>, QString> chengeFile;
    QTableWidget* table;
    QTextBrowser* notFound;
    QString paths;
    bool isEditTable = false;

};

#endif // GENERAL_H
