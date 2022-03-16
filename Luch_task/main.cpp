#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QLatin1String>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile file(":/my_style/qss/new_style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet{QLatin1String(file.readAll())};
    a.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
