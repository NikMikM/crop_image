#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "paintscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

   void on_EnterPoly_triggered();

   void on_CreatePoly_triggered();

   void on_DeletePoly_triggered();

   void on_DeleteScene_triggered();

private:
    Ui::MainWindow *ui;
    PaintScene * my_scene;
    int pix_width,pix_height;
    QString fileName;
};
#endif // MAINWINDOW_H
