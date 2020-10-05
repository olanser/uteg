#include "general.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    General generalClass(window.getTable(), window.getTextBrowser());
    window.setGeneralClass(&generalClass);
    window.show();
    if (argc > 2)
        generalClass.setErrorArgv();
    else if (argc == 2)
        generalClass.setPath(argv[1]);
    else
        generalClass.setPath(QDir::currentPath());
    return a.exec();
}
