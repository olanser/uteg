#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "general.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    model = new QFileSystemModel;
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->setRootPath("/"));
    for (int i = 1; i < model->columnCount(); i++)
        ui->treeView->hideColumn(i);
    ui->treeView->setHeaderHidden(false);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonCancel_clicked()
{
    this->hide();
}

void Dialog::setGeneralClass(General *newGeneralClass) {
    generalClass = newGeneralClass;
}

#include <iostream>
void Dialog::on_buttonOpen_clicked()
{
    QString file_name2 = model->filePath(ui-> treeView-> selectionModel()->currentIndex());
//    std::cout << file_name2.toUtf8().data() << std::endl;

    generalClass->setPath(file_name2);
//    std::cout << "122\n" << std::endl;
//    QDir dir(file_name2);
//    QStringList filters("*.mp3");
//    dir.setNameFilters(filters);
//    QFileInfoList list = dir.entryInfoList();
//    foreach (QFileInfo finfo, list) {
//       QString name = finfo.fileName();
//       printf("%s\n", name.toUtf8().data());
//    }
    hide();
}
