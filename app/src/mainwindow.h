#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include <QTableWidget>
#include <QTextBrowser>

namespace Ui {
class MainWindow;
}
class General;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTableWidget *getTable(void);
    QTextBrowser *getTextBrowser(void);
    void setGeneralClass(General *newGeneralClass);
    void updateTable();
    void setNewDir(QString& path);

private slots:
    void on_actionExit_triggered();
    void on_actionChange_folder_triggered();
    void on_action_Cancel_triggered();
    void on_action_Save_triggered();
    void on_actionUpdate_triggered();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Dialog *window;
    General *generalClass;
};

#endif // MAINWINDOW_H
