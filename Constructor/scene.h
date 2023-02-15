#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <stdio.h>


extern "C" {
    #include "../src/parser.h"
}

class Scene : public QOpenGLWidget
{
public:
    Scene(QWidget *parent);
    void read_file();
    QString filepath;
    data_t obj;
    void normalizeModel();
    void cleanOBJ();

private:
    float xRot, yRot, zRot;
//    data_t obj;
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
//    void initModel(data_t *obj);
    void scaleBigModel(double aspect);
public slots:
    void slot(QString filepath);
};

#endif // SCENE_H
