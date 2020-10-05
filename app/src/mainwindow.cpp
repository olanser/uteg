#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "general.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    window = new Dialog(this);
    ui->actionChange_folder->setIcon(QIcon("build/app/resources/Open-file-icon.png"));
    ui->action_Save->setIcon(QIcon("build/app/resources/save.png"));
    ui->action_Cancel->setIcon(QIcon("build/app/resources/cancel.png"));
    ui->actionExit->setIcon(QIcon("build/app/resources/exit.png"));
    ui->actionUpdate->setIcon(QIcon("build/app/resources/update.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionChange_folder_triggered()
{
    window->show();
}

QTableWidget *MainWindow::getTable(void) {
    return ui->tableWidget;
}

QTextBrowser *MainWindow::getTextBrowser(void){
    return ui->notFound;
}

void MainWindow::setGeneralClass(General *newGeneralClass) {
    generalClass = newGeneralClass;
    window->setGeneralClass(newGeneralClass);
}


void MainWindow::on_action_Cancel_triggered()
{
    generalClass->cancel();
}

void MainWindow::on_action_Save_triggered()
{
    generalClass->saveChange();
}

void MainWindow::on_actionUpdate_triggered()
{
    generalClass->update();
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    
    QList <QTableWidgetItem *> list = ui->tableWidget->selectedItems();
    foreach (QTableWidgetItem *f, list) {
            f->setSelected(false);
    }
    QString text = item->text();
    if (generalClass->ifEditTable()) {
        int idFile = ui->tableWidget->item(item->row(), 8)->text().toInt();
        generalClass->addNewChenge(idFile, item->column(), item->row(), item->text());
        foreach (QTableWidgetItem *f, list) {
            if (item != f && f->column() != 7)
                f->setText(text);
        }
    }
    foreach (QTableWidgetItem *f, list) {
        if (!f->isSelected())
            f->setSelected(true);
    }
}
