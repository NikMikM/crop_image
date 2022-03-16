#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintscene.h"
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pix_width = 0;//Инициализируем размеры будущего изображения
    pix_height = 0;
    my_scene = nullptr;
//    ui->polymenu->setVisible(false);//******
//    ui->undomenu->setVisible(false);

    ui->polymenu->menuAction()->setVisible(false);
    ui->undomenu->menuAction()->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, "Выбрать изображение","", "Изображения (*.jpeg *.png *.bmp *.jpg)");
    if(!fileName.isEmpty()){
    QPixmap pix(fileName);
    pix_width = pix.size().width();
    pix_height =  pix.size().height();
    my_scene = new PaintScene();
    ui->graphicsView->setScene(my_scene);
    my_scene->addPixmap(pix);
    my_scene->setSceneRect(0, 0,pix_width ,pix_height);
    ui->graphicsView->fitInView(my_scene->itemsBoundingRect(),Qt::KeepAspectRatio);
   ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//SmartViewportUpdate
     ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
     my_scene->SetPixmap(pix);
//    ui->polymenu->setVisible(true);//&&&&&&&&&&&
//    ui->undomenu->setVisible(true);
    ui->polymenu->menuAction()->setVisible(true);
    ui->undomenu->menuAction()->setVisible(true);
    }
}


void MainWindow::on_EnterPoly_triggered()
{
      my_scene->CanCreatePoly(true);
}


void MainWindow::on_CreatePoly_triggered()
{
    my_scene->CanCreatePoly(false);
    my_scene->EnterChangeRegime();
}


void MainWindow::on_DeletePoly_triggered()
{
     my_scene->ClearPoly();
}


void MainWindow::on_DeleteScene_triggered()
{
    my_scene->ClearScene();
}

