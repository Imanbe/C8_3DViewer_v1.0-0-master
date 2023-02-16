#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <locale.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initModel(&(ui->widget->obj));
}

MainWindow::~MainWindow()
{
    if (ui->widget->obj.meta_inf.memory_check != MEMORY_NULL) {
        free(ui->widget->obj.vertex_cords);
        free(ui->widget->obj.faces_cords);
        ui->widget->obj.meta_inf.memory_check = MEMORY_NULL;
        ui->widget->obj.meta_inf.faces_count = 0;
        ui->widget->obj.meta_inf.vertex_count = 0;
    }
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->widget->filepath = QFileDialog::getOpenFileName(0, "Open File .obj", "/Users/", "*.obj");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->read_file();
    update();
    qDebug() << "total faces counts" << ui->widget->obj.meta_inf.faces_count;
}

