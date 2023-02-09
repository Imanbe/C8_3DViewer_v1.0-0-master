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

private:
    float xRot, yRot, zRot;
    data_t obj = {0};
    QPoint mPos;
    QTimer tmr;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void draw();
public slots:
    void slot(QString filepath);
};

#endif // SCENE_H
