#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <locale.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (ui->widget->obj.meta_inf.memory_check != MEMORY_NULL) {
        free(ui->widget->obj.vertex_cords);
        free(ui->widget->obj.faces_cords);
        ui->widget->obj.meta_inf.memory_check = MEMORY_NULL;
        ui->widget->obj.meta_inf.faces_count = 0;
        ui->widget->obj.meta_inf.vertex_count = 0;
    }

}


void MainWindow::on_pushButton_clicked()
{
    ui->widget->filepath = QFileDialog::getOpenFileName();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->widget->obj.meta_inf.memory_check == MEMORY_OK) {
        ui->widget->cleanOBJ();
    }
    ui->widget->read_file();
    ui->widget->normalizeModel();
    update();
//    ui->textEdit->setText(QString::number(ui->widget->obj.meta_inf.faces_count));

    qDebug() << "total faces counts" << ui->widget->obj.meta_inf.faces_count*2;
}

