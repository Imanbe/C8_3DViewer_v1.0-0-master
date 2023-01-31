#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <stdio.h>

class Scene : public QOpenGLWidget
{
public:
    Scene(QWidget *parent);

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(float a);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

};

#endif // SCENE_H
