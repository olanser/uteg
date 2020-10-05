#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QtGui>
#include <QTreeView>

namespace Ui {
class Dialog;
}

class MainWindow;
class General;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setGeneralClass(General *newGeneralClass);
    ~Dialog();

private slots:
    void on_buttonOpen_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::Dialog *ui;
    QFileSystemModel *model;
    General *generalClass;
};

#endif // DIALOG_H
