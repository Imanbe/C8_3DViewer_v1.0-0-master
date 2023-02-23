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
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    if (ui->widget->obj.meta_inf.memory_check != MEMORY_NULL) {
        ui->widget->cleanOBJ(&ui->widget->obj);
    }
    delete ui;
}

/**********************************************************************/
/*                                                                    */
/*                     File loading buttons                           */
/*                                                                    */
/**********************************************************************/

void MainWindow::on_button_openfile_clicked()
{
    ui->widget->filepath = QFileDialog::getOpenFileName(0, "Open File .obj", "/Users/", "*.obj");
    if (ui->widget->filepath != "") {
        ui->widget->read_file(&ui->widget->obj);
        ui->widget->update();

        if (ui->widget->obj.meta_inf.memory_check == MEMORY_OK) {
            ui->infopole_location->setText(ui->widget->filepath);
            ui->infopole_name->setText(ui->widget->filepath.right(ui->widget->filepath.size()-ui->widget->filepath.lastIndexOf("/")-1));
            ui->infopole_vertexes->setText(QString::number(ui->widget->obj.meta_inf.vertex_count, 10));
            ui->infopole_poligons->setText(QString::number(ui->widget->obj.meta_inf.poligons_count, 10));
            ui->widget->isFileLoad = true;
        } else {
            ui->widget->isFileLoad = false;
        }

        qDebug() << "total faces counts" << ui->widget->obj.meta_inf.faces_count;
    }
}

/**********************************************************************/
/*                                                                    */
/*                             Menu Buttons                           */
/*                                                                    */
/**********************************************************************/

void MainWindow::on_button_info_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_button_settings_clicked()
{
    if (ui->widget->isFileLoad) {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::on_button_move_clicked()
{
    if (ui->widget->isFileLoad) {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

/**********************************************************************/
/*                                                                    */
/*                             Move Buttons                           */
/*                                                                    */
/**********************************************************************/

void MainWindow::on_moveButtonScale_clicked()
{
    s21_scale(&ui->widget->obj, ui->line_scale->text().toDouble());
    ui->widget->update();
}


void MainWindow::on_moveButtonOY_clicked()
{
    s21_moveOX(&ui->widget->obj, ui->line_OX->text().toDouble());
    ui->widget->update();
}


void MainWindow::on_moveButtonOX_clicked()
{
    s21_moveOY(&ui->widget->obj, ui->line_OY->text().toDouble());
    ui->widget->update();
}


void MainWindow::on_moveButtonOZ_clicked()
{
    s21_moveOZ(&ui->widget->obj, ui->line_OZ->text().toDouble());
    ui->widget->update();
}
/**********************************************************************/
/*                                                                    */
/*                           Help Functions                           */
/*                                                                    */
/**********************************************************************/

void MainWindow::cleanOBJ(data_t *obj)
{
    free(obj->faces_cords);
    free(obj->vertex_cords);
    obj->meta_inf.poligons_count = 0;
    obj->meta_inf.faces_count = 0;
    obj->meta_inf.vertex_count = 0;
    obj->meta_inf.memory_check = MEMORY_NULL;
}
