#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <stdio.h>


extern "C" {
    #include "../src/s21_parser.h"
}

class Scene : public QOpenGLWidget
{
public:
    Scene(QWidget *parent);

    QString filepath;
    data_t obj;
    bool isFileLoad;

    void read_file(data_t *obj);
    void normalizeModel(data_t *obj);
    void cleanOBJ(data_t *obj);

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;

    double aspected_model_width;
    double aspected_model_height;


    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void draw();
    void scaleBigModel(double aspect);
public slots:
    void slot(QString filepath);
};

#endif // SCENE_H
