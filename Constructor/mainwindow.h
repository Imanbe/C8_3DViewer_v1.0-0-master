#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>
#include <QFileDialog>

extern "C" {
#include "../src/s21_parser.h"
#include "../src/s21_MoveObj.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cleanOBJ(data_t *obj);

private slots:

    void on_button_openfile_clicked();

    void on_button_info_clicked();

    void on_button_settings_clicked();

    void on_button_move_clicked();

    void on_moveButtonScale_clicked();

    void on_moveButtonOY_clicked();

    void on_moveButtonOX_clicked();

    void on_moveButtonOZ_clicked();

private:
    Ui::MainWindow *ui;
signals:
    void signal(QString);
};
#endif // MAINWINDOW_H
