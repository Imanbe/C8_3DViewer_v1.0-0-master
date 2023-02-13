#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <locale.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{
    ui->widget->filepath = QFileDialog::getOpenFileName();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->read_file();
    ui->widget->normalizeModel();
    ui->textEdit->setText(QString::number(ui->widget->obj.meta_inf.faces_count));
}

